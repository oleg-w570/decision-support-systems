#pragma once
#include "algorithm.h"

class Piyavsky : public Algorithm {
    double m;

    double CalculateR(const Interval &interval) override;

    double NextPointCoordinate(const Interval &interval) override;

    bool UpdateDynamicsParameters(const std::array<Interval, 2> &intervals) override;

public:
    Piyavsky(const Problem &problem, const StopCondition &stop, double m = 20.0);
};