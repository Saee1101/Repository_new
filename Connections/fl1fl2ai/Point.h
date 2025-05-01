#ifndef POINT_H
#define POINT_H

#pragma once

class Point
{
    double x, y;

public:
    Point();
    Point(double x, double y);

    void setX(double x);
    double getX() const;

    void setY(double y);
    double getY() const;

    void setXY(double x, double y);

    void print() const;

private:

};

#endif