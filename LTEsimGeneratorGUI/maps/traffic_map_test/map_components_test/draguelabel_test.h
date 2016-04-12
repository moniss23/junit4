#ifndef DRAGUELABEL_TEST_H
#define DRAGUELABEL_TEST_H

#include <QtTest/QtTest>
#include "maps/traffic_map/map_components/draguelabel.h"

class DragUELabel_Test: public QObject
{
    Q_OBJECT
private slots:
    void testConstructor();
    void testDestructor();
    void testDoubleClickEvent();
    void testLabelText();
    void testSetMyArea();
    void testGetMyArea();

private:
    DragUELabel * myDragUELabelPtr;
};
#endif // DRAGUELABEL_TEST_H
