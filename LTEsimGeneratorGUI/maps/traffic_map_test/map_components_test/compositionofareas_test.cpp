#include "compositionofareas_test.h"

void CompositionOfAreas_Test::testConstructor()
{
    myCompositionOfAreasPtr = new CompositionOfAreas;
}

void CompositionOfAreas_Test::testDestructor()
{
    delete myCompositionOfAreasPtr;
}

void CompositionOfAreas_Test::testAddToList()
{
    my2ndCompositionOfAreasPtr = new CompositionOfAreas;
    myCell1Ptr = new CellArea(1000, 1000, "11");
    myCell2Ptr = new CellArea(3000, 3000, "12");

    for(int i = 0; i < 5; i++)
        myHandoverArea.append(new HandoverArea(myCell1Ptr, myCell2Ptr));
    for(int i = 0; i < 3; i++)
        myCellArea.append(new CellArea(100*1, 200*i, QString::number(i)));
    for(int i = 0; i < myHandoverArea.size(); i++)
        my2ndCompositionOfAreasPtr->addToList(myHandoverArea[i]);
    for(int i = 0; i < myCellArea.size(); i++)
        my2ndCompositionOfAreasPtr->addToList(myCellArea[i]);
    QVERIFY(my2ndCompositionOfAreasPtr->size() == 8);
    for(int i = 0; i < my2ndCompositionOfAreasPtr->size(); i++)
        QCOMPARE(my2ndCompositionOfAreasPtr->getID(), QString("composition"));
}

void CompositionOfAreas_Test::testSize()
{
    QVERIFY(my2ndCompositionOfAreasPtr->size() == 8);
}

void CompositionOfAreas_Test::testGetID()
{
    for(int i = 0; i < my2ndCompositionOfAreasPtr->size(); i++)
        QCOMPARE(my2ndCompositionOfAreasPtr->getID(), QString("composition"));
}

void CompositionOfAreas_Test::testContain()
{
    //TO BE FINISHED
}
