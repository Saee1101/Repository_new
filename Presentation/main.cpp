#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

Business_logic business_logic ;
QString databaseName,databaseType;
void ConnectionDB ()
{
   QSqlDatabase db=QSqlDatabase :: addDatabase(databaseType);
    db.setDatabaseName(databaseName);
    if(!db.open())
    {
        qDebug() << "main.cpp::'Failed to open the database!'";
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


     QString JsonFilePath="DBconnectionconfig.json";
      QFile file(JsonFilePath);

     if(file.open(QIODevice::ReadOnly))
     {
         QByteArray Bytes=file.readAll();
         file.close();

         QJsonParseError JsonError;
         QJsonDocument Document=QJsonDocument::fromJson(Bytes,&JsonError);
         if(JsonError.error != QJsonParseError::NoError)
         {
             qDebug()<<"Error In Json DB";
         }

         if(Document.isObject())
         {
             QJsonObject obj=Document.object();

             databaseType =obj.value("databaseType").toString();
             databaseName =obj.value("databaseName").toString();

         }
     }

     business_logic.entities.m_db.addDatabase(databaseName);
     business_logic.business_db.addDatabase(databaseName);
      ConnectionDB ();
     MainWindow w;
     // w.showFullScreen();
     w.show();

    return a.exec();
}
