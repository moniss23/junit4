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

    //Tests for MyScrollAreaWidget class
    MyScrollAreaWidget_Test myScrollAreaWidgetTest;
    QTest::qExec(&myScrollAreaWidgetTest);

    //Tests for CustomModelLabel class
    CustomModelLabel_Test customModelLabelTest;
    QTest::qExec(&customModelLabelTest);

    //Tests for StatisticsButton class
    StatisticsButton_Test statisticsButtonTest;
    QTest::qExec(&statisticsButtonTest);

    //Tests for TimeButton class
    TimeButton_Test timeButtonTest;
    QTest::qExec(&timeButtonTest);

    //Tests for TuningTrafficButton class
    TuningTrafficButton_Test tuningTrafficButtonTest;
    QTest::qExec(&tuningTrafficButtonTest);

    //Tests for Scale Template class
    Scale_Test scaleTest;
    QTest::qExec(&scaleTest);
}
