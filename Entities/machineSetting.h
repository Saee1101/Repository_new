#ifndef MACHINESETTING_H
#define MACHINESETTING_H

#include "BaseEntity.h"
#include <QString>
#include <QMetaObject>
#include <QMetaProperty>

class MachineSetting : public BaseEntity
{
    Q_GADGET
    Q_PROPERTY(int id MEMBER id)
    Q_PROPERTY(int sampleId MEMBER sampleId)
    Q_PROPERTY(int liftDelayFl MEMBER liftDelayFl)
    Q_PROPERTY(int liftTimeFl MEMBER liftTimeFl)
    Q_PROPERTY(int liftDelayCl MEMBER liftDelayCl)
    Q_PROPERTY(int liftTimeCl MEMBER liftTimeCl)
    Q_PROPERTY(int cameraDelayFl1 MEMBER cameraDelayFl1)
    Q_PROPERTY(int cameraDelayFl2 MEMBER cameraDelayFl2)
    Q_PROPERTY(int cameraDelayCl MEMBER cameraDelayCl)
    Q_PROPERTY(int pictureCountCl MEMBER pictureCountCl)
    Q_PROPERTY(int cameraIntervalCl MEMBER cameraIntervalCl)
    Q_PROPERTY(int rejectDelay MEMBER rejectDelay)
    Q_PROPERTY(int rejectTime MEMBER rejectTime)


    Q_PROPERTY(double d5Sensitivity MEMBER d5Sensitivity)
    Q_PROPERTY(double d4Sensitivity MEMBER d4Sensitivity)

    Q_PROPERTY(double pixelToMmFl2 MEMBER pixelToMmFl2)
    Q_PROPERTY(double pixelToMmFl1 MEMBER pixelToMmFl1)

    Q_PROPERTY(double clSensitivity MEMBER clSensitivity)
    Q_PROPERTY(double clStage MEMBER clStage)

    Q_PROPERTY(int clRejectStatus MEMBER clRejectStatus)
    Q_PROPERTY(int fl1RejectStatus MEMBER  fl1RejectStatus)
    Q_PROPERTY(int fl2RejectStatus MEMBER fl2RejectStatus)
public:
    // MachineSetting() = default;

    // void fromQuery(const QSqlQuery& query) {
    //     id = query.value("id").toInt();
    //     sampleId = query.value("sample_id").toInt();
    //     liftDelayFl = query.value("lift_delay_fl").toInt();
    //     liftTimeFl = query.value("lift_time_fl").toInt();
    //     liftDelayCl = query.value("lift_delay_cl").toInt();
    //     liftTimeCl = query.value("lift_time_cl").toInt();
    //     cameraDelayFl1 = query.value("camera_delay_fl1").toInt();
    //     cameraDelayFl2 = query.value("camera_delay_fl2").toInt();
    //     cameraDelayCl = query.value("camera_delay_cl").toInt();
    //     pictureCountCl = query.value("picture_count_cl").toInt();
    //     cameraIntervalCl = query.value("camera_interval_cl").toInt();
    //     rejectDelay = query.value("reject_delay").toInt();
    //     rejectTime = query.value("reject_time").toInt();
    //     d5Sensitivity = query.value("d5_sensitivity").toDouble();
    //     d4Sensitivity = query.value("d4_sensitivity").toDouble();
    //     pixelToMmFl2 = query.value("pixel_to_mm_fl2").toDouble();
    //     pixelToMmFl1 = query.value("pixel_to_mm_fl1").toDouble();
    //     clSensitivity = query.value("cl_sensitivity").toDouble();
    //     clStage = query.value("cl_stage").toDouble();
    //     clRejectStatus = query.value("cl_reject_status").toInt();
    //     fl1RejectStatus = query.value("fl1_reject_status").toInt();
    //     fl2RejectStatus = query.value("fl2_reject_status").toInt();
    // }

    // int getId() const { return id; }
    // int getSampleId() const { return sampleId; }
    // int getLiftDelayFl() const { return liftDelayFl; }
    // int getLiftTimeFl() const { return liftTimeFl; }
    // int getLiftDelayCl() const { return liftDelayCl; }
    // int getLiftTimeCl() const { return liftTimeCl; }
    // int getCameraDelayFl1() const { return cameraDelayFl1; }
    // int getCameraDelayFl2() const { return cameraDelayFl2; }
    // int getCameraDelayCl() const { return cameraDelayCl; }
    // int getPictureCountCl() const { return pictureCountCl; }
    // int getCameraIntervalCl() const { return cameraIntervalCl; }
    // int getRejectDelay() const { return rejectDelay; }
    // int getRejectTime() const { return rejectTime; }
    // double getD5Sensitivity() const { return d5Sensitivity; }
    // double getD4Sensitivity() const { return d4Sensitivity; }
    // double getPixelToMmFl2() const { return pixelToMmFl2; }
    // double getPixelToMmFl1() const { return pixelToMmFl1; }
    // double getClSensitivity() const { return clSensitivity; }
    // double getClStage() const { return clStage; }
    // int getClRejectStatus() const { return clRejectStatus; }
    // int getFl1RejectStatus() const { return fl1RejectStatus; }
    // int getFl2RejectStatus() const { return fl2RejectStatus; }

    int id;
    int sampleId;
    int liftDelayFl;
    int liftTimeFl;
    int liftDelayCl;
    int liftTimeCl;
    int cameraDelayFl1;
    int cameraDelayFl2;
    int cameraDelayCl;
    int pictureCountCl;
    int cameraIntervalCl;
    int rejectDelay;
    int rejectTime;
    double d5Sensitivity;
    double d4Sensitivity;
    double pixelToMmFl2;
    double pixelToMmFl1;
    double clSensitivity;
    double clStage;
    int clRejectStatus;
    int fl1RejectStatus;
    int fl2RejectStatus;
   DllImport QVariantMap toVariantMap() const override;
    DllImport void fromQueryAuto(const QSqlQuery& query) override;
//      QVariantMap toVariantMap() const override {
//     QVariantMap map;
//     const QMetaObject& metaObj = staticMetaObject;

//     for (int i = 0; i < metaObj.propertyCount(); ++i) {
//         QMetaProperty prop = metaObj.property(i);
//         map.insert(prop.name(), prop.readOnGadget(this));
//     }

//     return map;
// }

// void fromQueryAuto(const QSqlQuery& query) override {
//     const QMetaObject& metaObj = staticMetaObject;
//     QSqlRecord record = query.record();

//     for (int i = 0; i < metaObj.propertyCount(); ++i) {
//         QMetaProperty prop = metaObj.property(i);
//         int idx = record.indexOf(prop.name());
//         if (idx != -1) {
//             QVariant val = query.value(idx);
//             prop.writeOnGadget(this, val);
//         }
//     }
// }
};

#endif // MACHINESETTING_H
