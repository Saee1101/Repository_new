#ifndef GENERICREPOSITORY_IMPL_H
#define GENERICREPOSITORY_IMPL_H
#include "Repository.h"

#include <QSqlError>
#include <QDebug>

// template <typename T>
// GenericRepository<T>::GenericRepository(const QString& tableName, const QSqlDatabase& db)
//     : m_tableName(tableName), m_db(db) {}

template <typename T>
bool GenericRepository<T>::create(const QVariantMap& data) {
    QStringList columns, placeholders;

    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        columns << it.key();
        placeholders << ":" + it.key();
    }

    QString queryStr = QString("INSERT INTO %1 (%2) VALUES (%3)")
                           .arg(m_tableName)
                           .arg(columns.join(", "))
                           .arg(placeholders.join(", "));

    QSqlQuery query(m_db);
    query.prepare(queryStr);

    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        query.bindValue(":" + it.key(), it.value());
    }

    if (!query.exec()) {
        qDebug() << "Error creating record:" << query.lastError().text();
        return false;
    }

    return true;
}

// template <typename T>
// QList<T> GenericRepository<T>::readAll() {
//     QList<T> results;
//     QString queryStr = QString("SELECT * FROM %1").arg(m_tableName);
//     QSqlQuery query(m_db);

//     if (!query.exec(queryStr)) {
//         qDebug() << "Error reading records:" << query.lastError().text();
//         return results;
//     }

//     while (query.next()) {
//         T record;
//         record.fromQuery(query);
//         results.append(record);
//     }

//     return results;
// }

template <typename T>
T GenericRepository<T>::readById(int id) {
    QString queryStr = QString("SELECT * FROM %1 WHERE id = :id").arg(m_tableName);
    QSqlQuery query(m_db);
    query.prepare(queryStr);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error reading record by ID:" << query.lastError().text();
        return T();
    }

    if (query.next()) {
        T record;
        record.fromQuery(query);
        return record;
    }

    return T();
}

// template<typename T>
// T GenericRepository<T>::readByUsername(QString username)
// {
//     QString queryStr = QString("SELECT * FROM %1 WHERE user_name = :user_name").arg(m_tableName);
//     QSqlQuery query(m_db);
//     query.prepare(queryStr);
//     query.bindValue(":user_name", username);

//     if (!query.exec()) {
//         qDebug() << "Error reading record by user_name:" << query.lastError().text();
//         return T();
//     }

//     if (query.next()) {
//         T record;
//         record.fromQuery(query);
//         return record;
//     }

//     return T();
// }


// template <typename T>
// bool GenericRepository<T>::update(int id, const QVariantMap& data) {
//     QStringList assignments;

//     for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
//         assignments << QString("%1 = :%2").arg(it.key()).arg(it.key());
//     }

//     QString queryStr = QString("UPDATE %1 SET %2 WHERE id = :id")
//                            .arg(m_tableName)
//                            .arg(assignments.join(", "));

//     QSqlQuery query(m_db);
//     query.prepare(queryStr);
//     query.bindValue(":id", id);

//     for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
//         query.bindValue(":" + it.key(), it.value());
//     }

//     if (!query.exec()) {
//         qDebug() << "Error updating record:" << query.lastError().text();
//         return false;
//     }

//     return true;
// }

template <typename T>
bool GenericRepository<T>::remove(int id) {
    QString queryStr = QString("DELETE FROM %1 WHERE id = :id").arg(m_tableName);
    QSqlQuery query(m_db);
    query.prepare(queryStr);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error deleting record:" << query.lastError().text();
        return false;
    }

    return true;
}

#endif // GENERICREPOSITORY_IMPL_H


// #include "Repository.h"

// Repository::Repository(QString TableName) {
//     tablename=TableName;
//     QString JsonFilePath="DBconnectionconfig.json";

//     QFile file(JsonFilePath);
//     if(file.open(QIODevice::ReadOnly))
//     {
//         QByteArray Bytes=file.readAll();
//         file.close();

//         QJsonParseError JsonError;
//         QJsonDocument Document=QJsonDocument::fromJson(Bytes,&JsonError);
//         if(JsonError.error != QJsonParseError::NoError)
//         {
//             qDebug()<<"Error In Json DB";
//         }
//         if(Document.isObject())
//         {
//             QJsonObject obj=Document.object();
//             databaseType =obj.value("databaseType").toString();
//             databaseName =obj.value("databaseName").toString();
//         }
//     }

//     ConnectionDB ();
// }

// void Repository::Add(const QString& key,QString value)
// {

//     // T item;
//     // item.set_key(key);
//     // item.set_value(value);

//     QSqlQuery q;
//     q.prepare(QString("INSERT INTO %1 (key_, value_) VALUES (:key, :value)").arg(tablename));
//     // q.bindValue(":key", item.get_key());
//     // q.bindValue(":value", item.get_value());
//     q.bindValue(":key", key);
//     q.bindValue(":value", value);
//     if (!q.exec()) {
//         qDebug() << "Error executing Add query:" ;
//     }
// }




// void Repository::Delete(const QString& key)
// {
//     // T item;
//     // item.set_key(key);

//     QSqlQuery q;
//     q.prepare(QString("DELETE FROM %1 WHERE key_=:key").arg(tablename));
//     // q.bindValue(":key",item.get_key());
//     q.bindValue(":key",key);
//     if (!q.exec()) {
//         qDebug() << "Error executing Delete query:" ;
//     }
// }
// QSqlTableModel* Repository::GetAll()
// {

//     QSqlTableModel* model = new QSqlTableModel();
//     model->setTable(tablename);

//     if (!model->select()) {
//         qDebug() << "Error selecting table:" ;
//     }

//     return model;

// }


// void Repository::Update(const QString& key,QString value)
// {

// // qDebug()<<"value : "<<value;   // T item;
//     // item.set_key(key);
//     // item.set_value(value);
//     // QTimer::singleShot(200, []() {
//     //     qDebug() << "After delay";
//     // });

// // qDebug()<<"key : "<<key;



//      QSqlQuery q;
//     q.prepare(QString("UPDATE %1 SET key_=:key, value_=:value WHERE key_=:key ").arg(tablename));

//     // q.bindValue(":key",item.get_key());
//     // q.bindValue(":value",item.get_value());

//     q.bindValue(":key",key);
//     q.bindValue(":value",value);
//     // q.bindValue(":key",key);
//     if (!q.exec()) {
//         qDebug() << "Error executing Update query:" << q.lastError().text();
//     } else {
//         qDebug() << "Update successful for key:" << key;
//     }



//     // if (!q.exec()) {

//     //     qDebug() << "Error executing Update query:" ;
//     // }




// }

// QString Repository::GetValue(const QString &key)
// {
//     QString Value;
//     QSqlQuery q;
//     q.prepare(QString("SELECT value_ FROM %1 WHERE key_=:key").arg(tablename));
//     // q.bindValue(":key",item.get_key());
//     q.bindValue(":key",key);
//     q.exec();
//     if (q.next()) {
//         Value= q.value("value_").toString();
//     }
//     else  {
//         qDebug() << "Error executing Delete query:" ;
//     }

//     return Value;
// }

// void Repository::ConnectionDB ()
// {

//     db=QSqlDatabase :: addDatabase(databaseType);
//     db.setDatabaseName(databaseName);
//     if(!db.open())
//     {
//         qDebug() << "Entities::Repository.h::'Failed to open the database!'";
//     }
// }
