#include "../headers/utils.h"

void error(char *msj){
    perror(msj);
    exit(EXIT_FAILURE);
}

void get_pixels(char * img_path){
    char *const args[] = {"src/img_to_dots.py", NULL};

    pid_t pid = fork();
        switch(pid){
            case -1:
                perror("Fork");
                exit(EXIT_FAILURE);
            case 0:
                execvp(args[0], args);

                perror("execvp");
                exit(EXIT_FAILURE);
            default:
                printf("Se obtuvieron los pixeles de la imagen %s\n", img_path);
        }
}