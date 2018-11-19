#include "Point.h"
#include <math.h>

Point::Point()
: x(0), y(0) {}

Point::Point(double x, double y)
: x(x) , y(y) {}

Point& Point::operator+(const Point& a){
    x = x+a.x;
    y = y+a.y;

    return *this;
}

Point& Point::operator+=(const Point& a){
	
	*this = *this+a;
	
	return *this;
}

Point& Point::operator*(const double a){
    x = x * a;
    y = y * a;

    return *this;
}

Point& Point::operator*=(const double a){
	*this = *this*a;

	return *this;
}

Point& Point::operator/(const double a){
	x = x / a;
	y = y / a;

	return *this;
}

Point& Point::operator/=(const double a){
	*this = *this/a;

	return *this;
}

Point Point::operator=(const Point& a){
    return Point(a.x,a.y);
}

double Point::magnitude(){
    return sqrt(x*x + y*y);
}
