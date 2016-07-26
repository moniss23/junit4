#ifndef CELLAREA_TEST_H
#define CELLAREA_TEST_H

#include <QtTest/QtTest>
#include <Maps/Traffic/MapComponents/cellarea.h>
class CellArea_Test: public QObject
{
    Q_OBJECT
private slots:
    void testConstructor();
    void testDestructor();
    void testGetID();
    void testGetCenter();
    void testGetR();
    void testContain();

private:
    CellArea *myCellAreaPtr;
};
#endif // CELLAREA_TEST_H
