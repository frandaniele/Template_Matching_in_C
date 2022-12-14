#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>      
#include <string.h>
#include <limits.h>
#include <omp.h>

int naive(const char *p) {
    int x = 0;
    
    while (*p >= '0' && *p <= '9') {
        x = (x*10) + (*p - '0');
        ++p;
    }

    return x;
}

void error(char *msj){
    perror(msj);
    exit(EXIT_FAILURE);
}

int **read_image_pixels(char * img_path, int *height, int *width){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if ((fp = fopen(img_path, "r")) == NULL) error("fopen");

    if((read = getline(&line, &len, fp)) < 0) error("Read");
    char *ptr = strtok(line, " ");
    size_t ydim = (size_t) atoi(ptr);
    *height = (int)ydim;
    ptr = strtok(NULL, " ");
    size_t xdim = (size_t) atoi(ptr);
    *width = (int)xdim;

    int **array = (int **) malloc(ydim * sizeof(int *));
    for(int i = 0; i < (int)ydim; i++)
        array[i] = (int *) malloc(xdim * sizeof(int));

    for(int i = 0; i < *height; i++){
        if((read = getline(&line, &len, fp)) == -1) i = *height;
        int j = 0;
        char* token = strtok(line, " ");
        while(token){
            array[i][j] = naive(token);
            j++;
            token = strtok(NULL, " ");
        }
    }

    fclose(fp);
    if(line) free(line);

    return array;
}

void template_matching(int **image, int **template, int height_width_image[], int height_width_template[]){
    //int window[height_width_template[0]][height_width_template[1]];

    int min_distance = INT_MAX;
    int x_min, y_min;
    
    int height_template = height_width_template[0]; 
    int width_template = height_width_template[1]; 
    int rows = height_width_image[0] - height_template; 
    int columns = height_width_image[1] - width_template; 

    for(int i = 0; i <= rows; i++){
        for(int j = 0; j <= columns; j++){
            int sum_total = 0; // para la distancia total
            for(int k = 0; k < height_template; k++){//arranco cuadradito
                int sum_filas = 0;  //para las distancias punto a punto
               // int x = k + i;
                int *image_row = image[k + i];
                int *template_row = template[k];
                for(int l = 0; l < width_template; l++){//arranco fila de cuadradito
                   // window[k][l] = image[x][l + j];
                    int tmp = template_row[l] - image_row[l + j];
                    sum_filas += tmp*tmp;
                }
                if((sum_total += sum_filas) >= min_distance) break;
            }
            if(sum_total < min_distance){
                min_distance = sum_total;
                x_min = j;
                y_min = i;
            }
        }
    }
    
    printf("Valor del minimo encontrado: %i, con la", min_distance);
    printf(" esquina superior izquierda en (%i, %i) y de", x_min, y_min);
    printf(" dimension %ix%i.\n", width_template, height_template);
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

    double proc_time;

    proc_time = omp_get_wtime();
    template_matching(arr_full, arr_test, size_full, size_test);
    proc_time = omp_get_wtime() - proc_time;

    printf("\nTiempo de ejecuci??n: %f\n", proc_time);

    for(int j = 0; j < size_full[0]; j++)
        free(arr_full[j]);
    free(arr_full);

    for(int j = 0; j < size_test[0]; j++)
        free(arr_test[j]);
    free(arr_test);

    return 0;
}