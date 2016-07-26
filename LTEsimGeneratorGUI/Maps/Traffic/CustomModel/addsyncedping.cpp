#include "addsyncedping.h"

Addsyncedping::Addsyncedping()
{
    qciarray = 0;
    timebetweentasks = 0;
    numberofpings = 0;
    interval = 0;
    minreceivedpings = 0;
}

Addsyncedping::~Addsyncedping()
{
}

void Addsyncedping::setQciarray(QString value)
{
    this->qciarray = value.toInt();
}
QString Addsyncedping::getQciarray()
{
    return QString::number(qciarray);
}

void Addsyncedping::setTimeBetweenTasks(QString value)
{
    this->timebetweentasks = value.toInt();
}
QString Addsyncedping::getTimeBetweenTasks()
{
    return QString::number(timebetweentasks);
}

void Addsyncedping::setNumberOfPings(QString value)
{
    this->numberofpings = value.toInt();
}
QString Addsyncedping::getNumberOfPings()
{
    return QString::number(numberofpings);
}

void Addsyncedping::setInterval(QString value)
{
    this->interval = value.toInt();
}
QString Addsyncedping::getInterval()
{
    return QString::number(interval);
}

void Addsyncedping::setMinReceivedPings(QString value)
{
    this->minreceivedpings = value.toInt();
}
QString Addsyncedping::getMinReceivedPings()
{
    return QString::number(minreceivedpings);
}
