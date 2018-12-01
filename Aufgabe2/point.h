#ifndef POINT_H
#define POINT_H

// Structure to represent a two-dimensional point on the plane
// i.e. 2-dimensional vector
struct Point{
    // x- and y-coordinate
    double x;
    double y;

    // Constructors
    Point();
    Point(double x, double y);

    // Overloading of operator to work elementwise
    Point operator+(const Point&);
    Point& operator+=(const Point&);
    Point operator-(const Point&);
    Point& operator-=(const Point&);
    Point operator*(const double);
    Point& operator*=(const double);
    Point operator/(const double);
    Point& operator/=(const double);
    Point& operator=(const Point);

    // Calculate the euclidian and manhattan distance of given point to Point(0,0)
    double euclidianDistance();
    double manhattanDistance();
};

#endif
