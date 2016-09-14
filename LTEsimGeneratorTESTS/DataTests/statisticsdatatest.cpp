#include "statisticsdatatest.h"
#include "Maps/Traffic/Statistics/statisticsData.h"

#include <QtTest>
#include <QString>

StatisticsDataTest::StatisticsDataTest()
{

}

StatisticsDataTest::~StatisticsDataTest()
{

}

void StatisticsDataTest::initTestCase(){
}

void StatisticsDataTest::cleanupTestCase(){
}

void StatisticsDataTest::StatisticsDataTest1_serializeData()
{
    StatisticsData statisticsData;

    statisticsData.generalUe="";
    statisticsData.generalDelayBetweenPackets="";
    statisticsData.generalTotalNumberOfSeconds="";
    statisticsData.generalMtuSize="";
    statisticsData.generalMeasurementDelta="";

    statisticsData.ipexTguImsi="";
    statisticsData.ipexFileName="";
    statisticsData.ipexSeconds="";
    statisticsData.ipexMeasurement="";

    statisticsData.pdcpuBearerStatusImsi="";
    statisticsData.pdcpuBearerStatusEpsBearerId="";
    statisticsData.pdcpuBearerRohcImsi="";
    statisticsData.pdcpuBearerRohcEpsBearerId="";
    statisticsData.pdcpuBearerErrorImsi="";
    statisticsData.pdcpuBearerErrorEpsBearerId="";
    statisticsData.pdcpuFileName="";
    statisticsData.pdcpuSeconds="";
    statisticsData.pdcpuMeasurement="";

    QByteArray byteArray = statisticsData.serializeData();

    QVERIFY(byteArray.size() > 0);
}

void StatisticsDataTest::StatisticsDataTest2_deserializeData()
{
    StatisticsData statisticsData;

    statisticsData.generalUe="test string";

    QByteArray byteArray = statisticsData.serializeData();

    StatisticsData deserializedStatisticsData;

    deserializedStatisticsData.deserializeData(byteArray);

    if(statisticsData.generalUe != deserializedStatisticsData.generalUe) QVERIFY(false);

    QVERIFY(true);
}
