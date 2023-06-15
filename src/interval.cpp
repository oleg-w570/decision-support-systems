#include "interval.h"

const Point &Interval::leftPoint() const{
    return left;
}

const Point &Interval::rightPoint() const {
    return right;
}

Interval::Interval(const Point& right_, const Point& left_)
        : right(right_), left(left_) {}

double Interval::delta() const {
    return right.x - left.x;
}

double IntervalData::getR() const {
    return R;
}

Interval IntervalData::getInterval() const {
    return interval;
}

IntervalData::IntervalData(double R_, const Interval& interval_)
        : interval(interval_), R(R_) {}

bool IntervalData::operator<(const IntervalData &other) const {
    return R < other.R;
}

Point::Point(double x, double z)
        : x(x), z(z) {}
