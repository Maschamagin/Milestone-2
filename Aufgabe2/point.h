#ifndef POINT_H
#define POINT_H

// TODO: Abstand von zwei Points implementieren

struct Point{
    double x;
    double y;

    Point();
    Point(double x, double y);

    Point operator+(const Point&);
    Point& operator+=(const Point&);
    Point operator-(const Point&);
    Point& operator-=(const Point&);
    Point operator*(const double);
    Point& operator*=(const double);
    Point operator/(const double);
    Point& operator/=(const double);
    Point& operator=(const Point);
    double euclidianDistance();
    double manhattanDistance();
};

#endif
