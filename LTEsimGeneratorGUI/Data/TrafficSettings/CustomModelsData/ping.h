#ifndef PING_H
#define PING_H

#include "Data/Interfaces/serializeinterface.h"

/**
 * @brief The Ping class contains settings for Ping component
 */
class Ping : public SerializeInterface
{
public:
    Ping();
    ~Ping() {}

    int pingQci = 0;                ///< Ping QCI
    int pingNumberOfPings;          ///< Number of pings
    int pingInterval;               ///< Interval of pings
    int pingMinRecievedPings;       ///< Minimal amount of received pings

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // PING_H
