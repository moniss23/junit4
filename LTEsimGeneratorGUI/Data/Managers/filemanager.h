#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QByteArray>

#include "Data/project.h"

class FileManager {
public:
    FileManager();

    QByteArray readFromFile(const QString&);
    void writeToFile(const QString&, const QByteArray&);
    void generateTrafficScript(Project currentProject, int file_index);
    void generateParametersScript(QString location, QString projectName, QString content);
    void generateTrafficScript(QString location, QString projectName, QString content, QString fileName);

    QString readFileToQString(const QString &filename);
    void projectsFileSetup(const QString &projectsFilename);
};

#endif // FILEMANAGER_H
