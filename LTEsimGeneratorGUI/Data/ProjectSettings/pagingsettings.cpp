#include "pagingsettings.h"
#include <QDataStream>
#include <QBuffer>

PagingSettings::PagingSettings()
{

}
PagingSettings::~PagingSettings()
{

}

QString PagingSettings::getElementType() const
{
    return QString("PagingSettings");
}

QByteArray PagingSettings::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << isUsedInConfiguration << generators << names << imsiRanges << mmeCodes << uePagingIdentity << pagingSlapUris << bundlePaging;
    return serializedData.buffer();
}

void PagingSettings::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> isUsedInConfiguration >> generators >> names >> imsiRanges >> mmeCodes >> uePagingIdentity >> pagingSlapUris >> bundlePaging;
}
