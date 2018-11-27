#include "Point.h"
#include <math.h>
#include <utility>

// TODO: Abstand von zwei Points implementieren

Point::Point()
: x(0), y(0) {}

Point::Point(double x, double y)
: x(x) , y(y) {}

Point Point::operator+(const Point& a){

    return Point(x + a.x, y + a.y);
}

Point& Point::operator+=(const Point& a){

    *this = *this+a;

    return *this;
}

Point Point::operator-(const Point& a){

    return Point(x - a.x, y - a.y);
}

Point& Point::operator-=(const Point& a){

    *this = *this - a;

    return *this;
}

Point Point::operator*(const double a){
    return Point(x * a, y * a);
}

Point& Point::operator*=(const double a){
    *this = *this*a;

    return *this;
}

Point Point::operator/(const double a){
    return Point(x / a, y / a);
}

Point& Point::operator/=(const double a){
    *this = *this/a;

    return *this;
}

Point& Point::operator=(const Point a){
    x = a.x;
    y = a.y;

    return *this;
}

double Point::magnitude(){
    return sqrt(x*x + y*y);
}
