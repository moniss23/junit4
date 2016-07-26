#include "addvoip.h"

Addvoip::Addvoip()
{
    qci = 0;
    activityfactor=0;
    maxtransfertime=0;
    minpacketsreceivedintime=0;
}

Addvoip::~Addvoip()
{

}
//sets and gets
void Addvoip::setQci(QString value)
{
    this->qci = value.toInt();
}

QString Addvoip::getQci()
{
    return QString::number(qci);
}

void Addvoip::setDuration(QString value)
{
    this->duration = value.toInt();
}
QString Addvoip::getduration()
{
    return QString::number(duration);
}

void Addvoip::setActivityFactor(QString value)
{
    this->activityfactor = value.toInt();
}

QString Addvoip::getActivityFactor()
{
    return QString::number(activityfactor);
}

void Addvoip::setMaxTransferTime(QString value)
{
    this->maxtransfertime = value.toInt();
}

QString Addvoip::getMaxTransferTime()
{
    return QString::number(maxtransfertime);
}

void Addvoip::setMinPacketsReceivedInTime(QString value)
{
    this->minpacketsreceivedintime = value.toInt();
}

QString Addvoip::getMinPacketsReceivedInTime()
{
    return QString::number(minpacketsreceivedintime);
}
