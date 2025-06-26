#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <QVariantMap>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDebug>

class BaseEntity : public QObject
{
     Q_OBJECT
public:
    virtual ~BaseEntity() {}

    virtual QVariantMap toVariantMap() const = 0;
    virtual void fromQuery(const QSqlQuery& query) = 0;
};

#endif // BASEENTITY_H

