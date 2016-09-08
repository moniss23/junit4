#ifndef VOIP_H
#define VOIP_H

#include "Data/Interfaces/serializeinterface.h"

class Voip
{
public:
    Voip();
    ~Voip() {}

    QString currentQciTextVoip;
    int voipQci;
    int voipDuration;
    int voipActivityFactor;
    int voipMaxTransferTime;
    int voipMinPacketsReceivedInTime;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // VOIP_H
