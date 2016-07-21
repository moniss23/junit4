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
    explicit UEgroupData_Test(AppSettings *appSettings, QObject *parent = 0);

    QString ueNameTest = "UE1";
    QString mapIndexTest = "Traffic Map 1";
    QString pairsNameTest = "UE Group Name 1 Test";
    int amountOfPairsTest = 600;
    QString mobilityModelTest = "RandomWalker";
    QString CSbehaviourModeTest = "PowerOnPowerOff";
    QString PSbehaviorModeTest = "No PS";
    QString ueTypeTest = "IratHO";
    QString areaTest = "Center_11";
    QString testProjectName = "xmlTestFile";
    QString xmlQstring = "<UE ID=\"UE1\">\n <pairsName>UE Group Name 1 Test</pairsName>\n <amountOfPairs>600</amountOfPairs>\n <mobilityModel>RandomWalker</mobilityModel>\n <CSbehaviorMode>PowerOnPowerOff</CSbehaviorMode>\n <PSbehaviorMode>No PS</PSbehaviorMode>\n <UEtype>IratHO</UEtype>\n <area>Center_11</area>\n</UE>\n";
    QDomDocument xmlUePartTest;

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

    //save method
    void serializeToProjectFileTest();

    //serialisation
    void serializeFromProjectFileNewTest();

private:
    AppSettings *appSettings;

};

#endif // UEGROUPDATA_TEST_H
