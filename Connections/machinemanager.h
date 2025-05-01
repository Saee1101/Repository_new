#ifndef MACHINEMANAGER_H
#define MACHINEMANAGER_H

#include <QObject>
#include "machine.h"

class MachineManager : public QObject
{
    Q_OBJECT
public:

    explicit MachineManager(QObject *parent , Machine* machin_);
    Machine* machine;
    void setmachine(Machine* m);
    void SetMachineSenario(int Senario);
    void setrejectjack(int jacknumber);
    int rejectjack;
    void rejectsample();
    struct senario {
        static const int Inspection=0;
        static const int calibration=1;
        static const int systemOff=2;
        static const int setting = 3;
    };
signals:

};

#endif // MACHINEMANAGER_H

