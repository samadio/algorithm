#ifndef __CHAIN__
#define __CHAIN__

int **allocate_matrix_m(const int rows);
void deallocate_matrix(int **A, const int rows);
void matrixchain_aux(int* P,int** m,int** s,int i,int j);
int** matrixchain(int* P,int n);
#endif