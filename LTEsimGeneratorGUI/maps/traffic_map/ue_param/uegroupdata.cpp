#include "uegroupdata.h"

UEgroupData::UEgroupData(const QString &name, const QString &mapIndex)
{
    ue.ueName = name;
    mapIndexConst = mapIndex;
}

//getters
QString UEgroupData::getUEname() const
{
    return ue.ueName;
}

QString UEgroupData::getMapIndex() const
{
    return mapIndexConst;
}

QString UEgroupData::getPairsName() const
{
    return ue.pairsName;
}

int UEgroupData::getAmountOfPairs()
{
    return ue.amountOfPairs;
}
QString UEgroupData::getMobilityModel() const
{
    return ue.mobilityModel;
}
QString UEgroupData::getCSbehaviourMode() const
{
    return ue.csBehaviorMode;
}

QString UEgroupData::getPSbehaviourMode() const
{
    return ue.psBehaviorMode;
}

QString UEgroupData::getUEtype() const
{
    return ue.ueType;
}

QString UEgroupData::getArea() const
{
    return ue.area;
}


//setters

void UEgroupData::setPairsName(const QString &pairsNameCurrent)
{
    ue.pairsName = pairsNameCurrent;
}

void UEgroupData::setAmountOfPairs(int amountOfPairsCurrent)
{
    ue.amountOfPairs = amountOfPairsCurrent;
}

void UEgroupData::setMobilityModel(const QString &mobilityModelCurrent)
{
    ue.mobilityModel = mobilityModelCurrent;
}

void UEgroupData::setCSbehaviourMode(const QString &csBehaviorModeCurrent)
{
    ue.csBehaviorMode = csBehaviorModeCurrent;
}

void UEgroupData::setPSbehaviourMode(const QString &psBehaviorModeCurrent)
{
    ue.psBehaviorMode = psBehaviorModeCurrent;
}
void UEgroupData::setUEtype(const QString &ueTypeCurrent)
{
    ue.ueType = ueTypeCurrent;
}

void UEgroupData::setArea(const QString &areaCurrent)
{
    ue.area = areaCurrent;
}

//save method to QDomDocument - xml UE Group Data Part
void UEgroupData::serializeToProjectFile()
{
    QDomElement ueGroupXmlElement = xmlUePart.createElement("UE");
    xmlUePart.appendChild(ueGroupXmlElement);

    ueGroupXmlElement.setAttribute("ID", ue.ueName);
    QDomElement pairsNameXmlElement = xmlUePart.createElement("pairsName");
    QDomElement amountOfPairsXmlElement = xmlUePart.createElement("amountOfPairs");
    QDomElement mobilityModelXmlElement = xmlUePart.createElement("mobilityModel");
    QDomElement csBehaviorModeXmlElement = xmlUePart.createElement("CSbehaviorMode");
    QDomElement psBehaviorModeXmlElement = xmlUePart.createElement("PSbehaviorMode");
    QDomElement ueTypeXmlElement = xmlUePart.createElement("UEtype");
    QDomElement areaXmlElement = xmlUePart.createElement("area");

    ueGroupXmlElement.appendChild(pairsNameXmlElement);
    ueGroupXmlElement.appendChild(amountOfPairsXmlElement);
    ueGroupXmlElement.appendChild(mobilityModelXmlElement);
    ueGroupXmlElement.appendChild(csBehaviorModeXmlElement);
    ueGroupXmlElement.appendChild(psBehaviorModeXmlElement);
    ueGroupXmlElement.appendChild(ueTypeXmlElement);
    ueGroupXmlElement.appendChild(areaXmlElement);

    QDomText pairsNameXmlText = xmlUePart.createTextNode(ue.pairsName);
    QDomText amountOfPairsXmlText = xmlUePart.createTextNode(QString::number(ue.amountOfPairs) );
    QDomText mobilityModelXmlText = xmlUePart.createTextNode(ue.mobilityModel);
    QDomText csBehaviorModeXmlText = xmlUePart.createTextNode(ue.csBehaviorMode);
    QDomText psBehaviorModeXmlText = xmlUePart.createTextNode(ue.psBehaviorMode);
    QDomText ueTypeXmlText = xmlUePart.createTextNode(ue.ueType);
    QDomText areaXmlText = xmlUePart.createTextNode(ue.area);

    pairsNameXmlElement.appendChild(pairsNameXmlText);
    amountOfPairsXmlElement.appendChild(amountOfPairsXmlText);
    mobilityModelXmlElement.appendChild(mobilityModelXmlText);
    csBehaviorModeXmlElement.appendChild(csBehaviorModeXmlText);
    psBehaviorModeXmlElement.appendChild(psBehaviorModeXmlText);
    ueTypeXmlElement.appendChild(ueTypeXmlText);
    areaXmlElement.appendChild(areaXmlText);
}

//Read UE Parameters Part from Proj to QByteArray
QByteArray UEgroupData::readDataFromProj()
{
    QString projectDir = projectMng->getProjectDir(*projectName);
    QString xmlFileName;
    QString beginningOfSector("<UE ID=\"" + ue.ueName + "\">");
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
