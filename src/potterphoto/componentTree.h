#include "array.h"
#include "pixel.h"
#include "../imagelib/image.h"
#pragma once

// Declaramos el struct para un nodo de la lista
struct node_tree;
// Definimos un alias para el struct nodo.
// La sintaxis es "typedef tipo alias"
typedef struct node_tree NodeTree;

// Definimos el struct nodo
struct node_tree
{
    int id;
    NodeTree* parent;
    int umbral;
    Array* neighborhood;
    int n_children;
    NodeTree* head;
    NodeTree* tail;
    NodeTree* next;
    float cost;
    int cost_ready;

    };
NodeTree* node_tree_init( int id, int umbral, Array* neighborhood);
void node_tree_append_children(NodeTree* parent, NodeTree* children);
void node_tree_adjust(NodeTree* node, Pixel** pixels_list);
void node_tree_printf(NodeTree* node);
void node_recursive_printerf(NodeTree* node);
int node_cost(NodeTree* node, float alpha, int* marker, Image* image, Pixel** pixels_list);
int ps(NodeTree* node, int* marker,Pixel** pixels_list);
void node_pixel_append_new_image(NodeTree* node, Image* image, Pixel** pixels_list);
