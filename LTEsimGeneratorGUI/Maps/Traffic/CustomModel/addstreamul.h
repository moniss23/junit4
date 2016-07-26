#ifndef ADDSTREAMUL_H
#define ADDSTREAMUL_H
#include <QString>

class Addstreamul
{
public:
    Addstreamul();
    ~Addstreamul();

    void setQci(QString value);
    QString getQci();

    void setSpeed(QString value);
    QString getSpeed();

    void setDuration(QString value);
    QString getDuration();

    void setMinThroughput(QString value);
    QString getMinThroughput();

private:
    int qci;
    int speed;
    int duration;
    int minthroughput;
};

#endif // ADDSTREAMUL_H
