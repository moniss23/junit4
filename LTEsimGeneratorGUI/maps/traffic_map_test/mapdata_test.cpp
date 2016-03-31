#include "mapdata_test.h"

MapData_Test::MapData_Test(QObject *parent) : QObject(parent)
{
    //Creating new project for testing
    *projectName = testProjectName;
    QListWidgetItem* new_item = new QListWidgetItem(*projectName);
    projectMng->addProject(new_item,testProjectDir);

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
    MapData* mapTraffic = new MapData(testMapName,true);
    mapTraffic->fillActiveCellList();
    QCOMPARE(mapTraffic->parameterLists.activeCellList.size(),24);
    delete mapTraffic;
}

void MapData_Test::fillHandoverListTest()
{
    MapData* mapTraffic = new MapData(testMapName,true);
    mapTraffic->fillHandoverList();
    QCOMPARE(mapTraffic->parameterLists.handoverList.size(),53);
    delete mapTraffic;
}
