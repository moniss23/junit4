#ifndef TESTRUNNER_H
#define TESTRUNNER_H
#include <QTest>
#include <Maps/Traffic/MapTest/DataObjectsTest/HandoverDataTest/handoverdata_test.h>

#include <Maps/Traffic/MapTest/map_components_test/mapmanagement_test.h>
#include <Maps/Traffic/MapTest/map_components_test/myscrollareawidget_test.h>
#include <Maps/Traffic/MapTest/map_components_test/custommodellabel_test.h>
#include <Maps/Traffic/MapTest/map_components_test/statisticsbutton_test.h>
#include <Maps/Traffic/MapTest/map_components_test/timebutton_test.h>
#include <Maps/Traffic/MapTest/map_components_test/tuningtrafficbutton_test.h>
#include <Maps/Traffic/MapTest/map_components_test/scale_test.h>
#include <Maps/Traffic/MapTest/map_components_test/draguelabel_test.h>
#include <Maps/Traffic/MapTest/map_components_test/addbutton_test.h>
#include <Maps/Traffic/MapTest/map_components_test/cellarea_test.h>
#include <Maps/Traffic/MapTest/map_components_test/handoverarea_test.h>
#include <Maps/Traffic/MapTest/map_components_test/compositionofareas_test.h>

#include <AppSettings/appsettings.h>

#include <Maps/Traffic/MapTest/ue_param_test/uegroupdata_test.h>
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
