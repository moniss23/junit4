#ifndef PROJECT_H
#define PROJECT_H

#include <QBuffer>
#include <QDataStream>
#include <QListWidgetItem>
#include <vector>

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

    std::vector<TrafficData> trafficFilesList;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
public:
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};


#endif // PROJECT_H
