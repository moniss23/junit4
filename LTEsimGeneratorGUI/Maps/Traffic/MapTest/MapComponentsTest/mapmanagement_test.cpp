#include "mapmanagement_test.h"

void MapManagement_Test::testConstructor()
{
    mapManagementPtr = new MapManagement;
    QCOMPARE(mapManagementPtr->windowTitle(), QString("Map management"));
    QVERIFY(mapManagementPtr->maximumWidth() == 1100);
    QVERIFY(mapManagementPtr->maximumHeight() == 950);
    QVERIFY(mapManagementPtr->width() == 1100);
    QVERIFY(mapManagementPtr->height() == 950);
}

void MapManagement_Test::testDestructor()
{
    delete mapManagementPtr;
}
