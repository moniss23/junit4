#ifndef CELL_H
#define CELL_H

#include <QString>
#include <QVector>
#include <QStringList>
#include <QList>
#include <QCheckBox>
#include <maps/object_map/center.h>

class Cell
{
public:
    Cell(QString name);
    Cell();
    ~Cell();
    Cell *tabCell;

    QString getCell();
    QString *setParams();
    void resetParams();

     QString getSite();
     QString getPci();
     QString getPosition_X();
     QString getPosition_Y();
     QString getEarfcnDl();
     QString getTransmitPower();
     QString getUlNoiseAndInterference();

     void setCell(QString c);
     void setSite(QString s);
     void setPci(QString s);
     void setPosition_X(QString px);
     void setPosition_Y(QString py);
     void setEarfcnDl(QString e);
     void setTransmitPower(QString t);
     void setUlNoiseAndInterference(QString u);


     QCheckBox* chBox;
     Center* center;
     QString getCell_new_name() const;
     void setCell_new_name(const QString &value);

     bool wasThereChanges();

private:
    QString *tabParams;
    QString cell;
    QString cell_new_name;
    QString site;
    int pci;
    int position_X;
    int position_Y;
    int earfcnDl;
    float transmitPower;
    float ulNoiseAndInterference;

};

#endif // CELL_H
