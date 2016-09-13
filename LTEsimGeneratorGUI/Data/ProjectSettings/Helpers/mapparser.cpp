#include "mapparser.h"

MapParser::MapParser()
{

}

QString MapParser::ParseMap(QVector<QPair<Cell, Center>> &cellsInfo,MapRange &mapRange,QVector<Handover> &handover, UBSimSettings &ubSim, DataGeneratorSettings &dataGenerator)
{
    QString outputString;

    /********************* CELLS ************************/

    QString cellsHeader=" #\n\
 # Retrieve default parameters for Radio Environment.\n\
 #\n\
 def Parameters.getRecParameters()\n\
  # Define and return default values\n\
  default = {}\n\
\n\
  # Write with the following syntax:\n\
  # default[:rec] = [{<first set of cell params>},{<second set of cell params>}]\n\
  #\n\
  # A set of cell params includes:\n\
  #   :cell                    # Cell instance name\n\
  #   :site                    # Site instance name\n\
  #   :pci                     # Physical cell identifier\n\
  #   :position_X              # Cell position, coordinate X\n\
  #   :position_Y              # Cell position, coordinate Y\n\
  #   :earfcnDl                # Channel number for the central DL frequency\n\
  #   :transmitPower           # Transmit power in dBm\n\
  #   :ulNoiseAndInterference  # uplink N+I in dBm\n\
  default[:rec] = [\n";
    outputString.append(cellsHeader);
    for (int i=0;i<cellsInfo.size();i++) {
        // NAME
        outputString.append("{\n");
        outputString.append("  :cell => \"");
        outputString.append(cellsInfo[i].first.name);
        outputString.append("\",\n");
        // SITE
        outputString.append("  :site => \"");
        outputString.append(cellsInfo[i].first.site);
        outputString.append("\",\n");
        //PCI
        outputString.append("  :pci => ");
        outputString.append(QString::number(cellsInfo[i].first.pci));
        outputString.append(",\n");
        // POS X
        outputString.append("  :position_X => ");
        outputString.append(QString::number(cellsInfo[i].first.position_X));
        outputString.append(",\n");
        // POS Y
        outputString.append("  :position_Y => ");
        outputString.append(QString::number(cellsInfo[i].first.position_Y));
        outputString.append(",\n");
        // EARFCNDI
        outputString.append("  :earfcnDl => ");
        outputString.append(QString::number(cellsInfo[i].first.earfcnDl));
        outputString.append(",\n");
        // TRANSMIT POWER
        outputString.append("  :transmitPower => ");
        outputString.append(QString::number(cellsInfo[i].first.transmitPower));
        outputString.append(",\n");
        // NOISE AND INTERFERENCE
        outputString.append("  :ulNoiseAndInterference => ");
        outputString.append(QString::number(cellsInfo[i].first.ulNoiseAndInterference));
        outputString.append("\n");
        outputString.append("  },");
    }
    outputString.append("]\n");
    outputString.append("  return default\n");
    outputString.append(" end\n\n");

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

    outputString.append(" #\n\
 # Retrieve default parameters for user behavior models\n\
 #\n\
 def Parameters.getTraffBehaviourParameters()\n\
  # Define and return default values\n\
  default = {}\n\
\n\
  # IMSI range used by traffic models.\n\
  # IMSI ranges are specified with the\n\
  # following syntax (space separated string):\n\
  # \"<first_range> <second_range>\".\n");
// IMSI RANGE
outputString.append("  default[:imsiMapRange] = \"");
outputString.append(ubSim.imsiMapRange);
outputString.append("\"\n\n");
outputString.append("  # Size of geographical map\n");
// SOUTH
outputString.append("  default[:southBoundMap] = ");
outputString.append(QString::number(mapRange.southBoundMap));
outputString.append("\n");
// NORTH
outputString.append("  default[:northBoundMap] = ");
outputString.append(QString::number(mapRange.northBoundMap));
outputString.append("\n");
// WEST
outputString.append("  default[:westBoundMap] = ");
outputString.append(QString::number(mapRange.westBoundMap));
outputString.append("\n");
// EAST
outputString.append("  default[:eastBoundMap] = ");
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
  # Areas defined which are possible to use with traffic models (aka Cell Map)\n\
  #\n\
  # :area - naming convention for three types of areas:\n\
  #   Center     an area with a RBS cell in the center\n\
  #   Handover   an area with two RBS:es\n\
  #   Common     an area containing all cells\n\
  # Center:\n\
  #   :area => \"Center11\"             # Area name around cell1-1 (RBS-1)\n\
  #                    ^--- cell number\n\
  #                   ^--- RBS number\n\
  # Handover:\n\
  #   :area => \"Handover11_21\"        # Area name for possible inter handover between RBS-1 and RBS-2\n\
  #                         ^--- cell number\n\
  #                        ^--- RBS number\n\
  #                      ^--- cell number\n\
  #                     ^--- RBS number\n\
  # Common:\n\
  #   :area => \"Common\",              # Area common for all cells\n\
  #\n\
  # Boundaries, specified for all types of areas:\n\
  #   :southBoundary => 6900,         # South boundary of area\n\
  #   :northBoundary => 7100,         # North boundary of area\n\
  #   :westBoundary => 6900,          # West boundary of area\n\
  #   :eastBoundary => 7100,          # East boundary of area\n\
  default[:areas] = [\n");


outputString.append(areasHeader);

// CENTERS

for (int i=0; i<cellsInfo.size();i++) {
    outputString.append("{\n");
    // NAME
    outputString.append("  :area => \"");
    outputString.append(cellsInfo[i].second.area);
    outputString.append("\",\n");
    // SOUTH
    outputString.append("  :southBoundary => ");
    outputString.append(QString::number(cellsInfo[i].second.southBoundary));
    outputString.append(",\n");
    // NORTH
    outputString.append("  :northBoundary => ");
    outputString.append(QString::number(cellsInfo[i].second.northBoundary));
    outputString.append(",\n");
    // WEST
    outputString.append("  :westBoundary => ");
    outputString.append(QString::number(cellsInfo[i].second.westBoundary));
    outputString.append(",\n");
    // EAST
    outputString.append("  :eastBoundary => ");
    outputString.append(QString::number(cellsInfo[i].second.eastBoundary));
    outputString.append("\n  },");
}
for (int i=0;i<handover.size();i++){
    outputString.append("{\n");
    // NAME
    outputString.append("  :area => \"");
    outputString.append(handover[i].area);
    outputString.append("\",\n");
    // SOUTH
    outputString.append("  :southBoundary => ");
    outputString.append(QString::number(handover[i].southBoundary));
    outputString.append(",\n");
    // NORTH
    outputString.append("  :northBoundary => ");
    outputString.append(QString::number(handover[i].northBoundary));
    outputString.append(",\n");
    // WEST
    outputString.append("  :westBoundary => ");
    outputString.append(QString::number(handover[i].westBoundary));
    outputString.append(",\n");
    // EAST
    outputString.append("  :eastBoundary => ");
    outputString.append(QString::number(handover[i].eastBoundary));
    if (i==handover.size()-1){
        outputString.append("\n  }");
    }
    else {
        outputString.append("\n  },");
    }
}
outputString.append("\n ]\n\n");

    /**************** SAMPLE OUTPUT ***************/

    // :area => "Handover52_62",
    // :southBoundary => 31750,
    // :northBoundary => 36250,
    // :westBoundary => 15000,
    // :eastBoundary => 16000

    /******************************************/



// IPEX AND IPGWTG from DATAGENERATOR
outputString.append("  default[:dataGenerator] = \"");
outputString.append(dataGenerator.dataGenerator);
outputString.append("\"\n");
outputString.append("  # Use local IPGWTG\n");
outputString.append("\n");

// IPGWTG
outputString.append("  # Configuration of the ipgwtg user data generator,\n");
outputString.append("  default[:userDataGen] = ");
for (QString ipex:dataGenerator.userDataGenerator)
{
    outputString.append(ipex);
    outputString.append("\n");
}
outputString.append("\n");
outputString.append("\n");

outputString.append("  default[:start_isp_simulator] = ");
if (dataGenerator.startIspSimulator){
    outputString.append("true\n");
}
else{
    outputString.append("false\n");
}
outputString.append("  default[:ipgwtg_ipAddress] = \"");
outputString.append(dataGenerator.ipgwtg_IP_Address);
outputString.append("\"");
outputString.append("\t# IP address of the interface that can reach the PGW\n");

outputString.append("  default[:ipgwtg_inband_signaling] = ");
if (dataGenerator.ipgwtgInbandSignaling){
    outputString.append("true\n");
}
else {
    outputString.append("false\n");
}
outputString.append("  default[:ipgwtg_port] = ");
outputString.append(QString::number(dataGenerator.ipgwtgPort));
outputString.append("\n");

outputString.append("  default[:ipgwtg_ftp_sender_connect_put] = ");
if (dataGenerator.ipgwtgFtpSenderConnectPut){
    outputString.append("true\n");
}
else {
    outputString.append("false\n");
}
outputString.append("\n");
outputString.append("  return default\n");
outputString.append(" end\n");


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

QString MapParser::GenerateTrafficScript(const TrafficFileData &trafficFileData)
{
    QString outputString;

    QString testCasePreparationHeader="################################\n\
## Test Case - Preparation    ##\n\
################################\n";
            outputString.append(testCasePreparationHeader);

    outputString.append("\n");

    QString setupTuningParametersHeader="################################\n\
## Setup - Tuning parameters  ##\n\
################################\n";

            outputString.append(setupTuningParametersHeader);

    outputString.append("\n");

    QString setupCustomModelsHeader="################################\n\
## Setup - Custom Models      ##\n\
################################\n";

            outputString.append(setupCustomModelsHeader);

    outputString.append("\n");

    QString setupCreateUePairsHeader="################################\n\
## Setup - Create UE pairs    ##\n\
################################\n";

            outputString.append(setupCreateUePairsHeader);

    outputString.append("\n");

    QString setupConfigurePagingHeader="################################\n\
## Setup - Configure paging   ##\n\
################################\n";

            outputString.append(setupConfigurePagingHeader);

    outputString.append("\n");

    QString testCaseStartTrafficHeader="################################\n\
## Test Case - Start traffic  ##\n\
################################\n";

            outputString.append(testCaseStartTrafficHeader);

    outputString.append("\n");

    QString testCaseStatisticsHeader="################################\n\
## Test Case - Statistics     ##\n\
################################\n";

            outputString.append(testCaseStartTrafficHeader);

    outputString.append("\n");

    QString testCaseStopTrafficHeader="################################\n\
## Test Case - Stop Traffic   ##\n\
################################\n";

            outputString.append(testCaseStopTrafficHeader);

    outputString.append("\n");

    QString testCaseEndStatisticsHeader="################################\n\
## Test Case - End Statistics ##\n\
################################\n";

            outputString.append(testCaseEndStatisticsHeader);

    outputString.append("\n");

    QString testCaseCleanUpHeader="################################\n\
## Test Case - Clean-up       ##\n\
################################\n";

            outputString.append(testCaseCleanUpHeader);

    return outputString;
}
