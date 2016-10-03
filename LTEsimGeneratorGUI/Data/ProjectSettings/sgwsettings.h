#ifndef SGWSETTINGS_H
#define SGWSETTINGS_H

#include <QVector>
#include <QPair>

#include "Data/Interfaces/serializeinterface.h"
#include "Data/Interfaces/scriptable.h"

/**
 * @brief The SgwSettings class contains settings for SGW module
 */
class SgwSettings : public SerializeInterface, public Scriptable
{
public:
    SgwSettings();
    ~SgwSettings();

    QString name;           ///< Name
    QString ipAdress;       ///< IP address
    QString apnList;        ///< APN list
    int ldi;                ///< LDI
    bool coreNetworkGateway;    ///< CoreNetwork gateway setting (true/false)

    /****************************
    * SERIALIZATION INTERFACE  *
    ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);

    /****************************
    *   PARSING INTERFACE       *
    ****************************/
    virtual QString ParseToScript();
};

#endif // SGWSETTINGS_H
