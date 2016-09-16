#include "uedata.h"

UEData::UEData()
{

}

UEData::~UEData()
{

}

QString UEData::getElementType() const
{
    return QString("UEData");
}

QByteArray UEData::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << pairName << amountOfPairs << mobilityModelsPair.first << mobilityModelsPair.second <<
              csModelsPair.first << csModelsPair.second << psModelsPair.first << psModelsPair.second <<
              ueTypesPair.first << ueTypesPair.second << ueArea.first << ueArea.second;

    stream << positionX << positionY;

    return serializedData.buffer();
}

void UEData::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> pairName >> amountOfPairs >> mobilityModelsPair.first >> mobilityModelsPair.second >>
            csModelsPair.first >> csModelsPair.second >> psModelsPair.first >> psModelsPair.second >>
            ueTypesPair.first >> ueTypesPair.second >> ueArea.first >> ueArea.second;

    stream >> positionX >> positionY;
}