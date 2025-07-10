#ifndef USER_H
#define USER_H
#define DllImport   __declspec( dllimport )
#include "BaseEntity.h"
#include <QString>
#include <QMetaObject>
#include <QMetaProperty>

class User : public BaseEntity
{
    Q_GADGET
    Q_PROPERTY(int id MEMBER id)
    Q_PROPERTY(QString user_name MEMBER userName)
     Q_PROPERTY(QString password MEMBER passWord)
    Q_PROPERTY(QString developer_password MEMBER developerPassword)
public:
    // User() = default;

    // void fromQuery(const QSqlQuery& query) {
    //     id = query.value("id").toInt();
    //     userName = query.value("user_name").toString();
    //     password = query.value("password").toString();
    //     developerPassword = query.value("developer_password").toString();
    // }

    // int getId() const { return id; }
    // QString getUserName() const { return userName; }
    // QString getPassword() const { return password; }
    // QString getDeveloperPassword() const { return developerPassword; }


    int id;
    QString userName;
    QString passWord;
    QString developerPassword;
    DllImport QVariantMap toVariantMap() const override;
    // QMap<QString, QVariant> toVariantMap() const override;
     DllImport void fromQueryAuto(const QSqlQuery& query) override;
//  QVariantMap toVariantMap() const override {
//         QVariantMap map;
//         const QMetaObject& metaObj = staticMetaObject;

//         for (int i = 0; i < metaObj.propertyCount(); ++i) {
//             QMetaProperty prop = metaObj.property(i);
//             map.insert(prop.name(), prop.readOnGadget(this));
//         }

//         return map;
//     }

// void fromQueryAuto(const QSqlQuery& query) override {
//         const QMetaObject& metaObj = staticMetaObject;
//         QSqlRecord record = query.record();

//         for (int i = 0; i < metaObj.propertyCount(); ++i) {
//             QMetaProperty prop = metaObj.property(i);
//             int idx = record.indexOf(prop.name());
//             if (idx != -1) {
//                 QVariant val = query.value(idx);
//                 prop.writeOnGadget(this, val);
//             }
//         }
//     }


};

Q_DECLARE_METATYPE(User)
#endif // USER_H

