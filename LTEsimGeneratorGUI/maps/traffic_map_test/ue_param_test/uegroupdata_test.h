#ifndef UEGROUPDATA_TEST_H
#define UEGROUPDATA_TEST_H
#include <maps/traffic_map/ue_param/uegroupdata.h>
#include <dataelementsinterface.h>
#include <QtTest/QtTest>
#include <QObject>

class UEgroupData_Test : public QObject
{
    Q_OBJECT
public:
    explicit UEgroupData_Test(QObject *parent = 0);

    QString ueNameTest = "UE1";
    QString mapIndexTest = "Traffic Map 1";
    QString pairsNameTest = "UE Group Name 1 Test";
    int amountOfPairsTest = 600;
    QString mobilityModelTest = "RandomWalker";
    QString CSbehaviourModeTest = "PowerOnPowerOff";
    QString PSbehaviorModeTest = "No PS";
    QString ueTypeTest = "IratHO";
    QString areaTest = "Center_11";

private Q_SLOTS:

    //getters and setters
    void setgetUEnameTest();
    void setgetMapIndexTest();
    void setgetPairsNameTest();
    void setgetAmountOfPairsTest();
    void setgetMobilityModelTest();
    void setgetCSbehaviourModeTest();
    void setgetPSbehaviourModeTest();
    void setgetUEtypeTest();
    void setgetAreaTest();

    //read method
    void readDataFromProjTest();

    //save method
    void serializeToProjectFileTest();

    //serialisation
    void serializeFromProjectFileOldTest(QByteArray rawData);

};

#endif // UEGROUPDATA_TEST_H
