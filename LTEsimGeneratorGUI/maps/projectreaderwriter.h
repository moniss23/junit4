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
    static QByteArray readDataFromProj(const QString &beginningOfSector,const QString &endOfSector);
    static QByteArray readDataFromXml(const QString &beginningOfSector,const QString &endOfSector);
    static void writeDataToXml(const QDomDocument xmlDocument){}
};

#endif // PROJECTREADERWRITER_H
