#ifndef TIMEBUTTON_TEST_H
#define TIMEBUTTON_TEST_H

#include <QtTest/QtTest>
#include <Maps/Traffic/MapComponents/timebutton.h>
class TimeButton_Test: public QObject
{
    Q_OBJECT
private slots:
    void testConstructor();
    void testDestructor();
    void testPressEvent();

private:
    TimeButton *myTimeButtonPtr;
};
#endif // TIMEBUTTON_TEST_H
