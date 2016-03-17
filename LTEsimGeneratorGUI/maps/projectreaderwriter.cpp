#include "projectreaderwriter.h"

ProjectReaderWriter::ProjectReaderWriter()
{

}

QByteArray ProjectReaderWriter::readDataFromProj(const QString &beginningOfSector, const QString &endOfSector)
{
    QString projectDir = projectMng->getProjectDir(*projectName);
    QString projectFileName;
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

    //------------Cutting data from byte array------------------------
    start = parametersData.indexOf(beginningOfSector);
    end = parametersData.indexOf(endOfSector);

    parametersData.remove(end,parametersData.size() );
    parametersData.remove(0,start);

    return parametersData;
}

QByteArray ProjectReaderWriter::readDataFromXml(const QString &beginningOfSector, const QString &endOfSector)
{

    QString projectDir = projectMng->getProjectDir(*projectName);
    QString xmlFileName;
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
    QByteArray xmlData;

    xmlFileStream >> xmlData;

    xmlFile.close();

    //Cutting proper part of xml from byte array
    start = xmlData.indexOf(beginningOfSector);
    end = xmlData.indexOf(endOfSector) + endOfSector.size();

    if(start == -1 || end == -1)
        return NULL;

    xmlData.remove(end,xmlData.size() );
    xmlData.remove(0,start);

    return xmlData;
}

