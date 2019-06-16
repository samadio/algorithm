#include<stdio.h>
#include<stdlib.h>
#include<dijkstra.h>
#include<float.h>


void array_init(node* array, const size_t N, const size_t source){
    size_t i;
    for ( i = 0; i < N; i++)
    {
        array[i].id=i;
        array[i].d= (i==source) ? 0 : DBL_MAX ;
        array[i].prev= NULL;
        array[i].pos=i;        
    }
}


/**if the condition is satisfied, v is the next in path
/* with updated distance v.d=min.d+w,
/* where w=A[u,v]
*/ 
void array_relax(node* array, const size_t u,const size_t v, const double w){
    if(array[u].d+w<array[v].d){
        array[v].d=array[u].d+w;
        array[v].prev= &(array[u]);
    }
}

size_t take_min(node** queue, const size_t size){
    size_t min_id=0;
    double min=queue[0]->d;
    for (size_t i = 0; i < size; i++)
    {
        if(queue[i]->d < min){
            min_id=i;
            min=queue[i]->d;
        }
    }
    return queue[min_id]->id;
}

node* dijkstra_array(double ** adj, const size_t N, const size_t source){    
    node* list=(node*)calloc(N,sizeof(node));
    array_init(list,N,source);  
    node* queue[N];
    size_t queue_length=N;
    
    //create array of addresses
    for (size_t i = 0; i < N; i++) queue[i]=&(list[i]);


    size_t min_pos=source; //position of minimum in the queue
    size_t minimum=source; //start from source node
    queue[min_pos]=queue[queue_length-1]; //delete min_pos from queue by putting at the end
    queue[min_pos]->pos=min_pos;  //update pos variable of the (was) last queue element
    
    while(queue_length-1!=0){
        for (size_t i = 0; i < N; i++)
        {
            if(i!=minimum && adj[minimum][i]>=0) array_relax(list,minimum,i,adj[minimum][i]);
        }
        
        if(queue_length-1!=0){
            queue_length=queue_length-1;
            minimum=take_min(queue,queue_length);
            min_pos=list[minimum].pos;
            queue[min_pos]=queue[queue_length-1]; //delete min_pos from queue
            queue[min_pos]->pos=min_pos;  //update pos variable
        } 
    }
    return list;
}

/////////////////////////heap


void heap_relax (node *array, const size_t u, const size_t v, const double w, node** H){

	if (array[u].d + w < array[v].d){
	    array[v].prev = &(array[u]);
	    heap_decrease_key (H, array[v].pos, array[u].d + w);
	}
}


node* dijkstra_heap(double ** adj, const size_t N, const size_t source){    
    node* list=(node*)calloc(N,sizeof(node));
    array_init(list,N,source);  
    node* queue[N];
    size_t queue_length=N;
    
    //create array of addresses
    for (size_t i = 0; i < N; i++) queue[i]=&(list[i]);

    node *temp = queue[0];
    queue[0] = queue[source];
    queue[source] = temp;
    list[source].pos = 0;
    queue[source]->pos = source;

    build_heap(queue,queue_length);
    while(queue_length-1!=0){

        node *min = remove_minimum(queue,queue_length);
	    size_t min_id = min->id;

        if(queue_length-1!=0){
            queue_length=queue_length-1; 
        }

        for (size_t i = 0; i < N; i++)
        {
            if(i!=min_id && adj[min_id][i]>=0) heap_relax(list,min_id,i,adj[min_id][i],queue);
        }
        
    }
    return list;
}


///////////////////////////////
void print_path(node* target){
    printf("%lu", target->id+1);
    target=(target->prev);
    while(target!=NULL){
        printf(" %lu", target->id+1);
        target=(target->prev);    
    }
    printf("\n");
}