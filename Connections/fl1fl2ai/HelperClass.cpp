//
// Created by Newo on 9/20/2023.
//

#include "HelperClass.h"
#include "Constants.h"

using namespace HalconCpp;

HalconCpp::HImage HelperClass::getImage(const OvalityMeasures &oval, HalconCpp::HImage &image)
{
    window = HWindow(100, 100, -1, -1, 0, "buffer", "");
    drawOvalityMeasure(oval, image);
    HImage result = window.DumpWindowImage();

//    Hlong Row = oval.circleCenter.getY() - 2 * oval.radius;
//    Hlong Col = oval.circleCenter.getX() - 2 * oval.radius;
//    Hlong Width = 4 * oval.radius;
//    Hlong Height = 4 * oval.radius;
//    Row = Row > 0 ? Row : 0;
//    Col = Col > 0 ? Col : 0;
//    Width = Width < image.Width() ? Width : image.Width();
//    Height = Height < image.Height() ? Height : image.Height();

//    result = result.CropPart(Row, Col, Width, Height);
    return result;
}

HImage HelperClass::getImage(const HObject &xld, HImage &image) {
    window = HWindow(100, 100, -1, -1, 0, "buffer", "");
    drawXldContour(xld, image);
    HImage result = window.DumpWindowImage();
    return result;
}

void HelperClass::drawOvalityMeasure(const OvalityMeasures &oval, const HImage &image)
{
    window.ClearWindow();
    window.FlushBuffer();

    int width = image.Width();
    int height = image.Height();

    window.DispImage(image);

    int color = 2;
    int lineWidth = 3;

    drawCircle(oval.circleCenter, oval.radius, lineWidth, color);
    drawPoint(oval.circleCenter.getX(), oval.circleCenter.getY(), lineWidth, color);
}

void HelperClass::drawXldContour(const HObject &xld, const HImage &image)
{
    window.ClearWindow();
    window.FlushBuffer();

    int width = image.Width();
    int height = image.Height();

    window.DispImage(image);

    int color = 2;
//    int lineWidth = 3;

    setColor(color);
//    window.SetLineWidth(lineWidth);
//    window.SetDraw("margin");
    window.DispXld(xld);
}

void HelperClass::drawPoint(double x, double y, int size, int color)
{
    setColor(color);
    window.SetLineWidth(size);
    window.DispCircle(y, x, size);
}

void HelperClass::drawCircle(const Point &center, double radius, int lineWidth, int color)
{
    setColor(color);
    window.SetLineWidth(lineWidth);
    window.SetDraw("margin");
    window.DispCircle(center.getY(), center.getX(), radius);
}

void HelperClass::setColor(int color)
{
    HTuple colors = window.QueryColor();
    window.SetColor(colors[color % colors.Length()].C());
}
