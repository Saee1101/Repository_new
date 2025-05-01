#include "machinemanager.h"

MachineManager::MachineManager(QObject *parent,Machine*m)
    : QObject{parent}
{
    setmachine(m);
}

void MachineManager::setmachine(Machine *m)
{
    machine = m;
}

void MachineManager::SetMachineSenario(int Senario)
{
    if(Senario==senario::Inspection)
    {
        for(int i=0;i<machine->jacklist.length()-1;i++){
        machine->jacklist.at(i)->CycleExecuteOn();
        }
        machine->Device->WriteCoil(0x815,true);
    }else if(Senario == senario::calibration){
        machine->jacklist.at(0)->CycleExecuteOff();
        machine->jacklist.at(0)->JogOn();
        machine->jacklist.at(1)->JogOn();
        machine->Device->WriteCoil(0x815,true);
    }else if (Senario==senario::systemOff){
        for(int i=0;i<machine->jacklist.length();i++){
        machine->jacklist.at(i)->CycleExecuteOff();
        machine->jacklist.at(i)->JogOff();
        }
        machine->Device->WriteCoil(0x815,false);
    }else{

    }
}

void MachineManager::setrejectjack(int jacknumber)
{
    rejectjack = jacknumber;
}

void MachineManager::rejectsample()
{
    machine->jacklist.at(rejectjack)->triggerExecuteOn();
}
