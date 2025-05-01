#ifndef OVALITYMEASURES_H
#define OVALITYMEASURES_H

#pragma once

#include "Point.h"
class OvalityMeasures
{
public:
    double radius;
    double score;
    double innerRadius;
    int diam_num;
    double* diameters;

    Point circleCenter;


    OvalityMeasures();

    void print() const;
};

#endif