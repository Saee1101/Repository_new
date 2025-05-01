//
// Created on 3/1/2025.
//

#include "TopDiameter.h"

using namespace HalconCpp;

HTuple TopDiameter::Model;

TopDiameter::TopDiameter() {
    CreateROIModel(280, &TopDiameter::Model);

}

void TopDiameter::ContrastMargin(HObject ho_Image, HObject *ho_Margin, HTuple hv_sobelThresh, HTuple hv_centerRow,
                                 HTuple hv_centerCol) {
    // Local iconic variables
    HObject  ho_Sobel, ho_SobelRegion, ho_Regions;
    HObject  ho_SelectedRegions;

    // Local control variables
    HTuple  hv_DistMins, hv_DistMaxs, hv_minDist;
    HTuple  hv_nearIndex;

    SobelAmp(ho_Image, &ho_Sobel, "sum_abs", 3);
    Threshold(ho_Sobel, &ho_SobelRegion, hv_sobelThresh, 255);
    Connection(ho_SobelRegion, &ho_Regions);
    SelectShape(ho_Regions, &ho_SelectedRegions, "area", "and", 150, 100000000);
    DistancePRs(ho_SelectedRegions, hv_centerRow, hv_centerCol, &hv_DistMins, &hv_DistMaxs);

    hv_minDist = hv_DistMins.TupleFind(hv_DistMins.TupleMin());
    hv_nearIndex = HTuple(hv_minDist[(hv_minDist.TupleLength())-1])+1;
    SelectObj(ho_SelectedRegions, &(*ho_Margin), hv_nearIndex);
    return;
}

void TopDiameter::CreateROIModel (HTuple hv_radius, HTuple *hv_Model)
{

    // Local iconic variables
    HObject  ho_Image, ho_FullDomain, ho_Circle, ho_ROI;

    // Local control variables
    HTuple  hv_imageSize;

    hv_imageSize = (2*hv_radius)+20;

    GenImageConst(&ho_Image, "byte", hv_imageSize, hv_imageSize);
    GetDomain(ho_Image, &ho_FullDomain);
    OverpaintRegion(ho_Image, ho_FullDomain, 100, "fill");
    GenCircle(&ho_Circle, hv_imageSize/2, hv_imageSize/2, hv_radius);
    PaintRegion(ho_Circle, ho_Image, &ho_Image, 50, "fill");

    GenCircle(&ho_ROI, hv_imageSize/2, hv_imageSize/2, hv_radius+5);
    GenCircle(&ho_Circle, hv_imageSize/2, hv_imageSize/2, hv_radius-5);
    Difference(ho_ROI, ho_Circle, &ho_ROI);

    ReduceDomain(ho_Image, ho_ROI, &ho_Image);
    CreateScaledShapeModel(ho_Image, "auto", 0, 0, 0.01, .3, 3, "auto", "none", "use_polarity",
                           30, 10, &(*hv_Model));

    return;
}

void TopDiameter::Diameters(HObject ho_Contour, HTuple hv_centerRow, HTuple hv_centerCol, HTuple hv_diam_num,
                            HTuple *hv_Diameters) {
    // Local iconic variables
    HObject  ho_ContCircle;

    // Local control variables
    HTuple  hv_Radius, hv_resolution, hv_Rows, hv_Cols;
    HTuple  hv_WindowHandle, hv_i, hv_InteRow, hv_InteCol, hv_IsOverlapping;
    HTuple  hv_Distance;

    hv_Radius = 200;
    hv_resolution = (2*hv_Radius)*(((HTuple(180).TupleRad())/(2*hv_diam_num)).TupleSin());
    GenCircleContourXld(&ho_ContCircle, hv_centerRow, hv_centerCol, hv_Radius, 0, HTuple(360).TupleRad(),
                        "positive", hv_resolution);

    GetContourXld(ho_ContCircle, &hv_Rows, &hv_Cols);

//    if (HDevWindowStack::IsOpen())
//        hv_WindowHandle = HDevWindowStack::GetActive();

    (*hv_Diameters) = HTuple();
    {
        HTuple end_val9 = hv_diam_num-1;
        HTuple step_val9 = 1;
        for (hv_i=0; hv_i.Continue(end_val9, step_val9); hv_i += step_val9)
        {
//            if (HDevWindowStack::IsOpen())
//                SetColor(HDevWindowStack::GetActive(),"green");
//            DispLine(hv_WindowHandle, HTuple(hv_Rows[hv_i]), HTuple(hv_Cols[hv_i]), HTuple(hv_Rows[hv_diam_num+hv_i]),
//                     HTuple(hv_Cols[hv_diam_num+hv_i]));
            IntersectionLineContourXld(ho_Contour, HTuple(hv_Rows[hv_i]), HTuple(hv_Cols[hv_i]),
                                       HTuple(hv_Rows[hv_diam_num+hv_i]), HTuple(hv_Cols[hv_diam_num+hv_i]), &hv_InteRow,
                                       &hv_InteCol, &hv_IsOverlapping);

            if (0 != ((hv_InteRow.TupleLength())>=2))
            {
                ProcessIntersects(hv_InteRow, hv_InteCol, hv_centerRow, hv_centerCol, &hv_InteRow,
                                  &hv_InteCol);

                DistancePp(HTuple(hv_InteRow[0]), HTuple(hv_InteCol[0]), HTuple(hv_InteRow[1]),
                           HTuple(hv_InteCol[1]), &hv_Distance);
                (*hv_Diameters) = (*hv_Diameters).TupleConcat(hv_Distance);
//                if (HDevWindowStack::IsOpen())
//                    SetColor(HDevWindowStack::GetActive(),"orange");
//                DispCross(hv_WindowHandle, hv_InteRow, hv_InteCol, 20, HTuple(45).TupleRad());
            }
        }
    }

//    if (HDevWindowStack::IsOpen())
//        SetColored(HDevWindowStack::GetActive(),12);
    return;
}

void TopDiameter::DistancePCs(HObject ho_Contours, HTuple hv_Row, HTuple hv_Column, HTuple *hv_DistMins,
                              HTuple *hv_DistMaxs) {
    // Local iconic variables
    HObject  ho_Contour;

    // Local control variables
    HTuple  hv_size, hv_i, hv_DistMin, hv_DistMax;

    (*hv_DistMins) = HTuple();
    (*hv_DistMaxs) = HTuple();

    CountObj(ho_Contours, &hv_size);
    {
        HTuple end_val4 = hv_size;
        HTuple step_val4 = 1;
        for (hv_i=1; hv_i.Continue(end_val4, step_val4); hv_i += step_val4)
        {
            SelectObj(ho_Contours, &ho_Contour, hv_i);
            DistancePc(ho_Contour, hv_Row, hv_Column, &hv_DistMin, &hv_DistMax);
            (*hv_DistMins) = (*hv_DistMins).TupleConcat(hv_DistMin);
            (*hv_DistMaxs) = (*hv_DistMaxs).TupleConcat(hv_DistMax);
        }
    }
    return;
}

void TopDiameter::DistancePRs(HObject ho_Regions, HTuple hv_Row, HTuple hv_Column, HTuple *hv_DistMins,
                              HTuple *hv_DistMaxs) {
    // Local iconic variables
    HObject  ho_Contour;

    // Local control variables
    HTuple  hv_size, hv_i, hv_DistMin, hv_DistMax;

    (*hv_DistMins) = HTuple();
    (*hv_DistMaxs) = HTuple();

    CountObj(ho_Regions, &hv_size);
    {
        HTuple end_val4 = hv_size;
        HTuple step_val4 = 1;
        for (hv_i=1; hv_i.Continue(end_val4, step_val4); hv_i += step_val4)
        {
            SelectObj(ho_Regions, &ho_Contour, hv_i);
            DistancePr(ho_Contour, hv_Row, hv_Column, &hv_DistMin, &hv_DistMax);
            (*hv_DistMins) = (*hv_DistMins).TupleConcat(hv_DistMin);
            (*hv_DistMaxs) = (*hv_DistMaxs).TupleConcat(hv_DistMax);
        }
    }
    return;
}

void TopDiameter::FindImageROI(HObject ho_Image, HObject *ho_ImageROI, HTuple hv_Model, HTuple *hv_centerRow,
                               HTuple *hv_centerCol) {
    // Local iconic variables
    HObject  ho_EmphImage, ho_ModelContours, ho_ROI;

    // Local control variables
    HTuple  hv_RowCheck, hv_ColumnCheck, hv_AngleCheck;
    HTuple  hv_ScaleCheck, hv_Score, hv_m, hv_MovementOfObject;
    HTuple  hv_MoveAndScaleOfObject;

    Emphasize(ho_Image, &ho_EmphImage, 7, 7, 1);
    FindScaledShapeModel(ho_EmphImage, hv_Model, 0, 0, 0.3, 3, 0.5, 0, 1, "least_squares",
                         3, 0, &hv_RowCheck, &hv_ColumnCheck, &hv_AngleCheck, &hv_ScaleCheck, &hv_Score);
    if (0 != ((hv_ScaleCheck.TupleLength())<=0))
    {
        return;
    }
    hv_m = hv_ScaleCheck.TupleFind(hv_ScaleCheck.TupleMax());

    GetShapeModelContours(&ho_ModelContours, hv_Model, 1);
    VectorAngleToRigid(0, 0, 0, HTuple(hv_RowCheck[hv_m]), HTuple(hv_ColumnCheck[hv_m]),
                       HTuple(hv_AngleCheck[hv_m]), &hv_MovementOfObject);
    HomMat2dScale(hv_MovementOfObject, HTuple(hv_ScaleCheck[hv_m]), HTuple(hv_ScaleCheck[hv_m]),
                  HTuple(hv_RowCheck[hv_m]), HTuple(hv_ColumnCheck[hv_m]), &hv_MoveAndScaleOfObject);
    AffineTransContourXld(ho_ModelContours, &ho_ModelContours, hv_MoveAndScaleOfObject);
    AffineTransPoint2d(hv_MoveAndScaleOfObject, 0, 0, &(*hv_centerRow), &(*hv_centerCol));

    GenRegionContourXld(ho_ModelContours, &ho_ROI, "filled");
    ReduceDomain(ho_Image, ho_ROI, &(*ho_ImageROI));

    return;
}

void TopDiameter::GrayExtrems(HObject ho_Image, HObject ho_Region, HTuple *hv_minGray, HTuple *hv_maxGray) {
    // Local iconic variables

    // Local control variables
    HTuple  hv_Rows, hv_Cols, hv_Grayvals;

    GetRegionPoints(ho_Region, &hv_Rows, &hv_Cols);

    GetGrayval(ho_Image, hv_Rows, hv_Cols, &hv_Grayvals);

    (*hv_minGray) = hv_Grayvals.TupleMin();
    (*hv_maxGray) = hv_Grayvals.TupleMax();

    return;
}

void TopDiameter::IntersectRegionContour(HObject ho_Region, HObject ho_Contour, HTuple *hv_area) {
    // Local iconic variables
    HObject  ho_ContourRegion, ho_Intersection;

    GenRegionContourXld(ho_Contour, &ho_ContourRegion, "margin");

    Intersection(ho_Region, ho_ContourRegion, &ho_Intersection);

    RegionFeatures(ho_Intersection, "area", &(*hv_area));
    return;
}

void TopDiameter::ProcessIntersects(HTuple hv_InteRows, HTuple hv_InteCols, HTuple hv_centerRow, HTuple hv_centerCol,
                                    HTuple *hv_NewRows, HTuple *hv_NewCols) {
    // Local iconic variables

    // Local control variables
    HTuple  hv_left_num, hv_right_num, hv_i;

    (*hv_NewRows) = HTuple(2,0);
    (*hv_NewCols) = HTuple(2,0);

    hv_left_num = 0;
    hv_right_num = 0;

    {
        HTuple end_val6 = (hv_InteRows.TupleLength())-1;
        HTuple step_val6 = 1;
        for (hv_i=0; hv_i.Continue(end_val6, step_val6); hv_i += step_val6)
        {
            if (0 != (HTuple(HTuple(((HTuple(hv_InteRows[hv_i])-hv_centerRow).TupleAbs())>1).TupleAnd((HTuple(hv_InteRows[hv_i])-hv_centerRow)<0)).TupleOr(HTuple(((HTuple(hv_InteRows[hv_i])-hv_centerRow).TupleAbs())<1).TupleAnd((HTuple(hv_InteCols[hv_i])-hv_centerCol)<0))))
            {
                (*hv_NewRows)[0] = HTuple((*hv_NewRows)[0])*hv_left_num;
                (*hv_NewCols)[0] = HTuple((*hv_NewCols)[0])*hv_left_num;
                hv_left_num += 1;
                (*hv_NewRows)[0] = (HTuple((*hv_NewRows)[0])+HTuple(hv_InteRows[hv_i]))/hv_left_num;
                (*hv_NewCols)[0] = (HTuple((*hv_NewCols)[0])+HTuple(hv_InteCols[hv_i]))/hv_left_num;
            }
            else
            {
                (*hv_NewRows)[1] = HTuple((*hv_NewRows)[1])*hv_right_num;
                (*hv_NewCols)[1] = HTuple((*hv_NewCols)[1])*hv_right_num;
                hv_right_num += 1;
                (*hv_NewRows)[1] = (HTuple((*hv_NewRows)[1])+HTuple(hv_InteRows[hv_i]))/hv_right_num;
                (*hv_NewCols)[1] = (HTuple((*hv_NewCols)[1])+HTuple(hv_InteCols[hv_i]))/hv_right_num;
            }
        }
    }
    return;
}

void TopDiameter::PruneMargin(HObject ho_Margin, HObject *ho_MarginPart, HTuple hv_centerRow, HTuple hv_centerCol) {
    // Local iconic variables
    HObject  ho_circle, ho_ErodeMargin, ho_ErodeComps;
    HObject  ho_OpenedComps, ho_SelectedComps;

    // Local control variables
    HTuple  hv_area, hv_selectedCount, hv_DistMins;
    HTuple  hv_DistMaxs, hv_minDist, hv_nearIndex;

    RegionFeatures(ho_Margin, "area", &hv_area);
    if (0 != (hv_area<500))
    {
        (*ho_MarginPart) = ho_Margin;
        return;
    }

    GenCircle(&ho_circle, 5, 5, 1);
    Erosion1(ho_Margin, ho_circle, &ho_ErodeMargin, 1);
    Connection(ho_ErodeMargin, &ho_ErodeComps);
    DilationCircle(ho_ErodeComps, &ho_OpenedComps, 1);

    SelectShape(ho_OpenedComps, &ho_SelectedComps, (HTuple("area").Append("roundness")),
                "and", (HTuple(200).Append(.45)), (HTuple(1000000).Append(2)));

    CountObj(ho_SelectedComps, &hv_selectedCount);
    if (0 != (hv_selectedCount<=0))
    {
        return;
    }

    DistancePRs(ho_SelectedComps, hv_centerRow, hv_centerCol, &hv_DistMins, &hv_DistMaxs);

    hv_minDist = hv_DistMins.TupleFind(hv_DistMins.TupleMin());
    hv_nearIndex = HTuple(hv_minDist[(hv_minDist.TupleLength())-1])+1;
    SelectObj(ho_SelectedComps, &(*ho_MarginPart), hv_nearIndex);

    return;
}

void TopDiameter::ThresholdBorder(HObject ho_Image, HObject *ho_Border, HTuple hv_threshold, HTuple hv_centerRow,
                                  HTuple hv_centerCol) {
    // Local iconic variables
    HObject  ho_ThreshBorders, ho_SelectedBorders;

    // Local control variables
    HTuple  hv_DistMins, hv_DistMaxs, hv_minDist;
    HTuple  hv_nearIndex;

    ThresholdSubPix(ho_Image, &ho_ThreshBorders, hv_threshold);
    SelectShapeXld(ho_ThreshBorders, &ho_SelectedBorders, "contlength", "and", 150,
                   10000000);
    DistancePCs(ho_SelectedBorders, hv_centerRow, hv_centerCol, &hv_DistMins, &hv_DistMaxs);

    hv_minDist = hv_DistMins.TupleFind(hv_DistMins.TupleMin());

    hv_nearIndex = HTuple(hv_minDist[(hv_minDist.TupleLength())-1])+1;
    SelectObj(ho_SelectedBorders, &(*ho_Border), hv_nearIndex);
    return;
}

std::tuple<OvalityMeasures, HObject> TopDiameter::Analyze(const HImage &image) {
    OvalityMeasures measures;

    // Local iconic variables
    HObject  ho_Image, ho_Center, ho_Margin, ho_Border;

    // Local control variables
    HTuple  hv_files, hv_centerRow;
    HTuple  hv_centerCol, hv_contrastThresh, hv_grayIntersect;
    HTuple  hv_minGray, hv_maxGray, hv_t, hv_isClosed, hv_isInside;
    HTuple  hv_area, hv_grayMaxInt, hv__, hv_Diameters;

    hv_centerRow = 0;
    FindImageROI(image, &ho_Image, TopDiameter::Model, &hv_centerRow, &hv_centerCol);
    if (0 != (hv_centerRow==0))
    {
//        if (HDevWindowStack::IsOpen())
//            DispText(HDevWindowStack::GetActive(),"ROI could not be found!", "window",
//                     "top", "left", "black", HTuple(), HTuple());
        return std::tie(measures, ho_Border);
    }
    GenCircle(&ho_Center, hv_centerRow, hv_centerCol, 3);

    hv_contrastThresh = 70;
    ContrastMargin(ho_Image, &ho_Margin, hv_contrastThresh, hv_centerRow, hv_centerCol);
    PruneMargin(ho_Margin, &ho_Margin, hv_centerRow, hv_centerCol);

    hv_grayIntersect = HTuple();
    GrayExtrems(ho_Image, ho_Margin, &hv_minGray, &hv_maxGray);

    {
        HTuple end_val21 = hv_minGray;
        HTuple step_val21 = -1;
        for (hv_t=hv_maxGray; hv_t.Continue(end_val21, step_val21); hv_t += step_val21)
        {
            ThresholdBorder(ho_Image, &ho_Border, hv_t, hv_centerRow, hv_centerCol);
            TestClosedXld(ho_Border, &hv_isClosed);
            if (0 != hv_isClosed)
            {
                TestXldPoint(ho_Border, hv_centerRow, hv_centerCol, &hv_isInside);
                if (0 != hv_isInside)
                {
                    IntersectRegionContour(ho_Margin, ho_Border, &hv_area);
                    hv_grayIntersect[hv_t] = hv_area;
                }
            }
        }
    }

    if (0 != ((hv_grayIntersect.TupleLength())>0))
    {
        if (0 != ((hv_grayIntersect.TupleMax())>0))
        {
            hv_grayMaxInt = hv_grayIntersect.TupleFind(hv_grayIntersect.TupleMax());
            hv_grayMaxInt = HTuple(hv_grayMaxInt[0]).TupleMax2(hv_minGray);

            ThresholdBorder(ho_Image, &ho_Border, hv_grayMaxInt, hv_centerRow, hv_centerCol);
        }
        else
        {
//            if (HDevWindowStack::IsOpen())
//                DispText(HDevWindowStack::GetActive(),"No intesection between Contrast Margin and Threshold Borders!",
//                         "window", "top", "left", "black", HTuple(), HTuple());
            return std::tie(measures, ho_Border);
        }
    }
    else
    {
//        if (HDevWindowStack::IsOpen())
//            DispText(HDevWindowStack::GetActive(),"No Threshold Border containing Center point found!",
//                     "window", "top", "left", "black", HTuple(), HTuple());
        return std::tie(measures, ho_Border);
    }

    AreaCenterXld(ho_Border, &hv__, &hv_centerRow, &hv_centerCol, &hv__);
    Diameters(ho_Border, hv_centerRow, hv_centerCol, 40, &hv_Diameters);

    measures.circleCenter.setXY(hv_centerCol.D(), hv_centerRow.D());
//    measures.radius = hv_FinalRadius.D();
//    measures.score = hv_FinalScore.D();
//    measures.innerRadius = hv_FinalInnerRadius.D();
    measures.diameters = hv_Diameters.DArr();
    measures.diam_num = hv_Diameters.Length();

    return std::tie(measures, ho_Border);
}

