#include <QBuffer>
#include <QDataStream>

#include "trafficfiledata.h"

QString TrafficFileData::getElementType() const
{
    return QString("TrafficFileData");
}

QByteArray TrafficFileData::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << fileName << content;

    return serializedData.buffer();
}

void TrafficFileData::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> fileName >> content;
}
