#include "myscrollareawidget_test.h"

void MyScrollAreaWidget_Test::testStandardConstructor()
{
    myScrollAreaWidgetPtr = new MyScrollAreaWidget;
    QVERIFY(myScrollAreaWidgetPtr->acceptDrops() == true);
    QCOMPARE(myScrollAreaWidgetPtr->myLabel1.text(), QString("Add UE Group:"));
    QCOMPARE(myScrollAreaWidgetPtr->myLabel2.text(), QString("Custom Models:"));
}

void MyScrollAreaWidget_Test::testLargeConstructor()
{
    myLargeScrollAreaWidgetPtr = new MyScrollAreaWidget( true );
    QVERIFY(myLargeScrollAreaWidgetPtr->acceptDrops() == true);
    QCOMPARE(myLargeScrollAreaWidgetPtr->myLabel1.text(), QString("Add UE Group:"));
    QCOMPARE(myLargeScrollAreaWidgetPtr->myLabel2.text(), QString("Custom Models:"));
}

void MyScrollAreaWidget_Test::testDestructor()
{
    delete myScrollAreaWidgetPtr;
    delete myLargeScrollAreaWidgetPtr;
}
