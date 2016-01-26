#ifndef ADDSTREAMDL_H
#define ADDSTREAMDL_H
#include <QString>

class Addstreamdl
{
public:
    Addstreamdl();
    ~Addstreamdl();

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

#endif // ADDSTREAMDL_H
