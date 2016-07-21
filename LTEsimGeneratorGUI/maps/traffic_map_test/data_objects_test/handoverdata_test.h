#ifndef HANDOVERDATA_TEST_H
#define HANDOVERDATA_TEST_H
#include <maps/traffic_map/data_objects/handoverdata.h>
#include <common_constans.h>
#include <QtTest/QtTest>
#include <QObject>
#include <QString>
#include "maps/projectreaderwriter.h"
#include "appsettings.h"


class HandoverData_Test : public QObject
{
    Q_OBJECT
public:
    explicit HandoverData_Test(AppSettings *appSettings, QObject *parent = 0);
    ~HandoverData_Test();

    QString handoverName1 = "Handover11_21";
    QString handoverName2 = "Handover21_22";
    QString testOperatorsFile = "operators";
    QString testProjectName = "test";
    QString testProjectDir = "projects";
    HandoverParams testParams;
    const char* testPhrase = "Handover11_12";
    int testNumber = 7750;

    void setProjectReaderWriter(ProjectReaderWriter *value);

private Q_SLOTS:

    void getHandoverNameTest();
    void setHandoverNameTest();
    void setgetSouthBoundaryTest();
    void setgetNorthBoundaryTest();
    void setgetEastBoundaryTest();
    void setgetWestBoundaryTest();
    void getElementTypeTest();
    void serializeDeserializeOperatorTest();
    void parseDataFromListTest();
    void serializeFromProjectFileOldTest();
private:
    ProjectReaderWriter* projectReaderWriter;
    AppSettings *appSettings;

};

#endif // HANDOVERDATA_TEST_H
