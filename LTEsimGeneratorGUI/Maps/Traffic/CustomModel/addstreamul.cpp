#include "addstreamul.h"

Addstreamul::Addstreamul()
{
    qci = 0;
    speed = 0;
    duration = 0;
    minthroughput = 0;
}

Addstreamul::~Addstreamul()
{
}

//gets and sets
void Addstreamul::setQci(QString value)
{
    this->qci = value.toInt();
}

QString Addstreamul::getQci()
{
    return QString::number(qci);
}

void Addstreamul::setSpeed(QString value)
{
    this->speed = value.toInt();
}

QString Addstreamul::getSpeed()
{
    return QString::number(speed);
}

void Addstreamul::setDuration(QString value)
{
    this->duration = value.toInt();
}

QString Addstreamul::getDuration()
{
    return QString::number(duration);
}

void Addstreamul::setMinThroughput(QString value)
{
    this->minthroughput = value.toInt();
}

QString Addstreamul::getMinThroughput()
{
    return QString::number(minthroughput);
}