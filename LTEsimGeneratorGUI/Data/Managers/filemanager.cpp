#include "filemanager.h"

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
