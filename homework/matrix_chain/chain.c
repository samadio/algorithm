#include <stdio.h>
#include <stdlib.h>
#include<limits.h>

int **allocate_matrix_m(const int rows){                
   int **A=(int **)malloc(sizeof(int *)*rows);

   for (int i=0; i<rows; i++) {
     A[i]=(int *)malloc(sizeof(int)*(rows));
   }

   return A;
}

void deallocate_matrix(int **A, const int rows)
{
  for (int i=0; i<rows; i++) {
    free(A[i]);
  }

  free(A);
}


void matrixchain_aux(int* P,int** m,int** s,int i,int j){
    m[i][j]=INT_MAX;
    int q;
    for(int k = i; k < j; ++k)
    {
        q=m[i][k]+m[k+1][j]+P[i]*P[k+1]*P[j+1];
        if(q<m[i][j]){
            m[i][j]=q;
            s[i][j-1]=k+1;
        }
    }
    
}



int** matrixchain(int* P,int n){
    int** m=allocate_matrix_m(n);
    int** s=allocate_matrix_m(n-1);
    for(int i=0;i<n;i++){
        m[i][i]=0;
    }

    for(int l=1;l<n;l++){ //diagonal offset
        for(int i=0;i<n-l;i++){ //row
            int j=i+l;
            matrixchain_aux(P,m,s,i,j);
        }    
    }
    deallocate_matrix(s,n-1);
    return m;
}