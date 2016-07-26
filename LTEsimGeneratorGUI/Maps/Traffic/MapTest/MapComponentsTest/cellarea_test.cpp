#include "cellarea_test.h"

void CellArea_Test::testConstructor()
{
    QPoint testPoint(243, 815);
    myCellAreaPtr = new CellArea(testPoint.x(), testPoint.y(), "43");
    QCOMPARE(myCellAreaPtr->getID(), QString("43"));
    QVERIFY(myCellAreaPtr->getCenter().x() == testPoint.x());
    QVERIFY(myCellAreaPtr->getCenter().y() == testPoint.y());
    QVERIFY(myCellAreaPtr->getR() == 5000);
}

void CellArea_Test::testDestructor()
{
    delete myCellAreaPtr;
}

void CellArea_Test::testGetCenter()
{
    QPoint testPoint(841, 357);
    CellArea my2ndCellArea(testPoint.x(), testPoint.y(), "11");
    QVERIFY(my2ndCellArea.getCenter().x() == testPoint.x());
    QVERIFY(my2ndCellArea.getCenter().y() == testPoint.y());
}

void CellArea_Test::testGetID()
{
    CellArea my2ndCellArea(0, 0, "11");
    QCOMPARE(my2ndCellArea.getID(), QString("11"));
}

void CellArea_Test::testGetR()
{
    QVERIFY(CellArea::R == 5000);
}

void CellArea_Test::testContain()
{
    CellArea *my2ndCellAreaPtr = new CellArea(234, 234, "12");
    MyObjectArea *myObjectAreaPtr = NULL;

    QVERIFY(my2ndCellAreaPtr->contain(274, 204, &myObjectAreaPtr) == true);
    QVERIFY(myObjectAreaPtr == my2ndCellAreaPtr);
}
