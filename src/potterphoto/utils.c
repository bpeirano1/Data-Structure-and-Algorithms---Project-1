#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

Array* counter_umbral(int* list, int length){

    Array* umbrales_array = array_init(128);
    
    for (int i=0 ; i < length;i++){

        if (!array_in(umbrales_array,list[i]))
        {
            array_append(umbrales_array,list[i]);
        };
    };
    array_sort(umbrales_array);
    return umbrales_array;
};
void dfs_pixel(Pixel* pixel, Array* visited, Array* neighborhood, int umbral){
    
    if (!array_in(visited,pixel->id) && pixel->value >= umbral)
    {
        array_append(visited,pixel->id);
        array_append(neighborhood,pixel->id);
        if (pixel->up)
        {
            dfs_pixel(pixel->up,visited,neighborhood,umbral);
        };
        if (pixel->right)
        {
            dfs_pixel(pixel->right,visited,neighborhood,umbral);
        };
        if (pixel->down)
        {
            dfs_pixel(pixel->down,visited,neighborhood,umbral);
        };
        if (pixel->left)
        {
            dfs_pixel(pixel->left,visited,neighborhood,umbral);
        }
        
    };
};   

void recursion(NodeTree * node, int umbral_counter, Array* list_umbrales, Pixel** pixels_list, int* counter_node_id){
    if (umbral_counter >= list_umbrales->length)
    {
        return;
    }

    Array* visited = array_init(node->neighborhood->length);
    Array* neighborhood = array_init(node->neighborhood->length);
    // printf("Debug\n");

    for (int i = 0; i < node->neighborhood->length; i++)
    {
        // printf("Debug\n");
        if ((!array_in(visited, pixels_list[node -> neighborhood->array[i]]->id) && pixels_list[node -> neighborhood->array[i]]->value >= list_umbrales->array[umbral_counter] ))
        {
            dfs_pixel(pixels_list[node -> neighborhood->array[i]],visited,neighborhood, list_umbrales->array[umbral_counter]);
            if (neighborhood->length)
            {
                array_sort(neighborhood);
                if (neighborhood->length == node->neighborhood->length)
                {
                    recursion(node,umbral_counter+1,list_umbrales,pixels_list, counter_node_id);
                } else if (neighborhood->length < node->neighborhood->length)
                {
                    NodeTree* new_node = node_tree_init(counter_node_id[0],list_umbrales->array[umbral_counter],neighborhood);
                    counter_node_id[0] +=1 ;
                    new_node->parent = node;
                    node_tree_adjust(new_node,pixels_list);
                    node_tree_append_children(node, new_node);
                    recursion(new_node,umbral_counter+1,list_umbrales,pixels_list, counter_node_id);
                    // node_tree_printf(new_node);
                } else{
                    printf("ERROR en REcursion");
                }  
            }
            // if(!neighborhood->length){
            //     array_destroy(neighborhood);
            // }
            neighborhood = array_init(node->neighborhood->length);
            
        }
    }
    // array_destroy(visited);
    
    


    
};