#ifndef TRAFFICDATA_H
#define TRAFFICDATA_H

#include <QString>
#include <QStringList>

#include <Data/serializeinterface.h>

class TrafficData : public SerializeInterface
{
public:
    QString fileName;
    QString content;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
public:
    ~TrafficData() {}

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // TRAFFICDATA_H
