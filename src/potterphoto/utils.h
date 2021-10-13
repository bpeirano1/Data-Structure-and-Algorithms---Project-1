#include "array.h"
#include "pixel.h"
#include "componentTree.h"

#pragma once

Array* counter_umbral(int* list, int length);
void dfs_pixel(Pixel* pixel, Array* visited, Array* neighborhood, int umbral);
void recursion(NodeTree * node, int umbral_counter, Array* list_umbrales, Pixel** pixels_list,int* counter_node_id);