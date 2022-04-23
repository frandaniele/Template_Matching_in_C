#include "../headers/utils.h"

void error(char *msj){
    perror(msj);
    exit(EXIT_FAILURE);
}

int **read_image_pixels(char * img_path, int *size_x, int *size_y){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if ((fp = fopen(img_path, "r")) == NULL)
        error("fopen");

    getline(&line, &len, fp);
    char *ptr = strtok(line, " ");
    size_t xdim = (size_t) atoi(ptr);
    *size_x = (int)xdim;
    ptr = strtok(NULL, " ");
    size_t ydim = (size_t) atoi(ptr);
    *size_y = (int)ydim;

    int i = 0, j = 0;
    int **array = (int **) malloc(xdim * sizeof(int *));
    for(i = 0; i < (int)xdim; i++)
        array[i] = (int *) malloc(ydim * sizeof(int));

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