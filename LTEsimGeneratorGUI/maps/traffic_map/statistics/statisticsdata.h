#ifndef STATISTICSDATA_H
#define STATISTICSDATA_H

#include <QObject>
#include <QString>
#include <dataelementsinterface.h>
#include <QtXml>
#include <common_constans.h>
#include <QMap>

enum class Stats_settings
{
    listStatInfoForEachUE,
    resetAllStatCount,
    listStatOnNAS,
    listStatOnRRC,
    listMobStatPerModelAndArea,
    listThrStatPerAreaAndModel,
    listThrStatPerUeAndModel,
    listMobStatPerUE,
    listPsStatPerModel,
    listPsStatPerUE,
    listCsStatPerModel,
    listCsStatPerUE,
    ipgwtgProtStat,
    ipgwtgTguStat,
    ipgwtgContStat,
    pdcp_uProtStat,
    pdcp_uRohcProtStat,
    pdcp_uGenBearerInfo,
    pdcp_uBearerRohcInfo,
    pdcp_uBearerErrStat,
    pdcp_uContStat
};

class StatisticsData : public QObject, DataElementsInterface
{
    Q_OBJECT
    Q_ENUM(Stats_settings)
public:
    StatisticsData(QString &mapIndex);
    void setStatMap(Stats_settings &key, bool &value);
    bool getStatMap(Stats_settings &key);

private:
    QMap<enum Stats_settings, bool> statMap;
    QString mapIndexCurrent;
    bool value;
    Stats_settings enumStat;

    //interface methods
    QString getElementType() const override {}
    void serializeToProjectFile() override {}
    void serializeFromProjectFileOld(QByteArray rawData) override {}
    void serializeFromProjectFileNew(QByteArray rawData) override {}
    void serializeToScriptCommands() override {}
};

#endif // STATISTICSDATA_H
