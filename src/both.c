#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>      
#include <string.h>
#include <limits.h>
#include <omp.h>

void error(char *msj){
    perror(msj);
    exit(EXIT_FAILURE);
}

int **read_image_pixels(char * img_path, int *height, int *width){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if ((fp = fopen(img_path, "r")) == NULL)
        error("fopen");

    getline(&line, &len, fp);
    char *ptr = strtok(line, " ");
    size_t ydim = (size_t) atoi(ptr);
    *height = (int)ydim;
    ptr = strtok(NULL, " ");
    size_t xdim = (size_t) atoi(ptr);
    *width = (int)xdim;

    int i = 0, j = 0;
    int **array = (int **) malloc(ydim * sizeof(int *));
    for(i = 0; i < (int)ydim; i++)
        array[i] = (int *) malloc(xdim * sizeof(int));

    i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        ptr = strtok(line, " ");
        while(ptr != NULL){
            array[i][j] = atoi(ptr);
            j++;
            ptr = strtok(NULL, " ");
        }
        i++;
        j = 0;
    }

    fclose(fp);
    if(line) free(line);

    return array;
}

void template_matching(int **image, int **template, int height_width_image[], int height_width_template[]){
    int window[height_width_template[0]][height_width_template[1]];

    int min_distance = INT_MAX;
    int x_min, y_min;
    
    for(int i = 0; i <= height_width_image[0] - height_width_template[0]; i++){
        for(int j = 0; j <= height_width_image[1] - height_width_template[1]; j++){
            int sum_total = 0; // para la distancia total
            for(int k = 0; k < height_width_template[0]; k++){//arranco cuadradito
                int sum_filas = 0;  //para las distancias punto a punto
                int x = k + i;
                for(int l = 0; l < height_width_template[1]; l++){//arranco fila de cuadradito
                    window[k][l] = image[x][l + j];
                    int tmp = template[k][l] - window[k][l];
                    sum_filas += tmp*tmp;
                }
                sum_total += sum_filas;
            }
            if(sum_total < min_distance){
                min_distance = sum_total;
                x_min = j;
                y_min = i;
            }
        }
    }

    printf("x: %i y: %i min: %i\n", x_min, y_min, min_distance);
}

void template_matching_parallel(int **image, int **template, int height_width_image[], int height_width_template[]){
    int window[height_width_template[0]][height_width_template[1]];

    int min_distance = INT_MAX;
    int x_min, y_min;
    
    #pragma omp parallel num_threads(8) 
    for(int i = 0; i <= height_width_image[0] - height_width_template[0]; i++){
        #pragma omp for nowait schedule(static, 64)
        for(int j = 0; j <= height_width_image[1] - height_width_template[1]; j++){
            int sum_total = 0; // para la distancia total
            for(int k = 0; k < height_width_template[0]; k++){//arranco cuadradito
                int sum_filas = 0;  //para las distancias punto a punto
                int x = k + i;
                for(int l = 0; l < height_width_template[1]; l++){//arranco fila de cuadradito
                    window[k][l] = image[x][l + j];
                    int tmp = template[k][l] - window[k][l];
                    sum_filas += tmp*tmp;
                }
                sum_total += sum_filas;
            }
            #pragma omp critical
            {
                if(sum_total < min_distance){
                    min_distance = sum_total;
                    x_min = j;
                    y_min = i;
                }
            }
        }
    }

    printf("x: %i y: %i min: %i\n", x_min, y_min, min_distance);
}

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Uso: %s <full img pixels path> <pattern img pixels path> \n", argv[0]);
		exit(EXIT_SUCCESS);
    }

    int size_full[2]; // 0 -> height , 1 -> width
    int size_test[2];

    int **arr_full = read_image_pixels(argv[1], &size_full[0], &size_full[1]);
    int **arr_test = read_image_pixels(argv[2], &size_test[0], &size_test[1]);

    double proc_time, parallel_time;
    //double parallel_time;

    proc_time = omp_get_wtime();
    template_matching(arr_full, arr_test, size_full, size_test);
    proc_time = omp_get_wtime() - proc_time;

    printf("procedural time: %f\n", proc_time);

    parallel_time = omp_get_wtime();
    template_matching_parallel(arr_full, arr_test, size_full, size_test);
    parallel_time = omp_get_wtime() - parallel_time;

    printf("parallel time: %f\n", parallel_time);

    printf("Speedup: %f\n", proc_time/parallel_time);

    for(int j = 0; j < size_full[0]; j++)
        free(arr_full[j]);
    free(arr_full);

    for(int j = 0; j < size_test[0]; j++)
        free(arr_test[j]);
    free(arr_test);

    return 0;
}