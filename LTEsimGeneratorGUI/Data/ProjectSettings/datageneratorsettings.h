#ifndef DATAGENERATORSETTINGS_H
#define DATAGENERATORSETTINGS_H

#include "Data/Interfaces/serializeinterface.h"

/**
 * @brief The DataGeneratorSettings class contains settings for DataGenerator
 */
class DataGeneratorSettings : public SerializeInterface
{
public:
    DataGeneratorSettings();
    ~DataGeneratorSettings() {}

    QString dataGenerator;          ///< Data Generator's name
    QStringList userDataGenerator;  ///< Data Generator's users list

    QString ipgwtg_IP_Address;      ///< IPGWTG IP address
    int ipgwtgPort;                 ///< IPGWTG port

    bool startIspSimulator;         ///< ISP simulator starting setting (true/false)
    bool ipgwtgInbandSignaling;     ///< IPGWTG inband signaling setting (true/false)
    bool ipgwtgFtpSenderConnectPut; ///< IPGWTG FTP sender conn. put setting (true/false)
    bool runIpexEnvoirement;        ///< IPEX environment running setting (true/false)

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // DATAGENERATORSETTINGS_H
