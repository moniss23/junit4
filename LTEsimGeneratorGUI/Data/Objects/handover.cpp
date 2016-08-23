#include "Data/Objects/handover.h"
#include <Maps/Parameters/MapWindow/mapwindow.h>

//extern QStringList parametersFileContentList;

Handover::Handover() {}
Handover::Handover(const QString &name) {area = name;}

Handover::~Handover() {}

QString Handover::getArea() const {return area;}
QString Handover::getEastBoundary() const {return QString::number(eastBoundary);}
QString Handover::getWestBoundary() const {return QString::number(westBoundary);}
QString Handover::getNorthBoundary() const {return QString::number(northBoundary);}
QString Handover::getSouthBoundary() const {return QString::number(southBoundary);}

void Handover::setArea(const QString &name) { area = name; }
void Handover::setEastBoundary(const QString &east) {eastBoundary=east.toInt();}
void Handover::setWestBoundary(const QString &west) {westBoundary=west.toInt();}
void Handover::setNorthBoundary(const QString &north) {northBoundary=north.toInt();}
void Handover::setSouthBoundary(const QString &south) {southBoundary=south.toInt();}

/* TODO: zasypac jak tylko wczytywanie HO z klasy Project bedzie dokonczone */
void Handover::setParams() {}
void Handover::resetParams() {}
/* ------------------------------------------------------------------------ */
