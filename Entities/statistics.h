#ifndef STATISTICS_H
#define STATISTICS_H

#include <QString>
#include <QSqlQuery>

class Statistics
{
public:
    Statistics() = default;

    void fromQuery(const QSqlQuery& query) {
        id = query.value("id").toInt();
        date = query.value("date").toString();
        hour = query.value("hour").toInt();
        minute = query.value("minute").toInt();
        clAccepted = query.value("cl_accepted").toInt();
        clRejected = query.value("cl_rejected").toInt();
        fl2Accepted = query.value("fl2_accepted").toInt();
        fl2Rejected = query.value("fl2_rejected").toInt();
        fl1Accepted = query.value("fl1_accepted").toInt();
        fl1Rejected = query.value("fl1_rejected").toInt();
        sampleId = query.value("sample_id").toInt();
    }

    int getId() const { return id; }
    QString getDate() const { return date; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getClAccepted() const { return clAccepted; }
    int getClRejected() const { return clRejected; }
    int getFl2Accepted() const { return fl2Accepted; }
    int getFl2Rejected() const { return fl2Rejected; }
    int getFl1Accepted() const { return fl1Accepted; }
    int getFl1Rejected() const { return fl1Rejected; }
    int getSampleId() const { return sampleId; }

public :
    int id;
    QString date;
    int hour;
    int minute;
    int clAccepted;
    int clRejected;
    int fl2Accepted;
    int fl2Rejected;
    int fl1Accepted;
    int fl1Rejected;
    int sampleId;
};

#endif // STATISTICS_H
