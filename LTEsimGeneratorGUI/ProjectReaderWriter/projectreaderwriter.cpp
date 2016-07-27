#include "projectreaderwriter.h"

ProjectReaderWriter::ProjectReaderWriter(AppSettings *appSettings) : appSettings(appSettings)
{
}

QByteArray ProjectReaderWriter::readDataFromProj(const QString &beginningOfSector, const QString &endOfSector)
{
    QString projectDir = appSettings->getProjectDirectory(appSettings->getProjectName());
    QString projectFileName;
    int start,end;


    if(projectDir == "<default>")
    {
        projectFileName = QString("projects/" + appSettings->getProjectName() + "/" + appSettings->getProjectName() + ".proj");
    }
    else
    {
        projectFileName = QString(projectDir + "/" + appSettings->getProjectName() + "/" + appSettings->getProjectName() + ".proj");
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

QDomDocument ProjectReaderWriter::readDataFromXml(const QString &beginningOfSector, const QString &endOfSector)
{
    QDomDocument xmlDocument;
    QString projectDir = appSettings->getProjectDirectory(appSettings->getProjectName());
    QString xmlFileName;
    int start,end;

    if(projectDir == "<default>")
    {
        xmlFileName = QString("projects/" + appSettings->getProjectName() + "/" + appSettings->getProjectName() + ".xml");
    }
    else
    {
        xmlFileName = QString(projectDir + "/" + appSettings->getProjectName() + "/" + appSettings->getProjectName() + ".xml");
    }

    QFile xmlFile(xmlFileName);
    if(!xmlFile.open(QIODevice::ReadOnly) ) return xmlDocument;

    QDataStream xmlFileStream(&xmlFile);
    QByteArray xmlData;

    xmlFileStream >> xmlData;

    xmlFile.close();

    //Cutting proper part of xml from byte array
    start = xmlData.indexOf(beginningOfSector);
    end = xmlData.indexOf(endOfSector) + endOfSector.size();

    if(start == -1 || end == -1)
        return xmlDocument;

    xmlData.remove(end,xmlData.size() );
    xmlData.remove(0,start);
    xmlDocument.setContent(xmlData);


    return xmlDocument;
}

void ProjectReaderWriter::writeDataToXml(const QDomDocument xmlDocument)
{
    (void) xmlDocument;
}
