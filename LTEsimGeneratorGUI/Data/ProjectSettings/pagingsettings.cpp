#include "pagingsettings.h"
#include <QDataStream>
#include <QBuffer>

PagingSettings::PagingSettings()
{

}
PagingSettings PagingSettings::getElementType() const
{
    return QString("PagingSettings");
}

QByteArray PagingSettings::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << generators << names << imsiRanged << mmeCodes << uePagingIdentity << pagingSlapUris ;
    return serializedData.buffer();
}

void PagingSettings::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> generators >> names >> imsiRanged >> mmeCodes >> uePagingIdentity >> pagingSlapUris ;
}
