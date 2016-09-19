#include <QBuffer>
#include <QDataStream>

#include "trafficfiledata.h"

TrafficFileData::TrafficFileData()
{
    for(unsigned i = 0; i < cmAmount; i++) {
        customModels.push_back(CustomModelSettings());
        cmUsed[i] = false;
    }
}

QString TrafficFileData::getElementType() const
{
    return QString("TrafficFileData");
}

QByteArray TrafficFileData::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << filename << content;

    stream << customModels.size();
    for(auto &&CM : customModels) {
        stream << CM.serializeData();
    }

    for(unsigned i = 0; i < cmAmount; i++) {
        stream << cmUsed[i];
    }

    stream << userEquipments.size();
    for(auto &&UE : userEquipments) {
        stream << UE.serializeData();
    }

    stream << statisticsData.serializeData();

    stream << timeData.serializeData();

    stream << tuningTrafficData.serializeData();

    return serializedData.buffer();
}

void TrafficFileData::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> filename >> content;

    int customModelsAmount;

    stream >> customModelsAmount;
    for(unsigned i = 0; i < cmAmount; i++){
        QByteArray rawCustomModels;
        stream >> rawCustomModels;

        CustomModelSettings customModelSettings;
        customModelSettings.deserializeData(rawCustomModels);
        customModels[i] = customModelSettings;
    }

    for(unsigned i = 0; i < cmAmount; i++) {
        stream >> cmUsed[i];
    }

    unsigned userEquipmentsAmount;
    stream >> userEquipmentsAmount;
    for(unsigned i=0; i<userEquipmentsAmount; ++i) {
        QByteArray rawUserEquipment;
        stream >> rawUserEquipment;

        UEData ueData;
        ueData.deserializeData(rawUserEquipment);
        userEquipments.append(ueData);
    }

    QByteArray rawStatisticsData;
    stream >> rawStatisticsData;
    statisticsData.deserializeData(rawStatisticsData);

    QByteArray rawTimeData;
    stream >> rawTimeData;
    timeData.deserializeData(rawTimeData);

    QByteArray rawTuningTrafficData;
    stream >> rawTuningTrafficData;
    tuningTrafficData.deserializeData(rawTuningTrafficData);
}
