#include "sgwsettings.h"

#include <QBuffer>
#include <QDataStream>

SgwSettings::SgwSettings() {
}
SgwSettings::~SgwSettings() {
}
QString SgwSettings::getElementType() const
{
    return QString("SgwSettings");
}

QByteArray SgwSettings::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << name << ipAdress << apnList << ldi << coreNetworkGateway;
    return serializedData.buffer();
}

void SgwSettings::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> name >> ipAdress >> apnList >> ldi >> coreNetworkGateway;
}
QString SgwSettings::ParseToScript()
{
    QString outputString;
    outputString.append(" #\n "
                        " # Retrieve default parameters for SGW.\n "
                        " #\n "
                        " def Parameters.getSgwParameters()\n"
                        " #Define and return default values\n");
    outputString.append("  default = {}\n\n");
    // NAME
    outputString.append("  default[:sgw_names] = [\"");
    outputString.append(name);
    outputString.append("\"]");
    outputString.append("\t\t\t# Name of the Serving GWs\n");
    //IP ADRESS
    outputString.append("  default[:sgw_ipAddresses] = [\"");
    outputString.append(ipAdress);
    outputString.append("\"]\n");
    //APN
    outputString.append("  default[:apn_lists] = [\"");
    outputString.append(apnList);
    outputString.append("\"]\n");
    //LDI
    outputString.append("  default[:sgw_LDIs] = [\"");
    outputString.append(QString::number(ldi));
    outputString.append("\"]\n");
    //Core Network Gateway
    outputString.append("  default[:sgw_LDIs] = ");
    if (coreNetworkGateway){
        outputString.append("true");
    }
    else {
        outputString.append("false");
    }
    outputString.append("  # Indicates if the core network shall act\n");
    outputString.append("  # as an IP gateway to the UEs\n");
    outputString.append("\n");
    outputString.append("  # All JMX parameters can be listed with help :sgw in the ltesim_cli\n");
    outputString.append("  return default\n");
    outputString.append("\tend\n");
    return outputString;
}
