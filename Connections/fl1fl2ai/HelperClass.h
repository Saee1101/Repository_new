//
// Created by Newo on 9/20/2023.
//

#ifndef CPPS_HELPERCLASS_H
#define CPPS_HELPERCLASS_H

#include <HalconCpp.h>
#include "OvalityMeasures.h"

using namespace HalconCpp;

class HelperClass {
    HalconCpp::HWindow window;
public:
    HImage getImage(const OvalityMeasures &oval, HalconCpp::HImage &image);
    HImage getImage(const HalconCpp::HObject &xld, HalconCpp::HImage &image);

    void drawOvalityMeasure(const OvalityMeasures &oval, const HImage &image);
    void drawXldContour(const HObject &xld, const HImage &image);
    void drawPoint(double x, double y, int size, int color);
    void drawCircle(const Point &center, double radius, int lineWidth, int color);
    void setColor(int color);

};


#endif //CPPS_HELPERCLASS_H
