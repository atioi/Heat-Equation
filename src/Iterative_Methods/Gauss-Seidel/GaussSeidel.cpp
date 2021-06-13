double Gauss_Seidel(double *l, double *d, double *u, double *b, double *x, int N) {

    double *fi = new double[N];

    for (int i = 0; i < N; i++)
        fi[i] = -u[i] * x[i + 1] + b[i];
    fi[N - 1] = b[N - 1];

    for (int i = 0; i < N; i++) {
        if (i == 0)
            x[i] = fi[i] / d[i];
        else
            x[i] = (fi[i] - l[i - 1] * x[i - 1]) / d[i];
    }

    delete[] fi;
}
