#include "handoverdata.h"
#include "qdebug.h"
#include "QFile"

HandoverData::HandoverData(QString name)
{
    this->handoverName = name;
    readParamsFromScript();
}

//---------------------Getters------------------------------------------------------


QString HandoverData::getHandoverName()
{
    return handoverName;
}

QString HandoverData::getSouthBoundary()
{
    return QString::number(southBoundary);
}

QString HandoverData::getNorthBoundary()
{
    return QString::number(northBoundary);
}

QString HandoverData::getWestBoundary()
{
    return QString::number(westBoundary);
}

QString HandoverData::getEastBoundary()
{
    return QString::number(eastBoundary);
}

//---------------------Setters------------------------------------------------------


void HandoverData::setHandoverName(QString name)
{
    this->handoverName = name;
}

void HandoverData::setSouthBoundary(QString south)
{
    this->southBoundary = south.toInt();
}

void HandoverData::setNorthBoundary(QString north)
{
    this->northBoundary = north.toInt();
}

void HandoverData::setWestBoundary(QString west)
{
    this->westBoundary = west.toInt();
}

void HandoverData::setEastBoundary(QString east)
{
    this->eastBoundary = east.toInt();
}


void HandoverData::readParamsFromScript()
{

}
