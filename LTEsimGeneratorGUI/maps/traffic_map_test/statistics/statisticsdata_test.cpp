#include "statisticsdata_test.h"

StatisticsData_Test::StatisticsData_Test(QObject *parent) : QObject(parent){}

void StatisticsData_Test::setGetStatisticsParamTest()
{
    StatisticsData* params = new StatisticsData(mapIndexTest);
    for (int i = 0; i <= static_cast<int>( Stats_settings::pdcp_uContStat ); i++)
    {
        Stats_settings keyTest = static_cast<Stats_settings>( i );
        params->setStatMap(keyTest, valueTest);
        QCOMPARE(params->getStatMap(keyTest),valueTest);
    }
    delete params;
}

void StatisticsData_Test::serializeToProjectFileTest()
{
    for (int i = 0; i <= static_cast<int>( Stats_settings::pdcp_uContStat ); i++)
    {
        Stats_settings keyStatTest = static_cast<Stats_settings>( i );
        statMapTest.insert(keyStatTest, false);
    }
    StatisticsData* param = new StatisticsData(mapIndexTest);
    for(int i = 0; i < statMapTest.size(); i++)
    {
        QString keyMapTest = param->getStringFromEnum(i);
        QDomElement statisticsElementTest = xmlStatTest.createElement(keyMapTest);
        xmlStatTest.appendChild(statisticsElementTest);
        QDomText statisticsElementXmlTextTest = xmlStatTest.createTextNode(param->boolToString(statMapTest[param->getEnumFromString(keyMapTest)]) );
        statisticsElementTest.appendChild(statisticsElementXmlTextTest);
    }
    QCOMPARE(xmlStatTest.toString(), statXmlString);
}
