#ifndef BASEENTITY_H
#define BASEENTITY_H
#define DllImport   __declspec( dllimport )
#include <QVariantMap>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMetaProperty>
#include <QDebug>

class BaseEntity
{
     Q_GADGET
public:
    virtual ~BaseEntity() = default;

   DllImport virtual QVariantMap toVariantMap() const = 0;

   DllImport virtual void fromQueryAuto(const QSqlQuery& query) = 0;
};

#endif // BASEENTITY_H


