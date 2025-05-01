#include "machine.h"

Machine::Machine(QObject *parent,plcmodbusRW*m)
    : QObject{parent}
{
    SetDeviceConnection(m);
}

void Machine::setMachineMap(int jacknumber, int steppernumber)
{
    for(int i=0;i<jacknumber;i++)
        jacklist.append(new jack());
    for(int i=0;i<steppernumber;i++)
        motorlist.append(new StepperMotor());
    for(int i=0;i<jacklist.length();i++)
        jacklist.at(i)->SetPlcModbusRW(Device);
    for(int i=0;i<motorlist.length();i++)
        motorlist.at(i)->SetPlcModbusRW(Device);
}

void Machine::ReadMachineConfigFromJson(QStringList JackJsonAddresses, QStringList MotorJsonAddresses)
{
    for(int i=0;i<jacklist.length();i++)
        jacklist.at(i)->ReadMapFromJson(JackJsonAddresses.at(i));
    for(int i=0;i<motorlist.length();i++)
        motorlist.at(i)->ReadMapFromJson(MotorJsonAddresses.at(i));
}

void Machine::SetDeviceConnection(plcmodbusRW *device)
{
    Device=device;

}
