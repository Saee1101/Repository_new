#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>
#include "Plc_Classes/plcmodbusconnect.h"
#include "Plc_Classes/jack.h"
#include "Plc_Classes/steppermotor.h"
#include <QScopedPointer>
class Machine : public QObject
{
    Q_OBJECT
public:
    explicit Machine(QObject *parent,plcmodbusRW*);
    void setMachineMap(int jacknumber,int steppernumber);
    // QVector<QScopedPointer<jack>> jacklist;
    // QVector<QScopedPointer<StepperMotor>> motorlist;
    QVector<jack*> jacklist;
    QVector<StepperMotor*> motorlist;
    void ReadMachineConfigFromJson(QStringList JackJsonAddresses,QStringList MotorJsonAddresses);
    void SetDeviceConnection(plcmodbusRW*device);
    plcmodbusRW*Device;
signals:
};

#endif // MACHINE_H
