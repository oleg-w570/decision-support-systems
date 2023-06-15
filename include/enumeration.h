#pragma once
#include "algorithm.h"

class Enumeration: public Algorithm {
    double CalculateR(const Interval& interval) override;
    double NextPointCoordinate(const Interval& interval) override;
    bool UpdateDynamicsParameters(const std::array<Interval, 2>& intervals) override;
public:
    Enumeration(const Problem& problem, const StopCondition& param);
};