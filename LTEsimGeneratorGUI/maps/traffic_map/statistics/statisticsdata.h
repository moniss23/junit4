#ifndef STATISTICSDATA_H
#define STATISTICSDATA_H

#include <QObject>
#include <QString>
#include <dataelementsinterface.h>
#include <QtXml>
#include <common_constans.h>
#include <QMap>
#include <maps/projectreaderwriter.h>

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
    StatisticsData(QString &mapIndex, AppSettings *appSettings);
    void setStatMap(Stats_settings &key, bool &value);
    bool getStatMap(Stats_settings &key);
    QString getStringFromEnum(int &enumVal);
    Stats_settings getEnumFromString(QString &stringVal);
    bool stringToBool(QString &valString);
    QString boolToString(bool &valBool);

    //interface methods
    QString getElementType() const override {}
    void serializeToProjectFile() override;
    void serializeFromProjectFileOld(QByteArray rawData) override {}
    void serializeFromProjectFileNew(QDomDocument xmlDocument) override;
    void serializeToScriptCommands() override {}

    void setProjectReaderWriter(ProjectReaderWriter *value);

private:
    QMap<enum Stats_settings, bool> statMap;
    QString mapIndexCurrent;
    bool value;
    Stats_settings enumStat;
    QDomDocument xmlStatisticsPart;
    QStringList enumStatString;
    QList<QDomElement> elementsXmlList;
    QList<QDomText> textXmlList;

    ProjectReaderWriter* projectReaderWriter;
    AppSettings *appSettings;

};

#endif // STATISTICSDATA_H
