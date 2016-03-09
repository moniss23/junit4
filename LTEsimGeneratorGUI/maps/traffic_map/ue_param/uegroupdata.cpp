#include "uegroupdata.h"

//getters and setters
QString UEgroupData::getUEname() const
{
    return ueName;
}

QString UEgroupData::getMapIndex() const
{
    return mapIndexConst;
}

QString UEgroupData::getPairsName() const
{
    return pairsName;
}

void UEgroupData::setPairsName(const QString &pairsNameCurrent)
{
    pairsName = pairsNameCurrent;
}

int UEgroupData::getAmountOfPairs()
{
    return amountOfPairs;
}

void UEgroupData::setAmountOfPairs(int amountOfPairsCurrent)
{
    amountOfPairs = amountOfPairsCurrent;
}

QString UEgroupData::getMobilityModel() const
{
    return mobilityModel;
}

void UEgroupData::setMobilityModel(const QString &mobilityModelCurrent)
{
    mobilityModel = mobilityModelCurrent;
}

QString UEgroupData::getCSbehaviourMode() const
{
    return CSbehaviourMode;
}

void UEgroupData::setCSbehaviourMode(const QString &CSbehaviourModeCurrent)
{
    CSbehaviourMode = CSbehaviourModeCurrent;
}

QString UEgroupData::getPSbehaviourMode() const
{
    return PSbehaviorMode;
}

void UEgroupData::setPSbehaviourMode(const QString &PSbehaviorModeCurrent)
{
    PSbehaviorMode = PSbehaviorModeCurrent;
}

QString UEgroupData::getUEtype() const
{
    return ueType;
}

void UEgroupData::setUEtype(const QString &ueTypeCurrent)
{
    ueType = ueTypeCurrent;
}

QString UEgroupData::getArea() const
{
    return area;
}

void UEgroupData::setArea(const QString &areaCurrent)
{
    area = areaCurrent;
}
