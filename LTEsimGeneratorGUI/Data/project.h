#ifndef PROJECT_H
#define PROJECT_H

#include <QVector>
#include <QBuffer>
#include <QDataStream>
#include <QListWidgetItem>

#include <Data/cell.h>
#include <Data/center.h>
#include <Data/handover.h>
#include <Data/serializeinterface.h>
#include <Data/trafficfiledata.h>
#include <Data/parametersfiledata.h>


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

private:
    TrafficFileData* findTrafficFileByName(const QString &name);
};


#endif // PROJECT_H
