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

    return serializedData.buffer();
}

void TrafficFileData::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> filename >> content;

    int customModelsAmount;

    stream >> customModelsAmount;
    while(customModelsAmount--) {
        QByteArray rawCustomModels;
        stream >> rawCustomModels;

        CustomModelSettings customModelSettings;
        customModelSettings.deserializeData(rawCustomModels);
        customModels.push_back(customModelSettings);
    }

    for(unsigned i = 0; i < cmAmount; i++) {
        stream >> cmUsed[i];
    }
}
