#include "componentTree.h"
#include <stdlib.h>
#include <stdio.h>

NodeTree* node_tree_init( int id, int umbral, Array* neighborhood){
    NodeTree* node = calloc(1,sizeof(NodeTree));
    node -> id = id;
    node -> parent = NULL;
    node -> umbral = umbral;
    node -> neighborhood = neighborhood;
    node -> n_children = 0;
    node -> head = NULL;
    node -> tail = NULL;
    node -> next = NULL;
    node -> cost = -1;
    node -> cost_ready = 0;


    return node;
};
void node_tree_append_children(NodeTree* parent, NodeTree* children){

    if(parent -> head == NULL)
  {
    parent -> head = children;
  }
  // Sino, se pone como el siguiente del ultimo
  else
  {
    parent -> tail -> next = children;
  }
  // Luego se deja a este nodo como el último
  parent -> tail = children;
  parent -> n_children += 1;
};
void node_tree_adjust(NodeTree* node, Pixel** pixels_list){
    int min_value = 128;
    for (int i = 0; i < node->neighborhood->length; i++)
    {
        if (pixels_list[node->neighborhood->array[i]]->value < min_value)
        {
            min_value = pixels_list[node->neighborhood->array[i]]->value;
        };   
    }
    if (node->umbral < min_value)
    {
        node -> umbral = min_value;
    };
    
    
};
void node_tree_printf(NodeTree* node){
    printf("-----------------------------------------------------\n");
    printf("Nodo %i\n",node->id);
    if(node->parent){
        printf("Nodo Padre %i\n",node->parent->id);
    }else{
        printf("Nodo Padre Null\n");}

    printf("Umbral: %i \n",node->umbral);
   
    array_printf(node->neighborhood);
    printf("Hijes: (%i)\n", node->n_children);
    for (int i = 0; i < node->n_children; i++)
    {
        NodeTree* current = node->head;
        int counter = 0;
        while(counter<i){
           
            current = current->next;
            
            counter +=1;
        };
        
        printf("Nodo %i\n", current->id);
    }
    
    printf("-----------------------------------------------------\n");
};
void node_recursive_printerf(NodeTree* node){
    node_tree_printf(node);
    NodeTree* current = node->head;
    while(current){
        node_recursive_printerf(current);
        current = current -> next;
    };

};

int node_cost(NodeTree* node, float alpha, int* marker, Image* image, Pixel** pixels_list){
    if (!node ->cost_ready && !node->n_children)
    {
        int var_ps = ps(node,marker,pixels_list);
        int var_n = node->neighborhood->length-var_ps;
     if(alpha*var_n<(1-alpha)*var_ps){
         float var_cost = alpha*var_n;
         node->cost = var_cost;
         node->cost_ready=1;
         if (node->id!=0)
         {
             node_pixel_append_new_image(node,image,pixels_list);
         }
         return node->cost;
     }else{
         float var_cost = (1-alpha)*var_ps;
         node->cost =var_cost;
         node->cost_ready=1;
         return node -> cost;
     };
    }else if (node->cost_ready)
    {
        return node->cost;
    } 
    else
    {
        int var_ps = ps(node,marker,pixels_list);
        int var_n = node->neighborhood->length-var_ps;
        float temporal_cost = 0;
        NodeTree* current = node->head;
        while(current){
            temporal_cost += node_cost(current,alpha,marker,image,pixels_list);
            current = current -> next;
        };
        if(alpha*var_n<((1-alpha)*var_ps + temporal_cost)){
         float var_cost = alpha*var_n;
         node->cost = var_cost;
         node->cost_ready=1;
         if (node->id!=0)
         {
             node_pixel_append_new_image(node,image,pixels_list);
         }
         return node->cost;
        }else 
        {
        float var_cost = ((1-alpha)*var_ps + temporal_cost);
        node->cost = var_cost;
        node->cost_ready = 1;
        return node->cost;
        };
    };
};

int ps(NodeTree* node, int* marker,Pixel** pixels_list){
    int counter = 0;
    for (int i = 0; i < node->neighborhood->length; i++)
    {
        if (pixels_list[node->neighborhood->array[i]]->value == node->umbral && marker[node->neighborhood->array[i]]>0)
        {
            counter += 1;
        };
        
    }
    return counter;
    
}

void node_pixel_append_new_image(NodeTree* node, Image* image, Pixel** pixels_list){
    for (int i = 0; i < node->neighborhood->length; i++)
    {
        image->pixels[node->neighborhood->array[i]] = pixels_list[node->neighborhood->array[i]]->value;
    }
    
};



