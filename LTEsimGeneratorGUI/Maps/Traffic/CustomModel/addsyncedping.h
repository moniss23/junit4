#ifndef ADDSYNCEDPING_H
#define ADDSYNCEDPING_H
#include <QString>
class Addsyncedping
{
public:
    Addsyncedping();
    ~Addsyncedping();

    void setQciarray(QString value);
    QString getQciarray();

    void setTimeBetweenTasks(QString value);
    QString getTimeBetweenTasks();

    void setNumberOfPings(QString value);
    QString getNumberOfPings();

    void setInterval(QString value);
    QString getInterval();

    void setMinReceivedPings(QString value);
    QString getMinReceivedPings();
private:
    int qciarray;
    int timebetweentasks;
    int numberofpings;
    int interval;
    int minreceivedpings;
};

#endif // ADDSYNCEDPING_H
