#include "statisticsData.h"

StatisticsData::StatisticsData() {
    this->statisticsMap.clear();
    for(auto name: StatisticsData::NAMESLIST) {
        QPair<QString,bool> pair(name, false);
        this->statisticsMap.push_back(pair);
    }
}

StatisticsData::~StatisticsData()
{

}

bool StatisticsData::getStatMapFor(QString key) const {
    return this->statisticsMap.at(StatisticsData::NAMESLIST.indexOf(QRegExp(key))).second;
}

void StatisticsData::setStatMapFor(QString key, bool value) {
    QPair<QString,bool> pair(key, value);
    this->statisticsMap.replace(StatisticsData::NAMESLIST.indexOf(QRegExp(key)), pair);
}

QByteArray StatisticsData::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << this->generalUe << this->generalDelayBetweenPackets << this->generalTotalNumberOfSeconds <<
              generalMtuSize << this->generalMeasurementDelta << this->ipexTguImsi << this->ipexFileName << this->ipexSeconds <<
              ipexMeasurement << this->pdcpuBearerStatusImsi << this->pdcpuBearerStatusEpsBearerId <<
              pdcpuBearerRohcImsi << this->pdcpuBearerRohcEpsBearerId << this->pdcpuBearerErrorImsi <<
              pdcpuBearerErrorEpsBearerId << this->pdcpuFileName << this->pdcpuSeconds << this->pdcpuMeasurement;

    for(unsigned i = 0; i < statisticsMap.size(); i++) {
        stream << statisticsMap[i].second;
    }

    return serializedData.buffer();
}

void StatisticsData::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> this->generalUe >> this->generalDelayBetweenPackets >> this->generalTotalNumberOfSeconds >>
              generalMtuSize >> this->generalMeasurementDelta >> this->ipexTguImsi >> this->ipexFileName >> this->ipexSeconds >>
              ipexMeasurement >> this->pdcpuBearerStatusImsi >> this->pdcpuBearerStatusEpsBearerId >>
              pdcpuBearerRohcImsi >> this->pdcpuBearerRohcEpsBearerId >> this->pdcpuBearerErrorImsi >>
              pdcpuBearerErrorEpsBearerId >> this->pdcpuFileName >> this->pdcpuSeconds >> this->pdcpuMeasurement;

    for(unsigned i = 0; i < statisticsMap.size(); i++) {
        stream >> statisticsMap[i].second;
    }
}

QString StatisticsData::getElementType() const {
    return QString("SettingsData");
}

const QStringList StatisticsData::NAMESLIST = {
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
