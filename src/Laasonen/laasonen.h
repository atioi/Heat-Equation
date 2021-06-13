#ifndef HEATEQUATION_LAASONEN_H
#define HEATEQUATION_LAASONEN_H

#include <string>

void Laasonen(double lambda, double x0, double h, int N, double t0, double dt, int K);

void
Laasonen(double *d_vec, double *l_vec, double *u_vec, double *b_vec, double *x_vec, double lambda, int N, double x0,
         double h);

void Laasonen(double lambda, double x0, double h, int N, double t0, double dt, int K,
              double (*iterative_method)(double *, double *, double *, double *, double *, int),
              std::string iterative_method_name);

void Laasonen();

#endif //HEATEQUATION_LAASONEN_H
