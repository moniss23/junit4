#include "statisticsdata_test.h"

StatisticsData_Test::StatisticsData_Test(QObject *parent) : QObject(parent){}

void StatisticsData_Test::setGetStatisticsParamTest()
{
    StatisticsData* params = new StatisticsData(mapIndexTest);
    for (int i = 0; i <= static_cast<int>(Stats_settings::pdcp_uContStat) ; i++)
    {
        Stats_settings keyTest = static_cast<Stats_settings>(i);
        params->setStatMap(keyTest, valueTest);
        QCOMPARE(params->getStatMap(keyTest),valueTest);
    }
    delete params;
}
