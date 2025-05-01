#ifndef USER_H
#define USER_H

#include <QString>
#include <QSqlQuery>

class User
{
public:
    User() = default;

    void fromQuery(const QSqlQuery& query) {
        id = query.value("id").toInt();
        userName = query.value("user_name").toString();
        password = query.value("password").toString();
        developerPassword = query.value("developer_password").toString();
    }

    int getId() const { return id; }
    QString getUserName() const { return userName; }
    QString getPassword() const { return password; }
    QString getDeveloperPassword() const { return developerPassword; }

public:
    int id;
    QString userName;
    QString password;
    QString developerPassword;
};

#endif // USER_H

