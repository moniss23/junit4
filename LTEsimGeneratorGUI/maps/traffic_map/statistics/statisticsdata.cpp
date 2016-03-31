#include "statisticsdata.h"
#include <QDebug>

StatisticsData::StatisticsData(QString &mapIndex)
{
    mapIndexCurrent = mapIndex;
    enumStatString << "listStatInfoForEachUE" << "resetAllStatCount" << "listStatOnNAS" << "listStatOnRRC" << "listMobStatPerModelAndArea" << "listThrStatPerAreaAndModel" << "listThrStatPerUeAndModel" << "listMobStatPerUE" << "listPsStatPerModel" << "listPsStatPerUE" << "listCsStatPerModel" << "listCsStatPerUE" << "ipgwtgProtStat" << "ipgwtgTguStat" << "ipgwtgContStat" << "pdcp_uProtStat" << "pdcp_uRohcProtStat" << "pdcp_uGenBearerInfo" << "pdcp_uBearerRohcInfo" << "pdcp_uBearerErrStat" << "pdcp_uContStat";
    QString beginningOfStatSector = "<ST>";
    QDomDocument statisticsDocument = ProjectReaderWriter::readDataFromXml(beginningOfStatSector,endofStatSector);
    if(statisticsDocument.isNull() == 0)
    {
        serializeFromProjectFileNew(statisticsDocument);
    }
    else
    {
        for (int i = 0; i <= static_cast<int>( Stats_settings::pdcp_uContStat ); i++)
        {
            Stats_settings keyStat = static_cast<Stats_settings>( i );
            statMap.insert(keyStat, false);
        }
    }
}

bool StatisticsData::getStatMap(enum Stats_settings &key)
{
    value = statMap.value(key);
    return value;
}

void StatisticsData::setStatMap(enum Stats_settings &key, bool &value)
{
    statMap[key] = value;
}

void StatisticsData::serializeToProjectFile()
{
    QDomElement rootElement = xmlStatisticsPart.createElement("statistics");
    xmlStatisticsPart.appendChild(rootElement);
    for(int i = 0; i < statMap.size(); i++)
    {
        QString keyMap = getStringFromEnum(i);
        QDomElement statisticsElement = xmlStatisticsPart.createElement(keyMap);
        rootElement.appendChild(statisticsElement);
        QDomText statisticsElementXmlText = xmlStatisticsPart.createTextNode(boolToString(statMap[getEnumFromString(keyMap)]) );
        statisticsElement.appendChild(statisticsElementXmlText);
    }
}

void StatisticsData::serializeFromProjectFileNew(QDomDocument xmlDocument)
{
    xmlStatisticsPart = xmlDocument;
    QDomElement rootElement = xmlStatisticsPart.firstChildElement();
    QDomNodeList statistics = rootElement.childNodes();
    for(int i = 0; i < statistics.size(); i++)
    {
        QDomElement statisticsElements = statistics.at(i).toElement();
        QString keyString = enumStatString.at(i);
        Stats_settings key = getEnumFromString(keyString);
        QString valuestring = statisticsElements.text();
        bool value = stringToBool(valuestring);
        setStatMap(key, value);
    }
}

// Additional methods for enum, string and bool variable
//method converts enum to string
QString StatisticsData::getStringFromEnum(int &enumVal)
{
    return enumStatString.at(enumVal);
}
//method converts string to enum
Stats_settings StatisticsData::getEnumFromString(QString &stringVal)
{
    return static_cast<Stats_settings>( enumStatString.indexOf(stringVal) );
}
//method converts string to bool
bool StatisticsData::stringToBool(QString &valString)
{
    if(valString == "true")
        return true;
    else
        return false;
}
//method converts bool to string
QString StatisticsData::boolToString(bool &valBool)
{
    if(valBool == true)
        return "true";
    else
        return "false";
}
