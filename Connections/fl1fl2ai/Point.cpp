#include "Point.h"

#include <iostream>
using namespace std;

Point::Point() : x(0), y(0)
{
}

Point::Point(double x, double y) : x(x), y(y)
{
}

void Point::setX(double x)
{
    this->x = x;
}

double Point::getX() const
{
    return x;
}

void Point::setY(double y)
{
    this->y = y;
}

double Point::getY() const
{
    return y;
}

void Point::setXY(double x, double y)
{
    this->x = x;
    this->y = y;
}

void Point::print() const
{
    cout << "(" << x << ", " << y << ")" << endl;    
}
