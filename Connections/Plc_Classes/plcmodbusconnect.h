#ifndef PLCMODBUSCONNECT_H
#define PLCMODBUSCONNECT_H

#include <QObject>
#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <QFile>
#include <QSerialPort>
#include <QModbusTcpClient>
#include <QModbusRtuSerialMaster>
#include <QVariant>
class plcmodbusconnect : public QObject
{
    Q_OBJECT
public:
    explicit plcmodbusconnect(QObject *parent = nullptr);
    void PlcConnectionConfigFromJson(QString jsonaddress);
    bool PlcConnectionInit();
    void PlcDisConnect();
    bool PlcReconnection();
    bool connectionstateFLG=false;
    QModbusClient* getdevice();
    QModbusClient *modbusDevice;
    QVector<QVariant> plcconnectconf;
signals:
};

#endif // PLCMODBUSCONNECT_H
