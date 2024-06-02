#include <iostream>
#include <cmath>
#include <ctime>
#include <omp.h>
#define PI 3.1415926535897932384626433832795

double experiment(double *res);
void integral(const double a, const double b, const double h, double *res);

int main() {
    int i;
    double time, res, min_time, max_time, avg_time;
    int numbExp = 10;
    min_time = max_time = avg_time = experiment(&res);
    for(i = 0; i < numbExp - 1; i++) {
        time = experiment(&res);
        avg_time += time;
        if(max_time < time) max_time = time;
        if(min_time > time) min_time = time;
    }
    std::cout << "execution time : " << avg_time / numbExp << "; " << min_time << "; " << max_time << std::endl;
    std::cout.precision(8);
    std::cout << "integral value : " << res << std::endl;
    return 0;
}

double experiment(double *res) {
    double stime, ftime;
    double a = 0.0, b = PI, h = (b - a) / 1000.0;
    stime = clock();
    integral(a, b, h, res);
    ftime = clock();
    return (ftime - stime) / CLOCKS_PER_SEC;
}

void integral(const double a, const double b, const double h, double *res) {
    int n = (int)((b - a) / h);
    double sum = sin(a) + sin(b);
    #pragma omp parallel for reduction(+:sum)
    for (int k = 1; k < n; k++) {
        double x = a + k * h;
        sum += (k % 2 == 0) ? 2 * sin(x) : 4 * sin(x);
    }
    *res = (h / 3.0) * sum;
}