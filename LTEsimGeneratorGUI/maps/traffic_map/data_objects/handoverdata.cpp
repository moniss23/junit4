#include "handoverdata.h"
#include "qdebug.h"
#include "QFile"

HandoverData::HandoverData(QString name)
{
    this->handoverParams.handoverName = name;
}

//---------------------Getters------------------------------------------------------


QString HandoverData::getHandoverName()
{
    return handoverParams.handoverName;
}

int HandoverData::getSouthBoundary()
{
    return handoverParams.handoverArea.bottom();
}

int HandoverData::getNorthBoundary()
{
    return handoverParams.handoverArea.top();
}
int HandoverData::getWestBoundary()
{
    return handoverParams.handoverArea.left();
}

int HandoverData::getEastBoundary()
{
    return handoverParams.handoverArea.right();
}

HandoverParams HandoverData::getHandoverParams()
{
    return handoverParams;
}

//---------------------Setters------------------------------------------------------


void HandoverData::setHandoverName(QString name)
{
    handoverParams.handoverName = name;
}

void HandoverData::setSouthBoundary(int south)
{
    handoverParams.handoverArea.setBottom(south);
}
void HandoverData::setNorthBoundary(int north)
{
    handoverParams.handoverArea.setTop(north);
}
void HandoverData::setWestBoundary(int west)
{
    handoverParams.handoverArea.setLeft(west);
}

void HandoverData::setEastBoundary(int east)
{
    handoverParams.handoverArea.setRight(east);
}

void HandoverData::setHandoverParams(HandoverParams params)
{
    handoverParams = params;
}

HandoverParams HandoverData::parseDataFromList(QStringList paramsList)
{}

//---------------Overriden methods from DataElementsInterface---------------------

QString HandoverData::getElementType() const
{
    return QString("Handover");
}

void HandoverData::serializeFromProjectFileOld(QByteArray rawData)
{}

QByteArray HandoverData::readDataFromProj()
{
    QString projectDir=projectMng->getProjectDir(*projectName);
    QString projectFileName;
    QString beginningOfSector("default[:areas]");
    QString endOfSector("default[:dataGenerator]");
    int start,end;

    if(projectDir=="<default>")
    {
        projectFileName=QString("projects/"+*projectName+"/"+*projectName+".proj");
    }
    else
    {
        projectFileName=QString(projectDir+"/"+*projectName+"/"+*projectName+".proj");
    }

    QFile projectFile(projectFileName);
    if(!projectFile.open(QIODevice::ReadOnly)) return 0;

    unsigned int length=projectFile.bytesAvailable();
    char* cipherText=new char[length];

    QDataStream projectFileStream(&projectFile);
    projectFileStream.readRawData(cipherText,length);
    projectFile.close();

    //------------Decrypting data from project file-----------------------------------
    const char* plainText=crypt(cipherText,length,cipher_key.toStdString().c_str(),cipher_key.length());
    QByteArray parametersData(plainText);

    //------------Cutting data about handovers from byte array------------------------
    start=parametersData.indexOf(beginningOfSector);
    end=parametersData.indexOf(endOfSector);

    parametersData.remove(end,parametersData.size());
    parametersData.remove(0,start);

    return parametersData;
}

//------------------Serialize/Deserialize operators for future---------------------

QDataStream &operator<<(QDataStream &out, HandoverParams &handover)
{
    out << handover.handoverName << handover.handoverArea;
    return out;
}

QDataStream &operator>>(QDataStream &in, HandoverParams &handover)
{
    in >> handover.handoverName >> handover.handoverArea;
    return in;

}
