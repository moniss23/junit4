#include <QBuffer>
#include <QDataStream>

#include "trafficdata.h"

QString TrafficData::getElementType() const
{
    return QString("TrafficData");
}

QByteArray TrafficData::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << fileName << content;

    return serializedData.buffer();
}

void TrafficData::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> fileName >> content;
}
