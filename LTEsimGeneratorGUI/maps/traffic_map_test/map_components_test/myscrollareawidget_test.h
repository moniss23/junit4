#ifndef MYSCROLLAREAWIDGET_TEST_H
#define MYSCROLLAREAWIDGET_TEST_H

#include <QtTest/QtTest>
#include "maps/traffic_map/map_components/myscrollareawidget.h"

class MyScrollAreaWidget_Test: public QObject
{
    Q_OBJECT
private slots:
    void testStandardConstructor();
    void testLargeConstructor();
    void testDestructor();
    void testWhichObjectArea();

private:
    MyScrollAreaWidget *myScrollAreaWidgetPtr, *myLargeScrollAreaWidgetPtr;
};

#endif // MYSCROLLAREAWIDGET_TEST_H
