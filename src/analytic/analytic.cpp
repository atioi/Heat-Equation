#include <cmath>
#include "../calerf.h"

double Ux0(double x) {
    double b = 0.1;
    return x < 0.0 ? 0.0 : exp(-x / b);
}

double U(double x, double t) {
    double b = 0.1;
    double D = 1.0;
    return 0.5 * exp(D * t / (b * b) - x / b) * calerf::ERFCL((2.0 * D * t / b - x) / (2.0 * sqrt(D * t)));
}


