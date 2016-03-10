#include "handoverdata.h"
#include "QFile"

HandoverData::HandoverData(QString name)
{
    handoverParams.handoverName=name;
    QByteArray data=readDataFromProj();
    serializeFromProjectFileOld(data);
}

//---------------------Getters------------------------------------------------------


QString HandoverData::getHandoverName() const
{
    return handoverParams.handoverName;
}

int HandoverData::getSouthBoundary() const
{
    return handoverParams.handoverArea.bottom();
}

int HandoverData::getNorthBoundary() const
{
    return handoverParams.handoverArea.top();
}
int HandoverData::getWestBoundary() const
{
    return handoverParams.handoverArea.left();
}

int HandoverData::getEastBoundary() const
{
    return handoverParams.handoverArea.right();
}

HandoverParams HandoverData::getHandoverParams() const
{
    return handoverParams;
}

//---------------------Setters------------------------------------------------------


void HandoverData::setHandoverName(const QString &name)
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

void HandoverData::setHandoverParams(const HandoverParams &params)
{
    handoverParams = params;
}

HandoverParams HandoverData::parseDataFromList(QStringList &paramsList)
{
    HandoverParams loadedParams;
    QString searchHandoverName = ":area => \"" + handoverParams.handoverName + "\"" + ",";

    for(int i = 0; i < paramsList.size(); i++)
    {
        if(paramsList[i].contains(searchHandoverName) )
        {

            //cutting needed phrase from list
            loadedParams.handoverName = paramsList[i].section('"',1,1);

            paramsList[i + 1].remove(0,8);
            paramsList[i + 1] = paramsList[i + 1].section(' ',2,2);
            paramsList[i + 1].remove(",");
            loadedParams.handoverArea.setBottom(paramsList[i + 1].toInt() );

            paramsList[i + 2].remove(0,8);
            paramsList[i + 2] = paramsList[i + 2].section(' ',2,2);
            paramsList[i + 2].remove(",");
            loadedParams.handoverArea.setTop(paramsList[i + 2].toInt() );

            paramsList[i + 3].remove(0,8);
            paramsList[i + 3] = paramsList[i + 3].section(' ',2,2);
            paramsList[i + 3].remove(",");
            loadedParams.handoverArea.setLeft(paramsList[i + 3].toInt() );

            paramsList[i + 4].remove(0,8);
            paramsList[i + 4] = paramsList[i + 4].section(' ',2,2);
            paramsList[i + 4].remove(",");
            loadedParams.handoverArea.setRight(paramsList[i + 4].toInt() );

        }
    }

    return loadedParams;

}

//---------------Overriden methods from DataElementsInterface---------------------

QString HandoverData::getElementType() const
{
    return QString("Handover");
}

void HandoverData::serializeFromProjectFileOld(QByteArray rawData)
{
    HandoverParams loadedParams;
    QString projectData(rawData);
    QStringList projectDataList = projectData.split('\n');
    loadedParams=parseDataFromList(projectDataList);
    setHandoverParams(loadedParams);
}

QByteArray HandoverData::readDataFromProj()
{
    QString projectDir = projectMng->getProjectDir(*projectName);
    QString projectFileName;
    QString beginningOfSector("default[:areas]");
    QString endOfSector("default[:dataGenerator]");
    int start,end;

    if(projectDir == "<default>")
    {
        projectFileName = QString("projects/" + *projectName + "/" + *projectName + ".proj");
    }
    else
    {
        projectFileName = QString(projectDir + "/" + *projectName + "/" + *projectName + ".proj");
    }

    QFile projectFile(projectFileName);
    if(!projectFile.open(QIODevice::ReadOnly) ) return 0;

    unsigned int length = projectFile.bytesAvailable();
    char* cipherText = new char[length];

    QDataStream projectFileStream(&projectFile);
    projectFileStream.readRawData(cipherText,length);
    projectFile.close();

    //------------Decrypting data from project file-----------------------------------
    const char* plainText = crypt(cipherText,length,cipher_key.toStdString().c_str(),cipher_key.length() );
    QByteArray parametersData(plainText);

    //------------Cutting data about handovers from byte array------------------------
    start = parametersData.indexOf(beginningOfSector);
    end = parametersData.indexOf(endOfSector);

    parametersData.remove(end,parametersData.size() );
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
