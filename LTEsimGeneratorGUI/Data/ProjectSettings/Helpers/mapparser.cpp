#include "mapparser.h"

QString MapParser::ParseMap(QVector<QPair<Cell, Center>> &cellsInfo,MapRange &mapRange,QVector<Handover> &handover, UBSimSettings &ubSim, DataGeneratorSettings &dataGenerator)
{
    QString outputString;

    /********************* CELLS ************************/

    QString cellsHeader="\t#\n\
\t# Retrieve default parameters for Radio Environment.\n\
\t#\n\
\tdef Parameters.getRecParameters()\n\
\t\t# Define and return default values\n\
\t\tdefault = {}\n\
\n\
\t\t# Write with the following syntax:\n\
\t\t# default[:rec] = [{<first set of cell params>},{<second set of cell params>}]\n\
\t\t#\n\
\t\t# A set of cell params includes:\n\
\t\t#   :cell                    # Cell instance name\n\
\t\t#   :site                    # Site instance name\n\
\t\t#   :pci                     # Physical cell identifier\n\
\t\t#   :position_X              # Cell position, coordinate X\n\
\t\t#   :position_Y              # Cell position, coordinate Y\n\
\t\t#   :earfcnDl                # Channel number for the central DL frequency\n\
\t\t#   :transmitPower           # Transmit power in dBm\n\
\t\t#   :ulNoiseAndInterference  # uplink N+I in dBm\n\
\t\tdefault[:rec] = [\n";
    outputString.append(cellsHeader);
    for (int i=0;i<cellsInfo.size();i++) {
        // NAME
        outputString.append("{\n");
        outputString.append("\t\t:cell => \"");
        outputString.append(cellsInfo[i].first.name);
        outputString.append("\",\n");
        // SITE
        outputString.append("\t\t:site => \"");
        outputString.append(cellsInfo[i].first.site);
        outputString.append("\",\n");
        //PCI
        outputString.append("\t\t:pci => ");
        outputString.append(QString::number(cellsInfo[i].first.pci));
        outputString.append(",\n");
        // POS X
        outputString.append("\t\t:position_X => ");
        outputString.append(QString::number(cellsInfo[i].first.position_X));
        outputString.append(",\n");
        // POS Y
        outputString.append("\t\t:position_Y => ");
        outputString.append(QString::number(cellsInfo[i].first.position_Y));
        outputString.append(",\n");
        // EARFCNDI
        outputString.append("\t\t:earfcnDl => ");
        outputString.append(QString::number(cellsInfo[i].first.earfcnDl));
        outputString.append(",\n");
        // TRANSMIT POWER
        outputString.append("\t\t:transmitPower => ");
        outputString.append(QString::number(cellsInfo[i].first.transmitPower));
        outputString.append(",\n");
        // NOISE AND INTERFERENCE
        outputString.append("\t\t:ulNoiseAndInterference => ");
        outputString.append(QString::number(cellsInfo[i].first.ulNoiseAndInterference));
        outputString.append("\n");
        outputString.append("\t\t},");
    }
    outputString.append("]\n");
    outputString.append("\t\treturn default\n");
    outputString.append("\tend\n\n");

    /* ***************SAMPLE OUTPUT  **********/

    //{
    // :cell => "cell62",
    // :site => "site62",
    // :pci => 62,
    // :position_X => 17500,
    // :position_Y => 37000,
    // :earfcnDl => 2050,
    // :transmitPower => -75.0,
    // :ulNoiseAndInterference => -116.0

    /******************************************/



    /*********** TRAFFIC BEHAVIOUR PARAMETERS ************/

    // MAP RANGE

    outputString.append("\t#\n\
\t# Retrieve default parameters for user behavior models\n\
\t#\n\
\tdef Parameters.getTraffBehaviourParameters()\n\
\t\t# Define and return default values\n\
\t\tdefault = {}\n\
\n\
\t\t# IMSI range used by traffic models.\n\
\t\t# IMSI ranges are specified with the\n\
\t\t# following syntax (space separated string):\n\
\t\t# \"<first_range> <second_range>\".\n");
// IMSI RANGE
outputString.append("\t\tdefault[:imsiMapRange] = \"");
outputString.append(ubSim.imsiMapRange);
outputString.append("\"\n\n");
outputString.append("\t\t# Size of geographical map\n");
// SOUTH
outputString.append("\t\tdefault[:southBoundMap] = ");
outputString.append(QString::number(mapRange.southBoundMap));
outputString.append("\n");
// NORTH
outputString.append("\t\tdefault[:northBoundMap] = ");
outputString.append(QString::number(mapRange.northBoundMap));
outputString.append("\n");
// WEST
outputString.append("\t\tdefault[:westBoundMap] = ");
outputString.append(QString::number(mapRange.westBoundMap));
outputString.append("\n");
// EAST
outputString.append("\t\tdefault[:eastBoundMap] = ");
outputString.append(QString::number(mapRange.eastBoundMap));
outputString.append("\n");
    /**************** SAMPLE OUTPUT ***************/

    // default[:imsiMapRange] = "262800100326000+1499 262800100329000+1499"

    // default[:southBoundMap] = 0
    // default[:northBoundMap] = 42000
    // default[:westBoundMap] = 0
    // default[:eastBoundMap] = 35000

    /******************************************/

QString areasHeader = ("\n\
\t\t# Areas defined which are possible to use with traffic models (aka Cell Map)\n\
\t\t#\n\
\t\t# :area - naming convention for three types of areas:\n\
\t\t#   Center     an area with a RBS cell in the center\n\
\t\t#   Handover   an area with two RBS:es\n\
\t\t#   Common     an area containing all cells\n\
\t\t# Center:\n\
\t\t#   :area => \"Center11\"             # Area name around cell1-1 (RBS-1)\n\
\t\t#                    ^--- cell number\n\
\t\t#                   ^--- RBS number\n\
\t\t# Handover:\n\
\t\t#   :area => \"Handover11_21\"        # Area name for possible inter handover between RBS-1 and RBS-2\n\
\t\t#                         ^--- cell number\n\
\t\t#                        ^--- RBS number\n\
\t\t#                      ^--- cell number\n\
\t\t#                     ^--- RBS number\n\
\t\t# Common:\n\
\t\t#   :area => \"Common\",              # Area common for all cells\n\
\t\t#\n\
\t\t# Boundaries, specified for all types of areas:\n\
\t\t#   :southBoundary => 6900,         # South boundary of area\n\
\t\t#   :northBoundary => 7100,         # North boundary of area\n\
\t\t#   :westBoundary => 6900,          # West boundary of area\n\
\t\t#   :eastBoundary => 7100,          # East boundary of area\n\
\t\tdefault[:areas] = [\n");


outputString.append(areasHeader);

// CENTERS

for (int i=0; i<cellsInfo.size();i++) {
    outputString.append("{\n");
    // NAME
    outputString.append("\t\t:area => \"");
    outputString.append(cellsInfo[i].second.area);
    outputString.append("\",\n");
    // SOUTH
    outputString.append("\t\t:southBoundary => ");
    outputString.append(QString::number(cellsInfo[i].second.southBoundary));
    outputString.append(",\n");
    // NORTH
    outputString.append("\t\t:northBoundary => ");
    outputString.append(QString::number(cellsInfo[i].second.northBoundary));
    outputString.append(",\n");
    // WEST
    outputString.append("\t\t:westBoundary => ");
    outputString.append(QString::number(cellsInfo[i].second.westBoundary));
    outputString.append(",\n");
    // EAST
    outputString.append("\t\t:eastBoundary => ");
    outputString.append(QString::number(cellsInfo[i].second.eastBoundary));
    outputString.append("\n\t\t},");
}
for (int i=0;i<handover.size();i++){
    outputString.append("{\n");
    // NAME
    outputString.append("\t\t:area => \"");
    outputString.append(handover[i].area);
    outputString.append("\",\n");
    // SOUTH
    outputString.append("\t\t:southBoundary => ");
    outputString.append(QString::number(handover[i].southBoundary));
    outputString.append(",\n");
    // NORTH
    outputString.append("\t\t:northBoundary => ");
    outputString.append(QString::number(handover[i].northBoundary));
    outputString.append(",\n");
    // WEST
    outputString.append("\t\t:westBoundary => ");
    outputString.append(QString::number(handover[i].westBoundary));
    outputString.append(",\n");
    // EAST
    outputString.append("\t\t:eastBoundary => ");
    outputString.append(QString::number(handover[i].eastBoundary));
    if (i==handover.size()-1){
        outputString.append("\n\t\t}");
    }
    else {
        outputString.append("\n\t\t},");
    }
}
outputString.append("\n\t]\n\n");

    /**************** SAMPLE OUTPUT ***************/

    // :area => "Handover52_62",
    // :southBoundary => 31750,
    // :northBoundary => 36250,
    // :westBoundary => 15000,
    // :eastBoundary => 16000

    /******************************************/



// IPEX AND IPGWTG from DATAGENERATOR
outputString.append("\t\tdefault[:dataGenerator] = \"");
outputString.append(dataGenerator.dataGenerator);
outputString.append("\"\n");
outputString.append("\t\t# Use local IPGWTG\n");
outputString.append("\n");

// IPGWTG
outputString.append("\t\t# Configuration of the ipgwtg user data generator,\n");
outputString.append("\t\tdefault[:userDataGen] = ");
for (QString ipex:dataGenerator.userDataGenerator)
{
    if (ipex!=dataGenerator.userDataGenerator.first()) {
        outputString.append("\t\t\t\t\t");
    }
    outputString.append(ipex);
    outputString.append("\n");
}
outputString.append("\n");
outputString.append("\n");

outputString.append("\t\tdefault[:start_isp_simulator] = ");
if (dataGenerator.startIspSimulator){
    outputString.append("true\n");
}
else{
    outputString.append("false\n");
}
outputString.append("\t\tdefault[:ipgwtg_ipAddress] = \"");
outputString.append(dataGenerator.ipgwtg_IP_Address);
outputString.append("\"");
outputString.append("\t# IP address of the interface that can reach the PGW\n");

outputString.append("\t\tdefault[:ipgwtg_inband_signaling] = ");
if (dataGenerator.ipgwtgInbandSignaling){
    outputString.append("true\n");
}
else {
    outputString.append("false\n");
}
outputString.append("\t\tdefault[:ipgwtg_port] = ");
outputString.append(QString::number(dataGenerator.ipgwtgPort));
outputString.append("\n");

outputString.append("\t\tdefault[:ipgwtg_ftp_sender_connect_put] = ");
if (dataGenerator.ipgwtgFtpSenderConnectPut){
    outputString.append("true\n");
}
else {
    outputString.append("false\n");
}
outputString.append("\n");
outputString.append("\t\treturn default\n");
outputString.append("\tend\n");


/********************* SAMPLE OUTPUT ***********************/

// default[:dataGenerator] = "ipgwtg"
//
// default[:userDataGen] = "ipex.isp.sip.offset = 31000\n" +
//            "ipex.isp.qci1.port    = 31010\n" +
//            "ipex.isp.qci2.port    = 31020\n" +
//            "ipex.isp.qci5.port    = 31050\n"
//
//
// default[:start_isp_simulator] = true
// default[:ipgwtg_ipAddress] = "10.10.0.1"
// default[:ipgwtg_inband_signaling] = false
// default[:ipgwtg_port] = 32000
// default[:ipgwtg_ftp_sender_connect_put] = true

/************************************************************/

return outputString;


}
