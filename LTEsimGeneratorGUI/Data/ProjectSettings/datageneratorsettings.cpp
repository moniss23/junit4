#include "datageneratorsettings.h"

DataGeneratorSettings::DataGeneratorSettings()
{

}

QString DataGeneratorSettings::getElementType() const
{
    return QString("DataGeneratorSettings");
}

QByteArray DataGeneratorSettings::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << dataGenerator << userDataGenerator << ipgwtg_IP_Address << ipgwtgPort
           << startIspSimulator << ipgwtgInbandSignaling << ipgwtgFtpSenderConnectPut
           << runIpexEnvoirement;

    return serializedData.buffer();
}

void DataGeneratorSettings::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> dataGenerator >> userDataGenerator >> ipgwtg_IP_Address >> ipgwtgPort
           >> startIspSimulator >> ipgwtgInbandSignaling >> ipgwtgFtpSenderConnectPut
           >> runIpexEnvoirement;
}

