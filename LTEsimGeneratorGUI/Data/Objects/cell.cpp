#include "Data/Objects/cell.h"
#include <Maps/Parameters/MapWindow/mapwindow.h>

//extern QStringList parametersFileContentList;

Cell::Cell() {}
Cell::Cell(const QString &name) {cell = name;}
Cell::~Cell() {}

/* TODO: do zasypania jak tylko wczytywanie Cell z klasy Project bedzie dokonczone */
void Cell::setParams() {}
void Cell::resetParams() {}
/* ------------------------------------------------------------------------------- */

/**** GETTERS && SETTERS ****/

QString Cell::getCell() {return cell;}
void Cell::setCell(const QString &c) {cell = c; }

QString Cell::getSite() {return site;}
void Cell::setSite(const QString &s) {site = s;}

QString Cell::getPci() {return QString::number(pci);}
void Cell::setPci(const QString &p) {pci = p.toInt();}

QString Cell::getPosition_X() {return QString::number(position_X);}
void Cell::setPosition_X(const QString &p_x) {position_X = p_x.toInt();}

QString Cell::getPosition_Y() {return QString::number(position_Y);}
void Cell::setPosition_Y(const QString &p_y) {position_Y = p_y.toInt();}

QString Cell::getEarfcnDl() {return QString::number(earfcnDl);}
void Cell::setEarfcnDl(const QString &e) {earfcnDl = e.toInt();}

QString Cell::getTransmitPower() {return QString::number(transmitPower);}
void Cell::setTransmitPower(const QString &t) {transmitPower = t.toFloat();}

QString Cell::getUlNoiseAndInterference() {return QString::number(ulNoiseAndInterference);}
void Cell::setUlNoiseAndInterference(const QString &u) {ulNoiseAndInterference = u.toFloat();}

QString Cell::getCell_new_name() const { return cell_new_name; }
void Cell::setCell_new_name(const QString &value) { cell_new_name = value; }
