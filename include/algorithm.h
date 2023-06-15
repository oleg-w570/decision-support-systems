#pragma once

#include "interval.h"
#include <queue>
#include <utility>
#include <vector>
#include <functional>

struct Problem {
    std::function<double(double)> f;
    double leftBound;
    double rightBound;

    explicit Problem(std::function<double(double)> f = [](double x) { return x; },
                     double leftBound = 0.0, double rightBound = 1.0)
            : f(std::move(f)), leftBound(leftBound), rightBound(rightBound) {}
};

struct StopCondition {
    double eps;
    int iterationMax;

    explicit StopCondition(double eps = 0.01, int iterMax = 100)
            : eps(eps), iterationMax(iterMax) {}
};

struct Solution {
    std::vector<Point> trials;
    Point optimum;
    int iterationCount;

    Solution()
            : trials(), optimum(), iterationCount(0) {}
};

class Algorithm {
    Problem problem;
    StopCondition stop;
    Solution sol;
    std::priority_queue<IntervalData> Q;

    virtual double CalculateR(const Interval &interval) = 0;

    virtual double NextPointCoordinate(const Interval &interval) = 0;

    void FirstIteration();

    static std::array<Interval, 2> SplitInterval(const Interval &interval, const Point &point);

    virtual bool UpdateDynamicsParameters(const std::array<Interval, 2> &intervals) = 0;

    void Recalc();

    void Finalize(const Interval &interval);

public:
    Algorithm(const Problem &problem, const StopCondition &param);

    void run();

    const Solution &solution() const;
};
