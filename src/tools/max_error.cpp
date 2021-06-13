#include <cmath>

double max_error(double *vec, double *val, int N) {
    double error = 0.0;
    double max_error = -1.0;
    for (int i = 0; i < N; i++) {
        error = fabs(vec[i] - val[i]);
        if (max_error < error)
            max_error = error;
    }
    return max_error;
}
