#include "Entities.h"
#include <QDebug>

Entities::Entities(const QSqlDatabase& db)
    : m_db(db),
    CRUD_machine_setting_db("machine_setting", db),
    CRUD_user_db("user", db),
    CRUD_sample_db("sample",db)
{

}

void Entities::loadData()
{
    // بارگذاری MachineSetting
    QList<MachineSetting> machineSettings = CRUD_machine_setting_db.readAll();
    if (!machineSettings.isEmpty()) {
        const MachineSetting& setting = machineSettings.first();
        QVariantMap map = setting.toVariantMap();

        for (auto it = map.begin(); it != map.end(); ++it) {
            dataMap_machine_setting_db.insert(it.key(), it.value().toString());
        }
    }
        else {
        qDebug() << "No machine settings found!";
    }

    // بارگذاری Sample
    QList<Sample> samples = CRUD_sample_db.readAll();
    if (!samples.isEmpty()) {
        const Sample& sample = samples.first();
        QVariantMap map = sample.toVariantMap();

        for (auto it = map.begin(); it != map.end(); ++it) {
            dataMap_sample_db.insert(it.key(), it.value().toString());
        }
    }

    // بارگذاری User
    QList<User> users = CRUD_user_db.readAll();
    for (const auto& user : users) {
        // چون ما userName و password را در toVariantMap نمی‌بینیم، مستقیم استفاده می‌کنیم:
        dataMap_user_db.insert(user.userName,user.passWord);
    }
}



// #include "Entities.h"

// Entities::Entities()
//      : CRUD_machine_setting_db("machine_setting")
//     // ,CRUD_sample_db("sample")
//     ,CRUD_user_db("user")
//     ,CRUD_user_role_db("user_role")
// {

//     CRUD_sample_db_List.resize(5);
//     for(int i=0;i<5;i++)
//     {

//         CRUD_sample_db = new Repository("sample_"+QString::number(i));
//         // Repository* CRUD_sample_db = new Repository("sample");
//         CRUD_sample_db_List[i]=CRUD_sample_db ;
//     }
// }
// void Entities::push_map()
// {
//       // Repository repo("table_name");
//       // Repository CRUD_machine_setting_db("machine_setting");
//     QSqlTableModel* model_setting_machine_db = CRUD_machine_setting_db.GetAll();
//     if (!model_setting_machine_db) {
//         qDebug()<< "Failed to retrieve data from model.";
//     }
//     for(int row =0;row <model_setting_machine_db->rowCount();++row)
//     {
//         QString key=model_setting_machine_db->data(model_setting_machine_db->index(row,model_setting_machine_db->fieldIndex("key_"))).toString();
//         QString value=model_setting_machine_db->data(model_setting_machine_db->index(row,model_setting_machine_db->fieldIndex("value_"))).toString();
//         dataMap_machine_setting_db.insert(key,value);
//     }
//     /////////////////////////////////////////////////////////////////
//     // QSqlTableModel* model_setting_camera_db = CRUD_setting_camera_db->GetAll();
//     // if (!model_setting_camera_db) {
//     //     qDebug()<< "Failed to retrieve data from model.";
//     // }
//     // for(int row =0;row <model_setting_camera_db->rowCount();++row)
//     // {
//     //     QString key=model_setting_camera_db->data(model_setting_camera_db->index(row,model_setting_camera_db->fieldIndex("key_"))).toString();
//     //     QString value=model_setting_camera_db->data(model_setting_camera_db->index(row,model_setting_camera_db->fieldIndex("value_"))).toString();
//     //     dataMap_setting_camera_db.insert(key,value);
//     // }
//     // /////////////////////////////////////////////////

//     QSqlTableModel* model_sample_db =CRUD_sample_db_List[dataMap_machine_setting_db.value("sample_number").toInt()]->GetAll();
//     if (!model_sample_db) {
//         qDebug()<< "Failed to retrieve data from model.";
//     }

//     for(int row =0;row <model_sample_db->rowCount();++row)
//     {

//         QString key=model_sample_db->data(model_sample_db->index(row,model_sample_db->fieldIndex("key_"))).toString();
//         QString value=model_sample_db->data(model_sample_db->index(row,model_sample_db->fieldIndex("value_"))).toString();
//         dataMap_sample_db.insert(key,value);

//     }
//     // /////////////////////////////////////////
//     Repository CRUD_user_db("user");
//     QSqlTableModel* model_user_db =CRUD_user_db.GetAll();
//     if (!model_user_db) {
//         qDebug()<< "Failed to retrieve data from model.";
//     }
//     for(int row =0;row <model_user_db->rowCount();++row)
//     {
//         QString key=model_user_db->data(model_user_db->index(row,model_user_db->fieldIndex("key_"))).toString();
//         QString value=model_user_db->data(model_user_db->index(row,model_user_db->fieldIndex("value_"))).toString();
//         dataMap_user_db.insert(key,value);
//     }
//     // /////////////////////////////////////////////
//     // QSqlTableModel* model_user_role_db=CRUD_user_role_db.GetAll();
//     // if (!model_user_role_db) {
//     //     qDebug()<< "Failed to retrieve data from model.";
//     // }
//     // for(int row =0;row <model_user_role_db->rowCount();++row)
//     // {
//     //     QString key=model_user_role_db->data(model_user_role_db->index(row,model_user_role_db->fieldIndex("key_"))).toString();
//     //     QString value=model_user_role_db->data(model_user_role_db->index(row,model_user_role_db->fieldIndex("value_"))).toString();
//     //     dataMap_user_role_db.insert(key,value);
//     // }

// }
