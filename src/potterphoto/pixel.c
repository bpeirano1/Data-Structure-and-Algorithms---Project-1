#include "pixel.h"
#include <stdlib.h>
#include <stdio.h>

Pixel* pixel_init(int id, int value){
    Pixel* pixel = calloc(1,sizeof(Pixel));
    pixel -> id = id;
    pixel -> value = value;
    pixel-> up = NULL;
    pixel-> down = NULL;
    pixel-> right = NULL;
    pixel-> left = NULL;

    return pixel;
};

void pixel_print(Pixel* pixel){
    printf("Pixel %i: %i\n",pixel->id,pixel->value);
};
void pixel_destroy(Pixel* pixel){
    free(pixel);
};