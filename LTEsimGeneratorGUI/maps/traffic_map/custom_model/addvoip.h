#ifndef ADDVOIP_H
#define ADDVOIP_H

#include <QString>
#include <QList>

class Addvoip
{
public:
    Addvoip();
    ~Addvoip();

    void setQci(QString value);
    QString getQci();

    void setDuration(QString value);
    QString getduration();

    void setActivityFactor(QString value);
    QString getActivityFactor();

    void setMaxTransferTime(QString value);
    QString getMaxTransferTime();

    void setMinPacketsReceivedInTime(QString value);
    QString getMinPacketsReceivedInTime();


private:
    int qci;
    int duration;
    int activityfactor;
    int maxtransfertime;
    int minpacketsreceivedintime;

};

#endif // ADDVOIP_H
