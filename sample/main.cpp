#include <iostream>
#include "enumeration.h"
#include "piyavsky.h"
#include "strongin.h"
#include <cmath>

using namespace std;

int main() {
    std::function<double(double)> f = [](double x) { return 2.0 * sin(3.0 * x) + 3.0 * cos(5.0 * x); };
    Problem problem(f, 0.0, 8.0);
    StopCondition stop(0.01, 1000);
    Enumeration alg1(problem, stop);
    alg1.run();
    Piyavsky alg2(problem, stop, 20.0);
    alg2.run();
    Strongin alg3(problem, stop, 2.5);
    alg3.run();

    cout << "enumeration: " << alg1.solution().optimum.x << ", " << alg1.solution().optimum.z << ", iter: " << alg1.solution().iterationCount << endl;
    cout << "piyavsky: " << alg2.solution().optimum.x << ", " << alg2.solution().optimum.z << ", iter: " << alg2.solution().iterationCount << endl;
    cout << "strongin: " << alg3.solution().optimum.x << ", " << alg3.solution().optimum.z << ", iter: " << alg3.solution().iterationCount << endl;

    return 0;
}