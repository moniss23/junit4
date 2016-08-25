#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QByteArray>
#include <QDataStream>
#include "Data/project.h"

class FileManager {
public:
    FileManager();

    QByteArray readFromFile(const QString&);
    void writeToFile(const QString&, const QByteArray&);
    void generateParametersScript(Project currentProject);
    void generateTrafficScript(Project currentProject, int file_index);
};

#endif // FILEMANAGER_H
