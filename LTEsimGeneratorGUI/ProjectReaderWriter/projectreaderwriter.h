#ifndef PROJECTREADERWRITER_H
#define PROJECTREADERWRITER_H
#include <QByteArray>
#include <CommonConstans/common_constans.h>
#include <QFile>
#include <QtXml>
#include <DataSystem/datasystem.h>

class ProjectReaderWriter
{
public:

    ProjectReaderWriter(DataSystem *appSettings);
    // ReaderWriterRefactor:  deleted static
    QByteArray readDataFromProj(const QString &beginningOfSector,const QString &endOfSector);
    QDomDocument readDataFromXml(const QString &beginningOfSector,const QString &endOfSector);
    void writeDataToXml(const QDomDocument xmlDocument);

private:
    DataSystem *appSettings;

};

#endif // PROJECTREADERWRITER_H
