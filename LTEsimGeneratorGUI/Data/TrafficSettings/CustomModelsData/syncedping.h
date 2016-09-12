#ifndef SYNCEDPING_H
#define SYNCEDPING_H

#include <QVector>

#include "Data/Interfaces/serializeinterface.h"

class SyncedPing : public SerializeInterface
{
public:
    SyncedPing();
    ~SyncedPing() {}

    QVector<int> SyncedPingQciArray;
    int SyncedPingTimeBetweenTasks;
    int SyncedPingNumberOfPings;
    int SyncedPingInterval;
    int SyncedPingMinReceivedPings;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // SYNCEDPING_H
