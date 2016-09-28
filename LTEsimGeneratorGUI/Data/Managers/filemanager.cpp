#include "filemanager.h"
#include <QDir>
#include <QTextStream>
#include <QDataStream>
#include <QFile>

FileManager::FileManager()
{
}

QByteArray FileManager::readFromFile(const QString &fileFullPath) {
    QFile file(fileFullPath);
    file.open(QIODevice::ReadOnly);

    QByteArray rawData;
    QDataStream fileStream(&file);

    fileStream >> rawData;
    file.close();
    return rawData;
}

void FileManager::writeToFile(const QString &fileFullPath, const QByteArray &locationFileContent) {
    QFile file(fileFullPath);
    file.open(QIODevice::WriteOnly);

    QDataStream fileStream(&file);
    fileStream << locationFileContent;
    file.close();
}

QByteArray FileManager::readProjectFromFile(QString fullFilePath)
{
    QFile file(fullFilePath);
    file.open(QIODevice::ReadOnly);

    QByteArray rawData;
    QDataStream fileStream(&file);

    fileStream >> rawData;
    file.close();
    return rawData;
}

void FileManager::writeProjectToFile(QString location, QString projectName, QByteArray rawData)
{
    QDir dir;
    QFile file;
    if(!QDir(location).exists()) {
        dir.mkdir(location);
    }
    if(!QDir(location+"/"+projectName).exists()) {
        dir.mkdir(location+"/"+projectName);
    }
    file.setFileName(location+"/"+projectName+"/"+projectName+".proj");
    file.open(QIODevice::WriteOnly);
    QDataStream fileStream(&file);
    fileStream << rawData;
    file.close();
}

void FileManager::removeProjectDirectory(QString directory)
{
    QDir dir(directory);
    dir.removeRecursively();
}

void FileManager::removeTrafficFile(QString fullpath)
{
    QFile traffic(fullpath);
    traffic.remove();
}

void FileManager::generateParametersScript(QString location,QString projectName, QString fileName, QString content) {
    QDir dir;
    QFile file;
    if(!QDir(location).exists()) {
        dir.mkdir(location);
    }
    if(!QDir(location+"/"+projectName).exists()) {
        dir.mkdir(location+"/"+projectName);
    }
    if(!QDir(location+"/"+projectName+"/Scripts").exists()) {
        dir.mkdir((location+"/"+projectName+"/Scripts"));
    }
    file.setFileName(location+"/"+projectName+"/Scripts/"+fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream fileStream(&file);
    fileStream << content;
    file.close();
}

void FileManager::generateTrafficScript(QString location, QString projectName, QString content, QString fileName)
{
    QDir dir;
    QFile file;
    if(!QDir(location).exists()) {
        dir.mkdir(location);
    }
    if(!QDir(location+"/"+projectName).exists()) {
        dir.mkdir(location+"/"+projectName);
    }
    if(!QDir(location+"/"+projectName+"/Scripts").exists()) {
        dir.mkdir((location+"/"+projectName+"/Scripts"));
    }
    file.setFileName(location+"/"+projectName+"/Scripts/"+fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream fileStream(&file);
    fileStream << content;
    file.close();
}

// Check if projects file exists, create it if it doesn't
void FileManager::projectsFileSetup(const QString &projectsFilename) {
    QFile projectsFile(projectsFilename);
    if(!projectsFile.exists()) {
        projectsFile.open(QIODevice::WriteOnly);
        QTextStream str(&projectsFile);
        str << "0";
        projectsFile.close();
    }
}

QString FileManager::readFileToQString(const QString &filename) {
    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    QTextStream inStr(&file);
    QString fileContent = inStr.readAll();

    file.close();
    return fileContent;
}
