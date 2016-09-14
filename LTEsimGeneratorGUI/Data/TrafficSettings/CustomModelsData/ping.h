#ifndef PING_H
#define PING_H

#include "Data/Interfaces/serializeinterface.h"

class Ping : public SerializeInterface
{
public:
    Ping();
    ~Ping() {}

    int pingQci = 0;
    int pingNumberOfPings;
    int pingInterval;
    int pingMinRecievedPings;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // PING_H
