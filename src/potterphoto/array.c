#include "array.h"
#include <stdlib.h>
#include <stdio.h>

Array* array_init(int size)
{
  Array* array_instance = calloc(1,sizeof(Array));
  array_instance -> length = 0;
  array_instance -> size = size;
  
  int* list = calloc(size, sizeof(int));
  array_instance -> array = list;

  return array_instance;
}

void array_append(Array* array, int value){
    if (array->length < array->size)
    {
        array->array[array->length] = value;
        array->length += 1;
    }else{
        printf("No se puede agregar %i porque Arreglo Lleno\n",value);
    };
    
};

void array_destroy(Array* array){
    free(array -> array);
    free(array);
};

int array_in(Array* array, int value){
    for (int i = 0; i < array -> length; i++)
    {
        if (array->array[i]==value)
        {
            return 1;
        }
        
    }
    return 0;
    
}
void array_sort(Array* array){
    // Me base en el siguiente código para ordenar
    // https://www.javatpoint.com/c-program-to-sort-the-elements-of-an-array-in-ascending-order
    for (int i = 0; i < array->length; i++) {     
        for (int j = i+1; j < array->length; j++) {     
           if(array->array[i] > array->array[j]) {    
               int temp = array->array[i];    
               array->array[i] = array->array[j];    
               array->array[j] = temp;    
           }     
        }     
    }    
};
void array_printf(Array* array){
    printf("Vecindario: ");
    for (int i = 0; i < array->length; i++)
    {
        printf("%i,", array->array[i]);
    };
    printf("\n");
    
};