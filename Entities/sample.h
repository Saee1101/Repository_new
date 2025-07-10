#ifndef SAMPLE_H
#define SAMPLE_H

#include "BaseEntity.h"
#include <QString>
#include <QMetaObject>
#include <QMetaProperty>

class Sample: public BaseEntity
{
    Q_GADGET
    Q_PROPERTY(int id MEMBER id)
    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(double diamiter_min_fl2 MEMBER diamiter_min_fl2)
    Q_PROPERTY(double diamiter_max_fl2 MEMBER diamiter_max_fl2)
    Q_PROPERTY(double d5Ovality MEMBER d5Ovality)
    Q_PROPERTY(double d5 MEMBER d5)
    Q_PROPERTY(double d4 MEMBER d4)
    Q_PROPERTY(double diamiter_min_fl1 MEMBER diamiter_min_fl1)
    Q_PROPERTY(double diamiter_max_fl1 MEMBER diamiter_max_fl1)
    Q_PROPERTY(double d4Ovality MEMBER d4Ovality)
    Q_PROPERTY(int selected MEMBER selected)

public:

    // Sample() = default;

    // void fromQuery(const QSqlQuery& query) {
    //     id = query.value("id").toInt();
    //     name = query.value("name").toString();
    //     diamiter_min_fl2 = query.value("diamiter_min_fl2").toDouble();
    //     diamiter_max_fl2 = query.value("diamiter_max_fl2").toDouble();
    //     d5Ovality = query.value("d5_ovality").toDouble();
    //     d5 = query.value("d5").toDouble();
    //     d4 = query.value("d4").toDouble();
    //     diamiter_min_fl1 = query.value("diamiter_min_fl1").toDouble();
    //     diamiter_max_fl1 = query.value("diamiter_max_fl1").toDouble();
    //     d4Ovality = query.value("d4_ovality").toDouble();
    //     selected=query.value("selected").toInt();
    // }

    // int getId() const { return id; }
    // QString getName() const { return name; }
    // double getdiamiter_min_fl2() const { return diamiter_min_fl2; }
    // double getdiamiter_max_fl2() const { return diamiter_max_fl2; }
    // double getD5Ovality() const { return d5Ovality; }
    // double getD5() const { return d5; }
    // double getD4() const { return d4; }
    // double getdiamiter_min_fl1() const { return diamiter_min_fl1; }
    // double getdiamiter_max_fl1() const { return diamiter_max_fl1; }
    // double getD4Ovality() const { return d4Ovality; }
    // int getselected() const {return selected;}


    int id;
    QString name;
    double diamiter_min_fl2;
    double diamiter_max_fl2;
    double d5Ovality;
    double d5;
    double d4;
    double diamiter_min_fl1;
    double diamiter_max_fl1;
    double d4Ovality;
    int selected;
    DllImport QVariantMap toVariantMap() const override;
    DllImport void fromQueryAuto(const QSqlQuery& query) override;
    // QVariantMap toVariantMap() const override {
    //     QVariantMap map;
    //     const QMetaObject& metaObj = staticMetaObject;

    //     for (int i = 0; i < metaObj.propertyCount(); ++i) {
    //         QMetaProperty prop = metaObj.property(i);
    //         map.insert(prop.name(), prop.readOnGadget(this));
    //     }

    //     return map;
    // }

    // void fromQueryAuto(const QSqlQuery& query) override {
    //     const QMetaObject& metaObj = staticMetaObject;
    //     QSqlRecord record = query.record();

    //     for (int i = 0; i < metaObj.propertyCount(); ++i) {
    //         QMetaProperty prop = metaObj.property(i);
    //         int idx = record.indexOf(prop.name());
    //         if (idx != -1) {
    //             QVariant val = query.value(idx);
    //             prop.writeOnGadget(this, val);
    //         }
    //     }
    // }
};
Q_DECLARE_METATYPE(Sample)
#endif // SAMPLE_H

