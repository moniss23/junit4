#include "maprange.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <Maps/Parameters/MapWindow/mapwindow.h>

extern MapWindow* map_w;
extern QString parametersFileContent;
extern QStringList parametersFileContentList;
extern QString savedParametersFileContent;
extern std::vector<QString> trafficFilesContent;
extern std::vector<QString> savedTrafficFilesContent;
extern bool paramFileChanged;
extern bool paramFileModified;
extern std::vector<bool> trafficFilesChanged;
extern std::vector<bool> trafficFilesModified;

MapRange::MapRange()
{
   setParams();
}
int MapRange::getSouthBoundMap() const
{
    return southBoundMap;
}

void MapRange::setSouthBoundMap(int value)
{
    southBoundMap = value;
}
int MapRange::getNorthBoundMap() const
{
    return northBoundMap;
}

void MapRange::setNorthBoundMap(int value)
{
    northBoundMap = value;
}
int MapRange::getWestBoundMap() const
{
    return westBoundMap;
}

void MapRange::setWestBoundMap(int value)
{
    westBoundMap = value;
}
int MapRange::getEastBoundMap() const
{
    return eastBoundMap;
}

void MapRange::setEastBoundMap(int value)
{
    eastBoundMap = value;
}


void MapRange::openFile()
{
    QString fileName = ":/RbFiles/parameters.rb";
    QFile file1(fileName);

    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
        return;              // if coudn't open file: stop loading file

    QString text1="";
    QTextStream stream(&file1);

    while(!stream.atEnd()){
        text1 = stream.readLine();
        fileParameters << text1.trimmed();
   }
}

QString MapRange::searchParameters(QString name)
{
    QStringList list;
    QString text1= "";
    for (int i=0; i<parametersFileContentList.size();i++)
    {
        if (parametersFileContentList[i].contains(name)){
            text1 = parametersFileContentList[i];
            list = text1.split("#");
            text1 = list[0];
            list = text1.split("=");
            return list[1].remove(QChar('"'));
        }
    }
    return NULL;
}

void MapRange::setParams()
{
    southBoundMap = searchParameters("southBoundMap").toInt();
    northBoundMap = searchParameters("northBoundMap").toInt();
    westBoundMap = searchParameters("westBoundMap").toInt();
    eastBoundMap = searchParameters("eastBoundMap").toInt();
}

