#include "include/headers/utils.h"
#include <limits.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Uso: %s <full img pixels path> <pattern img pixels path> \n", argv[0]);
		exit(EXIT_SUCCESS);
    }

    int size_full[2];
    int size_test[2];

    int **arr_full = read_image_pixels(argv[1], &size_full[0], &size_full[1]);
    int **arr_test = read_image_pixels(argv[2], &size_test[0], &size_test[1]);

    int window[size_test[0]][size_test[1]];
    //int centro[2] = {size_test[0]/2, size_test[1]/2};

    int sum_filas[size_test[0]]; //para las distancias punto a punto
    int sum_total = 0; // para la distancia total
    int min_distance = INT_MAX;
    int x_min, y_min;
    
    for(int i = 0; i <= size_full[0] - size_test[0]; i++){
        for(int j = 0; j <= size_full[1] - size_test[1]; j++){
            sum_total = 0;
            for(int k = 0; k < size_test[0]; k++){//arranco cuadradito
                sum_filas[k] = 0;
                int x = k + i;
                for(int l = 0; l < size_test[1]; l++){//arranco fila de cuadradito
                    window[k][l] = arr_full[x][l + j];
                    int tmp = arr_test[k][l] - window[k][l];
                    sum_filas[k] += tmp*tmp;
                }
                sum_total += sum_filas[k];
            }
            if(sum_total < min_distance){
                min_distance = sum_total;
                x_min = j;
                y_min = i;
            }
        }
    }

    printf("x: %i y: %i min: %i\n", x_min, y_min, min_distance);

    for(int j = 0; j < size_full[0]; j++)
        free(arr_full[j]);
    free(arr_full);

    for(int j = 0; j < size_test[0]; j++)
        free(arr_test[j]);
    free(arr_test);

    return 0;
}