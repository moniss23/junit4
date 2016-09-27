#include "timeData.h"

TimeData::TimeData()
{
    tab1_attachRate = tab1_detachRate = tab1_statsRate = 0;
    tab2_attachRate = tab2_detachRate = tab2_statsRate = 0;
    tab1_timeTrafficDuration = tab2_timeTrafficDuration = 0;

    tab1_ueAttachDettach = tab1_statisticsWithRate = tab1_statisticsAfterEnd = false;
    tab2_ueAttachDettach = tab2_statisticsWithRate = tab2_statisticsAfterEnd = false;

    tab2_crdelUEPeriod = 0;
    resetAllStat1 = resetAllStat2 = false;
}

TimeData::~TimeData()
{
}

QString TimeData::getElementType() const
{
    return QString("TimeData");
}

QByteArray TimeData::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << tab1_attachRate << tab1_detachRate << tab1_statsRate
           << tab2_attachRate << tab2_detachRate << tab2_statsRate
           << tab1_timeTrafficDuration << tab2_timeTrafficDuration
           << tab2_crdelUEPeriod << tab1_ueAttachDettach << resetAllStat1 << resetAllStat2
           << tab1_statisticsWithRate << tab1_statisticsAfterEnd << tab2_ueAttachDettach
           << tab2_statisticsWithRate << tab2_statisticsAfterEnd << spn_time1 << spn_time2;

    return serializedData.buffer();
}

void TimeData::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> tab1_attachRate >> tab1_detachRate >> tab1_statsRate
           >> tab2_attachRate >> tab2_detachRate >> tab2_statsRate
           >> tab1_timeTrafficDuration >> tab2_timeTrafficDuration
           >> tab2_crdelUEPeriod >> tab1_ueAttachDettach >> resetAllStat1 >> resetAllStat2
           >> tab1_statisticsWithRate >> tab1_statisticsAfterEnd >> tab2_ueAttachDettach
           >> tab2_statisticsWithRate >> tab2_statisticsAfterEnd >> spn_time1 >> spn_time2 ;
}
