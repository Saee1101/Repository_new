#include "plcmodbusrw.h"
#include "QDebug"
plcmodbusRW::plcmodbusRW(QObject *parent,QModbusClient* modbusclient)
    : QObject{parent}
{
    setdevice(modbusclient);
}

void plcmodbusRW::setdevice(QModbusClient *ModbusDevice)
{
    Device = ModbusDevice;
}

bool plcmodbusRW::ReadRegisterList(int startaddress, int count)
{
    if (auto *reply = Device->sendReadRequest(QModbusDataUnit(QModbusDataUnit::HoldingRegisters,startaddress,count), 1)) {
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &plcmodbusRW::OnReadyRead);
        else
            delete reply; // broadcast replies return immediately
    } else {
        return false;
    }
    return true;
}

bool plcmodbusRW::ReadCoil(int address,int count)
{
    if (auto *reply = Device->sendReadRequest(QModbusDataUnit(QModbusDataUnit::Coils,address,count), 1)) {
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &plcmodbusRW::OnReadyRead);
        else
            delete reply; // broadcast replies return immediately
    } else {
        return false;
    }
    return true;
}

void plcmodbusRW::WriteCoil(int address ,bool data)
{
    QModbusDataUnit writeUnit(QModbusDataUnit::Coils,address,1);
    writeUnit.setValue(0,data);
    Device->sendWriteRequest(writeUnit,1);
}

void plcmodbusRW::WriteRegisterList(int startaddress,QVector<int> data)
{
    QModbusDataUnit writeUnit1(QModbusDataUnit::HoldingRegisters,startaddress,data.length());

    for (int i=0;i<=data.length();i++) {
        writeUnit1.setValue(i,data.value(i));
    }

    Device->sendWriteRequest(writeUnit1,1);
}

void plcmodbusRW::WriteRegister(int startaddress, int data)
{
    QModbusDataUnit writeUnit1(QModbusDataUnit::HoldingRegisters,startaddress,1);
    writeUnit1.setValue(0,data);
    Device->sendWriteRequest(writeUnit1,1);

}

void plcmodbusRW::OnReadyRead()
{
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        for (qsizetype i = 0, total = unit.valueCount(); i < total; ++i) {
            readdata.push_back(unit.value(i));
        }
        emit senddatavector(readdata);
    } else if (reply->error() == QModbusDevice::ProtocolError) {
        // statusBar()->showMessage(tr("Read response error: %1 (Modbus exception: 0x%2)").
        //                          arg(reply->errorString()).
        //                          arg(reply->rawResult().exceptionCode(), -1, 16), 5000);
    } else {
        // statusBar()->showMessage(tr("Read response error: %1 (code: 0x%2)").
        //                          arg(reply->errorString()).
        //                          arg(reply->error(), -1, 16), 5000);
    }

    reply->deleteLater();
}
