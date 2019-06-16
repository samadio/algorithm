#include<stdio.h>
#include<stdlib.h>
#include<dijkstra.h>
#include<float.h>
#include<time.h>

int main(){
    
    size_t N=5;
    //graph in class
    double mat[6][6] = {{-1,1,5,-1,-1,-1},{-1,-1,-1,-1,-1,15},{-1,-1,-1,2,-1,-1},{-7,-9,-1,-1,1,-12},{-1,-1,-1,-1,-1,3},{-1,-1,-15,-1,-23,-1}};
    
    //graph on book
    //double mat[5][5] = {{-1, 10, -1, -1, 5}, {-1, -1, 1, -1, 2}, {-1, -1, -1, 4, -1}, {7, -1, 6, -1, -1}, {-1, 3, 9, 2, -1}};


    double** M=(double**)calloc(N,sizeof(double*));
    for (size_t i = 0; i < N; i++)
    {
        M[i]=(double*)calloc(N,sizeof(double));
    }
    
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            M[i][j]=mat[i][j];
        }
        
    }
    
    node* results;
    size_t source=2;
    //results=dijkstra_array(M, N, source);

    results=dijkstra_heap(M, N, source);

    printf("source is node %lu \n",source+1);
    for (size_t i = 0; i < N; i++)
    {
        if(results[i].d==DBL_MAX){
            printf("node %ld not reachable from this source \n", i);
            continue;
        }
        printf("target is node %ld, total distance: %lf\n", results[i].id+1,results[i].d);
        print_path(&results[i]);
    }
    
    free(results);
    for (size_t i = 0; i < N; i++)
    {
        free(M[i]);
    }
    free(M);free(results);
    return 0;
}