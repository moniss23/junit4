#ifndef TRAFFICFILEDATA_H
#define TRAFFICFILEDATA_H

#include <QString>

#include <Data/Interfaces/serializeinterface.h>
#include "Maps/Traffic/Statistics/statisticsData.h"

class TrafficFileData : public SerializeInterface
{
public:
    QString filename;
    QString content;

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
