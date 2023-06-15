#include "algorithm.h"

class Strongin : public Algorithm {
    double r;
    double m;
    double M;

    double CalculateR(const Interval &interval) override;

    double NextPointCoordinate(const Interval &interval) override;

    bool UpdateDynamicsParameters(const std::array<Interval, 2> &intervals) override;

public:
    Strongin(const Problem &problem, const StopCondition &stop, double r = 2.5);
};