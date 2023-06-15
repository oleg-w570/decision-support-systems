#pragma once
#include <utility>

struct Point {
    double x;
    double z;
    explicit Point(double x = 0.0, double z = 0.0);
    bool operator<(const Point& other) const { return z < other.z;}
};

class Interval {
    Point right;
    Point left;
public:
    Interval(const Point& right_, const Point& left_);
    double delta() const;
    const Point& rightPoint() const;
    const Point& leftPoint() const;
};

class IntervalData {
    Interval interval;
    double R;
public:
    IntervalData(double R_, const Interval& interval_);
    bool operator<(const IntervalData& other) const;
    double getR() const;
    Interval getInterval() const;
};