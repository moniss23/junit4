#include "streamul.h"

#include <QByteArray>
#include <QDataStream>
#include <QBuffer>

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
    stream << currentQciTextStreamUl << streamUlQci << streamUlSpeed
           << streamUlDuration << streamUlMinThroughput;

    return serializedData.buffer();
}

void StreamUl::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> currentQciTextStreamUl >> streamUlQci >> streamUlSpeed
           >> streamUlDuration >> streamUlMinThroughput;
}
