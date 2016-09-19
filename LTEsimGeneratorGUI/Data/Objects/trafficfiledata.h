#ifndef TRAFFICFILEDATA_H
#define TRAFFICFILEDATA_H

#include <QVector>

#include "Data/TrafficSettings/uedata.h"
#include "Data/Interfaces/serializeinterface.h"
#include "Data/TrafficSettings/statisticsData.h"
#include "Data/TrafficSettings/custommodelsettings.h"
#include "Data/TrafficSettings/tuningTrafficData.h"
#include "Data/TrafficSettings/timeData.h"


class TrafficFileData : public SerializeInterface
{
public:
    TrafficFileData();

    QString content;
    QString filename;
    StatisticsData statisticsData;
    QVector<UEData> userEquipments;
    QVector<CustomModelSettings> customModels;
    TuningTrafficData tuningTrafficData;
    TimeData timeData;
    static const int cmAmount = 10;
    bool cmUsed[cmAmount];

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
public:
    ~TrafficFileData() {}

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // TRAFFICFILEDATA_H
