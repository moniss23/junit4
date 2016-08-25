#include "sgwsettings.h"

#include <QBuffer>
#include <QDataStream>

SgwSettings::SgwSettings() {
}
SgwSettings::~SgwSettings() {
}
QString SgwSettings::getElementType() const
{
    return QString("SgwSettings");
}

QByteArray SgwSettings::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << name << ipAdress << apnList << ldi << coreNetworkGateway;
    return serializedData.buffer();
}

void SgwSettings::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> name >> ipAdress >> apnList >> ldi >> coreNetworkGateway;
}
