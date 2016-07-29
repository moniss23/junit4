#include "handover.h"
#include "QFile"
#include <QTextStream>
#include <Maps/Parameters/MapWindow/mapwindow.h>
#include <qdebug.h>


extern QStringList parametersFileContentList;



Handover::Handover()
{
}
Handover::Handover(QString name){
    area = name;
    setParams();
}

Handover::~Handover()
{

}
QString Handover::getArea(){
    return area;
}
QString Handover::getEastBoundary(){
    return QString::number(eastBoundary);
}
QString Handover::getNorthBoundary(){
    return QString::number(northBoundary);
}
QString Handover::getSouthBoundary(){
    return QString::number(southBoundary);
}
QString Handover::getWestBoundary(){
    return QString::number(westBoundary);
}
void Handover::setEastBoundary(QString e){
    eastBoundary=e.toInt();
}

void Handover::setNorthBoundary(QString n){
    northBoundary=n.toInt();
}
void Handover::setSouthBoundary(QString s){
    southBoundary=s.toInt();
}
void Handover::setWestBoundary(QString w){
    westBoundary=w.toInt();
}

//void Handover::setParams(){
//    QString name_search = ":area => \"" +area + "\""+",";

//    QString fileName = ":/RbFiles/parameters.rb";
//    QFile file1(fileName);
//    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;              // if coudn't open file: stop loading file

//    QString text1="";
//    QTextStream stream(&file1);

//    QString text_search;
//    while(text_search != name_search && !stream.atEnd()){
//        text1 = stream.readLine();
//        text_search = text1.trimmed();
//   }


//    tabParams = new QString [5];
//    for (int i=0; i<5; i++)
//    {
//        tabParams[i] = text_search;
//        text1 = stream.readLine();
//        text_search = text1.trimmed();
//    }

//    QStringList list;
//    for (int i=0; i<5; i++)
//    {
//        list = tabParams[i].split(" ", QString::SkipEmptyParts);
//        tabParams[i]= list[2];
//        tabParams[i].remove(QChar('"'));
//        tabParams[i].remove(QChar(','));
//        tabParams[i].remove(QChar(','));
//    }

//    area = tabParams[0];
//    southBoundary = tabParams[1].toInt();
//    northBoundary = tabParams[2].toInt();
//    westBoundary = tabParams[3].toInt();
//    eastBoundary = tabParams[4].toInt();
//}
void Handover::setParams(){
    qDebug() << "Nazwa szukanego HO: " << area;
    QString name_search = ":area => \"" +area + "\""+",";
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
    qDebug() << "Nazwa Handowera: " << tabParams[0];
    //if (tabParams[0] !=
    QStringList list;
    for (int i=0; i<5; i++)
    {
        list = tabParams[i].split(" ", QString::SkipEmptyParts);
        tabParams[i]= list[2];
        tabParams[i].remove(QChar('"'));
        tabParams[i].remove(QChar(','));
        tabParams[i].remove(QChar(','));
    }

    area = tabParams[0];
    southBoundary = tabParams[1].toInt();
    northBoundary = tabParams[2].toInt();
    westBoundary = tabParams[3].toInt();
    eastBoundary = tabParams[4].toInt();
}


void Handover::resetParams()
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
    QString name_search = ":area => \"" +area + "\""+",";
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
        list = tabParams[i].split(" ", QString::SkipEmptyParts);
        tabParams[i]= list[2];
        tabParams[i].remove(QChar('"'));
        tabParams[i].remove(QChar(','));
        tabParams[i].remove(QChar(','));
    }

    area = tabParams[0];
    southBoundary = tabParams[1].toInt();
    northBoundary = tabParams[2].toInt();
    westBoundary = tabParams[3].toInt();
    eastBoundary = tabParams[4].toInt();

}
