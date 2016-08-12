#ifndef STATISTICSDATA_H
#define STATISTICSDATA_H

#include <QObject>
#include <QString>
#include <dataelementsinterface.h>
#include <QtXml>
#include <QMap>
#include <CommonConstans/common_constans.h>
#include <ProjectReaderWriter/projectreaderwriter.h>
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
    StatisticsData(QString &mapIndex, DataSystem *appSettings);

    StatisticsData& operator =(const StatisticsData& rhc);

    void setStatMap(Stats_settings &key, bool &value);
    void setStatMap(Stats_settings &key);
    bool getStatMap(Stats_settings &key);
    QString getStringFromEnum(int &enumVal);
    QString getMapIndex();
    Stats_settings getEnumFromString(QString &stringVal);
    bool stringToBool(QString &valString);
    QString boolToString(bool &valBool);

    //interface methods
    QString getElementType() const override;
    void serializeToProjectFile() override;
    void serializeFromProjectFileOld(QByteArray rawData) override;
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
    DataSystem *appSettings;

};

#endif // STATISTICSDATA_H
