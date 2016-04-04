#include "testrunner.h"



void TestRunner::runTests()
{
    //Tests for ManagementTemplate class
    ManagementTemplate managementTemplate;
    ManagementTemplate_Test managementTemplateTest(managementTemplate);
    QTest::qExec(&managementTemplateTest);

    //Tests for HandoverData class
    HandoverData_Test handoverTest;
    QTest::qExec(&handoverTest);

    //Test for UEgroupData class
    UEgroupData_Test ueGroupDataTest;
    QTest::qExec(&ueGroupDataTest);

    //Test for Statistics class
    StatisticsData_Test statisticsDataTest;
    QTest::qExec(&statisticsDataTest);

    //Tests for CellData class
    CellData_Test cellTest;
    QTest::qExec(&cellTest);

    //Tests for MapData class
    MapData_Test mapTest;
    QTest::qExec(&mapTest);

    //Tests for MapManagement class
    MapManagement_Test mapManagementTest;
    QTest::qExec(&mapManagementTest);
}
