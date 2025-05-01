#ifndef MACHINESETTING_H
#define MACHINESETTING_H

#include <QString>
#include <QSqlQuery>

class MachineSetting
{
public:
    MachineSetting() = default;

    void fromQuery(const QSqlQuery& query) {
        id = query.value("id").toInt();
        sampleId = query.value("sample_id").toInt();
        liftDelayFl = query.value("lift_delay_fl").toInt();
        liftTimeFl = query.value("lift_time_fl").toInt();
        liftDelayCl = query.value("lift_delay_cl").toInt();
        liftTimeCl = query.value("lift_time_cl").toInt();
        cameraDelayFl1 = query.value("camera_delay_fl1").toInt();
        cameraDelayFl2 = query.value("camera_delay_fl2").toInt();
        cameraDelayCl = query.value("camera_delay_cl").toInt();
        pictureCountCl = query.value("picture_count_cl").toInt();
        cameraIntervalCl = query.value("camera_interval_cl").toInt();
        rejectDelay = query.value("reject_delay").toInt();
        rejectTime = query.value("reject_time").toInt();
        d5Sensitivity = query.value("d5_sensitivity").toDouble();
        d4Sensitivity = query.value("d4_sensitivity").toDouble();
        pixelToMmFl2 = query.value("pixel_to_mm_fl2").toDouble();
        pixelToMmFl1 = query.value("pixel_to_mm_fl1").toDouble();
        clSensitivity = query.value("cl_sensitivity").toDouble();
        clStage = query.value("cl_stage").toDouble();
        clRejectStatus = query.value("cl_reject_status").toInt();
        fl1RejectStatus = query.value("fl1_reject_status").toInt();
        fl2RejectStatus = query.value("fl2_reject_status").toInt();
    }

    int getId() const { return id; }
    int getSampleId() const { return sampleId; }
    int getLiftDelayFl() const { return liftDelayFl; }
    int getLiftTimeFl() const { return liftTimeFl; }
    int getLiftDelayCl() const { return liftDelayCl; }
    int getLiftTimeCl() const { return liftTimeCl; }
    int getCameraDelayFl1() const { return cameraDelayFl1; }
    int getCameraDelayFl2() const { return cameraDelayFl2; }
    int getCameraDelayCl() const { return cameraDelayCl; }
    int getPictureCountCl() const { return pictureCountCl; }
    int getCameraIntervalCl() const { return cameraIntervalCl; }
    int getRejectDelay() const { return rejectDelay; }
    int getRejectTime() const { return rejectTime; }
    double getD5Sensitivity() const { return d5Sensitivity; }
    double getD4Sensitivity() const { return d4Sensitivity; }
    double getPixelToMmFl2() const { return pixelToMmFl2; }
    double getPixelToMmFl1() const { return pixelToMmFl1; }
    double getClSensitivity() const { return clSensitivity; }
    double getClStage() const { return clStage; }
    int getClRejectStatus() const { return clRejectStatus; }
    int getFl1RejectStatus() const { return fl1RejectStatus; }
    int getFl2RejectStatus() const { return fl2RejectStatus; }

public:
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
};

#endif // MACHINESETTING_H
