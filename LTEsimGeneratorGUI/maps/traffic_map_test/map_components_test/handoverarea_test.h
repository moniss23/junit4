#ifndef HANDOVERAREA_TEST_H
#define HANDOVERAREA_TEST_H

#include <QtTest/QtTest>
#include "maps/traffic_map/map_components/handoverarea.h"

class HandoverArea_Test: public QObject
{
    Q_OBJECT
private slots:
    void testConstructor();
    void testDestructor();
    void testGetID();
    void testContain();

private:
    HandoverArea *myHandoverAreaPtr;
    CellArea *myCell1Ptr, *myCell2Ptr;
};
#endif // HANDOVERAREA_TEST_H
