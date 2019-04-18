#ifndef __UTILS__
#define __UTILS__

int* create_array(const size_t len);
double* create_array_double(const size_t len);

double get_execution_time(const struct timespec b_time, const struct timespec e_time);

int ordered(int *v,const size_t len);
int ordered_double(double *v,const size_t len);

#endif