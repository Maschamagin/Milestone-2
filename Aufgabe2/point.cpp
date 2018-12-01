#include "point.h"
#include <cmath>
#include <utility>

using namespace std;

// Initializes Point(0,0)
Point::Point()
: x(0), y(0) {}

// Initialize Point with given x and y
Point::Point(double x, double y)
: x(x) , y(y) {}


Point Point::operator+(const Point& a){
    // Overload plus and return new point
    return Point(x + a.x, y + a.y);
}

Point& Point::operator+=(const Point& a){

    // Apply plus and return current point
    *this = *this+a;

    return *this;
}

Point Point::operator-(const Point& a){
    // Overload minis and return new point
    return Point(x - a.x, y - a.y);
}

Point& Point::operator-=(const Point& a){
    // Apply minus and return current point
    *this = *this - a;

    return *this;
}

Point Point::operator*(const double a){
    // Overload multiply and return new point
    return Point(x * a, y * a);
}

Point& Point::operator*=(const double a){
    // Apply multiply and return current point
    *this = *this*a;

    return *this;
}

Point Point::operator/(const double a){
    // Overload division and return new point
    return Point(x / a, y / a);
}

Point& Point::operator/=(const double a){
    // Apply division and return current point
    *this = *this/a;

    return *this;
}

Point& Point::operator=(const Point a){
    // Assign new values and return current point
    x = a.x;
    y = a.y;

    return *this;
}

double Point::euclidianDistance(){
    // Return euclidian distance to (0,0)
    return sqrt(x*x + y*y);
}

double Point::manhattanDistance(){
    // Return manhattan distance to (0,0)
    return abs(x)+abs(y);
}

