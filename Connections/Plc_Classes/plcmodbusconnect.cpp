#include "plcmodbusconnect.h"
#include "QDebug"
plcmodbusconnect::plcmodbusconnect(QObject *parent)
    : QObject{parent}
{}

void plcmodbusconnect::PlcConnectionConfigFromJson(QString jsonaddress)
{
    QString val;
    QFile file;
    plcconnectconf.clear();
    file.setFileName(jsonaddress);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<"PlcConnectionConfigFromJson can not open !";
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
    for(int i=0;i<plcconnectconf.length();i++)
        qDebug()<<plcconnectconf.at(i);
}

bool plcmodbusconnect::PlcConnectionInit()
{
    if(connectionstateFLG==false){
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
    if(modbusDevice->connectDevice()){
        qDebug()<<"1device is connect";
        connectionstateFLG=true;
    return true;
    }
    else{
        qDebug()<<"2device not connect";
        return false;
    }}else{
        return true;
        qDebug()<<"3device is connect";
    }

}

void plcmodbusconnect::PlcDisConnect()
{
    modbusDevice->disconnectDevice();
}

bool plcmodbusconnect::PlcReconnection()
{
    if(modbusDevice->connectDevice()){
        qDebug()<<"device is connect";
        return true;
    }
    else{
        qDebug()<<"device not connect";
        return false;
    }
}

QModbusClient* plcmodbusconnect::getdevice()
{
    return modbusDevice;
}
