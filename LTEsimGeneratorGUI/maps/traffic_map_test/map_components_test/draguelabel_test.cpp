#include "draguelabel_test.h"

void DragUELabel_Test::testConstructor()
{
    myDragUELabelPtr = new DragUELabel("ue1");
    QCOMPARE(myDragUELabelPtr->labelText(), QString("ue1"));
    QVERIFY(myDragUELabelPtr->myArea == NULL);
}

void DragUELabel_Test::testDestructor()
{
    delete myDragUELabelPtr;
}

void DragUELabel_Test::testDoubleClickEvent()
{
    //TO BE PERFOMED
}

void DragUELabel_Test::testLabelText()
{
    DragUELabel my2ndDragUELabel("ue2");
    QCOMPARE(my2ndDragUELabel.labelText(), QString("ue2"));
}

void DragUELabel_Test::testSetMyArea()
{
    //TO BE PERFORMED
}

void DragUELabel_Test::testGetMyArea()
{
    //TO BE PERFORMED
}
