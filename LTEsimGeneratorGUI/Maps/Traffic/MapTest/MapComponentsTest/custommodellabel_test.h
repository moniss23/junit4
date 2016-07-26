#ifndef CUSTOMMODELLABEL_TEST_H
#define CUSTOMMODELLABEL_TEST_H

#include <QtTest/QtTest>
#include <Maps/Traffic/MapComponents/custommodellabel.h>
class CustomModelLabel_Test: public QObject
{
    Q_OBJECT
private slots:
    void testConstructor();
    void testDestructor();
    void testDoubleClickEvent();

private:
    CustomModelLabel *myCustomModelLabelPtr;
};

#endif // CUSTOMMODELLABEL_TEST_H
