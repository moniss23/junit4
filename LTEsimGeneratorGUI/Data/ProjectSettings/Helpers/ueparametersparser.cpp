#include "ueparametersparser.h"

QString UeParametersParser::ParseToScript(UCToolSettings &ucTool,UeParameters &ue)
{
    QString outputString;
    QString header = "\tdef Parameters.getUeParameters()\n\
\t\t# Define and return default values\n\
\t\tdefault = {}\n\n";
    outputString.append(header);
    // Start Ue Component
    outputString.append("\t\tdefault[:start_ue_component] = ");
    if (ue.startUeComponent){
        outputString.append("true");
    }
    else {
        outputString.append("false");
    }
    outputString.append("\t\t\t# Decide if the UE component should be started\n");
    outputString.append("\n");
    // NAME
    outputString.append("\t\tdefault[:name] = \"");
    outputString.append(ue.name);
    outputString.append("\"");
    outputString.append("\t\t\t\t\t# Name of the UE component\n");
    outputString.append("\n");
    // MANAGERS
    outputString.append("\t\tdefault[:l1l2_managers] = \"");
    outputString.append(ue.managers);
    outputString.append("\"");
    outputString.append("\t\t# Space separated string with TYPE;instance tuples where allowed values of TYPE is UCTOOL.");
    outputString.append("\n");
    // PLUGIN FILTER PATH
    outputString.append("\t\tdefault[:rrc_pluginFilterPath] = \"");
    outputString.append(ue.pluginFilterPath);
    outputString.append("\"\n\n");
    // UCTOOL IP
    outputString.append("\t\tdefault[:uctool_ip] = \"{");
    outputString.append(ucTool.ucToolIP);
    outputString.append("}\"");
    outputString.append("\t\t# UCTOOL device name the IP address of the UCtool.");
    outputString.append("\n");
    outputString.append("\t\t# NOTE! If only IP address is given then the IP address will be\n");
    outputString.append("\t\t# applicable for all UCTOOL managers.\n");
    // UCTOOL CIDS
    outputString.append("\t\tdefault[:uctool_cIds] = \"{");
    outputString.append(ucTool.ucToolCIds);
    outputString.append("}\"");
    outputString.append("\t# UCTOOL device name and cell names used to map.\n");
    outputString.append("\t\t# the UCTOOL cells to corresponding cells in the REC.\n");
    // UCTOOL SERVICE IP
    outputString.append("\t\tdefault[:uctool_service_ip] = \"{");
    outputString.append(ucTool.ucToolServiceIp);
    outputString.append("}\"");
    outputString.append("\t# UCTOOL device name and the IP address of the service requested.\n");
    outputString.append("\t\t# NOTE! If only IP address is given then the IP address will be\n");
    outputString.append("\t\t # applicable for all UCTOOLs.\n");
    outputString.append("\n");
    outputString.append("###### Security related parameters ###################################################################################\n");
    // UE NETWORK CAPABILITY
    outputString.append("\t\tdefault[:ue_network_capability] = \"");
    outputString.append(ue.ueNetworkCapability);
    outputString.append("\"");
    outputString.append("\t\t# UE network capabilities. See 3GPP 24.008 for more details\n");
    outputString.append("\t\t# Used to control which integrity protection and ciphering algorithms a UE supports.\n");
    outputString.append("\n");
    // UE KEY DERIVATION ALGORITHM
    outputString.append("\t\tdefault[:ue_keyDerivationAlgorithm] = \"");
    outputString.append(ue.ueKeyDerivationAlgorithm);
    outputString.append("\"");
    outputString.append("\t# The algorithm used during EPS AKA procedure.\n");
    outputString.append("\t\t# Supported algorithms:\n");
    outputString.append("\t\t# * TEST_ALGORITHM - The test algorithm defined in TS 34.108.\n");
    outputString.append("\t\t# * MILENAGE - The milenage algorithm defined in TS 35.205.\n");
    outputString.append("\t\t# Also used in simulated MME.\n");
    outputString.append("\n");
    // UE KEY
    outputString.append("\t\tdefault[:ue_key] = \"");
    outputString.append(ue.ueKey);
    outputString.append("\"");
    outputString.append("\t# Used for MILENAGE");
    outputString.append("\n");
    // UE OP
    outputString.append("\t\tdefault[:ue_op] = \"");
    outputString.append(ue.ueOp);
    outputString.append("\"");
    outputString.append("\t# The OP used in the MILENAGE algorithm. Also used in simulated MME.");
    outputString.append("\n");
    outputString.append("######################################################################################################################");
    outputString.append("\n");
    outputString.append("\t\t# All JMX parameters can be listed with help :ue in the ltesim_cli\n");
    outputString.append("\t\treturn default\n");
    outputString.append("\tend\n");
    return outputString;
}
