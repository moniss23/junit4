#ifndef COMPOSITIONOFAREAS_TEST_H
#define COMPOSITIONOFAREAS_TEST_H

#include <QtTest/QtTest>
#include <Maps/Traffic/MapComponents/compositionofareas.h>
#include <Maps/Traffic/MapComponents/cellarea.h>
#include <Maps/Traffic/MapComponents/handoverarea.h>
class CompositionOfAreas_Test: public QObject
{
    Q_OBJECT
private slots:
    void testConstructor();
    void testDestructor();
    void testAddToList();
    void testSize();
    void testGetID();
    void testContain();

private:
    CompositionOfAreas *myCompositionOfAreasPtr;
    CompositionOfAreas *my2ndCompositionOfAreasPtr;
    QList<HandoverArea *> myHandoverArea;
    QList<CellArea *> myCellArea;
    CellArea *myCell1Ptr, *myCell2Ptr;
};
#endif // COMPOSITIONOFAREAS_TEST_H
