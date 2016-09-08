#include "syncedping.h"

#include <QByteArray>
#include <QDataStream>
#include <QBuffer>

SyncedPing::SyncedPing()
{
}

QString SyncedPing::getElementType() const
{
    return QString("SyncedPing");
}

QByteArray SyncedPing::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << currentQciTextSyncedPing << SyncedPingQciArray << SyncedPingTimeBetweenTasks
           << SyncedPingNumberOfPings << SyncedPingInterval << SyncedPingMinReceivedPings;

    return serializedData.buffer();
}

void SyncedPing::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> currentQciTextSyncedPing >> SyncedPingQciArray >> SyncedPingTimeBetweenTasks
           >> SyncedPingNumberOfPings >> SyncedPingInterval >> SyncedPingMinReceivedPings;
}
