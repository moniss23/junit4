#ifndef TESTT_H
#define TESTT_H

#include <QtWidgets>
#include <QtTest/QtTest>
#include <Maps/Traffic/MapComponents/mapmanagement.h>
class MapManagement_Test: public QObject
{
    Q_OBJECT
private slots:
    void testConstructor();
    void testDestructor();

private:
    MapManagement *mapManagementPtr;
};
#endif // TESTT_H
