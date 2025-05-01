#include "Entities.h"
#include <QDebug>

Entities::Entities(const QSqlDatabase& db)
    : m_db(db),
    CRUD_machine_setting_db("machine_setting", db),
    CRUD_user_db("user", db)
{
    // مقداردهی لیست نمونه‌ها (samples)
    CRUD_sample_db_List.resize(5);
    for (int i = 0; i < 5; ++i) {
        CRUD_sample_db_List[i] = new GenericRepository<Sample>("sample_" + QString::number(i), db);
    }

    // پیش‌فرض: نمونه اول
    CRUD_sample_db = CRUD_sample_db_List[0];
}

void Entities::loadData()
{
    // std::vector<MachineSetting> machineSettings = CRUD_machine_setting_db.readAll();
    QList<MachineSetting> machineSettings = CRUD_machine_setting_db.readAll();
    if (!machineSettings.empty()) {
        const MachineSetting& setting = machineSettings.first();

        dataMap_machine_setting_db.insert("sample_id", QString::number(setting.sampleId));
        dataMap_machine_setting_db.insert("lift_delay_fl", QString::number(setting.liftDelayFl));
        dataMap_machine_setting_db.insert("lift_time_fl", QString::number(setting.liftTimeFl));
        dataMap_machine_setting_db.insert("lift_delay_cl", QString::number(setting.liftDelayCl));
        dataMap_machine_setting_db.insert("lift_time_cl", QString::number(setting.liftTimeCl));
        dataMap_machine_setting_db.insert("camera_delay_fl1", QString::number(setting.cameraDelayFl1));
        dataMap_machine_setting_db.insert("camera_delay_fl2", QString::number(setting.cameraDelayFl2));
        dataMap_machine_setting_db.insert("camera_delay_cl", QString::number(setting.cameraDelayCl));
        dataMap_machine_setting_db.insert("picture_count_cl", QString::number(setting.pictureCountCl));
        dataMap_machine_setting_db.insert("camera_interval_cl", QString::number(setting.cameraIntervalCl));
        dataMap_machine_setting_db.insert("reject_delay", QString::number(setting.rejectDelay));
        dataMap_machine_setting_db.insert("reject_time", QString::number(setting.rejectTime));
        dataMap_machine_setting_db.insert("d5_sensitivity", QString::number(setting.d5Sensitivity));
        dataMap_machine_setting_db.insert("d4_sensitivity", QString::number(setting.d4Sensitivity));
        dataMap_machine_setting_db.insert("pixel_to_mm_fl2", QString::number(setting.pixelToMmFl2));
        dataMap_machine_setting_db.insert("pixel_to_mm_fl1", QString::number(setting.pixelToMmFl1));
        dataMap_machine_setting_db.insert("cl_sensitivity", QString::number(setting.clSensitivity));
        dataMap_machine_setting_db.insert("cl_stage", QString::number(setting.clStage));
        dataMap_machine_setting_db.insert("cl_reject_status", QString::number(setting.clRejectStatus));
        dataMap_machine_setting_db.insert("fl1_reject_status", QString::number(setting.fl1RejectStatus));
        dataMap_machine_setting_db.insert("fl2_reject_status", QString::number(setting.fl2RejectStatus));


        int sampleIndex = setting.sampleId;
        if (sampleIndex >= 0 && sampleIndex < CRUD_sample_db_List.size()) {
            CRUD_sample_db = CRUD_sample_db_List[sampleIndex];
        }
    } else {
        qDebug() << "No machine settings found!";
    }


    QList<Sample> samples = CRUD_sample_db->readAll();
    for (const auto& sample : samples) {
        dataMap_sample_db.insert(sample.name, QString::number(sample.id));
    }


    QList<User> users = CRUD_user_db.readAll();
    for (const auto& user : users) {
        dataMap_user_db.insert(user.userName, user.password);
    }

    // خواندن نقش کاربران (user roles) (فعلا اگر کلاسش آماده بشه اضافه می‌کنیم)
    // مثال برای آینده:
    // QList<UserRole> roles = CRUD_user_role_db.readAll();
    // for (const auto& role : roles) {
    //     dataMap_user_role_db.insert(role.roleName, role.description);
    // }
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
