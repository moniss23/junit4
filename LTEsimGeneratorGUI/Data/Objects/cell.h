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

    void setParams();
    void resetParams();

    QString getCell() const;
    QString getSite() const;
    QString getPci() const;
    QString getPosition_X() const;
    QString getPosition_Y() const;
    QString getEarfcnDl() const;
    QString getTransmitPower() const;
    QString getUlNoiseAndInterference() const;
    QString getCell_new_name() const;

    void setCell(const QString &c);
    void setSite(const QString &s);
    void setPci(const QString &s);
    void setPosition_X(const QString &p_x);
    void setPosition_Y(const QString &p_y);
    void setEarfcnDl(const QString &e);
    void setTransmitPower(const QString &t);
    void setUlNoiseAndInterference(const QString &u);
    void setCell_new_name(const QString &value);

private:
    QString cell;
    QString site;
    QString cell_new_name;

    int pci;
    int position_X;
    int position_Y;
    int earfcnDl;
    float transmitPower;
    float ulNoiseAndInterference;
};

#endif // CELL_H
