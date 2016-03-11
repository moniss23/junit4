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

QByteArray UEgroupData::readDataFromProj()
{
    QString projectDir = projectMng->getProjectDir(*projectName);
    QString xmlFileName;
    QString beginningOfSector("<UE ID=\"" + ueName + "\">");
    QString endOfSector("</UE>\n");
    int start,end;

    if(projectDir == "<default>")
    {
        xmlFileName = QString("projects/" + *projectName + "/" + *projectName + ".xml");
    }
    else
    {
        xmlFileName = QString(projectDir + "/" + *projectName + "/" + *projectName + ".xml");
    }

    QFile xmlFile(xmlFileName);
    if(!xmlFile.open(QIODevice::ReadOnly) ) return 0;

    QDataStream xmlFileStream(&xmlFile);
    QByteArray ueGroupData;

    xmlFileStream >> ueGroupData;

    xmlFile.close();

    //Cutting UEgroupData from byte array
    start = ueGroupData.indexOf(beginningOfSector);
    end = ueGroupData.indexOf(endOfSector) + endOfSector.size();

    if(start == -1 || end == -1)
        return NULL;

    ueGroupData.remove(end,ueGroupData.size() );
    ueGroupData.remove(0,start);

    return ueGroupData;
}
