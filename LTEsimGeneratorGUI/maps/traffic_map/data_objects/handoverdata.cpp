#include "handoverdata.h"
#include "qdebug.h"
#include "QFile"

HandoverData::HandoverData(QString name)
{
    this->handoverParams.handoverName = name;
}

//---------------------Getters------------------------------------------------------


QString HandoverData::getHandoverName()
{
    return handoverParams.handoverName;
}

QString HandoverData::getSouthBoundary()
{
    return QString::number(handoverParams.handoverArea.bottom() );
}

QString HandoverData::getNorthBoundary()
{
    return QString::number(handoverParams.handoverArea.top() );
}
QString HandoverData::getWestBoundary()
{
    return QString::number(handoverParams.handoverArea.left() );
}

QString HandoverData::getEastBoundary()
{
    return QString::number(handoverParams.handoverArea.right() );
}

HandoverParams HandoverData::getHandoverParams()
{
    return handoverParams;
}

//---------------------Setters------------------------------------------------------


void HandoverData::setHandoverName(QString name)
{
    handoverParams.handoverName = name;
}

void HandoverData::setSouthBoundary(int south)
{
    handoverParams.handoverArea.setBottom(south);
}
void HandoverData::setNorthBoundary(int north)
{
    handoverParams.handoverArea.setTop(north);
}
void HandoverData::setWestBoundary(int west)
{
    handoverParams.handoverArea.setLeft(west);
}

void HandoverData::setEastBoundary(int east)
{
    handoverParams.handoverArea.setRight(east);
}

void HandoverData::setHandoverParams(HandoverParams params)
{
    handoverParams = params;
}

HandoverParams HandoverData::parseDataFromList(QStringList paramsList)
{}

//---------------Overriden methods from DataElementsInterface---------------------

QString HandoverData::getElementType() const
{}

void HandoverData::serializeFromProjectFileOld(QByteArray rawData)
{}

QByteArray HandoverData::readDataFromProj()
{}

//------------------Serialize/Deserialize operators for future---------------------

QDataStream &operator<<(QDataStream &out, HandoverParams &handover)
{}

QDataStream &operator>>(QDataStream &in, HandoverParams &handover)
{}
