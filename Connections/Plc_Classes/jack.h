#ifndef JACK_H
#define JACK_H

#include <QObject>
#include "plcmodbusrw.h"
#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <QFile>
class jack : public QObject
{
    Q_OBJECT
public:
    explicit jack(QObject *parent = nullptr);
    void JogOn();
    void JogOff();
    void ReadMapFromJson(QString address);
    void ReadParamFromDB();
    void SetPlcModbusRW(plcmodbusRW *plc);
    int JogExeAddress,DelayAddress,TimeDurationAddress,CycleExeAddress,triggerExeAddress;
    void SetDelayTime(int data);
    void SetTimeDuration(int data);
    void CycleExecuteOn();
    void CycleExecuteOff();
    void triggerExecuteOn();
    void triggerExecuteOff();
    plcmodbusRW *plcRW;

signals:
};

#endif // JACK_H
