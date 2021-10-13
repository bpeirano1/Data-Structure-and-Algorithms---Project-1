#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../imagelib/image.h"
#include "pixel.h"
#include "utils.h"
#include "componentTree.h"


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

    // Contadores globales
    Pixel** pixels_list = calloc(image->pixel_count,sizeof(Pixel*));
    int* counter_node_id = calloc(1, sizeof(int));
    Array* int_pixel_origin_list = array_init(image->pixel_count);


    /* ------------- POR IMPLEMENTAR -------------- */
    /* Aqui debes crear el ComponentTree de la imagen.    */
    // for (int i=0 ; i < image->pixel_count;i++){
    //     printf("%i,",image->pixels[i]);
    // };
    // printf("\n");
    // printf("width: %i\n",image->width);
    // printf("height: %i\n",image->height);
    

    // Creo una lista de estructura pixeles
    for (int i=0 ; i < image->pixel_count;i++){
        Pixel* px = pixel_init(i,image->pixels[i]);
        pixels_list[i] = px;
        array_append(int_pixel_origin_list,i);
        // pixel_print(px);
    };

    // Unimos los pixeles
    for (int i=0 ; i < image->pixel_count;i++){
        Pixel* current = pixels_list[i];
        int col = i%image -> width;
        int row = i/image -> width;
        // printf("Pixel %i: col %i y row %i\n",current->id,col,row);
        if (col == 0)
        {
            current->left = NULL;
            current->right = pixels_list[i+1];
        };
        if (col == image->width-1)
        {
            current->left = pixels_list[i-1];
            current->right = NULL;
        };
        if (col != 0 && col != image->width-1)
        {
            current->left = pixels_list[i-1];
            current->right = pixels_list[i+1];
        };
        if (row == 0)
        {
            current->up = NULL;
            current->down = pixels_list[i + image->width];
        };
        if (row == image->height-1)
        {
            current->up =  pixels_list[i - image->width];
            current->down = NULL;
        };
        if (row!=0 && row != image->height-1)
        {
            current->up =  pixels_list[i - image->width];
            current->down = pixels_list[i + image->width];
        };   
    };

    Array* umbrales_array = counter_umbral(image->pixels,image->pixel_count);
    // printf("contador umbrales: %i\n", umbrales_array->length);
    // for (int i=0 ; i < umbrales_array->length;i++){
    //     printf("Umbral %i\n",umbrales_array->array[i]);
    // };

    NodeTree * root = node_tree_init(counter_node_id[0],umbrales_array->array[0],int_pixel_origin_list);
    counter_node_id[0] +=1 ;
    // printf("int_pixel_origin: %i\n", int_pixel_origin_list->length);
    // node_tree_printf(root);

    int umbral_counter = 1;
    recursion(root,umbral_counter,umbrales_array,pixels_list,counter_node_id);

    // printf("cantidad de nodos: %i\n", counter_node_id[0]);

    // node_recursive_printerf(root);

    // printf("cantidad de nodos: %i\n", counter_node_id[0]);




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

     int value = node_cost(root,alpha,marker->pixels,new_img,pixels_list);

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

    // Liberamos contadores

    for (int i=0 ; i < image->pixel_count;i++){
        free(pixels_list[i]);
    };
    free(pixels_list);
    array_destroy(umbrales_array);
    free(counter_node_id);
    array_destroy(int_pixel_origin_list);

    // Terminamos exitosamente
    return 0;
}