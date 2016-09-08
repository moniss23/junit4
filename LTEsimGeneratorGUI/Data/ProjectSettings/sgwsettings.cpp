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
    outputString.append("\t#\n "
                        "\t# Retrieve default parameters for SGW.\n "
                        "\t#\n "
                        "\tdef Parameters.getSgwParameters()\n"
                        "\t#Define and return default values\n");
    outputString.append("\t\tdefault = {}\n\n");
    // NAME
    outputString.append("\t\tdefault[:sgw_names] = [\"");
    outputString.append(name);
    outputString.append("\"]");
    outputString.append("\t\t\t\t\t# Name of the Serving GWs\n");
    //IP ADRESS
    outputString.append("\t\tdefault[:sgw_ipAddresses] = [\"");
    outputString.append(ipAdress);
    outputString.append("\"]\n");
    //APN
    outputString.append("\t\tdefault[:apn_lists] = [\"");
    outputString.append(apnList);
    outputString.append("\"]\n");
    //LDI
    outputString.append("\t\tdefault[:sgw_LDIs] = [\"");
    outputString.append(QString::number(ldi));
    outputString.append("\"]\n");
    //Core Network Gateway
    outputString.append("\t\tdefault[:sgw_LDIs] = ");
    if (coreNetworkGateway){
        outputString.append("true");
    }
    else {
        outputString.append("false");
    }
    outputString.append("\t\t\t\t\t# Indicates if the core network shall act\n");
    outputString.append("\t\t\t\t\t\t\t\t\t\t# as an IP gateway to the UEs\n");
    outputString.append("\n");
    outputString.append("\t\t# All JMX parameters can be listed with help :sgw in the ltesim_cli\n");
    outputString.append("\t\treturn default\n");
    outputString.append("\tend\n");
    return outputString;
}
