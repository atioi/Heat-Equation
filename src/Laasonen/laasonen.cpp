#include "../Iterative_Methods/Thomas/thomas.h"
#include "../Iterative_Methods/Gauss-Seidel/GaussSeidel.h"
#include "../analytic/analytic.h"
#include "../tools/tools.h"

#include <iostream>
#include <cmath>
#include <string>

double Laasonen(double lambda, double x0, double h, int N, double t0, double dt, int K,
                double (*iterative_method)(double *, double *, double *, double *, double *, int),
                std::string method_name);

void Laasonen() {

    int K = 7e3;
    double tK = 1.0;
    double t0 = 0.0;
    double D = 1.0;
    double dt = (tK - t0) / (K - 1);

    int N = 1e3;
    double xN = 6.0 * sqrt(D * tK);
    double x0 = -xN;
    double h = 2.0 * xN / (N - 1);


    double lambda = D * dt / (h * h);
    std::cout
            << "Metoda Laasonen" << std::endl
            << " N = " << N << std::endl
            << " K = " << K << std::endl
            << " [t0,tK] = " << "[" << t0 << "," << tK << "]" << std::endl
            << " dt = " << dt << std::endl
            << " h = " << h << std::endl
            << " [a,b] = " << "[" << x0 << "," << xN << "]" << std::endl
            << " Lambda = " << lambda << std::endl;


    Laasonen(lambda, x0, h, N, t0, dt, K, &Thomas, "T");
//    for (N = 1e3; N > 100; N -= 100) {
//        h = 2.0 * xN / (N - 1);
//        lambda = D * dt / (h * h);
//        save(log10(h), log10(Laasonen(lambda, x0, h, N, t0, dt, K, &Thomas, "T")), "../Results/Laasonen/T5.txt");
//    }

}
void
Laasonen(double *d_vec, double *u_vec, double *l_vec, double lambda, double h, int N, double *b_vec, double *x_vec,
         double x0) {

    for (int i = 1; i < N - 1; i++)
        d_vec[i] = -(1.0 + 2.0 * lambda);

    d_vec[0] = 1.0;
    d_vec[N - 1] = 1.0;

    for (int i = 0; i < N - 1; i++) {
        l_vec[i] = lambda;
        u_vec[i] = lambda;
    }
    u_vec[0] = 0.0;
    l_vec[N - 2] = 0.0;

    fill(x_vec, x0, h, &Ux0, N);

    for (int i = 1; i < N - 1; i++)
        b_vec[i] = -x_vec[i];

    b_vec[0] = 0.0;
    b_vec[N - 1] = 0.0;

}


double Laasonen(double lambda, double x0, double h, int N, double t0, double dt, int K,
                double (*iterative_method)(double *, double *, double *, double *, double *, int),
                std::string method_name) {

    double *d_vec, *l_vec, *u_vec, *x_vec, *b_vec, *analytic, *domain, *max_errors, *t_vec;

    l_vec = new double[N - 1];
    d_vec = new double[N];
    u_vec = new double[N - 1];
    x_vec = new double[N];
    b_vec = new double[N];
    analytic = new double[N];
    domain = new double[N];
    max_errors = new double[K - 1];
    t_vec = new double[K - 1];

    fill(domain, x0, h, N);
    Laasonen(d_vec, u_vec, l_vec, lambda, h, N, b_vec, x_vec, x0);

    double error = 0.0;
    for (int k = 1; k < K; k++) {

        iterative_method(l_vec, d_vec, u_vec, b_vec, x_vec, N);
        fill(analytic, x0, h, t0 + k * dt, &U, N);

        if (k == 1) {
            std::cout << t0 + k * dt << std::endl;
            save(domain, x_vec, N, "../Results/Laasonen/" + method_name + "1.txt", 1);
            save(domain, analytic, N, "../Results/Laasonen/A" + method_name + "1.txt", 1);
        } else if (k == 100) {
            std::cout << t0 + k * dt << std::endl;
            save(domain, x_vec, N, "../Results/Laasonen/" + method_name + "2.txt", 1);
            save(domain, analytic, N, "../Results/Laasonen/A" + method_name + "2.txt", 1);
        } else if (k == 1000) {
            std::cout << t0 + k * dt << std::endl;
            save(domain, x_vec, N, "../Results/Laasonen/" + method_name + "3.txt", 5);
            save(domain, analytic, N, "../Results/Laasonen/A" + method_name + "3.txt", 1);
        } else if (k == (K - 1)) {
            error = max_error(x_vec, analytic, N);
            std::cout << t0 + k * dt << std::endl;
            save(domain, x_vec, N, "../Results/Laasonen/" + method_name + "4.txt", 5);
            save(domain, analytic, N, "../Results/Laasonen/A" + method_name + "4.txt", 1);
        }


        max_errors[k - 1] = max_error(x_vec, analytic, N);
        t_vec[k - 1] = k * dt;

        for (int i = 1; i < N - 1; i++)
            b_vec[i] = -x_vec[i];

        b_vec[0] = 0.0;
        b_vec[N - 1] = 0.0;

    }

    save(t_vec, max_errors, K - 1, "../Results/Laasonen/" + method_name + "6.txt", 1);


    delete[] l_vec;
    delete[] d_vec;
    delete[] u_vec;
    delete[] domain;
    delete[] analytic;

    return error;

}