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

void FileManager::writeToFile(const QString &fileFullPath, const QByteArray &rawData) {
    QFile file(fileFullPath);
    file.open(QIODevice::WriteOnly);

    QDataStream fileStream(&file);
    fileStream << rawData;
    file.close();
}


void FileManager::generateParametersScript(QString location,QString projectName,QString content) {
    QDir dir;
    QFile file;
    dir.setCurrent(location);
    if (!QDir("projects").exists()) {
        dir.mkdir("projects");
    }
    if (!QDir("projects/"+projectName).exists()){
        dir.mkdir("projects/"+projectName);
    }
    dir.setCurrent("projects/"+projectName);
    file.setFileName("Parameters.rb");
    file.open(QIODevice::WriteOnly);
    QTextStream file_str(&file);
    file_str << content;
    file.close();
    dir.setCurrent("../../");
}

void FileManager::generateTrafficScript(QString location, QString projectName, QString content, QString fileName)
{
    QDir dir;
    QFile file;
    dir.setCurrent(location);
    if (!QDir("projects").exists()) {
        dir.mkdir("projects");
    }
    if (!QDir("projects/"+projectName).exists()){
        dir.mkdir("projects/"+projectName);
    }
    dir.setCurrent("projects/"+projectName);
    file.setFileName( fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream file_str(&file);
    file_str << content;
    file.close();
    dir.setCurrent("../../");
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
