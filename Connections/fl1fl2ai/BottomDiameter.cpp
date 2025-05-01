//
// Created on 3/1/2025.
//

#include "BottomDiameter.h"

HTuple BottomDiameter::Model;
HTuple BottomDiameter::AnisoModel;

BottomDiameter::BottomDiameter() {
    GenInnerModels(220, &BottomDiameter::Model, &BottomDiameter::AnisoModel);
}

void BottomDiameter::Diameters(HObject ho_Contour, HTuple hv_centerRow, HTuple hv_centerCol, HTuple hv_diam_num,
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

void BottomDiameter::FindInnerEdges(HObject ho_Image, HObject *ho_InnerEdge, HTuple hv_Model, HTuple hv_AnisoModel,
                                    HTuple *hv_centerRow, HTuple *hv_centerCol) {
    // Local iconic variables
    HObject  ho_EmphImage, ho_Center;

    // Local control variables
    HTuple  hv_RowCheck, hv_ColumnCheck, hv_AngleCheck;
    HTuple  hv_ScaleCheck, hv_Score, hv_m, hv_MovementOfObject;
    HTuple  hv_MoveAndScaleOfObject, hv_ARowCheck, hv_AColumnCheck;
    HTuple  hv_AAngleCheck, hv_ScaleRCheck, hv_ScaleCCheck;
    HTuple  hv_AScore, hv_AScaleCheck, hv_m2;

    Emphasize(ho_Image, &ho_EmphImage, 7, 7, 1);
    FindScaledShapeModel(ho_EmphImage, hv_Model, 0, 0, 0.3, 3, 0.5, 0, 1, "least_squares",
                         3, 0, &hv_RowCheck, &hv_ColumnCheck, &hv_AngleCheck, &hv_ScaleCheck, &hv_Score);
    if (0 != ((hv_Score.TupleLength())<=0))
    {
        return;
    }
    hv_m = hv_ScaleCheck.TupleFind(hv_ScaleCheck.TupleMin());
    VectorAngleToRigid(0, 0, 0, HTuple(hv_RowCheck[hv_m]), HTuple(hv_ColumnCheck[hv_m]),
                       HTuple(hv_AngleCheck[hv_m]), &hv_MovementOfObject);
    HomMat2dScale(hv_MovementOfObject, HTuple(hv_ScaleCheck[hv_m]), HTuple(hv_ScaleCheck[hv_m]),
                  HTuple(hv_RowCheck[hv_m]), HTuple(hv_ColumnCheck[hv_m]), &hv_MoveAndScaleOfObject);
    AffineTransPoint2d(hv_MoveAndScaleOfObject, 0, 0, &(*hv_centerRow), &(*hv_centerCol));

    GenCircle(&ho_Center, (*hv_centerRow), (*hv_centerCol), 5);
    ChangeDomain(ho_Image, ho_Center, &ho_Image);
    FindAnisoShapeModel(ho_Image, hv_AnisoModel, 0, 0.79, .97, 1.03, .97, 1.03, (hv_Score.TupleMax())-.1,
                        0, 1, "least_squares", 3, 0, &hv_ARowCheck, &hv_AColumnCheck, &hv_AAngleCheck,
                        &hv_ScaleRCheck, &hv_ScaleCCheck, &hv_AScore);

    if (0 != ((hv_AScore.TupleLength())>0))
    {
        hv_AScaleCheck = (hv_ScaleCCheck+hv_ScaleRCheck)/2;
        hv_m2 = hv_AScaleCheck.TupleFind(hv_AScaleCheck.TupleMin());
        if (0 != (HTuple(hv_AScaleCheck[hv_m2])<HTuple(hv_ScaleCheck[hv_m])))
        {
            GetShapeModelContours(&(*ho_InnerEdge), hv_AnisoModel, 1);
            VectorAngleToRigid(0, 0, 0, HTuple(hv_ARowCheck[hv_m2]), HTuple(hv_AColumnCheck[hv_m2]),
                               HTuple(hv_AAngleCheck[hv_m2]), &hv_MovementOfObject);
            HomMat2dScale(hv_MovementOfObject, HTuple(hv_ScaleRCheck[hv_m2]), HTuple(hv_ScaleCCheck[hv_m2]),
                          HTuple(hv_ARowCheck[hv_m2]), HTuple(hv_AColumnCheck[hv_m2]), &hv_MoveAndScaleOfObject);
            AffineTransContourXld((*ho_InnerEdge), &(*ho_InnerEdge), hv_MoveAndScaleOfObject);
            AffineTransPoint2d(hv_MoveAndScaleOfObject, 0, 0, &(*hv_centerRow), &(*hv_centerCol));
            return;
        }
    }

    GetShapeModelContours(&(*ho_InnerEdge), hv_Model, 1);
    AffineTransContourXld((*ho_InnerEdge), &(*ho_InnerEdge), hv_MoveAndScaleOfObject);

    return;
}

void BottomDiameter::GenInnerModels(HTuple hv_radius, HTuple *hv_Model, HTuple *hv_AnisoModel) {
    // Local iconic variables
    HObject  ho_Image, ho_FullDomain, ho_Circle, ho_ROI;

    // Local control variables
    HTuple  hv_imageSize;

    hv_imageSize = (2*hv_radius)+20;

    GenImageConst(&ho_Image, "byte", hv_imageSize, hv_imageSize);
    GetDomain(ho_Image, &ho_FullDomain);
    OverpaintRegion(ho_Image, ho_FullDomain, 50, "fill");
    GenCircle(&ho_Circle, hv_imageSize/2, hv_imageSize/2, hv_radius);
    PaintRegion(ho_Circle, ho_Image, &ho_Image, 100, "fill");

    GenCircle(&ho_ROI, hv_imageSize/2, hv_imageSize/2, hv_radius+5);
    GenCircle(&ho_Circle, hv_imageSize/2, hv_imageSize/2, hv_radius-5);
    Difference(ho_ROI, ho_Circle, &ho_ROI);

    ReduceDomain(ho_Image, ho_ROI, &ho_Image);
    CreateScaledShapeModel(ho_Image, "auto", 0, 0, 0.01, .3, 3, "auto", "none", "use_polarity",
                           30, 10, &(*hv_Model));
    CreateAnisoShapeModel(ho_Image, "auto", 0, 0.79, 0.01, .9, 1.1, "auto", .9, 1.1,
                          "auto", "none", "use_polarity", 30, 10, &(*hv_AnisoModel));

    return;
}

void BottomDiameter::ProcessIntersects(HTuple hv_InteRows, HTuple hv_InteCols, HTuple hv_centerRow, HTuple hv_centerCol,
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

std::tuple<OvalityMeasures, HObject> BottomDiameter::Analyze(const HImage &image) {
    OvalityMeasures measures;

    // Local iconic variables
    HObject  ho_ImageROI, ho_InnerEdge;

    // Local control variables
    HTuple  hv_files, hv_i;
    HTuple  hv_file, hv_centerRow, hv_centerCol, hv_Diameters;

    GenEmptyObj(&ho_ImageROI);
    hv_centerRow = 0;
    FindInnerEdges(image, &ho_InnerEdge, BottomDiameter::Model, BottomDiameter::AnisoModel, &hv_centerRow,
                   &hv_centerCol);

    if (0 != (hv_centerRow==0))
    {
//        if (HDevWindowStack::IsOpen())
//            DispText(HDevWindowStack::GetActive(),"ROI not found!", "window", 0, 0, "black",
//                     HTuple(), HTuple());
        // stop(...); only in hdevelop
        return std::tie(measures, ho_InnerEdge);
    }

    Diameters(ho_InnerEdge, hv_centerRow, hv_centerCol, 40, &hv_Diameters);
    // stop(...); only in hdevelop

    measures.circleCenter.setXY(hv_centerCol.D(), hv_centerRow.D());
//    measures.radius = hv_FinalRadius.D();
//    measures.score = hv_FinalScore.D();
//    measures.innerRadius = hv_FinalInnerRadius.D();
    measures.diameters = hv_Diameters.DArr();
    measures.diam_num = hv_Diameters.Length();

    return std::tie(measures, ho_InnerEdge);
}
