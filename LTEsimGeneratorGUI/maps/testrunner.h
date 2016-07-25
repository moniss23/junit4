#ifndef TESTRUNNER_H
#define TESTRUNNER_H
#include <QTest>

#include <maps/traffic_map_test/data_objects_test/handoverdata_test.h>
#include <maps/traffic_map_test/ue_param_test/uegroupdata_test.h>
#include <maps/traffic_map_test/statistics/statisticsdata_test.h>
#include <maps/traffic_map_test/data_objects_test/celldata_test.h>
#include <maps/traffic_map_test/mapdata_test.h>
#include <maps/traffic_map_test/managementtemplate_test.h>
#include <maps/traffic_map_test/map_components_test/mapmanagement_test.h>
#include <maps/traffic_map_test/map_components_test/myscrollareawidget_test.h>
#include <maps/traffic_map_test/map_components_test/custommodellabel_test.h>
#include <maps/traffic_map_test/map_components_test/statisticsbutton_test.h>
#include <maps/traffic_map_test/map_components_test/timebutton_test.h>
#include <maps/traffic_map_test/map_components_test/tuningtrafficbutton_test.h>
#include <maps/traffic_map_test/map_components_test/scale_test.h>
#include <maps/traffic_map_test/map_components_test/draguelabel_test.h>
#include <maps/traffic_map_test/map_components_test/addbutton_test.h>
#include <maps/traffic_map_test/map_components_test/cellarea_test.h>
#include <maps/traffic_map_test/map_components_test/handoverarea_test.h>
#include <maps/traffic_map_test/map_components_test/compositionofareas_test.h>

#include "appsettings.h"

class TestRunner
{
public:
    TestRunner(AppSettings *appSettings) : appSettings(appSettings){}
    void runTests();

private:
    AppSettings *appSettings;

};

#endif // TESTRUNNER_H
