#include "filemanager.h"
#include <QDir>
#include <QTextStream>

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


void FileManager::generateParametersScript(Project currentProject) {
    QDir dir;
    if(currentProject.genScriptDir=="<default>"){
        QFile file;
        if(currentProject.fullpath=="<default>"){
            QString path("projects/"+currentProject.name);
            dir.mkpath(path);
            file.setFileName("projects/"+currentProject.name+"/"+currentProject.parametersFile.filename);
        }else{
            QString project_dir=currentProject.fullpath;
            QString path(project_dir+"/"+currentProject.name);
            dir.mkpath(path);
            file.setFileName(project_dir+"/"+currentProject.name+"/"+currentProject.parametersFile.filename);
        }
        file.open(QIODevice::WriteOnly);
        QTextStream file_str(&file);
        file_str<<currentProject.parametersFile.content;
        file.close();
    }else{
        QFile file(currentProject.genScriptDir+"/"+currentProject.parametersFile.filename);
        file.open(QIODevice::WriteOnly);
        QTextStream file_str(&file);
        file_str<<currentProject.parametersFile.content;
        file.close();
    }
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
