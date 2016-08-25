#include "Data/Objects/cell.h"
#include <Maps/Parameters/MapWindow/mapwindow.h>

//extern QStringList parametersFileContentList;

Cell::Cell() {}
Cell::Cell(const QString &name) {cell = name;}
Cell::~Cell() {}

QString Cell::getCell() const {return cell;}
QString Cell::getSite() const {return site;}
QString Cell::getPci() const {return QString::number(pci);}
QString Cell::getEarfcnDl() const {return QString::number(earfcnDl);}
QString Cell::getPosition_X() const {return QString::number(position_X);}
QString Cell::getPosition_Y() const {return QString::number(position_Y);}
QString Cell::getTransmitPower() const {return QString::number(transmitPower);}
QString Cell::getUlNoiseAndInterference() const {return QString::number(ulNoiseAndInterference);}
QString Cell::getCell_new_name() const { return cell_new_name; }

void Cell::setCell(const QString &c) {cell = c; }
void Cell::setSite(const QString &s) {site = s;}
void Cell::setPci(const QString &p) {pci = p.toInt();}
void Cell::setEarfcnDl(const QString &e) {earfcnDl = e.toInt();}
void Cell::setPosition_X(const QString &p_x) {position_X = p_x.toInt();}
void Cell::setPosition_Y(const QString &p_y) {position_Y = p_y.toInt();}
void Cell::setTransmitPower(const QString &t) {transmitPower = t.toFloat();}
void Cell::setUlNoiseAndInterference(const QString &u) {ulNoiseAndInterference = u.toFloat();}
void Cell::setCell_new_name(const QString &value) { cell_new_name = value; }

/* TODO: do zasypania jak tylko wczytywanie Cell z klasy Project bedzie dokonczone */
void Cell::setParams() {}
void Cell::resetParams() {}
/* ------------------------------------------------------------------------------- */


QDataStream &operator<<(QDataStream &out, const Cell &cell)
{
    out <<cell.cell<<cell.site<<cell.cell_new_name;
    out <<cell.pci<<cell.position_X<<cell.position_Y;
    out <<cell.earfcnDl<<cell.transmitPower<<cell.ulNoiseAndInterference;

    return out;
}


QDataStream &operator>>(QDataStream &in, Cell &cell)
{
    in >>cell.cell>>cell.site>>cell.cell_new_name;
    in >>cell.pci>>cell.position_X>>cell.position_Y;
    in >>cell.earfcnDl>>cell.transmitPower>>cell.ulNoiseAndInterference;

    return in;
}
