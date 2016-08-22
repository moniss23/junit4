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

class Project : public SerializeInterface
{
public:
    Project();

    QString name;
    QString fullpath;
    QString genScriptDir;

    ParametersFileData parametersFile;
    QVector<TrafficFileData> trafficFilesList;

    ~Project() {}

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);

    TrafficFileData* findTrafficFileByName(const QString &name);
};


#endif // PROJECT_H
