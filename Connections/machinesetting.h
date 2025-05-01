#ifndef MACHINESETTING_H
#define MACHINESETTING_H

#include <QObject>
#include "machine.h"
class MachineSetting_con : public QObject
{
    Q_OBJECT
public:
    explicit MachineSetting_con(QObject *parent ,Machine* machine_);
    Machine *machine;
    void setmachine(Machine* m);
    void UpdateJackSetting(int jacknimber,double delayjack,double jacktime);
    void UpdateMotorSetting(int Motornumber,double motorspeed);
    void JackJogTest(int jacknumber,bool Direction);
    void JackCycleState(int jacknumber,bool EXC);
    void JackTriggerState(int jacknumber,bool EXC);
    void MotorState(int Motornumber,bool DIrection,bool OnOff);

signals:
};

#endif // MACHINESETTING_H
