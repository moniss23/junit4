#ifndef MAPPARSER_H
#define MAPPARSER_H

#include "Data/ProjectSettings/maprange.h"
#include "Data/Objects/cell.h"
#include "Data/Objects/handover.h"
#include "Data/ProjectSettings/ubsimsettings.h"
#include "Data/ProjectSettings/datageneratorsettings.h"

#include <QString>
#include <QPair>
#include <QVector>

class MapParser
{
public:
    MapParser();
    ~MapParser(){}

    static QString ParseMap(QVector<QPair<Cell, Center>> &cellsInfo, MapRange &mapRange, QVector<Handover> &handover, UBSimSettings &ubSim, DataGeneratorSettings &dataGenerator);
};

#endif // MAPPARSER_H
