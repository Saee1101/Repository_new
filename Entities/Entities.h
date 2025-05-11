#ifndef ENTITIES_H
#define ENTITIES_H

#include "Entities_global.h"
#include "Repository.h"
#include "machineSetting.h"
#include "user.h"
#include "sample.h"

// #include "UserRole.h"
#include <QMap>
#include <QVector>
#include <QSqlDatabase>

class ENTITIES_EXPORT Entities
{
public:
    explicit Entities(const QSqlDatabase& db);

    void loadData();



    QSqlDatabase m_db;


    GenericRepository<MachineSetting> CRUD_machine_setting_db;
    GenericRepository<User> CRUD_user_db;
     GenericRepository<Sample> CRUD_sample_db;


    // QVector<GenericRepository<Sample>*> CRUD_sample_db_List;
    // GenericRepository<Sample>* CRUD_sample_db = nullptr;


    QMap<QString, QString> dataMap_machine_setting_db;
    QMap<QString, QString> dataMap_user_db;
    QMap<QString, QString> dataMap_sample_db;
    QMap<QString, QString> dataMap_user_role_db;
};

#endif // ENTITIES_H

// #ifndef ENTITIES_H
// #define ENTITIES_H

// #include "Entities_global.h"
// #include "Repository.h"


// #include "machineSetting.h"
// #include "user.h"
// // #include "UserRole.h"
// #include "sample.h"

// #include <QMap>
// #include <QVector>
// #include <QString>
// #include <QSqlDatabase>

// class ENTITIES_EXPORT Entities
// {
// public:
//     Entities(const QSqlDatabase& db);

//     void pushMap();


//     GenericRepository<MachineSetting> CRUD_machine_setting_db;
//     GenericRepository<User> CRUD_user_db;
//     // GenericRepository<UserRole> CRUD_user_role_db;

//     QVector<GenericRepository<Sample>*> CRUD_sample_db_List;
//     GenericRepository<Sample>* CRUD_sample_db = nullptr;


//     QMap<QString, QString> dataMap_machine_setting_db;
//     QMap<QString, QString> dataMap_user_db;
//     QMap<QString, QString> dataMap_sample_db;
//     QMap<QString, QString> dataMap_user_role_db;

// private:
//     QSqlDatabase m_db;
// };

// #endif // ENTITIES_H

