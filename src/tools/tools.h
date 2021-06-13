#ifndef HEATEQUATION_FILL_H
#define HEATEQUATION_FILL_H

#include <string>

void fill(double *vec, double x0, double dx, double t, double (*function)(double, double), int N);

void fill(double *vec, double x0, double dx, double (*function)(double), int N);

void fill(double *vec, double x0, double dx, int N);

void save(double *x, double *y, int N, std::string file_name, int step);

void save(double x, double y, std::string file_name);

double max_error(double *vec, double *val, int N);

#endif //HEATEQUATION_FILL_H
