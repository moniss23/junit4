#ifndef CUSTOMMODELSETTINGS_H
#define CUSTOMMODELSETTINGS_H

#include <QVector>
#include <QObject>

#include "Data/Interfaces/serializeinterface.h"

#include "Data/TrafficSettings/CustomModelsData/ftpdl.h"
#include "Data/TrafficSettings/CustomModelsData/ftpul.h"
#include "Data/TrafficSettings/CustomModelsData/ping.h"
#include "Data/TrafficSettings/CustomModelsData/servicereq.h"
#include "Data/TrafficSettings/CustomModelsData/streamdl.h"
#include "Data/TrafficSettings/CustomModelsData/streamul.h"
#include "Data/TrafficSettings/CustomModelsData/syncedping.h"
#include "Data/TrafficSettings/CustomModelsData/voip.h"

class CustomModelSettings : public SerializeInterface
{
public:
    CustomModelSettings();
    ~CustomModelSettings() {}

    QVector <Ping> CMPings;
    QVector <Voip> CMVoips;
    QVector <FtpDl> CMFtpDls;
    QVector <FtpUl> CMFtpUls;
    QVector <StreamDl> CMStreamDls;
    QVector <StreamUl> CMStreamUls;
    QVector <SyncedPingSettings> CMSyncedPings;
    QVector <ServiceReq> CMServiceReqs;

    static const int amountOfQci = 9;
    bool qciUsed[amountOfQci];

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);

};

#endif // CUSTOMMODELSETTINGS_H
