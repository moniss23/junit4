#include <QBuffer>
#include <QDataStream>

#include "trafficfiledata.h"

TrafficFileData::TrafficFileData()
{
    for(unsigned i = 0; i < 10; i++) {
        customModels.push_back(CustomModelSettings());
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

    return serializedData.buffer();
}

void TrafficFileData::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> filename >> content;
}
