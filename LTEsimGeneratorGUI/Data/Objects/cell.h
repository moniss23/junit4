#ifndef CELL_H
#define CELL_H

#include <QString>
#include <QCheckBox>

#include "Data/Objects/center.h"

/**
 * @brief The Cell class represents LTEsim cell object
 */
class Cell {
public:
    Cell();
    Cell(const QString &name);
    ~Cell();


    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
public:
    /**
     * @brief resetParams restores Cell default parameters
     */
    void resetParams();

public:
    QString name;                           ///< Name
    QString site;                           ///< Site

    Center* center;                         ///< Center of a cell represented by Center class

    int pci;                                ///< PCI
    int position_X = 4000;                  ///< Position of a cell on X axis
    int position_Y = 4000;                  ///< Position of a cell on Y axis
    int earfcnDl = 2050;                    ///< EARFCN Downlink
    float transmitPower = -75.0;            ///< Transmit Power
    float ulNoiseAndInterference = -116.0;  ///< Uplink noise and interference
};

QDataStream &operator>>(QDataStream &in, Cell &cell);
QDataStream &operator<<(QDataStream &out, const Cell &cell);

#endif // CELL_H
