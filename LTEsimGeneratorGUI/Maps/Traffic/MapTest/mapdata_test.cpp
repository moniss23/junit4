#include "mapdata_test.h"

MapData_Test::MapData_Test(AppSettings *appSettings, QObject *parent)
    :  QObject(parent),appSettings(appSettings)
{
    //Creating new project for testing
    appSettings->setProjectName(testProjectName);
    QListWidgetItem* new_item = new QListWidgetItem(appSettings->getProjectName());
    projectMng->addWidgetToListWidget(new_item);
    appSettings->addProject(new_item,testProjectDir);
    projectMng->setButtonsStates(new_item);
}

MapData_Test::~MapData_Test()
{
    //Removing project file after tests
    QDir l_dir(testProjectDir + "/" + testProjectName);

    if(l_dir.exists() )
        l_dir.removeRecursively();
}

void MapData_Test::fillActiveCellListTest()
{
    MapData* mapTraffic = new MapData(testMapName, appSettings);
    mapTraffic->fillActiveCellList();
    QCOMPARE(mapTraffic->parameterLists.activeCellList.size(),24);
    delete mapTraffic;
}

void MapData_Test::fillHandoverListTest()
{
    MapData* mapTraffic = new MapData(testMapName, appSettings);
    mapTraffic->fillHandoverList();
    QCOMPARE(mapTraffic->parameterLists.handoverList.size(),53);
    delete mapTraffic;
}
