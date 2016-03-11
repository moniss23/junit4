#include "uegroupdata_test.h"

UEgroupData_Test::UEgroupData_Test(QObject *parent) : QObject(parent)
{}

void UEgroupData_Test::setgetUEnameTest()
{
    UEgroupData* ueName = new UEgroupData(ueNameTest, mapIndexTest);
    QCOMPARE(ueName->getUEname(),ueNameTest);
    delete ueName;
}

void UEgroupData_Test::setgetMapIndexTest()
{
    UEgroupData* mapIndex = new UEgroupData(ueNameTest, mapIndexTest);
    QCOMPARE(mapIndex->getMapIndex(),mapIndexTest);
    delete mapIndex;
}

void UEgroupData_Test::setgetPairsNameTest()
{
    UEgroupData* pairsName = new UEgroupData(ueNameTest, mapIndexTest);
    pairsName->setPairsName(pairsNameTest);
    QCOMPARE(pairsName->getPairsName(),pairsNameTest);
    delete pairsName;
}

void UEgroupData_Test::setgetAmountOfPairsTest()
{
    UEgroupData* amountOfPairs = new UEgroupData(ueNameTest, mapIndexTest);
    amountOfPairs->setAmountOfPairs(amountOfPairsTest);
    QCOMPARE(amountOfPairs->getAmountOfPairs(),amountOfPairsTest);
    delete amountOfPairs;
}

void UEgroupData_Test::setgetMobilityModelTest()
{
    UEgroupData* mobilityModel = new UEgroupData(ueNameTest, mapIndexTest);
    mobilityModel->setMobilityModel(mobilityModelTest);
    QCOMPARE(mobilityModel->getMobilityModel(),mobilityModelTest);
    delete mobilityModel;
}

void UEgroupData_Test::setgetCSbehaviourModeTest()
{
    UEgroupData* CSbehaviourMode = new UEgroupData(ueNameTest, mapIndexTest);
    CSbehaviourMode->setCSbehaviourMode(CSbehaviourModeTest);
    QCOMPARE(CSbehaviourMode->getCSbehaviourMode(),CSbehaviourModeTest);
    delete CSbehaviourMode;
}

void UEgroupData_Test::setgetPSbehaviourModeTest()
{
    UEgroupData* PSbehaviorMode = new UEgroupData(ueNameTest, mapIndexTest);
    PSbehaviorMode->setPSbehaviourMode(PSbehaviorModeTest);
    QCOMPARE(PSbehaviorMode->getPSbehaviourMode(),PSbehaviorModeTest);
    delete PSbehaviorMode;
}

void UEgroupData_Test::setgetUEtypeTest()
{
    UEgroupData* ueType = new UEgroupData(ueNameTest, mapIndexTest);
    ueType->setUEtype(ueTypeTest);
    QCOMPARE(ueType->getUEtype(),ueTypeTest);
    delete ueType;
}

void UEgroupData_Test::setgetAreaTest()
{
    UEgroupData* area = new UEgroupData(ueNameTest, mapIndexTest);
    area->setArea(areaTest);
    QCOMPARE(area->getArea(),areaTest);
    delete area;
}

void UEgroupData_Test::readDataFromProjTest()
{
    QString projectFileName = QString("projects/" + testProjectName + "/" + testProjectName + ".xml");
    QFile testFile(projectFileName);
    QByteArray testArray;
    UEgroupData* ueGroup = new UEgroupData(ueNameTest, mapIndexTest);
    const char* testPhrase = "<UE>\n</UE>";
    testArray = ueGroup->readDataFromProj();

    if(!testFile.exists() )
    {
        QCOMPARE(testArray.size(),0);
    }
    else
    {
        QVERIFY(testArray.contains(testPhrase) );
    }
}

void UEgroupData_Test::serializeToProjectFileTest(){}

void UEgroupData_Test::serializeFromProjectFileOldTest(QByteArray rawData){}
