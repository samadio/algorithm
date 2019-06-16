#ifndef __DIJKSTRA__
#define __DIJKSTRA__

#include<stdlib.h>

struct graph_node{
    size_t id; //node identifier in graph
    double d; //distance from source node
    struct graph_node* prev; //points to previous node in shortest path
    size_t pos; //position of the node in queue
};
typedef struct graph_node node;



//adjacency matrix, N=number of nodes=length(adj), source=source node id
node* dijkstra_array(double ** adj, const size_t N, const size_t source);
node* dijkstra_heap(double ** adj, const size_t N, const size_t source);

void build_heap(node** A,int size);
void heap_decrease_key(node** H,int i, double value);
void swap(node** H, int i, int j);
node* remove_minimum(node** H,int size);


void print_path(node* target);
#endif
