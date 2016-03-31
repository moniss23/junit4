#ifndef STATISTICSDATA_TEST_H
#define STATISTICSDATA_TEST_H

#include <QObject>
#include <maps/traffic_map/statistics/statisticsdata.h>
#include <QtTest/QtTest>

class StatisticsData_Test : public QObject
{
    Q_OBJECT
public:
    explicit StatisticsData_Test(QObject *parent = 0);
    QString mapIndexTest = "mapa";
    bool valueTest = true;
    QString statXmlString = "<statistics>\n <listStatInfoForEachUE>false</listStatInfoForEachUE>\n <resetAllStatCount>false</resetAllStatCount>\n <listStatOnNAS>false</listStatOnNAS>\n <listStatOnRRC>false</listStatOnRRC>\n <listMobStatPerModelAndArea>false</listMobStatPerModelAndArea>\n <listThrStatPerAreaAndModel>false</listThrStatPerAreaAndModel>\n <listThrStatPerUeAndModel>false</listThrStatPerUeAndModel>\n <listMobStatPerUE>false</listMobStatPerUE>\n <listPsStatPerModel>false</listPsStatPerModel>\n <listPsStatPerUE>false</listPsStatPerUE>\n <listCsStatPerModel>false</listCsStatPerModel>\n <listCsStatPerUE>false</listCsStatPerUE>\n <ipgwtgProtStat>false</ipgwtgProtStat>\n <ipgwtgTguStat>false</ipgwtgTguStat>\n <ipgwtgContStat>false</ipgwtgContStat>\n <pdcp_uProtStat>false</pdcp_uProtStat>\n <pdcp_uRohcProtStat>false</pdcp_uRohcProtStat>\n <pdcp_uGenBearerInfo>false</pdcp_uGenBearerInfo>\n <pdcp_uBearerRohcInfo>false</pdcp_uBearerRohcInfo>\n <pdcp_uBearerErrStat>false</pdcp_uBearerErrStat>\n <pdcp_uContStat>false</pdcp_uContStat>\n</statistics>\n";
    QMap<enum Stats_settings, bool> statMapTest;
    QDomDocument xmlStatTest;

private Q_SLOTS:
    void setGetStatisticsParamTest();
    void serializeToProjectFileTest();
    void serializeFromProjectFileNewTest();
};

#endif // STATISTICSDATA_TEST_H
