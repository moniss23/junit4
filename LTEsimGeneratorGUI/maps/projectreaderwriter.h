#ifndef PROJECTREADERWRITER_H
#define PROJECTREADERWRITER_H
#include <QByteArray>
#include <common_constans.h>
#include <QFile>
#include <QtXml>

class ProjectReaderWriter
{
public:
    ProjectReaderWriter();
    // ReaderWriterRefactor:  deleted static
    QByteArray readDataFromProj(const QString &beginningOfSector,const QString &endOfSector);
    QDomDocument readDataFromXml(const QString &beginningOfSector,const QString &endOfSector);
    void writeDataToXml(const QDomDocument xmlDocument){}
};

#endif // PROJECTREADERWRITER_H
