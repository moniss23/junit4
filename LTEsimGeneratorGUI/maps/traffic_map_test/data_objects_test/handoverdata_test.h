#ifndef HANDOVERDATA_TEST_H
#define HANDOVERDATA_TEST_H
#include <maps/traffic_map/data_objects/handoverdata.h>
#include <QtTest/QtTest>
#include <QObject>
#include <QString>

class HandoverData_Test : public QObject
{
    Q_OBJECT
public:
    explicit HandoverData_Test(QObject *parent = 0);

    QString handoverName1 = "Handover11_12";
    QString handoverName2 = "Handover21_22";
    QString testNumber = "1000";

private Q_SLOTS:

    void getHandoverNameTest();
    void setHandoverNameTest();
    void setgetSouthBoundaryTest();
    void setgetNorthBoundaryTest();
    void setgetEastBoundaryTest();
    void setgetWestBoundaryTest();

};

#endif // HANDOVERDATA_TEST_H
