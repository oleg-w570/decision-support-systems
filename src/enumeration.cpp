#include "enumeration.h"

Enumeration::Enumeration(const Problem &problem, const StopCondition &param) : Algorithm(problem, param) {}

double Enumeration::CalculateR(const Interval& interval) {
    return interval.delta();
}

double Enumeration::NextPointCoordinate(const Interval& interval) {
    const double& lx = interval.leftPoint().x;
    const double& rx = interval.rightPoint().x;

    return 0.5 * (lx + rx);
}

bool Enumeration::UpdateDynamicsParameters(const std::array<Interval, 2> &intervals) {
    return false;
}

