#ifndef SYNCEDPING_H
#define SYNCEDPING_H

#include <QVector>

#include "Data/Interfaces/serializeinterface.h"

/**
 * @brief The SyncedPing class contains settings for SyncedPing component
 */
class SyncedPing : public SerializeInterface
{
public:
    SyncedPing();
    ~SyncedPing() {}

    QVector<int> SyncedPingQciArray;    ///< Container of SyncedPing QCIs
    int SyncedPingTimeBetweenTasks;     ///< Time between tasks
    int SyncedPingNumberOfPings;        ///< Number of pings
    int SyncedPingInterval;             ///< Interval between pings
    int SyncedPingMinReceivedPings;     ///< Minimal amount of received pings

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // SYNCEDPING_H
