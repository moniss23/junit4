#include "Data/Objects/center.h"

#include "QFile"
#include <QTextStream>
#include <Maps/Parameters/MapWindow/mapwindow.h>

//extern QStringList parametersFileContentList;

Center::Center() {}

Center::Center(QString name) {
    area = name;
}

QString Center::getArea(){return area;}
QString Center::getEastBoundary() {return QString::number(eastBoundary);}
QString Center::getNorthBoundary() {return QString::number(northBoundary);}
QString Center::getSouthBoundary() {return QString::number(southBoundary);}
QString Center::getWestBoundary() {return QString::number(westBoundary);}

void Center::setArea(QString value) {area = value;}
void Center::setEastBoundary(QString e) {eastBoundary=e.toInt();}
void Center::setNorthBoundary(QString n) {northBoundary=n.toInt();}
void Center::setSouthBoundary(QString s) {southBoundary=s.toInt();}
void Center::setWestBoundary(QString w) {westBoundary=w.toInt();}


QString Center::getNew_name_area() const {return new_name_area;}
void Center::setNew_name_area(const QString &value) {new_name_area = value;}

/* TODO: zasypac sola jak tylko wczytywanie centerow z projektu zacznie dzialac */
void Center::setParams() {}
void Center::resetParams() {}
/* ---------------------------------------------------------------------------- */
