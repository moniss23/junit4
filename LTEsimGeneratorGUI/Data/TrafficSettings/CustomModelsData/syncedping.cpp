#include "syncedping.h"

#include <QByteArray>
#include <QDataStream>
#include <QBuffer>

SyncedPingForm::SyncedPingForm()
{
}

QString SyncedPingForm::getElementType() const
{
    return QString("SyncedPing");
}

QByteArray SyncedPingForm::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << SyncedPingQciArray << SyncedPingTimeBetweenTasks
           << SyncedPingNumberOfPings << SyncedPingInterval << SyncedPingMinReceivedPings;

    return serializedData.buffer();
}

void SyncedPingForm::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> SyncedPingQciArray >> SyncedPingTimeBetweenTasks
           >> SyncedPingNumberOfPings >> SyncedPingInterval >> SyncedPingMinReceivedPings;
}
