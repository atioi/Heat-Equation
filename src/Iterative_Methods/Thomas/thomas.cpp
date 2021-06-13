double Thomas(double *l_vec, double *d_vec, double *u_vec, double *b_vec, double *x_vec, int N) {
    double *eta, *r;
    eta = new double[N];
    r = new double[N];

    eta[0] = d_vec[0];
    r[0] = b_vec[0];

    for (int i = 1; i < N - 1; i++) {
        eta[i] = d_vec[i] - l_vec[i] * u_vec[i - 1] / eta[i - 1];
        r[i] = b_vec[i] - l_vec[i] * r[i - 1] / eta[i - 1];
    }

    x_vec[N] = r[N] / eta[N];
    for (int i = N - 2; i >= 0; i--)
        x_vec[i] = (r[i] - u_vec[i] * x_vec[i + 1]) / eta[i];

    delete eta;
    delete r;
}
