#include "handoverdata.h"
#include "qdebug.h"
#include "QFile"

HandoverData::HandoverData(QString l_name)
{

    this->m_handoverName=l_name;
    readParamsFromScript();

}

//---------------------Getters------------------------------------------------------


QString HandoverData::getHandoverName()
{
    return m_handoverName;
}

QString HandoverData::getSouthBoundary()
{
    return QString::number(m_southBoundary);
}

QString HandoverData::getNorthBoundary()
{
    return QString::number(m_northBoundary);
}

QString HandoverData::getWestBoundary()
{
    return QString::number(m_westBoundary);
}

QString HandoverData::getEastBoundary()
{
    return QString::number(m_eastBoundary);
}

//---------------------Setters------------------------------------------------------


void HandoverData::setHandoverName(QString l_name)
{
    this->m_handoverName=l_name;
}

void HandoverData::setSouthBoundary(QString l_south)
{
    this->m_southBoundary=l_south.toInt();
}

void HandoverData::setNorthBoundary(QString l_north)
{
    this->m_northBoundary=l_north.toInt();
}

void HandoverData::setWestBoundary(QString l_west)
{
    this->m_westBoundary=l_west.toInt();
}

void HandoverData::setEastBoundary(QString l_east)
{
    this->m_eastBoundary=l_east.toInt();
}


void HandoverData::readParamsFromScript()
{

}
