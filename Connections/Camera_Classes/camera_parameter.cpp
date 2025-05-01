#include "camera_parameter.h"


Camera_Parameter::Camera_Parameter(QObject *parent) : QObject(parent)
{

}

void Camera_Parameter::Camera_Construction(QString CameraName)
{
    QString result = CameraName ;
    // QStringList result1 = result.split("_");
    // company_name = result1.at(1);
    // QString final = result1.at(0);
    grabber= new HFramegrabber("GigEVision2", 0, 0, 0, 0, 0, 0, "progressive", -1, "default",
                               -1, "false", "default", result.toStdString().c_str(), 0, -1);

    // qDebug() << "brand :" << company_name;
    //    qDebug() << "name :" << final;

}

void Camera_Parameter::Camera_Read_Configuration_From_Json(QString JsonAdress)
{
    QFile file(JsonAdress);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening file!";
    }

    QByteArray fileData = file.readAll();
    file.close();

    // تجزیه JSON
    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    if (doc.isNull()) {
        qDebug() << "Invalid JSON format!";
    }

    QJsonObject jsonObject = doc.object();
    QStringList paramlist_final;

    if (company_name == "IMS" && jsonObject.contains("IMSConfiguration")) {
        QJsonObject imsConfig = jsonObject["IMSConfiguration"].toObject();
        if (imsConfig.contains("ParameterName")) {
            QJsonArray paramNames = imsConfig["ParameterName"].toArray();
            for (const QJsonValue &value : paramNames) {
                paramlist_final.append(value.toString());
            }
        }
    } else if (company_name == "ZDS" && jsonObject.contains("ZDSConfiguration")) {
        QJsonObject zdsConfig = jsonObject["ZDSConfiguration"].toObject();
        if (zdsConfig.contains("ParameterName")) {
            QJsonArray paramNames = zdsConfig["ParameterName"].toArray();
            for (const QJsonValue &value : paramNames) {
                paramlist_final.append(value.toString());
            }
        }
    }

    qDebug() << "Final parameter list for" << company_name << ":" << paramlist_final;
    ParametersNameList = paramlist_final;
}



void Camera_Parameter::Camera_Set_Parameters_List(QStringList ParameterNameList, QVector<QVariant> ParametersValueList)
{
    if (ParameterNameList.size() != ParametersValueList.size()) {
        qDebug() << "Mismatch between parameter names and values!";
        return;
    }
    for (int i = 0; i < ParameterNameList.size(); i++) {
        qDebug() << "parameters values are ::" << ParametersValueList.at(i);
        if (ParametersValueList.at(i).type() == QVariant::Double) {
            grabber->SetFramegrabberParam(ParameterNameList.at(i).toStdString().c_str(), ParametersValueList.at(i).toDouble());
        }
        else if (ParametersValueList.at(i).type() == QVariant::Int){
            grabber->SetFramegrabberParam(ParameterNameList.at(i).toStdString().c_str() , ParametersValueList.at(i).toInt());
        }
        else if (ParametersValueList.at(i).type() == QVariant::String) {
            grabber->SetFramegrabberParam(ParameterNameList.at(i).toStdString().c_str(), ParametersValueList.at(i).toString().toStdString().c_str());
        }
    }
}



HFramegrabber* Camera_Parameter::Camera_Get_Grabber()
{
    return grabber;
}

void Camera_Parameter::Camera_Update_Params(QVector<QVariant> ParameterList)
{
    Camera_Set_Parameters_List(ParametersNameList, ParameterList);
}

void Camera_Parameter::CameraGetParamList(QStringList ParameterNameList)
{
    QVector<QVariant> cameraparamlist;
    for (int i = 0; i < ParameterNameList.size(); i++) {

        cameraparamlist.append(QString::fromStdString(grabber->GetFramegrabberParam(ParameterNameList.at(i).toStdString().c_str()).ToString().Text()));
    }
    send_param = cameraparamlist;
}

void Camera_Parameter::Camera_Get_Params()
{

    CameraGetParamList(ParametersNameList);
}

void Camera_Parameter::SetPlcModbusRW(plcmodbusRW *plc)
{
    device = plc;
}

void Camera_Parameter::Camera_Set_Grabber(HFramegrabber *g)
{
    grabber = g;
}

void Camera_Parameter::Camera_Trigger_Input_Delay_Address(int delayaddress)
{
    cameradelayaddres =delayaddress;
}

void Camera_Parameter::Camera_Set_Delay(int delay)
{
    qDebug()<<"cameradelayadress"<<cameradelayaddres<<" "<<delay;
    device->WriteRegister(cameradelayaddres,delay);
}

