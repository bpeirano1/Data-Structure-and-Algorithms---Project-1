#pragma once

// Declaramos el struct para un nodo de la lista
struct array;
// Definimos un alias para el struct nodo.
// La sintaxis es "typedef tipo alias"
typedef struct array Array;

// Definimos el struct nodo
struct array
{
  /** El valor que guarda el nodo */
  int length;
  int size;
  /** Un puntero al siguiente nodo de la lista */
  int* array;
};

Array* array_init(int size);
void array_append(Array* array, int value);
void array_destroy(Array* array);
int array_in(Array* array, int value);