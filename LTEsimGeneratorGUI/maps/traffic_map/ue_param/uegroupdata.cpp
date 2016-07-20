#include "uegroupdata.h"

UEgroupData::UEgroupData(const QString &name, const QString &mapIndex)
{
    ue.ueName = name;
    mapIndexConst = mapIndex;
    QString beginningOfUESector("<UE ID=\"" + ue.ueName + "\">");
    QDomDocument ueXmlDocument = projectReaderWriter->readDataFromXml(beginningOfUESector,endOfUESector);
    //reading parameter from proj/creating new ue with default parameters
    if(ueXmlDocument.isNull() == 0)
    {
        serializeFromProjectFileNew(ueXmlDocument);
    }
    else
    {
        ue.pairsName = "";
        ue.amountOfPairs = 0;
        ue.mobilityModel = "RandomWalker";
        ue.csBehaviorMode = "PowerOnPowerOff";
        ue.psBehaviorMode = "NoPS";
        ue.ueType = "IratHO";
        ue.area = "";
    }
    projectReaderWriter = new ProjectReaderWriter;
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

//serialize data from proj to variables
void UEgroupData::serializeFromProjectFileNew(QDomDocument xmlDocument)
{
    xmlUePart=xmlDocument;
    QDomElement ue1 = xmlUePart.firstChildElement();
    QDomNodeList ue1Attributes = ue1.childNodes();
    for(int i = 0; i < ue1Attributes.size(); i++)
    {
        QDomElement ueAtrr = ue1Attributes.at(i).toElement();
        if(ueAtrr.nodeName() == "pairsName")
        {
            QDomElement pairsNameXmlElement = ueAtrr.toElement();
            setPairsName(pairsNameXmlElement.text());
        }
        if(ueAtrr.nodeName() == "amountOfPairs")
        {
            QDomElement amountOfPairsXmlElement = ueAtrr.toElement();
            ue.amountOfPairs = amountOfPairsXmlElement.text().toInt();
        }
        if(ueAtrr.nodeName() == "mobilityModel")
        {
            QDomElement mobilityModelXmlElement = ueAtrr.toElement();
            ue.mobilityModel = mobilityModelXmlElement.text();
        }
        if(ueAtrr.nodeName() == "CSbehaviorMode")
        {
            QDomElement csBehaviorModeXmlElement = ueAtrr.toElement();
            ue.csBehaviorMode = csBehaviorModeXmlElement.text();
        }
        if(ueAtrr.nodeName() == "PSbehaviorMode")
        {
            QDomElement psBehaviorModeXmlElement = ueAtrr.toElement();
            ue.psBehaviorMode = psBehaviorModeXmlElement.text();
        }
        if(ueAtrr.nodeName() == "UEtype")
        {
            QDomElement ueTypeXmlElement = ueAtrr.toElement();
            ue.ueType = ueTypeXmlElement.text();
        }
        if(ueAtrr.nodeName() == "area")
        {
            QDomElement areaXmlElement = ueAtrr.toElement();
            ue.area = areaXmlElement.text();
        }
    }
}

void UEgroupData::setProjectReaderWriter(ProjectReaderWriter *value)
{
    projectReaderWriter = value;
}
