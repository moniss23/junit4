#ifndef UCTOOLDSETTINGS_H
#define UCTOOLDSETTINGS_H

#include "Data/Interfaces/serializeinterface.h"

class UCToolSettings : public SerializeInterface
{
public:
    UCToolSettings();
    ~UCToolSettings() {}

    QString ucToolIP;
    QString ucToolCIds;
    QString ucToolServiceIp;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // UCTOOLDSETTINGS_H
