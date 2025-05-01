#include "plcdelta.h"

PLCDelta::PLCDelta(QObject *parent)
    : QObject{parent}
{}

void PLCDelta::PlcMapRegisterFromJson(QJsonDocument document)
{

}

void PLCDelta::PlcConnectionConfigFromJson(QString jsonaddress)
{

    QString val;
    QFile file;
    file.setFileName(jsonaddress);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("plcconnectionconfig"));
    QJsonObject item = value.toObject();

    plcconnectconf.push_back(item.value(QString("COMname")).toString());
    plcconnectconf.push_back(item.value(QString("SerialParityParameter")).toInt());
    plcconnectconf.push_back(item.value(QString("SerialBaudRateParameter")).toInt());
    plcconnectconf.push_back(item.value(QString("SerialDataBitsParameter")).toInt());
    plcconnectconf.push_back(item.value(QString("SerialStopBitsParameter")).toInt());
    plcconnectconf.push_back(item.value(QString("settimeout")).toInt());
    plcconnectconf.push_back(item.value(QString("setNumberOfRetries")).toInt());
}

void PLCDelta::PlcConnectionInit()
{
    modbusDevice = new QModbusRtuSerialMaster(this);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                         plcconnectconf.at(0).toString());
    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
                                         plcconnectconf.at(1).toInt());
    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                                         plcconnectconf.at(2).toInt());
    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                                         plcconnectconf.at(3).toInt());
    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                                         plcconnectconf.at(4).toInt());
    modbusDevice->setTimeout(plcconnectconf.at(5).toInt());
    modbusDevice->setNumberOfRetries(plcconnectconf.at(6).toInt());
}

bool PLCDelta::PlcConnectionTry()
{
   return modbusDevice->connectDevice();
}
