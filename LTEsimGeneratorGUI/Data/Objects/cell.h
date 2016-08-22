#ifndef CELL_H
#define CELL_H

#include <QList>
#include <QString>
#include <QVector>
#include <QCheckBox>
#include <QStringList>

#include "Data/Objects/center.h"

class Cell
{
public:
    Cell();
    Cell(const QString &name);

    ~Cell();

    Center* center;
    QCheckBox* chBox;

    void resetParams();
    QVector<QString> setParams();

    QString getCell();
    void setCell(const QString &c);

    QString getSite();
    void setSite(const QString &s);

    QString getPci();
    void setPci(const QString &s);

    QString getPosition_X();
    void setPosition_X(const QString &p_x);

    QString getPosition_Y();
    void setPosition_Y(const QString &p_y);

    QString getEarfcnDl();
    void setEarfcnDl(const QString &e);

    QString getTransmitPower();
    void setTransmitPower(const QString &t);

    QString getUlNoiseAndInterference();
    void setUlNoiseAndInterference(const QString &u);

    QString getCell_new_name() const;
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
