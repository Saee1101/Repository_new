#include "flai.h"
#include "QDebug"
#include "QElapsedTimer"

FLAI::FLAI(QObject *parent)
    : QObject{parent}
{}


void FLAI::getImage(HImage *rawImage)
{
     // mutex->lock();
    qDebug()<<"fl2imagerecived";


    QElapsedTimer timer;
    timer.start();

    InputImage=*rawImage;
    InputImage.WriteImage("tiff",0,"fl1last");
    HObject border;
    if (topbottonflg)
        try{
    std::tie(oval, border) = bottomDiameter.Analyze(InputImage);
    } catch (...)
        {

    }

    else{
        try{
        std::tie(oval, border) = topDiameter.Analyze(InputImage);
        }catch (...)
        {

        }
    }
    // double * results = oval1.diameters;
    //    QVector <double> Results;
    // // QVector<double> Results = QVector<double>::fromStdVector(std::vector<double>(results, results + oval1.diam_num));
    // // QVector<double> Results = QVector<double>::fromStdVector(std::vector<double>(results, results + oval1.diam_num));
    //    for (int i=0;i<oval1.diam_num;i++)
    //        Results.append(results[i]);
    // /// MIN

    // auto min=std::min_element(Results.constBegin(),Results.constEnd());
    // double firstmin=*min;
    // double MIN=firstmin;
    // /// MAX
    //   qDebug()<<"Imagerecived";
    // auto max=std::max_element(Results.constBegin(),Results.constEnd());
    // double firstmax=*max;
    // double  MAX=firstmax;
    resultImage =InputImage;
    qDebug()<<"fl2imagesendsorheresdddddddddddd";

    if(oval.diam_num>0){
        qDebug()<<"fl2imagesendsorhere";
        std::vector<double> sortedVec(oval.diameters,oval.diameters+oval.diam_num) ;
        std::sort(sortedVec.begin(), sortedVec.end());
        // resultImage=circleDiameter.getImage(border, InputImage);
        double minAvg = std::accumulate(sortedVec.begin()+1, sortedVec.begin() + 6, 0.0) / 5.0;
        double maxAvg = std::accumulate(sortedVec.end() - 3, sortedVec.end(), 0.0) / 3.0;

        emit sendresults(&resultImage,minAvg,maxAvg);
    }else
    {
       qDebug()<<"fl2imagesendshere";
        emit sendresults(&resultImage,0,0);
    }
    qDebug()<<"top or bottom"<<topbottonflg<<"time:"<<timer.elapsed();

    // mutex->unlock();

}
