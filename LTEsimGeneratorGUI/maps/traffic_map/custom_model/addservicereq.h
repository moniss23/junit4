#ifndef ADDSERVICEREQ_H
#define ADDSERVICEREQ_H
#include <QString>

class Addservicereq
{
public:
    Addservicereq();
    ~Addservicereq();

    void setQciarray(QString value);
    QString getQciarray();

    void setTimeToWaitForAttach(QString value);
    QString getTimeToWaitForAttach();

    void setIntervalBetweenUlData(QString value);
    QString getIntervalBetweenUlData();
private:
    int qciarray;
    int timetowaitforattach;
    int intervalbetweenuldata;
};

#endif // ADDSERVICEREQ_H
