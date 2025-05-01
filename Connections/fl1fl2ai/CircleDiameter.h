//
// Created by Newo on 9/20/2023.
//

#ifndef CPPS_CIRCLEDIAMETER_H
#define CPPS_CIRCLEDIAMETER_H

#include <HalconCpp.h>
#include "OvalityMeasures.h"

using namespace HalconCpp;

class CircleDiameter {
    HalconCpp::HWindow window;
    static HTuple top_Model;
    static HTuple bottom_Model;
public:
    CircleDiameter();
    OvalityMeasures topAnalyze(const HalconCpp::HImage &image);
    OvalityMeasures bottomAnalyze(const HalconCpp::HImage &image);
    int findBestCircle(const HTuple &RowCheck, const HTuple &ColumnCheck, const HTuple &ScaleCheck, const HTuple &Score);
    static void Diameters (HObject ho_Contour, HTuple hv_centerRow, HTuple hv_centerCol, HTuple hv_diam_num,
                    HTuple *hv_Diameters);
    static void ProcessIntersects (HTuple hv_InteRows, HTuple hv_InteCols, HTuple hv_centerRow,
                            HTuple hv_centerCol, HTuple *hv_NewRows, HTuple *hv_NewCols);
    HImage getImage(const OvalityMeasures &oval, HalconCpp::HImage &image);

    void drawOvalityMeasure(const OvalityMeasures &oval, const HImage &image);
    void drawPoint(double x, double y, int size, int color);
    void drawCircle(const Point &center, double radius, int lineWidth, int color);
    void setColor(int color);

};


#endif //CPPS_CIRCLEDIAMETER_H
