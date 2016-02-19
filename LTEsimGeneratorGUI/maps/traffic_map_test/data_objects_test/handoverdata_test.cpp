#include "maps/traffic_map_test/data_objects_test/handoverdata_test.h"

HandoverData_Test::HandoverData_Test(QObject *parent) : QObject(parent)
{

}

void HandoverData_Test::getHandoverNameTest()
{
    HandoverData* p_handover= new HandoverData(m_handoverName1);
    QCOMPARE(p_handover->getHandoverName(),m_handoverName1);
}

void HandoverData_Test::setHandoverNameTest()
{
    HandoverData* p_handover= new HandoverData(m_handoverName1);
    p_handover->setHandoverName(m_handoverName2);
    QCOMPARE(p_handover->getHandoverName(),m_handoverName2);

}

void HandoverData_Test::setgetSouthBoundaryTest()
{
    HandoverData* p_handover= new HandoverData(m_handoverName1);
    p_handover->setSouthBoundary(m_testNumber);
    QCOMPARE(p_handover->getSouthBoundary(),m_testNumber);

}

void HandoverData_Test::setgetNorthBoundaryTest()
{
    HandoverData* p_handover= new HandoverData(m_handoverName1);
    p_handover->setNorthBoundary(m_testNumber);
    QCOMPARE(p_handover->getNorthBoundary(),m_testNumber);

}

void HandoverData_Test::setgetEastBoundaryTest()
{
    HandoverData* p_handover= new HandoverData(m_handoverName1);
    p_handover->setEastBoundary(m_testNumber);
    QCOMPARE(p_handover->getEastBoundary(),m_testNumber);

}

void HandoverData_Test::setgetWestBoundaryTest()
{
    HandoverData* p_handover= new HandoverData(m_handoverName1);
    p_handover->setWestBoundary(m_testNumber);
    QCOMPARE(p_handover->getWestBoundary(),m_testNumber);

}
