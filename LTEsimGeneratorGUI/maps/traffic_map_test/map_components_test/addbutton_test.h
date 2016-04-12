#ifndef ADDBUTTON_TEST_H
#define ADDBUTTON_TEST_H

#include <QtTest/QtTest>
#include "maps/traffic_map/map_components/addbutton.h"

class AddButton_Test: public QObject
{
    Q_OBJECT
private slots:
    void testConstructor();
    void testDestructor();
    void testPressEvent();

private:
    AddButton *myAddButtonPtr;
};
#endif // ADDBUTTON_TEST_H
