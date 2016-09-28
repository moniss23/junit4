#ifndef MAPPARSER_H
#define MAPPARSER_H

#include "Data/ProjectSettings/maprange.h"
#include "Data/Objects/cell.h"
#include "Data/Objects/handover.h"
#include "Data/ProjectSettings/ubsimsettings.h"
#include "Data/ProjectSettings/datageneratorsettings.h"
#include "Data/project.h"

#include <QString>
#include <QPair>
#include <QVector>
/**
 * @brief The MapParser class is used to generate part of Parameters script responsible for map and whole Traffic script
 */
class MapParser
{
public:
    MapParser();
    ~MapParser(){}
    /**
     * @brief ParseMap converts Map data to Ruby script
     * @param cellsInfo holds information about all the cells
     * @param mapRange holds information about map size and map scale
     * @param handovers holds informaton about all the handovers
     * @param ubSim holds the UBSim settings
     * @param dataGenerator holds DataGenerator settings
     * @return QString with whole script content
     */
    static QString ParseMap(QVector<QPair<Cell, Center>> &cellsInfo,
                            MapRange &mapRange,
                            QVector<Handover> &handovers,
                            UBSimSettings &ubSim,
                            DataGeneratorSettings &dataGenerator);
    /**
     * @brief GenerateTrafficScript generates the Traffic.rb script
     * @param project holds data bout the project
     * @param index is the index of TrafficFileData in a vector
     * @return QString with whold script content
     */
    static QString GenerateTrafficScript(const Project &project, const int &index);
};

#endif // MAPPARSER_H
