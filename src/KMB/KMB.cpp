#include <iostream>
#include <cmath>

#include "../analytic/analytic.h"
#include "../tools/tools.h"


void KMB(double lambda, double *u_next, double *u_before, int N);

double KMB(double lambda, double x0, double h, int N, double t0, double dt, int K);

void KMB() {

    int K = 1e5;
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
            << std::endl << std::endl
            << "KMB:" << std::endl
            << " N = " << N << std::endl
            << " K = " << K << std::endl
            << " [t0,tK] = " << "[" << t0 << "," << tK << "]" << std::endl
            << " dt = " << dt << std::endl
            << " h = " << h << std::endl
            << " [a,b] = " << "[" << x0 << "," << xN << "]" << std::endl
            << " Lambda = " << lambda << std::endl;


    KMB(lambda, x0, h, N, t0, dt, K);

//    for (N = 1e3; N > 100; N -= 100) {
//        h = 2.0 * xN / (N - 1);
//        lambda = D * dt / (h * h);
//        save(log10(h), log10(KMB(lambda, x0, h, N, t0, dt, K)), "../KMB/KMB5.txt");
//    }


}


void KMB(double lambda, double *u_next, double *u_before, int N) {
    u_next[0] = (1 - 2 * lambda) * u_before[0] + lambda * u_before[1];
    for (int i = 1; i < N - 1; i++)
        u_next[i] = lambda * u_before[i - 1] + (1 - 2 * lambda) * u_before[i] + lambda * u_before[i + 1];
    u_next[N - 1] = lambda * u_before[N - 2] + (1 - 2 * lambda) * u_before[N - 1];
}


double KMB(double lambda, double x0, double h, int N, double t0, double dt, int K) {

    double *u_before, *u_next, *x_vec, *analytic, *t_vec, *max_errors;

    u_before = new double[N];
    u_next = new double[N];
    x_vec = new double[N];
    t_vec = new double[K - 1];
    analytic = new double[N];
    max_errors = new double[K - 1];

    // Warunek początkowy:
    fill(u_before, x0, h, &Ux0, N);

    // Potrzebe do zapisu:
    fill(x_vec, x0, h, N);

    double error = 0.0;
    for (int k = 1; k < K; k++) {

        fill(analytic, x0, h, t0 + k * dt, &U, N);
        KMB(lambda, u_next, u_before, N);

        if (k == 1) {
            std::cout << t0 + k * dt << std::endl;
            save(x_vec, u_next, N, "../Results/KMB/KMB1.txt", 1);
            save(x_vec, analytic, N, "../Results/KMB/KMB1_a.txt", 1);
        } else if (k == (K / 100)) {
            std::cout << t0 + k * dt << std::endl;
            save(x_vec, u_next, N, "../Results/KMB/KMB2.txt", 20);
            save(x_vec, analytic, N, "../Results/KMB/KMB2_a.txt", 20);
        } else if (k == (K / 10)) {
            std::cout << t0 + k * dt << std::endl;
            save(x_vec, u_next, N, "../Results/KMB/KMB3.txt", 20);
            save(x_vec, analytic, N, "../Results/KMB/KMB3_a.txt", 20);
        } else if (k == K - 1) {
            std::cout << t0 + k * dt << std::endl;
            error = max_error(u_next, analytic, N);
            save(x_vec, u_next, N, "../Results/KMB/KMB4.txt", 20);
            save(x_vec, analytic, N, "../Results/KMB/KMB4_a.txt", 20);
        }

//        max_errors[k - 1] = max_error(u_next, analytic, N);
//        t_vec[k - 1] = k * dt;
        std::swap(u_next, u_before);
    }

//    save(t_vec, max_errors, K - 1, "../Results/KMB/KMB6.txt", 1);

    delete[] u_before;
    delete[] u_next;
    delete[] x_vec;
    delete[] t_vec;
    delete[] analytic;
    delete[] max_errors;

    return error;

}


