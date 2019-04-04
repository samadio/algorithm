#ifndef __CHAIN__
#define __CHAIN__

int **allocate_matrix_m(const int rows);
void deallocate_matrix(int **A, const int rows);
int** matrixchain(int* P,int n);
#endif