#include "ping.h"

Ping::Ping()
{

}

QString Ping::getElementType() const
{
    return QString("Ping");
}

QByteArray Ping::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << pingQci << pingNumberOfPings <<
              pingInterval << pingMinRecievedPings;

    return serializedData.buffer();
}

void Ping::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> pingQci >> pingNumberOfPings >>
              pingInterval >> pingMinRecievedPings;
}
