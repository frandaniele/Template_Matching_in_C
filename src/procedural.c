#include "include/headers/utils.h"

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Uso: %s <full img pixels path> <pattern img pixels path> \n", argv[0]);
		exit(EXIT_SUCCESS);
    }

    int size_full[2];
    int size_test[2];

    int **arr_full = read_image_pixels(argv[1], &size_full[0], &size_full[1]);
    int **arr_test = read_image_pixels(argv[2], &size_test[0], &size_test[1]);

    printf("%i\n",arr_full[0][0]);

    printf("%i\n",arr_test[0][0]);

    int window[size_test[0]][size_test[1]];

    printf("%li\n",sizeof(window));

    for(int j = 0; j < size_full[0]; j++)
        free(arr_full[j]);
    free(arr_full);

    for(int j = 0; j < size_test[0]; j++)
        free(arr_test[j]);
    free(arr_test);

    return 0;
}