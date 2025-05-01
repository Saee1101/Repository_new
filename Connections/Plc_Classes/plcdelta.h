#ifndef PLCDELTA_H
#define PLCDELTA_H

#include <QObject>
#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <QFile>
#include <QSerialPort>
#include <QModbusTcpClient>
#include <QModbusRtuSerialMaster>
#include <QVariant>
class PLCDelta : public QObject
{
    Q_OBJECT
public:
    explicit PLCDelta(QObject *parent = nullptr);
    void PlcMapRegisterFromJson(QJsonDocument document);
    void PlcConnectionConfigFromJson(QString jsonaddress);
    void PlcConnectionInit();
    bool PlcConnectionTry();
    QModbusClient *modbusDevice;
    QVector<QVariant> plcconnectconf;
signals:
};

#endif // PLCDELTA_H
