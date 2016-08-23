#include "Data/Objects/center.h"

#include "QFile"
#include <QTextStream>
#include <Maps/Parameters/MapWindow/mapwindow.h>

//extern QStringList parametersFileContentList;

Center::Center() {}
Center::Center(const QString &name) {area = name;}

QString Center::getArea() const {return area;}
QString Center::getNew_name_area() const {return new_name_area;}
QString Center::getEastBoundary() const {return QString::number(eastBoundary);}
QString Center::getWestBoundary() const {return QString::number(westBoundary);}
QString Center::getNorthBoundary() const {return QString::number(northBoundary);}
QString Center::getSouthBoundary() const {return QString::number(southBoundary);}

void Center::setArea(const QString &value) {area = value;}
void Center::setNew_name_area(const QString &value) {new_name_area = value;}
void Center::setEastBoundary(const QString &east) {eastBoundary=east.toInt();}
void Center::setWestBoundary(const QString &west) {westBoundary=west.toInt();}
void Center::setNorthBoundary(const QString &north) {northBoundary=north.toInt();}
void Center::setSouthBoundary(const QString &south) {southBoundary=south.toInt();}

/* TODO: zasypac sola jak tylko wczytywanie centerow z projektu zacznie dzialac */
void Center::setParams() {}
void Center::resetParams() {}
/* ---------------------------------------------------------------------------- */
