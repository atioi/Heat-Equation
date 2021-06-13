void fill(double *vec, double x0, double dx, double t, double (*function)(double, double), int N) {
    double x = x0;
    for (int i = 0; i < N; i++) {
        vec[i] = function(x, t);
        x += dx;
    }
}

void fill(double *vec, double x0, double dx, double (*function)(double), int N) {
    double x = x0;
    for (int i = 0; i < N; i++) {
        vec[i] = function(x);
        x += dx;
    }
}

void fill(double *vec, double x0, double dx, int N) {
    double x = x0;
    for (int i = 0; i < N; i++) {
        vec[i] = x;
        x += dx;
    }
}