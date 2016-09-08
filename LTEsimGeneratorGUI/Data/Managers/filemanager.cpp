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

void FileManager::generateTrafficScript(Project currentProject, int file_index) {
    QDir dir;
    if(currentProject.genScriptDir=="<default>"){
        if(currentProject.fullpath=="<default>"){
            QString path("projects/"+currentProject.name);
            dir.mkpath(path);
            QFile file("projects/"+currentProject.name+"/"+currentProject.trafficFilesList[file_index].filename);
            file.open(QIODevice::WriteOnly);
            QTextStream file_str(&file);
            file_str<<currentProject.trafficFilesList[file_index].content;
            file.close();
        }
        else{

            QString project_dir=currentProject.fullpath;
            QString path(project_dir+"/"+currentProject.name);
            dir.mkpath(path);
            QFile file("projects/"+currentProject.name+"/"+currentProject.trafficFilesList[file_index].filename);
            file.open(QIODevice::WriteOnly);
            QTextStream file_str(&file);
            file_str<<currentProject.trafficFilesList[file_index].content;
            file.close();
        }
    }
    else{
        QFile file("projects/"+currentProject.name+"/"+currentProject.trafficFilesList[file_index].filename);
        file.open(QIODevice::WriteOnly);
        QTextStream file_str(&file);
        file_str<<currentProject.trafficFilesList[file_index].content;
        file.close();
    }
}
