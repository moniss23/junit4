#ifndef CELL_H
#define CELL_H

#include <QString>
#include <QCheckBox>

#include "Data/Objects/center.h"

class Cell {
public:
    Cell();
    Cell(const QString &name);
    ~Cell();

    Center* center;
    QCheckBox* chBox;

    void resetParams();

public:
    QString name;
    QString site;

    int pci;
    int position_X = 4000;
    int position_Y = 4000;
    int earfcnDl = 2050;
    float transmitPower = -75.0;
    float ulNoiseAndInterference = -116.0;
};

QDataStream &operator<<(QDataStream &out, const Cell &cell);
QDataStream &operator>>(QDataStream &in, Cell &cell);

#endif // CELL_H
