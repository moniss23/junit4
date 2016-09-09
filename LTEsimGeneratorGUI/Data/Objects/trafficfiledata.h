#ifndef TRAFFICFILEDATA_H
#define TRAFFICFILEDATA_H

#include <QVector>

#include <Data/Interfaces/serializeinterface.h>
#include "Maps/Traffic/Statistics/statisticsData.h"
#include "Data/TrafficSettings/custommodelsettings.h"

class TrafficFileData : public SerializeInterface
{
public:
    TrafficFileData();
    QString filename;
    QString content;
    StatisticsData statisticsData;

    QVector<CustomModelSettings> customModels;
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
