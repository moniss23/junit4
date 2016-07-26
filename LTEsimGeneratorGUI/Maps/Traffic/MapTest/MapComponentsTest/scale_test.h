#ifndef SCALE_TEST_H
#define SCALE_TEST_H

#include <QtTest/QtTest>
#include <Maps/Traffic/MapComponents/scale.h>
class Scale_Test: public QObject
{
    Q_OBJECT
private slots:
    void testConstructor();
    void testDestructor();
    void testGetRealX();
    void testGetRealY();
    void testGetDisplayX();
    void testGetDisplayY();
    void testGetLengthOX();
    void testGetLengthOY();

private:
    Scale<double, int> *myScalePtr, *my2ndScalePtr;
};
#endif // SCALE_TEST_H
