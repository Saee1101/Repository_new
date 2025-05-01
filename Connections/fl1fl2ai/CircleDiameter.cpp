//
// Created by Newo on 9/20/2023.
//

#include "CircleDiameter.h"
#include "Constants.h"

using namespace HalconCpp;

HTuple CircleDiameter::top_Model;
HTuple CircleDiameter::bottom_Model;

CircleDiameter::CircleDiameter() {
    HObject  ho_OuterCircle, ho_Outside, ho_InnerCircle, ho_SynthImage, ho_ROI, ho_ROI1, ho_ROI2;

    // Local control variables
    HTuple  hv_RadiusCircle, hv_SizeSynthImage;
    HTuple  hv_j, hv_MovementOfObject, hv_MoveAndScaleOfObject;

    hv_SizeSynthImage = (2*consts::circul::top::MODEL_CIRCLE_RADIUS)+10;
    GenEllipseContourXld(&ho_OuterCircle, hv_SizeSynthImage / 2, hv_SizeSynthImage / 2, 0, consts::circul::top::MODEL_CIRCLE_RADIUS,
                         consts::circul::top::MODEL_CIRCLE_RADIUS, 0, 6.28318, "positive", 1.5);
    GenEllipseContourXld(&ho_InnerCircle, hv_SizeSynthImage/2, hv_SizeSynthImage/2,
                         0, consts::circul::bottom::MODEL_CIRCLE_RADIUS, consts::circul::bottom::MODEL_CIRCLE_RADIUS, 0, 6.28318, "positive", 1.5);
    GenImageConst(&ho_SynthImage, "byte", hv_SizeSynthImage, hv_SizeSynthImage);
    PaintXld(ho_OuterCircle, ho_SynthImage, &ho_SynthImage, 50);
    PaintXld(ho_InnerCircle, ho_SynthImage, &ho_SynthImage, 100);

    GenCircle(&ho_ROI1, hv_SizeSynthImage/2, hv_SizeSynthImage/2, consts::circul::top::MODEL_CIRCLE_RADIUS+5);
    GenCircle(&ho_ROI2, hv_SizeSynthImage/2, hv_SizeSynthImage/2, consts::circul::top::MODEL_CIRCLE_RADIUS-5);
    Difference(ho_ROI1, ho_ROI2, &ho_ROI);
    ReduceDomain(ho_SynthImage, ho_ROI, &ho_SynthImage);
    CreateScaledShapeModel(ho_SynthImage, "auto", 0, 0, 0.01, consts::circul::top::MIN_SHAPE_SCALE,
                           consts::circul::top::MAX_SHAPE_SCALE, "auto", "none",
                           "use_polarity", 30, 10, &top_Model);

    GenCircle(&ho_ROI1, hv_SizeSynthImage/2, hv_SizeSynthImage/2, consts::circul::bottom::MODEL_CIRCLE_RADIUS+5);
    GenCircle(&ho_ROI2, hv_SizeSynthImage/2, hv_SizeSynthImage/2, consts::circul::bottom::MODEL_CIRCLE_RADIUS-5);
    Difference(ho_ROI1, ho_ROI2, &ho_ROI);
    ChangeDomain(ho_SynthImage, ho_ROI, &ho_SynthImage);
    CreateScaledShapeModel(ho_SynthImage, "auto", 0, 0, 0.01, consts::circul::bottom::MIN_SHAPE_SCALE,
                           consts::circul::bottom::MAX_SHAPE_SCALE, "auto", "none",
                           "use_polarity", 30, 10, &bottom_Model);

}

OvalityMeasures CircleDiameter::topAnalyze(const HalconCpp::HImage &image) {
    // Local iconic variables
    HObject  ho_Image, ho_EmphImage, ho_ROI, ho_ImageROI, ho_Edges, ho_UnionContours, ho_SelectedContours;
    HObject ho_UnionRegions, ho_Convexes, ho_CurrentConvex, ho_SelectedConvexes, ho_FinalConvex, ho_FinalContour;
    HObject ho_FinalConvexRegion, ho_PointsRegion, ho_FinalCircle, ho_FinalInnerRegion;

    // Local control variables
    HTuple hv_RowCheck, hv_ColumnCheck, hv_AngleCheck, hv_ScaleCheck, hv_Score;
    HTuple hv_m, hv_Circularity, hv_AreaDivCirc, hv_circ_count, hv_Circles, hv_Indexes, hv_j, hv_CurArea;
    HTuple hv_Radius, hv_StartPhi, hv_EndPhi, hv_PointOrder, hv_Row, hv_Column;
    HTuple hv_Number, hv_Area, hv_min_Area, hv_minIndex, hv__;
    HTuple hv_FinalScore, hv_FinalRow, hv_FinalColumn, hv_FinalRadius;
    HTuple hv_Rows, hv_Cols, hv_FinalInnerRadius, hv_Diameters;

    Emphasize(image, &ho_EmphImage, 7, 7, 1);
    FindScaledShapeModel(ho_EmphImage, top_Model, 0, 0, consts::circul::top::MIN_SHAPE_SCALE, consts::circul::top::MAX_SHAPE_SCALE,
                         consts::circul::top::MIN_SHAPE_SCORE, 0, 1, "least_squares",
                         3, 0, &hv_RowCheck, &hv_ColumnCheck, &hv_AngleCheck, &hv_ScaleCheck, &hv_Score);

    OvalityMeasures measures;
    measures.radius = 0;
    measures.score = 0;
    measures.circleCenter.setXY(0, 0);
    measures.diameters = nullptr;
    measures.diam_num = 0;

    if (hv_ScaleCheck.TupleLength() <= 0)
        return measures;

    hv_m = hv_ScaleCheck.TupleFind(hv_ScaleCheck.TupleMax());
    GenCircle(&ho_ROI, HTuple(hv_RowCheck[hv_m]), HTuple(hv_ColumnCheck[hv_m]),
              consts::circul::top::MODEL_CIRCLE_RADIUS*HTuple(hv_ScaleCheck[hv_m]));
    ReduceDomain(ho_EmphImage, ho_ROI, &ho_ImageROI);

    EdgesSubPix(ho_ImageROI, &ho_Edges, "deriche1", 1, 20, 80);
    SelectShapeXld(ho_Edges, &ho_SelectedContours, "contlength", "and", 100, 200000);
    UnionCotangentialContoursXld(ho_SelectedContours, &ho_UnionContours, 5, 30, HTuple(45).TupleRad(),
                                 40, 10, 20, "attr_forget");
    ShapeTransXld(ho_UnionContours, &ho_Convexes, "convex");
    CircularityXld(ho_Convexes, &hv_Circularity);
    hv_AreaDivCirc = HTuple(hv_Circularity.TupleLength(),HTuple(10).TuplePow(10));
    hv_circ_count = 0;

    for (hv_j=0; hv_j < hv_Circularity.TupleLength(); hv_j += 1)
        if (HTuple(hv_Circularity[hv_j]) > .7)
        {
            SelectObj(ho_Convexes, &ho_CurrentConvex, hv_j+1);
            AreaCenterXld(ho_CurrentConvex, &hv_CurArea, &hv_Row, &hv_Column, &hv_PointOrder);
            hv_AreaDivCirc[hv_j] = hv_CurArea / HTuple(hv_Circularity[hv_j]);
            hv_circ_count += 1;
        }

    if ( hv_circ_count <= 0)
        return measures;


    hv_min_Area = hv_AreaDivCirc.TupleMin();
    hv_minIndex = hv_AreaDivCirc.TupleFind(hv_min_Area);

    SelectObj(ho_UnionContours, &ho_FinalContour, hv_minIndex+1);
    SelectObj(ho_Convexes, &ho_FinalConvex, hv_minIndex+1);

    GenRegionContourXld(ho_FinalConvex, &ho_FinalConvexRegion, "margin");
    Roundness(ho_FinalConvexRegion, &hv__, &hv__, &hv_FinalScore, &hv__);

    FitCircleContourXld(ho_FinalContour, "geometric", -1, 0, 0, 3, 2, &hv_FinalRow,
                        &hv_FinalColumn, &hv_FinalRadius, &hv_StartPhi, &hv_EndPhi, &hv_PointOrder);
    GenCircle(&ho_FinalCircle, hv_FinalRow, hv_FinalColumn, hv_FinalRadius);

    GetContourXld(ho_FinalContour, &hv_Rows, &hv_Cols);
    GenRegionPoints(&ho_PointsRegion, hv_Rows, hv_Cols);
    Difference(ho_FinalCircle, ho_PointsRegion, &ho_FinalInnerRegion);
    InnerCircle(ho_FinalInnerRegion, &hv_Row, &hv_Column, &hv_FinalInnerRadius);

    Diameters(ho_FinalContour, hv_FinalRow, hv_FinalColumn, 40, &hv_Diameters);

    measures.circleCenter.setXY(hv_FinalColumn.D(), hv_FinalRow.D());
    measures.radius = hv_FinalRadius.D();
    measures.score = hv_FinalScore.D();
    measures.innerRadius = hv_FinalInnerRadius.D();
    measures.diameters = hv_Diameters.DArr();
    measures.diam_num = hv_Diameters.Length();

    return measures;
}

int CircleDiameter::findBestCircle(const HTuple &RowCheck, const HTuple &ColumnCheck, const HTuple &ScaleCheck, const HTuple &Score) {
    int selectedIndex = 0;
    for (int i = 1; i < Score.TupleLength(); ++i)
        if (Score[0].D() - Score[i].D() < consts::circul::top::MAX_SCORE_DEVIA &&
            std::abs(RowCheck[0].D() - RowCheck[i].D()) < consts::circul::top::MAX_COORD_DEVIA &&
            std::abs(ColumnCheck[0].D() - ColumnCheck[i].D()) < consts::circul::top::MAX_COORD_DEVIA &&
            ScaleCheck[0].D() > ScaleCheck[i].D())
            selectedIndex = i;

    return selectedIndex;
}

OvalityMeasures CircleDiameter::bottomAnalyze(const HalconCpp::HImage &image) {
    // Local iconic variables
    HObject ho_Image, ho_ROI, ho_ROI1, ho_ROI2, ho_ImageROI;
    HObject ho_Edges, ho_Edge, ho_EdgesRegion, ho_Region, ho_InnerRegion;

    // Local control variables
    HTuple hv_RowCheck, hv_ColumnCheck, hv_AngleCheck, hv_ScaleCheck, hv_Score;
    HTuple hv_Indexes, hv_HighScore, hv_min_Scale, hv_minIndex, hv_j, hv_RadiusCircle = 150;
    HTuple hv_expandPixel, hv_EdgeNum, hv_EdgeRows, hv_EdgeCols, hv_i, hv_Rows, hv_Cols;
    HTuple hv_InnerRadius, hv_Row, hv_Col;

    ho_Image = image;
    FindScaledShapeModel(ho_Image, bottom_Model, 0, 0, consts::circul::bottom::MIN_SHAPE_SCALE, consts::circul::bottom::MAX_SHAPE_SCALE,
                         consts::circul::bottom::MIN_SHAPE_SCORE, 0, 1, "least_squares",
                         3, 0, &hv_RowCheck, &hv_ColumnCheck, &hv_AngleCheck, &hv_ScaleCheck, &hv_Score);

    OvalityMeasures measures;
    measures.radius = 0;
    measures.innerRadius = 0;
    measures.score = 0;
    measures.circleCenter.setXY(0, 0);

    if (hv_Score.TupleLength()>0)
    {
        hv_min_Scale = hv_ScaleCheck.TupleMin();
        hv_j = hv_ScaleCheck.TupleFind(hv_min_Scale);
        hv_expandPixel = 5;
        GenCircle(&ho_ROI1, HTuple(hv_RowCheck[hv_j]), HTuple(hv_ColumnCheck[hv_j]),
                  (consts::circul::bottom::MODEL_CIRCLE_RADIUS*HTuple(hv_ScaleCheck[hv_j]))+hv_expandPixel);
        GenCircle(&ho_ROI2, HTuple(hv_RowCheck[hv_j]), HTuple(hv_ColumnCheck[hv_j]),
                  (consts::circul::bottom::MODEL_CIRCLE_RADIUS*HTuple(hv_ScaleCheck[hv_j]))-(2*hv_expandPixel));
        Difference(ho_ROI1, ho_ROI2, &ho_ROI);
        ReduceDomain(ho_Image, ho_ROI, &ho_ImageROI);
        EdgesSubPix(ho_ImageROI, &ho_Edges, "sobel", 1, 1, 40);

        CountObj(ho_Edges, &hv_EdgeNum);
        hv_EdgeRows = HTuple();
        hv_EdgeCols = HTuple();
        {
            HTuple end_val54 = hv_EdgeNum;
            HTuple step_val54 = 1;
            for (hv_i=1; hv_i.Continue(end_val54, step_val54); hv_i += step_val54)
            {
                SelectObj(ho_Edges, &ho_Edge, hv_i);
                GetContourXld(ho_Edge, &hv_Rows, &hv_Cols);
                hv_EdgeRows = hv_EdgeRows.TupleConcat(hv_Rows);
                hv_EdgeCols = hv_EdgeCols.TupleConcat(hv_Cols);
            }
        }
        GenRegionPoints(&ho_EdgesRegion, hv_EdgeRows, hv_EdgeCols);
        GenCircle(&ho_Region, HTuple(hv_RowCheck[hv_j]), HTuple(hv_ColumnCheck[hv_j]),
                  consts::circul::bottom::MODEL_CIRCLE_RADIUS*HTuple(hv_ScaleCheck[hv_j]));

        Difference(ho_Region, ho_EdgesRegion, &ho_InnerRegion);
        InnerCircle(ho_InnerRegion, &hv_Row, &hv_Col, &hv_InnerRadius);


        measures.circleCenter.setXY(hv_ColumnCheck[hv_j].D(), hv_RowCheck[hv_j].D());
        measures.radius = consts::circul::bottom::MODEL_CIRCLE_RADIUS * hv_ScaleCheck[hv_j].D();
        measures.innerRadius = hv_InnerRadius.D();
        measures.score = hv_Score[hv_j].D();
    }

    return measures;
}

void CircleDiameter::Diameters (HObject ho_Contour, HTuple hv_centerRow, HTuple hv_centerCol, HTuple hv_diam_num,
                HTuple *hv_Diameters)
{

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

    if (HDevWindowStack::IsOpen())
        hv_WindowHandle = HDevWindowStack::GetActive();

    (*hv_Diameters) = HTuple();
    {
        HTuple end_val9 = hv_diam_num-1;
        HTuple step_val9 = 1;
        for (hv_i=0; hv_i.Continue(end_val9, step_val9); hv_i += step_val9)
        {
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
            }
        }
    }

    if (HDevWindowStack::IsOpen())
        SetColored(HDevWindowStack::GetActive(),12);
    return;
}

void CircleDiameter::ProcessIntersects (HTuple hv_InteRows, HTuple hv_InteCols, HTuple hv_centerRow,
                        HTuple hv_centerCol, HTuple *hv_NewRows, HTuple *hv_NewCols)
{

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

HalconCpp::HImage CircleDiameter::getImage(const OvalityMeasures &oval, HalconCpp::HImage &image)
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

void CircleDiameter::drawOvalityMeasure(const OvalityMeasures &oval, const HImage &image)
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

void CircleDiameter::drawPoint(double x, double y, int size, int color)
{
    setColor(color);
    window.SetLineWidth(size);
    window.DispCircle(y, x, size);
}

void CircleDiameter::drawCircle(const Point &center, double radius, int lineWidth, int color)
{
    setColor(color);
    window.SetLineWidth(lineWidth);
    window.SetDraw("margin");
    window.DispCircle(center.getY(), center.getX(), radius);
}

void CircleDiameter::setColor(int color)
{
    HTuple colors = window.QueryColor();
    window.SetColor(colors[color % colors.Length()].C());
}
