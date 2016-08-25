#ifndef SGWSETTINGS_H
#define SGWSETTINGS_H

#include <QString>
#include <QVector>
#include <QPair>

#include "Data/Interfaces/serializeinterface.h"

class SgwSettings : public SerializeInterface
{
public:
    SgwSettings();
    ~SgwSettings();
    QString name;
    QString ipAdress;
    QVector<QPair<QString,QString>> apnList;
    int ldi;
    bool coreNetworkGateway;

    /****************************
    * SERIALIZATION INTERFACE  *
    ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);

};

#endif // SGWSETTINGS_H
