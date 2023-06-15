#include "algorithm.h"

Algorithm::Algorithm(const Problem &problem, const StopCondition &param)
        : problem(problem), stop(param) {}

void Algorithm::FirstIteration() {
    const double &lx = problem.leftBound;
    const double lz = problem.f(lx);
    const double &rx = problem.rightBound;
    const double rz = problem.f(rx);

    sol.optimum = Point(lx, lz);
    sol.trials.emplace_back(lx, lz);
    Interval firstInterval(Point(rx, rz), Point(lx, lz));
    UpdateDynamicsParameters({firstInterval, firstInterval});
    Q.emplace(0.0, firstInterval);
}

std::array<Interval, 2> Algorithm::SplitInterval(const Interval& interval, const Point& point) {
    const Point &leftPoint = interval.leftPoint();
    const Point &rightPoint = interval.rightPoint();
    Interval left(point, leftPoint);
    Interval right(rightPoint, point);

    return std::array<Interval, 2>({left, right});
}

void Algorithm::Recalc() {
    std::priority_queue<IntervalData> newQ;
    while (!Q.empty()) {
        const Interval interval = Q.top().getInterval();
        const double R = CalculateR(interval);
        newQ.emplace(R, interval);
        Q.pop();
    }
    Q.swap(newQ);
}

void Algorithm::Finalize(const Interval& interval) {
    const double x = NextPointCoordinate(interval);
    const double z = problem.f(x);
    const Point last(x, z);
    sol.trials.push_back(last);
    if (last < sol.optimum)
        sol.optimum = last;

    while (!Q.empty()) {
        const Point &point = Q.top().getInterval().rightPoint();
        sol.trials.push_back(point);
        if (point < sol.optimum)
            sol.optimum = point;
        Q.pop();
    }
}

void Algorithm::run() {
    FirstIteration();
    Interval interval = Q.top().getInterval();
    const double delta = interval.delta();
    Q.pop();
    while (interval.delta() > stop.eps && sol.iterationCount < stop.iterationMax) {
        const double x = NextPointCoordinate(interval);
        const double z = problem.f(x);
        auto newIntervals = SplitInterval(interval, Point(x, z));

        if (UpdateDynamicsParameters(newIntervals))
            Recalc();

        for (const Interval &intrvl: newIntervals) {
            const double R = CalculateR(intrvl);
            Q.emplace(R, intrvl);
        }

        interval = Q.top().getInterval();
        Q.pop();
        sol.iterationCount++;
    }
    Finalize(interval);
}

const Solution &Algorithm::solution() const {
    return sol;
}
