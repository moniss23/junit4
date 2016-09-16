#ifndef UEDATA_H
#define UEDATA_H

#include "Data/Interfaces/serializeinterface.h"

class UEData : public SerializeInterface
{
public:
    UEData();
    ~UEData();

    QString pairName;
    int amountOfPairs;
    std::pair<QString,QString> mobilityModelsPair;
    std::pair<QString,QString> csModelsPair;
    std::pair<QString,QString> psModelsPair;
    std::pair<QString,QString> ueTypesPair;
    std::pair<QString,QString> ueArea;

    int positionX=2000, positionY=2000; //TODO: remove as soon as reading ueArea is ready

    // SerializeInterface interface
public:
    QString getElementType() const;
    QByteArray serializeData();
    void deserializeData(const QByteArray &rawData);
};

#endif // UEDATA_H
