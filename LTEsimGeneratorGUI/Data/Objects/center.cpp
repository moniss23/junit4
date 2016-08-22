#include "Data/Objects/center.h"

#include "QFile"
#include <QTextStream>
#include <Maps/Parameters/MapWindow/mapwindow.h>

extern QStringList parametersFileContentList;

Center::Center()
{
}
Center::Center(QString name){
    area = name;
    setParams();
}

Center::~Center()
{

}
QString Center::getArea(){
    return area;
}

QString Center::getEastBoundary(){
    return QString::number(eastBoundary);
}

QString Center::getNorthBoundary(){
    return QString::number(northBoundary);
}
QString Center::getSouthBoundary(){
    return QString::number(southBoundary);
}
QString Center::getWestBoundary(){
    return QString::number(westBoundary);
}

void Center::setArea(QString value)
{
    area= value;
}
void Center::setEastBoundary(QString e){
    eastBoundary=e.toInt();
}
void Center::setNorthBoundary(QString n){
    northBoundary=n.toInt();
}
void Center::setSouthBoundary(QString s){
    southBoundary=s.toInt();
}
void Center::setWestBoundary(QString w){
    westBoundary=w.toInt();
}

void Center::setParams(){
    QString name_search = ":area => \"" +area;
    tabParams = new QString [5];
    for( int i=0; i<parametersFileContentList.size(); i++){
        if(parametersFileContentList[i].contains(name_search)){
            tabParams[0] = parametersFileContentList[i].trimmed();
            tabParams[1] = parametersFileContentList[i+1].trimmed();
            tabParams[2] = parametersFileContentList[i+2].trimmed();
            tabParams[3] = parametersFileContentList[i+3].trimmed();
            tabParams[4] = parametersFileContentList[i+4].trimmed();
        }
    }

    QStringList list;
    for (int i=0; i<5; i++)
    {
        list = tabParams[i].split(" ");
        if (list.size() > 3){
            tabParams[i] = list[2];
            list[3].remove(",");
            new_name_area = list[3].remove("\"");
        }
        tabParams[i]= list[2];
        tabParams[i].remove(QChar('"'));
        tabParams[i].remove(QChar(','));

    }
    area = tabParams[0];
    southBoundary = tabParams[1].toInt();
    northBoundary = tabParams[2].toInt();
    westBoundary = tabParams[3].toInt();
    eastBoundary = tabParams[4].toInt();
}
void Center::resetParams()
{
    QString fileName = ":/RbFiles/parameters.rb";
    QFile file1(fileName);

    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
        return;              // if coudn't open file: stop loading file

    QString text1="";
    QTextStream stream(&file1);
    QList <QString> fileParameters;
    while(!stream.atEnd()){
        text1 = stream.readLine();
        fileParameters << text1.trimmed();
   }

    QString name_search = ":area => \"" +area;
    tabParams = new QString [5];
    for( int i=0; i<fileParameters.size(); i++){
        if(fileParameters[i].contains(name_search)){
            tabParams[0] = fileParameters[i].trimmed();
            tabParams[1] = fileParameters[i+1].trimmed();
            tabParams[2] = fileParameters[i+2].trimmed();
            tabParams[3] = fileParameters[i+3].trimmed();
            tabParams[4] = fileParameters[i+4].trimmed();
        }
    }
    QStringList list;
    for (int i=0; i<5; i++)
    {
        list = tabParams[i].split(" ");
        tabParams[i]= list[2];
        tabParams[i].remove(QChar('"'));
        tabParams[i].remove(QChar(','));
    }
    new_name_area = "";
    area = tabParams[0];
    southBoundary = tabParams[1].toInt();
    northBoundary = tabParams[2].toInt();
    westBoundary = tabParams[3].toInt();
    eastBoundary = tabParams[4].toInt();
}
QString Center::getNew_name_area() const
{
    return new_name_area;
}

void Center::setNew_name_area(const QString &value)
{
    new_name_area = value;
}

