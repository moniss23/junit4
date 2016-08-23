#ifndef DATAGENERATORSETTINGS_H
#define DATAGENERATORSETTINGS_H

#include <QString>
#include <QBuffer>
#include <QDataStream>

#include "Data/Interfaces/serializeinterface.h"


class DataGeneratorSettings : public SerializeInterface
{
public:
    DataGeneratorSettings();
    ~DataGeneratorSettings() {}

    QString dataGenerator;
    QString userDataGenerator;
    QString ipgwtg_IP_Address;

    int ipgwtgPort;

    bool startIspSimulator;
    bool ipgwtgInbandSignaling;
    bool ipgwtgFtpSenderConnectPut;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // DATAGENERATORSETTINGS_H