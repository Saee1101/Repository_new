#include "machinesetting.h"

MachineSetting_con::MachineSetting_con(QObject *parent,Machine*m)
    : QObject{parent}
{
    setmachine(m);
}

void MachineSetting_con::setmachine(Machine *m)
{
    machine = m;
}

void MachineSetting_con::UpdateJackSetting(int jacknimber, double delayjack, double jacktime)
{
    qDebug()<<"177"<<delayjack;
    machine->jacklist.at(jacknimber)->SetDelayTime(delayjack);
    machine->jacklist.at(jacknimber)->SetTimeDuration(jacktime);

}

void MachineSetting_con::UpdateMotorSetting(int Motornumber, double motorspeed)
{
    machine->motorlist.at(Motornumber)->SetFreqPulse(motorspeed);
}

void MachineSetting_con::JackJogTest(int jacknumber, bool Direction)
{
    if(Direction)
        machine->jacklist.at(jacknumber)->JogOn();
    else
        machine->jacklist.at(jacknumber)->JogOff();
}

void MachineSetting_con::JackCycleState(int jacknumber, bool EXC)
{
    if(EXC)
        machine->jacklist.at(jacknumber)->CycleExecuteOn();
    else
        machine->jacklist.at(jacknumber)->CycleExecuteOff();
}

void MachineSetting_con::JackTriggerState(int jacknumber, bool EXC)
{
    if(EXC)
        machine->jacklist.at(jacknumber)->triggerExecuteOn();
    else
        machine->jacklist.at(jacknumber)->triggerExecuteOff();
}

void MachineSetting_con::MotorState(int Motornumber, bool DIrection, bool OnOff)
{
    if(OnOff)
        machine->motorlist.at(Motornumber)->JogOn(DIrection);
     else
        machine->motorlist.at(Motornumber)->JogOff();

}
