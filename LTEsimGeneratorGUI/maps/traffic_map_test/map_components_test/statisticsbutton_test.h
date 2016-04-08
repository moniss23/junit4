#ifndef STATISTICSBUTTON_TEST_H
#define STATISTICSBUTTON_TEST_H

#include <QtTest/QtTest>
#include "maps/traffic_map/map_components/statisticsbutton.h"

class StatisticsButton_Test: public QObject
{
    Q_OBJECT
private slots:
    void testConstructor();
    void testDestructor();
    void testPressEvent();

private:
    StatisticsButton *myStatisticsButtonPtr;
};
#endif // STATISTICSBUTTON_TEST_H
