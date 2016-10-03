#ifndef VOIP_H
#define VOIP_H

#include "Data/Interfaces/serializeinterface.h"

/**
 * @brief The Voip class contains settings for VoIP component
 */
class Voip
{
public:
    Voip();
    ~Voip() {}

    int voipQci = 0;                    ///< QCI
    int voipDuration;                   ///< Duration
    int voipActivityFactor;             ///< Activity factor
    int voipMaxTransferTime;            ///< Maximal transfer time
    int voipMinPacketsReceivedInTime;   ///< Minimal amount of packets received in time

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // VOIP_H
