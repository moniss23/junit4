#include "syncedping.h"

#include <QByteArray>
#include <QDataStream>
#include <QBuffer>

SyncedPingSettings::SyncedPingSettings()
{
}

QString SyncedPingSettings::getElementType() const
{
    return QString("SyncedPing");
}

QByteArray SyncedPingSettings::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << SyncedPingQciArray << SyncedPingTimeBetweenTasks
           << SyncedPingNumberOfPings << SyncedPingInterval << SyncedPingMinReceivedPings;

    return serializedData.buffer();
}

void SyncedPingSettings::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> SyncedPingQciArray >> SyncedPingTimeBetweenTasks
           >> SyncedPingNumberOfPings >> SyncedPingInterval >> SyncedPingMinReceivedPings;
}
