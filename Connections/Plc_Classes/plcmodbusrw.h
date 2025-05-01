#ifndef PLCMODBUSRW_H
#define PLCMODBUSRW_H

#include <QObject>
#include <QSerialPort>
#include <QModbusTcpClient>
#include <QModbusRtuSerialMaster>
class plcmodbusRW : public QObject
{
    Q_OBJECT
public:
    explicit plcmodbusRW(QObject *parent ,QModbusClient*m);
    void setdevice(QModbusClient *ModbusDevice);
    bool ReadRegisterList(int startaddress, int count);
    bool ReadCoil(int address,int count);
    void WriteCoil(int address,bool data);
    void WriteRegisterList(int startaddress ,QVector<int> data);
    void WriteRegister(int startaddress ,int data);
    QVector<int> readdata;
    QModbusClient *Device;
public slots:
    void OnReadyRead();
signals:
    void senddatavector(QVector<int> datavector);
};

#endif // PLCMODBUSRW_H
