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