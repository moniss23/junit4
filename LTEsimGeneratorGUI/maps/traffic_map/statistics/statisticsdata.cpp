#include "statisticsdata.h"
#include <QDebug>

StatisticsData::StatisticsData(QString &mapIndex)
{
    mapIndexCurrent = mapIndex;

    for (int i = 0; i <= static_cast<int>( Stats_settings::pdcp_uContStat ); i++)
    {
        Stats_settings keyStat = static_cast<Stats_settings>( i );
        statMap.insert(keyStat, false);
    }
}

bool StatisticsData::getStatMap(enum Stats_settings &key)
{
    value = statMap.value(key);
    return value;
}

void StatisticsData::setStatMap(enum Stats_settings &key, bool &value)
{
    statMap[key] = value;
}
