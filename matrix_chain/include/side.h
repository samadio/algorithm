#ifndef __side__

#define __side__

void randomly_fill_matrix(float **A, const size_t A_rows, const size_t A_cols);

float **allocate_matrix(const size_t rows,
                        const size_t cols);

void deallocate_matrix_fl(float **A, const size_t rows);

int naive_matrix_mult(float **C,
                        float **A,
                        float **B,
                        const size_t A_rows,
                        const size_t A_cols,
                        const size_t B_rows,
                        const size_t B_cols);

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time);

void copy_matrix(float **A, float**B, int Ar, int Ac);

double using_s(float **res,float ***A,int *P,int **s,int left,int right,double *time);

#endif