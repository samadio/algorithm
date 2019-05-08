#ifndef __UTILS__
#define __UTILS__

void copy_vec(float *v1, float* v2, int len);

int* create_array(const size_t len);
double* create_array_double(const size_t len);
float* create_array_float(const size_t len);
float* create_norep(size_t size);

double get_execution_time(const struct timespec b_time, const struct timespec e_time);

int ordered(int *v,const size_t len);
int ordered_double(double *v,const size_t len);
int ordered_float(float *v,const size_t len);
int ordered_reverse(float *v,const size_t len);

#endif