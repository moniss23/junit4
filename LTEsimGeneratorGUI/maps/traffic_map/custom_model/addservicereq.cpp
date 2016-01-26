#include "addservicereq.h"

Addservicereq::Addservicereq()
{
    qciarray = 0;
    timetowaitforattach = 0;
    intervalbetweenuldata = 0;
}

Addservicereq::~Addservicereq()
{
}

void Addservicereq::setQciarray(QString value)
{
    this->qciarray = value.toInt();
}
QString Addservicereq::getQciarray()
{
    return QString::number(qciarray);
}

void Addservicereq::setTimeToWaitForAttach(QString value)
{
    this->timetowaitforattach = value.toInt();
}
QString Addservicereq::getTimeToWaitForAttach()
{
    return QString::number(timetowaitforattach);
}

void Addservicereq::setIntervalBetweenUlData(QString value)
{
    this->intervalbetweenuldata = value.toInt();
}
QString Addservicereq::getIntervalBetweenUlData()
{
    return QString::number(intervalbetweenuldata);
}
