#ifndef ADDPING_H
#define ADDPING_H
#include <QString>
#include <QList>
class Addping
{
public:
    Addping();
    ~Addping();

    void setQci(QString value);
    QString getQci();

    void setNumberOfPings(QString value);
    QString getNumberOfPings();

    void setInterval(QString value);
    QString getInterval();

    void setMinRecievedPings(QString value);
    QString getMinRecievedPings();

private:
    int qci;
    int numberofpings;
    int interval;
    int minrecievedpings;
};

#endif // ADDPING_H
