#ifndef SGWSETTINGS_H
#define SGWSETTINGS_H

#include <QString>
#include <QVector>
#include <QPair>

#include "Data/Interfaces/serializeinterface.h"
#include "Data/Interfaces/scriptable.h"

class SgwSettings : public SerializeInterface, public Scriptable
{
public:
    SgwSettings();
    ~SgwSettings();
    QString name;
    QString ipAdress;
    QString apnList;
    int ldi;
    bool coreNetworkGateway;

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
