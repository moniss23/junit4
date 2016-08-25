#include "uctoolsettings.h"

UCToolSettings::UCToolSettings()
{
}

QString UCToolSettings::getElementType() const
{
    return QString("UCToolSettings");
}

QByteArray UCToolSettings::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << ucToolIP << ucToolCIds << ucToolServiceIp;

    return serializedData.buffer();
}

void UCToolSettings::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> ucToolIP >> ucToolCIds >> ucToolServiceIp;
}
