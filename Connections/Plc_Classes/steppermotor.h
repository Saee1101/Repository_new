#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <QObject>
#include "plcmodbusrw.h"
#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <QFile>
class StepperMotor : public QObject
{
    Q_OBJECT
public:
    explicit StepperMotor(QObject *parent = nullptr);
    void JogOn(bool forward);
    void JogOff();
    void ReadMapFromJson(QString address);
    void ReadParamFromDB();
    void SetPlcModbusRW(plcmodbusRW *plc);
    int JogExeAddress,JogDirAddress,JogPulseFreqAddress;
    void SetFreqPulse(int data);
    plcmodbusRW *plcRW;

signals:
};

#endif // STEPPERMOTOR_H
