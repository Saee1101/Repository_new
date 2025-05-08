#ifndef GENERICREPOSITORY_H
#define GENERICREPOSITORY_H
#define DllImport   __declspec( dllimport )
#include <QString>
#include <QSqlDatabase>
#include <QVariantMap>
#include <QSqlQuery>
#include <QList>

template <typename T>
class GenericRepository
{
public:

    GenericRepository(const QString& tableName, const QSqlDatabase& db)
        : m_tableName(tableName), m_db(db) {}
    QVariant GetValue(const QString& columnName) {
        QString queryStr = QString("SELECT %1 FROM %2 LIMIT 1").arg(columnName, m_tableName);
        QSqlQuery query(m_db);
        if (query.exec(queryStr) && query.next()) {
            return query.value(0);
        }
        qDebug() << "GetValue error:" ;
        return QVariant();
    }
    bool create(const QVariantMap& data);
    QList<T> readAll() {
        QList<T> results;
        QString queryStr = QString("SELECT * FROM %1").arg(m_tableName);
        QSqlQuery query(m_db);

        if (!query.exec(queryStr)) {
            qDebug() << "readAll :: Error reading records :" ;
            return results;
        }

        while (query.next()) {
            T record;
            record.fromQuery(query);
            results.append(record);
        }

        return results;
    }

    T readById(int id);

    T readByField(const QString& columnName, const QVariant& value)
    {
        QString queryStr = QString("SELECT * FROM %1 WHERE %2 = :value").arg(m_tableName, columnName);
        QSqlQuery query(m_db);
        query.prepare(queryStr);
        query.bindValue(":value", value);

        if (!query.exec()) {
            qDebug() << "Error reading record by field:" ;
            return T();
        }

        if (query.next()) {
            T record;
            record.fromQuery(query);
            return record;
        }

        return T();  // if not found
    }

    bool update(const QString& condition, const QVariantMap& data) {
        QStringList assignments;

        for (auto it = data.begin(); it != data.end(); ++it) {
            assignments << QString("%1 = :%2").arg(it.key()).arg(it.key());
        }

        QString queryStr = QString("UPDATE %1 SET %2 WHERE %3")
                               .arg(m_tableName)
                               .arg(assignments.join(", "))
                               .arg(condition);

        QSqlQuery query(m_db);
        query.prepare(queryStr);

        for (auto it = data.begin(); it != data.end(); ++it) {
            query.bindValue(":" + it.key(), it.value());
        }

        if (!query.exec()) {
            qDebug() << "Error updating record:" ;
            return false;
        }
        return true;
    }

    bool remove(int id);

    QString m_tableName;
    QSqlDatabase m_db;
};

#endif // GENERICREPOSITORY_H






// #ifndef GENERICREPOSITORY_H
// #define GENERICREPOSITORY_H
// #define DllImport   __declspec( dllimport )
// #include <QString>
// #include <QSqlDatabase>
// #include <QVariantMap>
// #include <QSqlQuery>
// // #include <vector>

// template <typename T>
// class GenericRepository
// {
// public:
//     GenericRepository(const QString& tableName, const QSqlDatabase& db)
//          : m_tableName(tableName), m_db(db) {}

//     bool create(const QVariantMap& data);
//     // std::vector<T> readAll();
//     QList<T> readAll(){
//         QList<T> results;
//         QString queryStr = QString("SELECT * FROM %1").arg(m_tableName);
//         QSqlQuery query(m_db);

//         if (!query.exec(queryStr)) {
//             qDebug() << "Error reading records:" ;
//             return results;
//         }

//         while (query.next()) {
//             T record;
//             record.fromQuery(query);
//             results.append(record);
//         }

//         return results;
//     }
//     T readById(int id);
//     T readByUsername(QString username);
//     // bool update(int id, const QVariantMap& data);
//     bool update(const QString& condition, const QVariant data);
//     bool remove(int id);

// private:
//     QString m_tableName;
//     QSqlDatabase m_db;
// };



// #endif // GENERICREPOSITORY_H


