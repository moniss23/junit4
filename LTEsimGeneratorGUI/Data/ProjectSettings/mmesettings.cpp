#include "mmesettings.h"
#include <QBuffer>
#include <QDataStream>
MmeSettings::MmeSettings()
{

}
MmeSettings::~MmeSettings(){}
QString MmeSettings::getElementType() const
{
    return QString("MmeSettings");
}

QByteArray MmeSettings::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << simulatedCoreNetwork << names << tais << numberOfMme << uris << pluginFilterPath;
    return serializedData.buffer();
}

void MmeSettings::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> simulatedCoreNetwork >> names >> tais >> numberOfMme >> uris >> pluginFilterPath;
}
QString MmeSettings::ParseToScript()
{
    QString outputString;
    //  HEADER
    outputString.append("\t#\n\
    \t# Retrieve default parameters for MME.\n\
    \t# \n\
    \tdef Parameters.getMmeParameters()\n\
    \t# Define and return default values\n\
    \tdefault = {}\n\n");

    // SIMULATE CORE
    outputString.append("\t\tdefault[:simulate_core] = ");
    if (simulatedCoreNetwork){
        outputString.append("true");
    }
    else {
        outputString.append("false");
    }
    outputString.append("\t# Set to true if simulated core is used in the configuration.\n");

    // NAMES
    outputString.append("\t\tdefault[:mme_names] = ");
    outputString.append("[");
    for (int i=0;i<names.size();i++){
        outputString.append("\"");
        outputString.append(names[i]);
        outputString.append("\"");
        if (i<names.size()-1) {
            outputString.append(", ");
        }
    }
    outputString.append("]");
    outputString.append("\t# Name of the MME component\n");

    // TAIS
    outputString.append("\t\tdefault[:mme_tais] = ");
    outputString.append("[\"");
    outputString.append(tais);
    outputString.append("\"]");
    outputString.append("\t# MME tracking area identity value\n");

    // NUMBER OF MMES
    outputString.append("\t\tdefault[:mmes] = ");
    outputString.append(QString::number(numberOfMme));
    outputString.append("\t# Number of MMEs (used in multiple MME configuration)\n");

    outputString.append("\t\t# The IP addresses must be available on the LTEsum server and reachable from the eNB CP interface\n");

    // MME S1AP URIS
    outputString.append("\t\tdefault[:mme_s1ap_uris] = ");
    outputString.append("[\"");
    outputString.append(uris);
    outputString.append("\"]\n");

    // S1AP PLUGIN FILTER PATH
    outputString.append("\t\tdefault[:s1ap_pluginFilterPath] = ");
    outputString.append("\"");
    outputString.append(pluginFilterPath);
    outputString.append("\"");
    outputString.append("\t# Set the filter path\n");

    // FOOTER
    outputString.append("\n\t\t# All JMX parameters can be listed with help :mme in the ltesim_cli\n");
    outputString.append("\t\treturn default\n");
    outputString.append("\tend\n\n");

    return outputString;
}
