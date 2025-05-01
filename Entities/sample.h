#ifndef SAMPLE_H
#define SAMPLE_H

#include <QString>
#include <QSqlQuery>

class Sample
{
public:
    Sample() = default;

    void fromQuery(const QSqlQuery& query) {
        id = query.value("id").toInt();
        name = query.value("name").toString();
        d5Telp = query.value("d5_telp").toDouble();
        d5Teln = query.value("d5_teln").toDouble();
        d5Ovality = query.value("d5_ovality").toDouble();
        d5 = query.value("d5").toDouble();
        d4 = query.value("d4").toDouble();
        d4Telp = query.value("d4_telp").toDouble();
        d4Teln = query.value("d4_teln").toDouble();
        d4Ovality = query.value("d4_ovality").toDouble();
    }

    int getId() const { return id; }
    QString getName() const { return name; }
    double getD5Telp() const { return d5Telp; }
    double getD5Teln() const { return d5Teln; }
    double getD5Ovality() const { return d5Ovality; }
    double getD5() const { return d5; }
    double getD4() const { return d4; }
    double getD4Telp() const { return d4Telp; }
    double getD4Teln() const { return d4Teln; }
    double getD4Ovality() const { return d4Ovality; }

public :
    int id;
    QString name;
    double d5Telp;
    double d5Teln;
    double d5Ovality;
    double d5;
    double d4;
    double d4Telp;
    double d4Teln;
    double d4Ovality;
};

#endif // SAMPLE_H

