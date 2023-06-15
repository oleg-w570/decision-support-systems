#include "piyavsky.h"

double Piyavsky::CalculateR(const Interval &interval) {
    const double delta = interval.delta();
    const double &lz = interval.leftPoint().z;
    const double &rz = interval.rightPoint().z;

    return 0.5 * (m * delta) - 0.5 * (lz + rz);
}

double Piyavsky::NextPointCoordinate(const Interval &interval) {
    const double &lx = interval.leftPoint().x;
    const double &rx = interval.rightPoint().x;
    const double &lz = interval.leftPoint().z;
    const double &rz = interval.rightPoint().z;

    return 0.5 * (rx + lx) - 0.5 * (rz - lz) / m;
}

bool Piyavsky::UpdateDynamicsParameters(const std::array<Interval, 2> &intervals) {
    return false;
}

Piyavsky::Piyavsky(const Problem &problem, const StopCondition &stop, double m)
        : Algorithm(problem, stop), m(m) {}
