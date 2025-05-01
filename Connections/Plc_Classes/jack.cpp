#include "jack.h"

jack::jack(QObject *parent)
    : QObject{parent}
{}

void jack::JogOn()
{
    plcRW->WriteCoil(JogExeAddress,true);
}

void jack::JogOff()
{
    plcRW->WriteCoil(JogExeAddress,false);
}

void jack::ReadMapFromJson(QString address)
{
    QString val;
    QFile file;
    bool ok;
    file.setFileName(address);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("jack_config"));
    QJsonObject item = value.toObject();
    JogExeAddress = item.value(QString("JogExeAddress")).toString().toInt(&ok,16);
    DelayAddress= item.value(QString("DelayAddress")).toString().toInt(&ok,16);
    TimeDurationAddress=  item.value(QString("TimeDurationAddress")).toString().toInt(&ok,16);
    CycleExeAddress=  item.value(QString("CycleExeAddress")).toString().toInt(&ok,16);
    triggerExeAddress = item.value(QString("triggerExeAddress")).toString().toInt(&ok,16);
}

void jack::SetPlcModbusRW(plcmodbusRW *plc)
{
    plcRW=plc;
}

void jack::SetDelayTime(int data)
{
    plcRW->WriteRegister(DelayAddress,data);
}

void jack::SetTimeDuration(int data)
{
    plcRW->WriteRegister(TimeDurationAddress,data);
}

void jack::CycleExecuteOn()
{
    plcRW->WriteCoil(CycleExeAddress,true);
}

void jack::CycleExecuteOff()
{
    plcRW->WriteCoil(CycleExeAddress,false);
}

void jack::triggerExecuteOn()
{
    plcRW->WriteCoil(triggerExeAddress,true);
}
void jack::triggerExecuteOff()
{
    plcRW->WriteCoil(triggerExeAddress,false);
}
