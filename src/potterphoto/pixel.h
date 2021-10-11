#pragma once

// Declaramos el struct para un nodo de la lista
struct pixel;
// Definimos un alias para el struct nodo.
// La sintaxis es "typedef tipo alias"
typedef struct pixel Pixel;

// Definimos el struct nodo
struct pixel
{
  /** El valor que guarda el nodo */
  int id;
  int value;
  /** Un puntero al siguiente nodo de la lista */
  Pixel* up;
  Pixel* down;
  Pixel* right;
  Pixel* left;
  
};

Pixel* pixel_init(int id, int value);
void pixel_print(Pixel* pixel);
void pixel_destroy(Pixel* pixel);