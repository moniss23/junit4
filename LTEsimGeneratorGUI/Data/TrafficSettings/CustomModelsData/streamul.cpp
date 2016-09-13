#include "streamul.h"

StreamUl::StreamUl()
{

}

QString StreamUl::getElementType() const
{
    return QString("StreamUl");
}

QByteArray StreamUl::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << streamUlQci << streamUlSpeed
           << streamUlDuration << streamUlMinThroughput;

    return serializedData.buffer();
}

void StreamUl::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> streamUlQci >> streamUlSpeed
           >> streamUlDuration >> streamUlMinThroughput;
}
