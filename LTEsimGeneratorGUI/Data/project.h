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

#include "Data/ProjectSettings/sgwsettings.h"
#include "Data/ProjectSettings/uctoolsettings.h"
#include "Data/ProjectSettings/channelmodelsettings.h"
#include "Data/ProjectSettings/datageneratorsettings.h"
#include "Data/ProjectSettings/mmesettings.h"
#include "Data/ProjectSettings/pagingsettings.h"

class Project : public SerializeInterface
{
public:
    Project();
    ~Project() {}

    //-- Project info --//
    QString name;
    QString fullpath;
    QString genScriptDir;

    //-- Project objects  --//
    QVector<Cell>     cells;
    QVector<Center>   centers;
    QVector<Handover> handovers;

    //-- Project  data --//
    SgwSettings             sgwSettings;
    UCToolSettings          ucToolSettings;
    ChannelModelSettings    channelModelSettings;
    DataGeneratorSettings   dataGeneratorSettings;
    MmeSettings             mmeSettings;
    PagingSettings          pagingSettings;
    bool                    SimulatedCoreNetwork = false;
    bool                    SimulatedUe = false;

    //-- Project files --//
    ParametersFileData      parametersFile;
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
