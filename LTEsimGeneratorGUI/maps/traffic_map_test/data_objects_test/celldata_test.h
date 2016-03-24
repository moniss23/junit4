#ifndef CELLDATA_TEST_H
#define CELLDATA_TEST_H
#include <QtTest/QtTest>
#include <QObject>
#include <maps/traffic_map/data_objects/celldata.h>

extern QString* projectName;
extern ProjectManagement* projectMng;

class CellData_Test : public QObject
{
    Q_OBJECT
public:
    explicit CellData_Test (QObject *parent = 0);
    ~CellData_Test();

    QString cellName1 = "cell11";
    QString cellName2 = "cell33";
    QString centerName1 = "Center11";
    QString centerName2 = "Center33";
    QString testOperatorsFile = "operators";
    int testNumber1 = 11;
    float testNumber2 = 6900;
    QString testProjectName = "test";
    QString testProjectDir = "projects";
    const char* testPhrase = "cell11";

private Q_SLOTS:

    void setgetCellNameTest();
    void setgetCenterNameTest();
    void setgetPciTest();
    void setgetPositionXTest();
    void setgetPositionYTest();
    void setgetEarfcnDlTest();
    void setgetTransmitPowerTest();
    void setgetUlNoiseAndInterferenceTest();
    void setgetSouthBoundaryTest();
    void setgetNorthBoundaryTest();
    void setgetEastBoundaryTest();
    void setgetWestBoundaryTest();
    void serializeDeserializeCellOperatorTest();
    void parseCellDataFromListTest();
    void parseCenterDataFromListTest();
    void serializeFromProjFileOldTest();

};


#endif // CELLDATA_TEST_H
