#include "handoverarea_test.h"

void HandoverArea_Test::testConstructor()
{
    myCell1Ptr = new CellArea(1000, 1000, "11");
    myCell2Ptr = new CellArea(3000, 3000, "12");
    myHandoverAreaPtr = new HandoverArea(myCell1Ptr, myCell2Ptr);
    QVERIFY(myHandoverAreaPtr->getID() == QString("1112"));
}

void HandoverArea_Test::testDestructor()
{
    delete myHandoverAreaPtr;
    delete myCell1Ptr;
    delete myCell2Ptr;
}

void HandoverArea_Test::testGetID()
{
    CellArea cell1(3000, 2000, "23");
    CellArea cell2(4000, 3000, "34");
    HandoverArea my2ndHandoverArea(&cell1, &cell2);
    QVERIFY(my2ndHandoverArea.getID() == QString("2334"));
}

void HandoverArea_Test::testContain()
{
    //TO BE FINISHED
}
