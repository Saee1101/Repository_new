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
        diamiter_min_fl2 = query.value("diamiter_min_fl2").toDouble();
        diamiter_max_fl2 = query.value("diamiter_max_fl2").toDouble();
        d5Ovality = query.value("d5_ovality").toDouble();
        d5 = query.value("d5").toDouble();
        d4 = query.value("d4").toDouble();
        diamiter_min_fl1 = query.value("diamiter_min_fl1").toDouble();
        diamiter_max_fl1 = query.value("diamiter_max_fl1").toDouble();
        d4Ovality = query.value("d4_ovality").toDouble();
        selected=query.value("selected").toInt();
    }

    int getId() const { return id; }
    QString getName() const { return name; }
    double getdiamiter_min_fl2() const { return diamiter_min_fl2; }
    double getdiamiter_max_fl2() const { return diamiter_max_fl2; }
    double getD5Ovality() const { return d5Ovality; }
    double getD5() const { return d5; }
    double getD4() const { return d4; }
    double getdiamiter_min_fl1() const { return diamiter_min_fl1; }
    double getdiamiter_max_fl1() const { return diamiter_max_fl1; }
    double getD4Ovality() const { return d4Ovality; }
    int getselected() const {return selected;}


    int id;
    QString name;
    double diamiter_min_fl2;
    double diamiter_max_fl2;
    double d5Ovality;
    double d5;
    double d4;
    double diamiter_min_fl1;
    double diamiter_max_fl1;
    double d4Ovality;
    int selected;
};

#endif // SAMPLE_H

