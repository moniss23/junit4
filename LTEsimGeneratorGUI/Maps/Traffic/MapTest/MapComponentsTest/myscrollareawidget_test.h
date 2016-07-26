#ifndef MYSCROLLAREAWIDGET_TEST_H
#define MYSCROLLAREAWIDGET_TEST_H

#include <QtTest/QtTest>
#include <Maps/Traffic/MapComponents/myscrollareawidget.h>

class MyScrollAreaWidget_Test : public QObject
{
    Q_OBJECT
private slots:
    void testStandardConstructor();
    void testLargeConstructor();
    void testDestructor();
    void testWhichObjectArea();
    void testPressEvent();

private:
    MyScrollAreaWidget *myScrollAreaWidgetPtr, *myLargeScrollAreaWidgetPtr;
};

#endif // MYSCROLLAREAWIDGET_TEST_H
