#include "strongin.h"

Strongin::Strongin(const Problem &problem, const StopCondition &stop, double r)
        : Algorithm(problem, stop), r(r), m(1.0), M(0.0) {}

double Strongin::CalculateR(const Interval &interval) {
    const double delta = interval.delta();
    const double &lz = interval.leftPoint().z;
    const double &rz = interval.rightPoint().z;

    return m * delta - (rz - lz) * (rz - lz) / (m * delta) - 2 * (rz + lz);
}

double Strongin::NextPointCoordinate(const Interval &interval) {
    const double &lx = interval.leftPoint().x;
    const double &rx = interval.rightPoint().x;
    const double &lz = interval.leftPoint().z;
    const double &rz = interval.rightPoint().z;

    return 0.5 * (rx + lx) - 0.5 * (rz - lz) / m;
}

bool Strongin::UpdateDynamicsParameters(const std::array<Interval, 2> &intervals) {
    bool changed = false;
    for (const Interval &intrvl: intervals) {
        const double delta = intrvl.delta();
        const double &lz = intrvl.leftPoint().z;
        const double &rz = intrvl.rightPoint().z;
        const double tempM = std::abs(rz - lz) / delta;
        if (M < tempM) {
            M = tempM;
            changed = true;
        }
    }

    if (M > 0.0)
        m = r * M;
    else
        m = 1.0;

    return changed;
}
