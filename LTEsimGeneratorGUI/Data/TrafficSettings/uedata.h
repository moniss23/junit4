#ifndef UEDATA_H
#define UEDATA_H

#include "Data/Interfaces/serializeinterface.h"

class UEData : public SerializeInterface
{
public:
    UEData();
    ~UEData();

    QString pairName;
    int amountOfPairs = 100;
    std::pair<QString,QString> mobilityModelsPair{"RandomWalker","RandomWalker"};
    std::pair<QString,QString> csModelsPair{"PowerOnPowerOff", "PowerOnPowerOff"};
    std::pair<QString,QString> psModelsPair{"NoPs", "NoPs"};
    std::pair<QString,QString> ueTypesPair{"iratHO", "iratHO"};
    std::pair<QString,QString> ueArea;

    int positionX=2000, positionY=2000; //TODO: remove as soon as reading ueArea is ready

    // SerializeInterface interface
public:
    QString getElementType() const;
    QByteArray serializeData();
    void deserializeData(const QByteArray &rawData);
};

#endif // UEDATA_H
