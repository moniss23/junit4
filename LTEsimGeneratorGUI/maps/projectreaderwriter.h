#ifndef PROJECTREADERWRITER_H
#define PROJECTREADERWRITER_H
#include <QByteArray>
#include <common_constans.h>
#include <QFile>
#include <QtXml>
#include "appsettings.h"

class ProjectReaderWriter
{
public:

    ProjectReaderWriter(AppSettings *appSettings);
    // ReaderWriterRefactor:  deleted static
    QByteArray readDataFromProj(const QString &beginningOfSector,const QString &endOfSector);
    QDomDocument readDataFromXml(const QString &beginningOfSector,const QString &endOfSector);
    void writeDataToXml(const QDomDocument xmlDocument){}

private:
    AppSettings *appSettings;

};

#endif // PROJECTREADERWRITER_H
