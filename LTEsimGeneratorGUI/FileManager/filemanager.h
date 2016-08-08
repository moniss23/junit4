#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QString>
#include <QByteArray>
#include <QDataStream>

class FileManager {
public:
    FileManager();

    QByteArray readFromFile(const QString&);
    void writeToFile(const QString&, const QByteArray&);
};

#endif // FILEMANAGER_H
