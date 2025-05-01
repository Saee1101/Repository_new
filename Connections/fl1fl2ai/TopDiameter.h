//
// Created on 3/1/2025.
//

#ifndef CPPS_TOPDIAMETER_H
#define CPPS_TOPDIAMETER_H

#include <HalconCpp.h>
#include "OvalityMeasures.h"

using namespace HalconCpp;

class TopDiameter {
    static HTuple Model;
public:
    TopDiameter();
    void ContrastMargin (HObject ho_Image, HObject *ho_Margin, HTuple hv_sobelThresh,
                         HTuple hv_centerRow, HTuple hv_centerCol);
    void CreateROIModel (HTuple hv_radius, HTuple *hv_Model);
    void Diameters (HObject ho_Contour, HTuple hv_centerRow, HTuple hv_centerCol, HTuple hv_diam_num,
                    HTuple *hv_Diameters);
    void DistancePCs (HObject ho_Contours, HTuple hv_Row, HTuple hv_Column, HTuple *hv_DistMins,
                      HTuple *hv_DistMaxs);
    void DistancePRs (HObject ho_Regions, HTuple hv_Row, HTuple hv_Column, HTuple *hv_DistMins,
                      HTuple *hv_DistMaxs);
    void FindImageROI (HObject ho_Image, HObject *ho_ImageROI, HTuple hv_Model, HTuple *hv_centerRow,
                       HTuple *hv_centerCol);
    void GrayExtrems (HObject ho_Image, HObject ho_Region, HTuple *hv_minGray, HTuple *hv_maxGray);
    void IntersectRegionContour (HObject ho_Region, HObject ho_Contour, HTuple *hv_area);
    void ProcessIntersects (HTuple hv_InteRows, HTuple hv_InteCols, HTuple hv_centerRow,
                            HTuple hv_centerCol, HTuple *hv_NewRows, HTuple *hv_NewCols);
    void PruneMargin (HObject ho_Margin, HObject *ho_MarginPart, HTuple hv_centerRow,
                      HTuple hv_centerCol);
    void ThresholdBorder (HObject ho_Image, HObject *ho_Border, HTuple hv_threshold,
                          HTuple hv_centerRow, HTuple hv_centerCol);
    std::tuple<OvalityMeasures, HObject> Analyze(const HalconCpp::HImage &image);
};


#endif //CPPS_TOPDIAMETER_H
