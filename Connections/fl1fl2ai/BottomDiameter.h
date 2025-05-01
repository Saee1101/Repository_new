//
// Created on 3/1/2025.
//

#ifndef CPPS_BOTTOMDIAMETER_H
#define CPPS_BOTTOMDIAMETER_H

#include <HalconCpp.h>
#include "OvalityMeasures.h"

using namespace HalconCpp;

class BottomDiameter {
    static HTuple Model;
    static HTuple AnisoModel;
public:
    BottomDiameter();
    void Diameters (HObject ho_Contour, HTuple hv_centerRow, HTuple hv_centerCol, HTuple hv_diam_num,
                    HTuple *hv_Diameters);
    void FindInnerEdges (HObject ho_Image, HObject *ho_InnerEdge, HTuple hv_Model, HTuple hv_AnisoModel,
                         HTuple *hv_centerRow, HTuple *hv_centerCol);
    void GenInnerModels (HTuple hv_radius, HTuple *hv_Model, HTuple *hv_AnisoModel);
    void ProcessIntersects (HTuple hv_InteRows, HTuple hv_InteCols, HTuple hv_centerRow,
                            HTuple hv_centerCol, HTuple *hv_NewRows, HTuple *hv_NewCols);
    std::tuple<OvalityMeasures, HObject> Analyze(const HalconCpp::HImage &image);

};


#endif //CPPS_BOTTOMDIAMETER_H
