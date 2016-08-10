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
#include <Data/trafficdata.h>


class Project : public SerializeInterface
{
public:
    QString name;
    QString fullpath;
    QString rbOutputDir;
    QString chosenMapType;

    TrafficData parametersFile;
    QVector<TrafficData> trafficFilesList;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
public:
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};


#endif // PROJECT_H
