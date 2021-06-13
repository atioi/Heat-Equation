#include <fstream>
#include <string>


void save(double *x, double *y, int N, std::string file_name, int step) {
    std::fstream file;
    file.open(file_name, std::ios::app);
    for (int i = 0; i < N; i += step)
        file << x[i] << " " << y[i] << std::endl;
    file.close();
}

void save(double x, double y, std::string file_name) {
    std::fstream file;
    file.open(file_name, std::ios::app);
    file << x << " " << y << std::endl;
    file.close();
}
