#ifndef TESTRUNNER_H
#define TESTRUNNER_H
#include <maps/traffic_map_test/data_objects_test/handoverdata_test.h>
#include <maps/traffic_map_test/ue_param_test/uegroupdata_test.h>
#include <maps/traffic_map_test/statistics/statisticsdata_test.h>
#include <maps/traffic_map_test/data_objects_test/celldata_test.h>
#include <maps/traffic_map_test/mapdata_test.h>
#include <maps/traffic_map_test/managementtemplate_test.h>
#include <maps/traffic_map_test/map_components_test/mapmanagement_test.h>
#include <maps/traffic_map_test/map_components_test/myscrollareawidget_test.h>
#include <maps/traffic_map_test/map_components_test/custommodellabel_test.h>
#include <QTest>

class TestRunner
{
public:
    TestRunner(){}
    void runTests();
};

#endif // TESTRUNNER_H
