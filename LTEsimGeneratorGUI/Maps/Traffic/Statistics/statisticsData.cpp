#include "statisticsData.h"

StatisticsData::StatisticsData() {
    this->statisticsMap.clear();
    for (auto name: StatisticsData::namesList) {
        auto tuple = std::make_tuple (name,false);
        this->statisticsMap.append(tuple);
    }
}

StatisticsData::StatisticsData(const StatisticsData& statisticsData){
    this->statisticsMap.clear();
    for (auto name: StatisticsData::namesList) {
        auto tuple = std::make_tuple (name,statisticsData.getStatMapFor(name));
        this->statisticsMap.append(tuple);
    }
}

StatisticsData& StatisticsData::operator =(const StatisticsData& rhc) {
    this->generalDelayBetweenPackets = rhc.generalDelayBetweenPackets;
    this->generalMeasurementDelta =rhc.generalMeasurementDelta;
    this->generalMtuSize = rhc.generalMtuSize;
    this->generalTotalNumberOfSeconds = rhc.generalTotalNumberOfSeconds;
    this->generalUe = rhc.generalUe;
    this->ipexFileName = rhc.ipexFileName;
    this->ipexMeasurement = rhc.ipexMeasurement;
    this->ipexSeconds = rhc.ipexSeconds;
    this->ipexTguImsi = rhc.ipexTguImsi;
    this->pdcpuBearerErrorEpsBearerId = rhc.pdcpuBearerErrorEpsBearerId;
    this->pdcpuBearerErrorImsi = rhc.pdcpuBearerErrorImsi;
    this->pdcpuBearerRohcEpsBearerId = rhc.pdcpuBearerRohcEpsBearerId;
    this->pdcpuBearerRohcImsi = rhc.pdcpuBearerRohcImsi;
    this->pdcpuBearerStatusEpsBearerId = rhc.pdcpuBearerStatusEpsBearerId;
    this->pdcpuBearerStatusImsi = rhc.pdcpuBearerStatusImsi;
    this->pdcpuFileName = rhc.pdcpuFileName;
    this->pdcpuMeasurement = rhc.pdcpuMeasurement;
    this->pdcpuSeconds = rhc.pdcpuSeconds;
    this->statisticsMap = rhc.statisticsMap;

    return *this;
}

bool StatisticsData::getStatMapFor(QString key) const {
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

const QStringList StatisticsData::namesList = {
    "Ue Static Info",
    "Model Exp Nas",
    "Model Exp Rrc",
    "Model Exp Mobility",
    "Model Exp Throughput",
    "Per Ue Throughput",
    "Ue Exp Mobility",
    "Model Exp Ps",
    "Ue Exp Ps",
    "Model Exp Cs",
    "Ue Exp Cs",
    "Write Statistics to file",
    "Ipex Protocol Stats",
    "Ipex Tgu Stats",
    "Write IPEX to file",
    "Protocol Stats",
    "Protocol Rohc Stats",
    "Bearer Status Words Stats",
    "Bearer Rohc Stats",
    "Bearer Error Stats",
    "Write PdcpU to file"
    };
