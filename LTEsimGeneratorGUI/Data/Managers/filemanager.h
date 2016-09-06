#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QByteArray>

#include "Data/project.h"

class FileManager {
public:
    FileManager();

    QByteArray readFromFile(const QString&);
    void writeToFile(const QString&, const QByteArray&);
    void generateParametersScript(QString location, QString projectName, QString content);
    void generateTrafficScript(Project currentProject, int file_index);

};

#endif // FILEMANAGER_H
