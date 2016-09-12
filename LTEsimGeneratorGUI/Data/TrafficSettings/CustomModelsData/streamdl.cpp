#include "streamdl.h"

#include <QByteArray>
#include <QDataStream>
#include <QBuffer>

StreamDl::StreamDl()
{

}

QString StreamDl::getElementType() const
{
    return QString("StreamDl");
}

QByteArray StreamDl::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << streamDlQci << streamDlSpeed
           << streamDlDuration << streamDlMinThroughput;

    return serializedData.buffer();
}

void StreamDl::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> streamDlQci >> streamDlSpeed
           >> streamDlDuration >> streamDlMinThroughput;
}
