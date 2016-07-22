#include "uegroupdata_test.h"

UEgroupData_Test::UEgroupData_Test(AppSettings *appSettings, QObject *parent)
    : QObject(parent), appSettings(appSettings)
{}

void UEgroupData_Test::setgetUEnameTest()
{
    UEgroupData* ueName = new UEgroupData(ueNameTest, mapIndexTest, appSettings);
    QCOMPARE(ueName->getUEname(),ueNameTest);
    delete ueName;
}

void UEgroupData_Test::setgetMapIndexTest()
{
    UEgroupData* mapIndex = new UEgroupData(ueNameTest, mapIndexTest, appSettings);
    QCOMPARE(mapIndex->getMapIndex(),mapIndexTest);
    delete mapIndex;
}

void UEgroupData_Test::setgetPairsNameTest()
{
    UEgroupData* pairsName = new UEgroupData(ueNameTest, mapIndexTest, appSettings);
    pairsName->setPairsName(pairsNameTest);
    QCOMPARE(pairsName->getPairsName(),pairsNameTest);
    delete pairsName;
}

void UEgroupData_Test::setgetAmountOfPairsTest()
{
    UEgroupData* amountOfPairs = new UEgroupData(ueNameTest, mapIndexTest, appSettings);
    amountOfPairs->setAmountOfPairs(amountOfPairsTest);
    QCOMPARE(amountOfPairs->getAmountOfPairs(),amountOfPairsTest);
    delete amountOfPairs;
}

void UEgroupData_Test::setgetMobilityModelTest()
{
    UEgroupData* mobilityModel = new UEgroupData(ueNameTest, mapIndexTest, appSettings);
    mobilityModel->setMobilityModel(mobilityModelTest);
    QCOMPARE(mobilityModel->getMobilityModel(),mobilityModelTest);
    delete mobilityModel;
}

void UEgroupData_Test::setgetCSbehaviourModeTest()
{
    UEgroupData* CSbehaviourMode = new UEgroupData(ueNameTest, mapIndexTest, appSettings);
    CSbehaviourMode->setCSbehaviourMode(CSbehaviourModeTest);
    QCOMPARE(CSbehaviourMode->getCSbehaviourMode(),CSbehaviourModeTest);
    delete CSbehaviourMode;
}

void UEgroupData_Test::setgetPSbehaviourModeTest()
{
    UEgroupData* PSbehaviorMode = new UEgroupData(ueNameTest, mapIndexTest, appSettings);
    PSbehaviorMode->setPSbehaviourMode(PSbehaviorModeTest);
    QCOMPARE(PSbehaviorMode->getPSbehaviourMode(),PSbehaviorModeTest);
    delete PSbehaviorMode;
}

void UEgroupData_Test::setgetUEtypeTest()
{
    UEgroupData* ueType = new UEgroupData(ueNameTest, mapIndexTest, appSettings);
    ueType->setUEtype(ueTypeTest);
    QCOMPARE(ueType->getUEtype(),ueTypeTest);
    delete ueType;
}

void UEgroupData_Test::setgetAreaTest()
{
    UEgroupData* area = new UEgroupData(ueNameTest, mapIndexTest, appSettings);
    area->setArea(areaTest);
    QCOMPARE(area->getArea(),areaTest);
    delete area;
}

void UEgroupData_Test::serializeToProjectFileTest()
{
    QDomElement ueGroupXmlElementTest = xmlUePartTest.createElement("UE");
    xmlUePartTest.appendChild(ueGroupXmlElementTest);

    ueGroupXmlElementTest.setAttribute("ID", ueNameTest);
    QDomElement pairsNameXmlElementTest = xmlUePartTest.createElement("pairsName");
    QDomElement amountOfPairsXmlElementTest = xmlUePartTest.createElement("amountOfPairs");
    QDomElement mobilityModelXmlElementTest = xmlUePartTest.createElement("mobilityModel");
    QDomElement csBehaviorModeXmlElementTest = xmlUePartTest.createElement("CSbehaviorMode");
    QDomElement psBehaviorModeXmlElementTest = xmlUePartTest.createElement("PSbehaviorMode");
    QDomElement ueTypeXmlElementTest = xmlUePartTest.createElement("UEtype");
    QDomElement areaXmlElementTest = xmlUePartTest.createElement("area");

    ueGroupXmlElementTest.appendChild(pairsNameXmlElementTest);
    ueGroupXmlElementTest.appendChild(amountOfPairsXmlElementTest);
    ueGroupXmlElementTest.appendChild(mobilityModelXmlElementTest);
    ueGroupXmlElementTest.appendChild(csBehaviorModeXmlElementTest);
    ueGroupXmlElementTest.appendChild(psBehaviorModeXmlElementTest);
    ueGroupXmlElementTest.appendChild(ueTypeXmlElementTest);
    ueGroupXmlElementTest.appendChild(areaXmlElementTest);

    QDomText pairsNameXmlTextTest = xmlUePartTest.createTextNode(pairsNameTest);
    QDomText amountOfPairsXmlTextTest = xmlUePartTest.createTextNode(QString::number(amountOfPairsTest) );
    QDomText mobilityModelXmlTextTest = xmlUePartTest.createTextNode(mobilityModelTest);
    QDomText csBehaviorModeXmlTextTest = xmlUePartTest.createTextNode(CSbehaviourModeTest);
    QDomText psBehaviorModeXmlTextTest = xmlUePartTest.createTextNode(PSbehaviorModeTest);
    QDomText ueTypeXmlTextTest = xmlUePartTest.createTextNode(ueTypeTest);
    QDomText areaXmlTextTest = xmlUePartTest.createTextNode(areaTest);

    pairsNameXmlElementTest.appendChild(pairsNameXmlTextTest);
    amountOfPairsXmlElementTest.appendChild(amountOfPairsXmlTextTest);
    mobilityModelXmlElementTest.appendChild(mobilityModelXmlTextTest);
    csBehaviorModeXmlElementTest.appendChild(csBehaviorModeXmlTextTest);
    psBehaviorModeXmlElementTest.appendChild(psBehaviorModeXmlTextTest);
    ueTypeXmlElementTest.appendChild(ueTypeXmlTextTest);
    areaXmlElementTest.appendChild(areaXmlTextTest);
    QCOMPARE(xmlUePartTest.toString(), xmlQstring);
}

void UEgroupData_Test::serializeFromProjectFileNewTest()
{
    UEgroupData* ueGroup = new UEgroupData(ueNameTest, mapIndexTest, appSettings);
    UEgroupData* ueGroup2 = new UEgroupData(ueNameTest, mapIndexTest, appSettings);
    ueGroup->serializeToProjectFile();
    delete ueGroup;
    ueGroup2->serializeFromProjectFileNew(xmlUePartTest);
    QCOMPARE(ueGroup2->getPairsName(), pairsNameTest);
    QCOMPARE(ueGroup2->getAmountOfPairs(), amountOfPairsTest);
    QCOMPARE(ueGroup2->getMobilityModel(), mobilityModelTest);
    QCOMPARE(ueGroup2->getCSbehaviourMode(), CSbehaviourModeTest);
    QCOMPARE(ueGroup2->getPSbehaviourMode(), PSbehaviorModeTest);
    QCOMPARE(ueGroup2->getUEtype(), ueTypeTest);
    QCOMPARE(ueGroup2->getArea(), areaTest);
}
