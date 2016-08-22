#include "statisticsData.h"

StatisticsData::StatisticsData() {
    this->statisticsMap.clear();
    for (auto name: StatisticsData::namesList) {
        auto tuple = std::make_tuple (name,false);
        this->statisticsMap.append(tuple);
    }
}

StatisticsData::StatisticsData(StatisticsData& statisticsData){
    this->statisticsMap.clear();
    for (auto name: StatisticsData::namesList) {
        auto tuple = std::make_tuple (name,statisticsData.getStatMapFor(name));
        this->statisticsMap.append(tuple);
    }
}

StatisticsData& StatisticsData::operator =(const StatisticsData& rhc) {
    statisticsMap = rhc.statisticsMap;
    return *this;
}

bool StatisticsData::getStatMapFor(QString key) {
    auto value = this->statisticsMap.at(StatisticsData::namesList.indexOf(QRegExp(key)));
    return std::get<1>(value);
}

void StatisticsData::setStatMapFor(QString key, bool value) {
    auto tuple = std::make_tuple (key,value);
    this->statisticsMap.replace(StatisticsData::namesList.indexOf(QRegExp(key)),tuple);
}

QString StatisticsData::getElementType() const {
    return QString("SettingsData");
}

const QStringList StatisticsData::namesList = {"Listing Static Information for Each UE",
                               "Resetting All Statistics Counters",
                               "Listing Statistics on NAS",
                               "Listing Statistics on RRC",
                               "Listing Mobility Statistics per Model and Area",
                               "Listing Throughput Statistics per Area and Model",
                               "Listing Throughput Statistics per UE and Model",
                               "Listing Mobility Statistics per UE",
                               "Listing PS Statistics per Model",
                               "Listing PS Statistics per UE",
                               "Listing CS Statistics per Model",
                               "Listing CS Statistics per UE",
                               "Protocol Statistics",
                               "TGU Statistics",
                               "Countinuous Statistics",
                               "Protocol Statistics",
                               "ROHC Protocol Statistics",
                               "General Bearer information",
                               "Bearer ROHC information",
                               "Bearer Error Statistics",
                               "Continuous Statistics"};
