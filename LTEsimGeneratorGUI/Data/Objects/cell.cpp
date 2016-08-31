#include "Data/Objects/cell.h"
#include "Maps/Parameters/MapWindow/mapwindow.h"

Cell::Cell() {}
Cell::Cell(const QString &name) {cell = name;}
Cell::~Cell() {}

void Cell::resetParams() {}


QDataStream &operator<<(QDataStream &out, const Cell &cell)
{
    out << cell.cell << cell.site;
    out << cell.pci << cell.position_X << cell.position_Y;
    out << cell.earfcnDl << cell.transmitPower << cell.ulNoiseAndInterference;

    return out;
}

QDataStream &operator>>(QDataStream &in, Cell &cell)
{
    in >> cell.cell >> cell.site;
    in >> cell.pci >> cell.position_X >> cell.position_Y;
    in >> cell.earfcnDl >> cell.transmitPower >> cell.ulNoiseAndInterference;

    return in;
}
