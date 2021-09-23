#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../imagelib/image.h"

void invert(Image* image){
    int aux[128]; 
    for (int i = 0; i < 128; i++){
        aux[i] = 127 - i;
    }
    for (int i = 0; i < image->pixel_count; i++){
        image->pixels[i] = aux[image->pixels[i]];
    }
}

int main(int argc, char** argv)
{
    // Revisamos los argumentos
    if(argc < 5) {
        printf("Modo de uso: %s <input.png> <output.png> <command> [args]\n", argv[0]);
        return 1;
    }

    // Cargamos la imagen original desde el archivo
    Image* image = img_png_read_from_file(argv[1]);
    Image* marker = img_png_read_from_file(argv[3]);

    /* ------------- Parametro R opcional, invierte la imagen -------------- */
    if (argc > 5){
        invert(image);
    }

    /* ------------- POR IMPLEMENTAR -------------- */
    /* Aqui debes crear el ComponentTree de la imagen.    */


    // Creamos una nueva imagen de igual tamaño, para el output
    Image* new_img = calloc(1, sizeof(Image));
    *new_img = (Image) {
        .height = image->height,
        .width = image->width,
        .pixel_count = image->pixel_count,
        .pixels = calloc(image->pixel_count, sizeof(int))
    };

    /* ------- Leemos el filtro alpha  --------      */  
   float alpha = atof(argv[4]); 

    /* ------------- POR IMPLEMENTAR -------------- */
    /* Aqui debes implementar el filtro Alpha y     */
    /* guardar la imagen filtrada en new_img.       */

    /* Se vuelve a invertir la imagen para dejarla como la original  */
    if (argc > 5){
        invert(new_img);
    }    

    // Exportamos la nueva imagen
    printf("Guardando imagen en %s\n", argv[2]);
    img_png_write_to_file(new_img, argv[2]);
    printf("Listo!\n");

    // Liberamos los recursos
    img_png_destroy(image);
    img_png_destroy(new_img);
    img_png_destroy(marker);

    // Terminamos exitosamente
    return 0;
}