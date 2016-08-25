#ifndef PROJECT_H
#define PROJECT_H

#include <QVector>
#include <QBuffer>
#include <QDataStream>
#include <QListWidgetItem>

#include "Data/Interfaces/serializeinterface.h"
#include "Data/Objects/cell.h"
#include "Data/Objects/center.h"
#include "Data/Objects/handover.h"
#include "Data/Objects/trafficfiledata.h"
#include "Data/Objects/parametersfiledata.h"
#include "Data/ProjectSettings/datageneratorsettings.h"
#include "Data/ProjectSettings/sgwsettings.h"
#include "Data/ProjectSettings/uctoolsettings.h"

class Project : public SerializeInterface
{
public:
    Project();
    ~Project() {}

    QString name;
    QString fullpath;
    QString genScriptDir;

    QVector<Cell> cells;
    QVector<Center> centers;
    QVector<Handover> handovers;
    DataGeneratorSettings dataGeneratorSettings;
    UCToolSettings ucToolSettings;
    SgwSettings sgwSettings;
    bool SimulatedCoreNetwork = false;
    bool SimulatedUe = false;
    ParametersFileData parametersFile;
    QVector<TrafficFileData> trafficFilesList;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);

    TrafficFileData* findTrafficFileByName(const QString &name);
};


#endif // PROJECT_H
