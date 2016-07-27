#ifndef TESTRUNNER_H
#define TESTRUNNER_H
#include <QTest>
#include <Maps/Traffic/MapTest/DataObjectsTest/HandoverDataTest/handoverdata_test.h>

#include <Maps/Traffic/MapTest/MapComponentsTest/mapmanagement_test.h>
#include <Maps/Traffic/MapTest/MapComponentsTest/myscrollareawidget_test.h>
#include <Maps/Traffic/MapTest/MapComponentsTest/custommodellabel_test.h>
#include <Maps/Traffic/MapTest/MapComponentsTest/statisticsbutton_test.h>
#include <Maps/Traffic/MapTest/MapComponentsTest/timebutton_test.h>
#include <Maps/Traffic/MapTest/MapComponentsTest/tuningtrafficbutton_test.h>
#include <Maps/Traffic/MapTest/MapComponentsTest/scale_test.h>
#include <Maps/Traffic/MapTest/MapComponentsTest/draguelabel_test.h>
#include <Maps/Traffic/MapTest/MapComponentsTest/addbutton_test.h>
#include <Maps/Traffic/MapTest/MapComponentsTest/cellarea_test.h>
#include <Maps/Traffic/MapTest/MapComponentsTest/handoverarea_test.h>
#include <Maps/Traffic/MapTest/MapComponentsTest/compositionofareas_test.h>

#include <AppSettings/appsettings.h>

#include <Maps/Traffic/MapTest/UeParametersTest/uegroupdata_test.h>
#include <Maps/Traffic/MapTest/statistics/statisticsdata_test.h>
#include <Maps/Traffic/MapTest/DataObjectsTest/CellDataTest/celldata_test.h>
#include <Maps/Traffic/MapTest/mapdata_test.h>
#include <Maps/Traffic/MapTest/mapdata_test.h>
#include <Maps/Traffic/MapTest/managementtemplate_test.h>


class TestRunner
{
public:
    TestRunner(AppSettings *appSettings) : appSettings(appSettings){}
    void runTests();

private:
    AppSettings *appSettings;

};

#endif // TESTRUNNER_H
