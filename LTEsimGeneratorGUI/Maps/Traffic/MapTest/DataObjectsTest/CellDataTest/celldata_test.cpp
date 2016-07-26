#include "celldata_test.h"
#include <AppSettings/appsettings.h>

CellData_Test::CellData_Test(AppSettings *appSettings, QObject *parent) :
    QObject(parent), appSettings(appSettings)
{
    //Creating new project for testing
    appSettings->setProjectName(testProjectName);
    QListWidgetItem* new_item = new QListWidgetItem(appSettings->getProjectName());
    projectMng->addProject(new_item,testProjectDir);

}

CellData_Test::~CellData_Test()
{
    //Removing project file after tests
    QDir l_dir(testProjectDir + "/" + testProjectName);

    if(l_dir.exists() )
        l_dir.removeRecursively();

}

void CellData_Test::setgetCellNameTest()
{

    CellData* cell11 = new CellData(cellName1,centerName1, appSettings);
    cell11->setCellName(cellName2);
    QCOMPARE(cell11->getCellName(),cellName2);

}

void CellData_Test::setgetCenterNameTest()
{
    CellData* cell11 = new CellData(cellName1,centerName1, appSettings);
    cell11->setCenterName(centerName2);
    QCOMPARE(cell11->getCenterName(),centerName2);
}

void CellData_Test::setgetPciTest()
{
    CellData* cell11 = new CellData(cellName1,centerName1, appSettings);
    cell11->setPci(testNumber1);
    QCOMPARE(cell11->getPci(),testNumber1);

}

void CellData_Test::setgetPositionXTest()
{
    CellData* cell11 = new CellData(cellName1,centerName1, appSettings);
    cell11->setPosition_X(testNumber1);
    QCOMPARE(cell11->getPosition_X(),testNumber1);
}

void CellData_Test::setgetPositionYTest()
{
    CellData* cell11 = new CellData(cellName1,centerName1, appSettings);
    cell11->setPosition_Y(testNumber1);
    QCOMPARE(cell11->getPosition_Y(),testNumber1);
}

void CellData_Test::setgetEarfcnDlTest()
{
    CellData* cell11 = new CellData(cellName1,centerName1, appSettings);
    cell11->setEarfcnDl(testNumber1);
    QCOMPARE(cell11->getEarfcnDl(),testNumber1);
}

void CellData_Test::setgetTransmitPowerTest()
{
    CellData* cell11 = new CellData(cellName1,centerName1,appSettings);
    cell11->setTransmitPower(testNumber2);
    QCOMPARE(cell11->getTransmitPower(),testNumber2);
}

void CellData_Test::setgetUlNoiseAndInterferenceTest()
{
    CellData* cell11 = new CellData(cellName1,centerName1, appSettings);
    cell11->setUlNoiseAndInterference(testNumber2);
    QCOMPARE(cell11->getUlNoiseAndInterference(),testNumber2);
}

void CellData_Test::setgetSouthBoundaryTest()
{
    CellData* cell11 = new CellData(cellName1,centerName1, appSettings);
    cell11->setSouthCellBoundary(testNumber1);
    QCOMPARE(cell11->getSouthCellBoundary(),testNumber1);
}

void CellData_Test::setgetNorthBoundaryTest()
{
    CellData* cell11 = new CellData(cellName1,centerName1, appSettings);
    cell11->setNorthCellBoundary(testNumber1);
    QCOMPARE(cell11->getNorthCellBoundary(),testNumber1);
}

void CellData_Test::setgetEastBoundaryTest()
{
    CellData* cell11 = new CellData(cellName1,centerName1, appSettings);
    cell11->setEastCellBoundary(testNumber1);
    QCOMPARE(cell11->getEastCellBoundary(),testNumber1);
}

void CellData_Test::setgetWestBoundaryTest()
{
    CellData* cell11 = new CellData(cellName1,centerName1, appSettings);
    cell11->setWestCellBoundary(testNumber1);
    QCOMPARE(cell11->getWestCellBoundary(),testNumber1);
}

void CellData_Test::serializeDeserializeCellOperatorTest()
{
    QFile projFile(testProjectDir + "/" + testProjectName + "/" + testOperatorsFile);
    CellParams params;
    CellParams params2;
    params.cellName = cellName1;
    params.cellPosition.setX(testNumber1);
    params.cellPosition.setY(testNumber1);
    params.earfcnDl = testNumber1;
    params.pci = testNumber1;
    params.transmitPower = testNumber2;
    params.ulNoiseAndInterference = testNumber2;
    params.centerParams.centerArea.setTop(testNumber1);


    //-------Serialize params to file-----------------
    QDataStream dataStreamWriter(&projFile);
    projFile.open(QIODevice::WriteOnly);
    dataStreamWriter << params;
    projFile.close();

    //-------Deserialize params from file-------------
    QDataStream dataStreamReader(&projFile);
    projFile.open(QIODevice::ReadOnly);
    dataStreamReader >> params2;
    projFile.close();

    QCOMPARE(params2.cellName,cellName1);
    QCOMPARE(params2.cellPosition.x(),testNumber1);
    QCOMPARE(params2.cellPosition.y(),testNumber1);
    QCOMPARE(params2.earfcnDl,testNumber1);
    QCOMPARE(params2.pci,testNumber1);
    QCOMPARE(params2.transmitPower,testNumber2);
    QCOMPARE(params2.ulNoiseAndInterference,testNumber2);
    QCOMPARE(params2.centerParams.centerArea.top(),testNumber1);

}

void CellData_Test::parseCellDataFromListTest()
{
    CellData* cell11 = new CellData(cellName1,centerName1, appSettings);
    CellParams paramsStruct;
    QByteArray testCellArray;
    testCellArray = projectReaderWriter->readDataFromProj(beginningOfCellSector,endOfCellSector);
    QString testCellString(testCellArray);
    QStringList testCellList = testCellString.split('\n');
    paramsStruct = cell11->parseCellDataFromList(testCellList);
    QCOMPARE(paramsStruct.cellName,cellName1);
    QCOMPARE(paramsStruct.pci,testNumber1);
}

void CellData_Test::parseCenterDataFromListTest()
{
    CellData* cell11 = new CellData(cellName1,centerName1, appSettings);
    CenterParams paramsStruct;
    QByteArray testCenterArray;
    testCenterArray = projectReaderWriter->readDataFromProj(beginningOfCellSector,endOfCellSector);
    QString testCenterString(testCenterArray);
    QStringList testCenterList = testCenterString.split('\n');
    paramsStruct = cell11->parseCenterDataFromList(testCenterList);
    QCOMPARE(paramsStruct.centerName,centerName1);
    QCOMPARE(paramsStruct.centerArea.bottom(),(int)testNumber2);
}

void CellData_Test::serializeFromProjFileOldTest()
{
    QByteArray loadedData;
    loadedData = projectReaderWriter->readDataFromProj(beginningOfCellSector,endOfCellSector);

    CellData* cell11 = new CellData(cellName1,centerName1, appSettings);

    cell11->serializeFromProjectFileOld(loadedData);
    QCOMPARE(cell11->getPci(),testNumber1);
    QCOMPARE(cell11->getSouthCellBoundary(),(int)testNumber2);
}

void CellData_Test::setProjectReaderWriter(ProjectReaderWriter *value)
{
    projectReaderWriter = value;
}
