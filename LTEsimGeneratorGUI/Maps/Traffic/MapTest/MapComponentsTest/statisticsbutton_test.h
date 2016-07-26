#ifndef STATISTICSBUTTON_TEST_H
#define STATISTICSBUTTON_TEST_H

#include <QtTest/QtTest>
#include <Maps/Traffic/MapComponents/statisticsbutton.h>

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
