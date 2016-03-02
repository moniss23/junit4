#include "maps/traffic_map_test/data_objects_test/handoverdata_test.h"

HandoverData_Test::HandoverData_Test(QObject *parent) : QObject(parent)
{}

void HandoverData_Test::getHandoverNameTest()
{
    HandoverData* handover = new HandoverData(handoverName1);
    QCOMPARE(handover->getHandoverName(),handoverName1);
}

void HandoverData_Test::setHandoverNameTest()
{
    HandoverData* handover = new HandoverData(handoverName1);
    handover->setHandoverName(handoverName2);
    QCOMPARE(handover->getHandoverName(),handoverName2);

}

void HandoverData_Test::setgetSouthBoundaryTest()
{
    HandoverData* handover = new HandoverData(handoverName1);
    handover->setSouthBoundary(testNumber);
    QCOMPARE(handover->getSouthBoundary(),testNumber);

}

void HandoverData_Test::setgetNorthBoundaryTest()
{
    HandoverData* handover = new HandoverData(handoverName1);
    handover->setNorthBoundary(testNumber);
    QCOMPARE(handover->getNorthBoundary(),testNumber);

}

void HandoverData_Test::setgetEastBoundaryTest()
{
    HandoverData* handover = new HandoverData(handoverName1);
    handover->setEastBoundary(testNumber);
    QCOMPARE(handover->getEastBoundary(),testNumber);

}

void HandoverData_Test::setgetWestBoundaryTest()
{
    HandoverData* handover = new HandoverData(handoverName1);
    handover->setWestBoundary(testNumber);
    QCOMPARE(handover->getWestBoundary(),testNumber);

}
