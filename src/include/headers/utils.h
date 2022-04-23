#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>      
#include <string.h>

void error(char * msj);

int **read_image_pixels(char * img_path, int *size_x, int *size_y);