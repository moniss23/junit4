#ifndef TUNINGTRAFFICBUTTON_TEST_H
#define TUNINGTRAFFICBUTTON_TEST_H

#include <QtTest/QtTest>
#include "maps/traffic_map/map_components/tuningtrafficbutton.h"

class TuningTrafficButton_Test: public QObject
{
    Q_OBJECT
private slots:
    void testConstructor();
    void testDestructor();
    void testPressEvent();

private:
    TuningTrafficButton *myTuningTrafficButtonPtr;
};
#endif // TUNINGTRAFFICBUTTON_TEST_H
