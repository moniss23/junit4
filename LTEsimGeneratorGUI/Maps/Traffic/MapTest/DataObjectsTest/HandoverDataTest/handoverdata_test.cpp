#include <Maps/Traffic/MapTest/DataObjectsTest/HandoverDataTest/handoverdata_test.h>
HandoverData_Test::HandoverData_Test(AppSettings *appSettings, QObject *parent) :
   QObject(parent), appSettings(appSettings)
{
    //Creating project file just for testing
    appSettings->setProjectName(testProjectName);
    QListWidgetItem* newItem = new QListWidgetItem(appSettings->getProjectName());
    projectMng->addWidgetToListWidget(newItem);
    appSettings->addProject(newItem,testProjectDir);
    projectMng->setButtonsStates(newItem);

    projectReaderWriter = new ProjectReaderWriter(appSettings);
}

HandoverData_Test::~HandoverData_Test()
{
    //Removing project file after tests
    QDir dir(testProjectDir + "/" + testProjectName);

    if(dir.exists() )
        dir.removeRecursively();
}

void HandoverData_Test::getHandoverNameTest()
{
    HandoverData* handover = new HandoverData(handoverName1, appSettings);
    QCOMPARE(handover->getHandoverName(),handoverName1);
    delete handover;
}

void HandoverData_Test::setHandoverNameTest()
{
    HandoverData* handover = new HandoverData(handoverName1, appSettings);
    handover->setHandoverName(handoverName2);
    QCOMPARE(handover->getHandoverName(),handoverName2);
    delete handover;
}

void HandoverData_Test::setgetSouthBoundaryTest()
{
    HandoverData* handover = new HandoverData(handoverName1, appSettings);
    handover->setSouthBoundary(testNumber);
    QCOMPARE(handover->getSouthBoundary(),testNumber);
    delete handover;
}

void HandoverData_Test::setgetNorthBoundaryTest()
{
    HandoverData* handover = new HandoverData(handoverName1, appSettings);
    handover->setNorthBoundary(testNumber);
    QCOMPARE(handover->getNorthBoundary(),testNumber);
    delete handover;
}

void HandoverData_Test::setgetEastBoundaryTest()
{
    HandoverData* handover = new HandoverData(handoverName1, appSettings);
    handover->setEastBoundary(testNumber);
    QCOMPARE(handover->getEastBoundary(),testNumber);
    delete handover;
}

void HandoverData_Test::setgetWestBoundaryTest()
{
    HandoverData* handover = new HandoverData(handoverName1, appSettings);
    handover->setWestBoundary(testNumber);
    QCOMPARE(handover->getWestBoundary(),testNumber);
    delete handover;
}

void HandoverData_Test::getElementTypeTest()
{
    HandoverData* handover = new HandoverData(handoverName1, appSettings);
    QCOMPARE(handover->getElementType(),QString("Handover") );
    delete handover;
}

void HandoverData_Test::serializeDeserializeOperatorTest()
{
    QFile projFile(testProjectDir + "/" + testProjectName + "/" + testOperatorsFile);
    HandoverParams params;
    HandoverParams params2;
    params.handoverName = handoverName1;
    params.handoverArea.setBottom(testNumber);
    params.handoverArea.setTop(testNumber);
    params.handoverArea.setLeft(testNumber);
    params.handoverArea.setRight(testNumber);

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

    QCOMPARE(params2.handoverName,handoverName1);
    QCOMPARE(params2.handoverArea.top(),testNumber);
    QCOMPARE(params2.handoverArea.bottom(),testNumber);
    QCOMPARE(params2.handoverArea.left(),testNumber);
    QCOMPARE(params2.handoverArea.right(),testNumber);
}

void HandoverData_Test::parseDataFromListTest()
{
    HandoverData* handover = new HandoverData(handoverName1, appSettings);
    HandoverParams paramsStruct;
    QByteArray testDataArray;

    testDataArray = projectReaderWriter->readDataFromProj(beginningOfHandoverSector,endOfHandoverSector);

    QString testHandoverString(testDataArray);
    QStringList testHandoverList = testHandoverString.split('\n');
    paramsStruct = handover->parseDataFromList(testHandoverList);

    QCOMPARE(paramsStruct.handoverName,handoverName1);
    QCOMPARE(paramsStruct.handoverArea.bottom(),testNumber);
    delete handover;
}

void HandoverData_Test::serializeFromProjectFileOldTest()
{
    HandoverData* handover = new HandoverData(handoverName1, appSettings);
    QByteArray testDataArray;

    testDataArray = projectReaderWriter->readDataFromProj(beginningOfHandoverSector,endOfHandoverSector);

    handover->serializeFromProjectFileOld(testDataArray);

    QCOMPARE(handover->getHandoverName(),handoverName1);
    QCOMPARE(handover->getSouthBoundary(),testNumber);
    delete handover;
}

void HandoverData_Test::setProjectReaderWriter(ProjectReaderWriter *value)
{
    projectReaderWriter = value;
}
