#include "maps/traffic_map_test/data_objects_test/handoverdata_test.h"

HandoverData_Test::HandoverData_Test(QObject *parent) : QObject(parent)
{
    //Creating project file just for testing
    *projectName = testProjectName;
    QListWidgetItem* newItem = new QListWidgetItem(*projectName);
    projectMng->addProject(newItem,testProjectDir);

}

HandoverData_Test::~HandoverData_Test()
{
    //Removing project file after tests
    QDir dir(testProjectDir + "/" + testProjectName);

    if(dir.exists() )
        dir.removeRecursively();
}

void HandoverData_Test::getHandoverNameTest()
{
    HandoverData* handover = new HandoverData(handoverName1);
    QCOMPARE(handover->getHandoverName(),handoverName1);
    delete handover;
}

void HandoverData_Test::setHandoverNameTest()
{
    HandoverData* handover = new HandoverData(handoverName1);
    handover->setHandoverName(handoverName2);
    QCOMPARE(handover->getHandoverName(),handoverName2);
    delete handover;
}

void HandoverData_Test::setgetSouthBoundaryTest()
{
    HandoverData* handover = new HandoverData(handoverName1);
    handover->setSouthBoundary(testNumber);
    QCOMPARE(handover->getSouthBoundary(),testNumberText);
    delete handover;
}

void HandoverData_Test::setgetNorthBoundaryTest()
{
    HandoverData* handover = new HandoverData(handoverName1);
    handover->setNorthBoundary(testNumber);
    QCOMPARE(handover->getNorthBoundary(),testNumberText);
    delete handover;
}

void HandoverData_Test::setgetEastBoundaryTest()
{
    HandoverData* handover = new HandoverData(handoverName1);
    handover->setEastBoundary(testNumber);
    QCOMPARE(handover->getEastBoundary(),testNumberText);
    delete handover;
}

void HandoverData_Test::setgetWestBoundaryTest()
{
    HandoverData* handover = new HandoverData(handoverName1);
    handover->setWestBoundary(testNumber);
    QCOMPARE(handover->getWestBoundary(),testNumberText);
    delete handover;
}
