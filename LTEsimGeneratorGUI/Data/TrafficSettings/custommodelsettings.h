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

/**
 * @brief The CustomModelSettings class contains settings for CustomModel component
 */
class CustomModelSettings : public SerializeInterface
{
public:
    CustomModelSettings();
    ~CustomModelSettings() {}

    QVector <Ping> CMPings;                 ///< Container of Pings
    QVector <Voip> CMVoips;                 ///< Container of VoIPs
    QVector <FtpDl> CMFtpDls;               ///< Container of FTPDLs
    QVector <FtpUl> CMFtpUls;               ///< Container of FTPULs
    QVector <StreamDl> CMStreamDls;         ///< Container of StreamDLs
    QVector <StreamUl> CMStreamUls;         ///< Container of StreamULs
    QVector <SyncedPing> CMSyncedPings;     ///< Container of SyncedPings
    QVector <ServiceReq> CMServiceReqs;     ///< Container of ServiceReqs

    static const int amountOfQci = 9;       ///< Amount of QCIs available
    bool qciUsed[amountOfQci];              ///< Container storing data about which QCIs are being used

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // CUSTOMMODELSETTINGS_H
