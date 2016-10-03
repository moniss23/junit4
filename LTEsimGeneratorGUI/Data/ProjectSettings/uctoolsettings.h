#ifndef UCTOOLDSETTINGS_H
#define UCTOOLDSETTINGS_H

#include "Data/Interfaces/serializeinterface.h"

/**
 * @brief The UCToolSettings class contains settings for UCTool module
 */
class UCToolSettings : public SerializeInterface
{
public:
    UCToolSettings();
    ~UCToolSettings() {}

    QString ucToolIP;           ///< UCTool IP address
    QString ucToolCIds;         ///< UCTool CIds
    QString ucToolServiceIp;    ///< UCTool Service IP

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // UCTOOLDSETTINGS_H
