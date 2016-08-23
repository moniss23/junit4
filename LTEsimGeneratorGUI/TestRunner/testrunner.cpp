#include "testrunner.h"



void TestRunner::runTests()
{
    //Tests for ManagementTemplate class
    ManagementTemplate managementTemplate;
    ManagementTemplate_Test managementTemplateTest(managementTemplate);
    QTest::qExec(&managementTemplateTest);

    //Test for UEgroupData class
    UEgroupData_Test ueGroupDataTest(appSettings);
    QTest::qExec(&ueGroupDataTest);

    //Test for Statistics class
    StatisticsData_Test statisticsDataTest(appSettings);
    QTest::qExec(&statisticsDataTest);

    //Tests for CellData class
    CellData_Test cellTest(appSettings);
    QTest::qExec(&cellTest);

    //Tests for MapData class
    MapData_Test mapTest(appSettings);
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

    //Tests for DragUELabel class
    DragUELabel_Test dragUELabelTest;
    QTest::qExec(&dragUELabelTest);

    //Tests for AddButton class
    AddButton_Test addButtonTest;
    QTest::qExec(&addButtonTest);

    //Tests for CellArea class
    CellArea_Test cellAreaTest;
    QTest::qExec(&cellAreaTest);

    //Tests for HandoverArea class
    HandoverArea_Test handoverAreaTest;
    QTest::qExec(&handoverAreaTest);

    //Tests fo CompositionOfAreas class
    CompositionOfAreas_Test compositionOfAreasTest;
    QTest::qExec(&compositionOfAreasTest);
}
