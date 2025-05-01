#include "acmotor.h"

AcMotor::AcMotor(QObject *parent)
    : QObject{parent}
{}

void AcMotor::JogOn(bool forward)
{
    plcRW->WriteCoil(JogDirAddress,forward);
    plcRW->WriteCoil(JogExeAddress,true);
}

void AcMotor::JogOff()
{
    plcRW->WriteCoil(JogExeAddress,false);

}

void AcMotor::ReadMapFromJson(QString address)
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
    QJsonValue value = sett2.value(QString("ACMotor_config"));
    QJsonObject item = value.toObject();
    JogExeAddress = item.value(QString("JogExeAddress")).toString().toInt(&ok,16);
    JogDirAddress= item.value(QString("JogDirAddress")).toString().toInt(&ok,16);
    JogPulseFreqAddress=  item.value(QString("JogPulseFreqAddress")).toString().toInt(&ok,16);
}

void AcMotor::SetPlcModbusRW(plcmodbusRW *plc)
{
    plcRW=plc;

}

void AcMotor::SetFreqPulse(int data)
{
    plcRW->WriteRegister(JogPulseFreqAddress,data);

}
