#include "include/headers/utils.h"
#include <string.h>

int main(void){

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("./test.txt", "r");
    if (fp == NULL)
        error("fopen");

    int i = 0, j = 0;
    int arr[100][100];
    while ((read = getline(&line, &len, fp)) != -1) {
        char *ptr = strtok(line, " ");
        while(ptr != NULL){
            arr[i][j] = atoi(ptr);
            printf("%i ", arr[i][j]);
            j++;
            ptr = strtok(NULL, " ");
        }
        i++;
       
        printf("----------------------------");
        printf("\n");
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);

    return 0;
}