#include "user.h"

QVariantMap User::toVariantMap() const {
    QVariantMap map;
    const QMetaObject& metaObj = staticMetaObject;

    for (int i = 0; i < metaObj.propertyCount(); ++i) {
        QMetaProperty prop = metaObj.property(i);
        map.insert(prop.name(), prop.readOnGadget(this));
    }

    return map;
}

void User::fromQueryAuto(const QSqlQuery& query) {
    const QMetaObject& metaObj = staticMetaObject;
    QSqlRecord record = query.record();

    for (int i = 0; i < metaObj.propertyCount(); ++i) {
        QMetaProperty prop = metaObj.property(i);
        int idx = record.indexOf(prop.name());
        if (idx != -1) {
            QVariant val = query.value(idx);
            prop.writeOnGadget(this, val);
        }
    }
}
