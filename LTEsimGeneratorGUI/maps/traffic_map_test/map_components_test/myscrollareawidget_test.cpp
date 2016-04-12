#include "myscrollareawidget_test.h"

void MyScrollAreaWidget_Test::testStandardConstructor()
{
    myScrollAreaWidgetPtr = new MyScrollAreaWidget;
    QVERIFY(myScrollAreaWidgetPtr->acceptDrops() == true);
    QCOMPARE(myScrollAreaWidgetPtr->myLabel1.text(), QString("Add UE Group:") );
    QCOMPARE(myScrollAreaWidgetPtr->myLabel2.text(), QString("Custom Models:") );
}

void MyScrollAreaWidget_Test::testLargeConstructor()
{
    myLargeScrollAreaWidgetPtr = new MyScrollAreaWidget( true );
    QVERIFY(myLargeScrollAreaWidgetPtr->acceptDrops() == true);
    QCOMPARE(myLargeScrollAreaWidgetPtr->myLabel1.text(), QString("Add UE Group:") );
    QCOMPARE(myLargeScrollAreaWidgetPtr->myLabel2.text(), QString("Custom Models:") );
}

void MyScrollAreaWidget_Test::testDestructor()
{
    delete myScrollAreaWidgetPtr;
    delete myLargeScrollAreaWidgetPtr;
}

void MyScrollAreaWidget_Test::testWhichObjectArea()
{
    MyScrollAreaWidget myTestScrollAreaWidget(true);
    QVERIFY(myTestScrollAreaWidget.whichObjectArea(200, 100)->getID() == "61");
    QVERIFY(myTestScrollAreaWidget.whichObjectArea(600, 800)->getID() == "14");
    QVERIFY(myTestScrollAreaWidget.whichObjectArea(450, 530)->getID() == "33");
    QVERIFY(myTestScrollAreaWidget.whichObjectArea(600, 270)->getID() == "54");
}

void MyScrollAreaWidget_Test::testPressEvent()
{
    MyScrollAreaWidget myTestScrollAreaWidget(true);
    QPoint pressPosition = QPoint(400, 400);
    QTest::mousePress(&myTestScrollAreaWidget, Qt::LeftButton, 0, pressPosition);
    QVERIFY(myTestScrollAreaWidget.startPos == pressPosition);
    QVERIFY(myTestScrollAreaWidget.startPos != QPoint(123, 234) );
}
