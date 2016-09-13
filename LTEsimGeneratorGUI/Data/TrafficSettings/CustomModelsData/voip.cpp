#include "voip.h"

Voip::Voip()
{

}

QString Voip::getElementType() const
{
    return QString("Voip");
}

QByteArray Voip::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << voipQci << voipDuration <<
              voipActivityFactor << voipMaxTransferTime << voipMinPacketsReceivedInTime;

    return serializedData.buffer();
}

void Voip::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> voipQci >> voipDuration >>
              voipActivityFactor >> voipMaxTransferTime >> voipMinPacketsReceivedInTime;
}
