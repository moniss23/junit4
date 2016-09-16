#ifndef TIMEDATA_H
#define TIMEDATA_H

#include <QTime>
#include <QString>

#include "Data/Interfaces/serializeinterface.h"

class TimeData : public SerializeInterface
{
public:
    TimeData();
    ~TimeData();

    QTime spn_time1, spn_time2;
    int tab1_attachRate, tab1_detachRate, tab1_statsRate;
    int tab2_attachRate, tab2_detachRate, tab2_statsRate;
    int tab1_timeTrafficDuration, tab2_timeTrafficDuration;
    int tab2_crdelUEPeriod;

    bool tab1_ueAttachDettach, tab1_statisticsWithRate, tab1_statisticsAfterEnd;
    bool tab2_ueAttachDettach, tab2_statisticsWithRate, tab2_statisticsAfterEnd;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // TIMEDATA_H
