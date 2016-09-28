#include "mapparser.h"

MapParser::MapParser()
{

}

QString MapParser::ParseMap(QVector<QPair<Cell, Center>> &cellsInfo,MapRange &mapRange,QVector<Handover> &handovers, UBSimSettings &ubSim, DataGeneratorSettings &dataGenerator)
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
    for (int i=0;i<handovers.size();i++){
        outputString.append("{\n");
        // NAME
        outputString.append("  :area => \"");
        outputString.append(handovers[i].area);
        outputString.append("\",\n");
        // SOUTH
        outputString.append("  :southBoundary => ");
        outputString.append(QString::number(handovers[i].southBoundary));
        outputString.append(",\n");
        // NORTH
        outputString.append("  :northBoundary => ");
        outputString.append(QString::number(handovers[i].northBoundary));
        outputString.append(",\n");
        // WEST
        outputString.append("  :westBoundary => ");
        outputString.append(QString::number(handovers[i].westBoundary));
        outputString.append(",\n");
        // EAST
        outputString.append("  :eastBoundary => ");
        outputString.append(QString::number(handovers[i].eastBoundary));
        if (i==handovers.size()-1){
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

QString MapParser::GenerateTrafficScript(const Project &project, const int &index)
{
    QString outputString;
    outputString=project.trafficFilesList.at(index).content;
    QStringList contentList;
    contentList=outputString.split('\n');

    QString testCasePreparation;

    for(int i=0;i<project.cellsInfo.size();i++)
    {
        testCasePreparation.append("LteSimCli.bean(:name=>\"/ltesim/rec/");
        testCasePreparation.append(project.cellsInfo.at(i).first.name);
        testCasePreparation.append("\").isDiscovered \n");
    }

    testCasePreparation.append("\n");

    for(int i=0;i<project.cellsInfo.size();i++)
    {
        testCasePreparation.append("LteSimCli.bean(:name=>\"/ltesim/rec/");
        testCasePreparation.append(project.cellsInfo.at(i).first.name);
        testCasePreparation.append("\").isReady \n");
    }

    testCasePreparation.append("\n");

    if(project.pagingSettings.isUsedInConfiguration)
    {
        for(int i=0;i<project.pagingSettings.names.size();i++)
        {
            testCasePreparation.append("LteSimCli.bean(:name=>\"/ltesim/paginggenerator/");
            testCasePreparation.append(project.pagingSettings.names.at(i));
            testCasePreparation.append("\").s1ConnectionComplete \n");
        }
    }

    contentList.insert(contentList.indexOf("## Test Case - Preparation    ##")+3,testCasePreparation);

    QString tuningParameters;

    for(int i=0;i<project.trafficFilesList.at(index).tuningTrafficData.csParamGroup.size();i++)
    {
        if(project.trafficFilesList.at(index).tuningTrafficData.csParamGroup.at(i).callIntensity!=1.0)
        {
            tuningParameters.append("UBsimTuning.setModelValue(\"");
            tuningParameters.append(project.trafficFilesList.at(index).tuningTrafficData.csParamGroup.at(i).csName);
            tuningParameters.append("\", \"call_intensity\", ");
            tuningParameters.append(QString::number(project.trafficFilesList.at(index).tuningTrafficData.csParamGroup.at(i).callIntensity));
            tuningParameters.append(")\n");
        }
        if(project.trafficFilesList.at(index).tuningTrafficData.csParamGroup.at(i).callDuration!=1.0)
        {
            tuningParameters.append("UBsimTuning.setModelValue(\"");
            tuningParameters.append(project.trafficFilesList.at(index).tuningTrafficData.csParamGroup.at(i).csName);
            tuningParameters.append("\", \"call_duration\", ");
            tuningParameters.append(QString::number(project.trafficFilesList.at(index).tuningTrafficData.csParamGroup.at(i).callDuration));
            tuningParameters.append(")\n");
        }
        if(project.trafficFilesList.at(index).tuningTrafficData.csParamGroup.at(i).recoveryStartInterval!=1.0)
        {
            tuningParameters.append("UBsimTuning.setModelValue(\"");
            tuningParameters.append(project.trafficFilesList.at(index).tuningTrafficData.csParamGroup.at(i).csName);
            tuningParameters.append("\", \"recovery_start_interval\", ");
            tuningParameters.append(QString::number(project.trafficFilesList.at(index).tuningTrafficData.csParamGroup.at(i).recoveryStartInterval));
            tuningParameters.append(")\n");
        }
    }
    tuningParameters.append("\n");

    for(int i=0;i<project.trafficFilesList.at(index).tuningTrafficData.psParamGroup.size();i++)
    {
        if(project.trafficFilesList.at(index).tuningTrafficData.psParamGroup.at(i).psIntensity!=1.0)
        {
            tuningParameters.append("UBsimTuning.setModelValue(\"");
            tuningParameters.append(project.trafficFilesList.at(index).tuningTrafficData.psParamGroup.at(i).psName);
            tuningParameters.append("\", \"ps_intensity\", ");
            tuningParameters.append(QString::number(project.trafficFilesList.at(index).tuningTrafficData.psParamGroup.at(i).psIntensity));
            tuningParameters.append(")\n");
        }
        if(project.trafficFilesList.at(index).tuningTrafficData.psParamGroup.at(i).psDuration!=1.0)
        {
            tuningParameters.append("UBsimTuning.setModelValue(\"");
            tuningParameters.append(project.trafficFilesList.at(index).tuningTrafficData.psParamGroup.at(i).psName);
            tuningParameters.append("\", \"ps_duration\", ");
            tuningParameters.append(QString::number(project.trafficFilesList.at(index).tuningTrafficData.psParamGroup.at(i).psDuration));
            tuningParameters.append(")\n");
        }
    }
    tuningParameters.append("\n");

    for(int i=0;i<project.trafficFilesList.at(index).tuningTrafficData.mobilityGroup.size();i++)
    {
        if(project.trafficFilesList.at(index).tuningTrafficData.mobilityGroup.at(i).speed!=1.0)
        {
            tuningParameters.append("UBsimTuning.setModelValue(\"");
            tuningParameters.append(project.trafficFilesList.at(index).tuningTrafficData.mobilityGroup.at(i).mobilityName);
            tuningParameters.append("\", \"speed\", ");
            tuningParameters.append(QString::number(project.trafficFilesList.at(index).tuningTrafficData.mobilityGroup.at(i).speed));
            tuningParameters.append(")\n");
        }
        if(project.trafficFilesList.at(index).tuningTrafficData.mobilityGroup.at(i).granularity!=1.0)
        {
            tuningParameters.append("UBsimTuning.setModelValue(\"");
            tuningParameters.append(project.trafficFilesList.at(index).tuningTrafficData.mobilityGroup.at(i).mobilityName);
            tuningParameters.append("\", \"granularity\", ");
            tuningParameters.append(QString::number(project.trafficFilesList.at(index).tuningTrafficData.mobilityGroup.at(i).granularity));
            tuningParameters.append(")\n");
        }
    }
    tuningParameters.append("\n");

    contentList.insert(contentList.indexOf("## Setup - Tuning parameters  ##")+3,tuningParameters);

    QString customModels;

    for(unsigned i=0;i<10;i++)
    {
        for(int j=0; j<project.trafficFilesList.at(index).customModels.at(i).CMPings.size();j++)
        {
            customModels.append("LteSimCli.bean(:name=>\"/ltesim/models/LteCustom");
            customModels.append(QString::number(i+1));
            customModels.append("\").addPing(");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMPings.at(j).pingQci));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMPings.at(j).pingNumberOfPings));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMPings.at(j).pingInterval));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMPings.at(j).pingMinRecievedPings));
            customModels.append(")\n");
        }
        for(int j=0; j<project.trafficFilesList.at(index).customModels.at(i).CMVoips.size();j++)
        {
            customModels.append("LteSimCli.bean(:name=>\"/ltesim/models/LteCustom");
            customModels.append(QString::number(i+1));
            customModels.append("\").addVoip(");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMVoips.at(j).voipQci));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMVoips.at(j).voipActivityFactor));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMVoips.at(j).voipMaxTransferTime));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMVoips.at(j).voipMinPacketsReceivedInTime));
            customModels.append(")\n");
        }
        for(int j=0; j<project.trafficFilesList.at(index).customModels.at(i).CMFtpDls.size();j++)
        {
            customModels.append("LteSimCli.bean(:name=>\"/ltesim/models/LteCustom");
            customModels.append(QString::number(i+1));
            customModels.append("\").addFtpDl(");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMFtpDls.at(j).ftpDlQci));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMFtpDls.at(j).ftpDlFilesize));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMFtpDls.at(j).ftpDlMinThroughput));
            customModels.append(")\n");
        }
        for(int j=0; j<project.trafficFilesList.at(index).customModels.at(i).CMFtpUls.size();j++)
        {
            customModels.append("LteSimCli.bean(:name=>\"/ltesim/models/LteCustom");
            customModels.append(QString::number(i+1));
            customModels.append("\").addFtpUl(");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMFtpUls.at(j).ftpUlQci));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMFtpUls.at(j).ftpUlFilesize));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMFtpUls.at(j).ftpUlMinThroughput));
            customModels.append(")\n");
        }
        for(int j=0; j<project.trafficFilesList.at(index).customModels.at(i).CMStreamDls.size();j++)
        {
            customModels.append("LteSimCli.bean(:name=>\"/ltesim/models/LteCustom");
            customModels.append(QString::number(i+1));
            customModels.append("\").addStreamDl(");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMStreamDls.at(j).streamDlQci));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMStreamDls.at(j).streamDlSpeed));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMStreamDls.at(j).streamDlDuration));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMStreamDls.at(j).streamDlMinThroughput));
            customModels.append(")\n");
        }
        for(int j=0; j<project.trafficFilesList.at(index).customModels.at(i).CMStreamUls.size();j++)
        {
            customModels.append("LteSimCli.bean(:name=>\"/ltesim/models/LteCustom");
            customModels.append(QString::number(i+1));
            customModels.append("\").addStreamUl(");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMStreamUls.at(j).streamUlQci));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMStreamUls.at(j).streamUlSpeed));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMStreamUls.at(j).streamUlDuration));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMStreamUls.at(j).streamUlMinThroughput));
            customModels.append(")\n");
        }
        for(int j=0; j<project.trafficFilesList.at(index).customModels.at(i).CMSyncedPings.size();j++)
        {
            QString qciArray=QString::number(project.trafficFilesList.at(index).customModels.at(i).CMSyncedPings.at(j).SyncedPingQciArray.at(0));
            for(int k=1;k<project.trafficFilesList.at(index).customModels.at(i).CMSyncedPings.at(j).SyncedPingQciArray.size();k++)
                qciArray+=","+QString::number(project.trafficFilesList.at(index).customModels.at(i).CMSyncedPings.at(j).SyncedPingQciArray.at(k));
            customModels.append("LteSimCli.bean(:name=>\"/ltesim/models/LteCustom");
            customModels.append(QString::number(i+1));
            customModels.append("\").addSyncedPing([");
            customModels.append(qciArray);
            customModels.append("],");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMSyncedPings.at(j).SyncedPingTimeBetweenTasks));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMSyncedPings.at(j).SyncedPingNumberOfPings));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMSyncedPings.at(j).SyncedPingInterval));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMSyncedPings.at(j).SyncedPingMinReceivedPings));
            customModels.append(")\n");
        }
        for(int j=0; j<project.trafficFilesList.at(index).customModels.at(i).CMServiceReqs.size();j++)
        {
            QString qciArray=QString::number(project.trafficFilesList.at(index).customModels.at(i).CMServiceReqs.at(j).ServiceReqQciArray.at(0));
            for(int k=1;k<project.trafficFilesList.at(index).customModels.at(i).CMServiceReqs.at(j).ServiceReqQciArray.size();k++)
                qciArray+=","+QString::number(project.trafficFilesList.at(index).customModels.at(i).CMServiceReqs.at(j).ServiceReqQciArray.at(k));
            customModels.append("LteSimCli.bean(:name=>\"/ltesim/models/LteCustom");
            customModels.append(QString::number(i+1));
            customModels.append("\").addServiceReq([");
            customModels.append(qciArray);
            customModels.append("],");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMServiceReqs.at(j).ServiceReqTimeToWaitForAttach));
            customModels.append(",");
            customModels.append(QString::number(project.trafficFilesList.at(index).customModels.at(i).CMServiceReqs.at(j).ServiceReqIntervalBetweenUlData));
            customModels.append(")\n");
        }
    }

    contentList.insert(contentList.indexOf("## Setup - Custom Models      ##")+3,customModels);

    QString createUEPairs;

    for(int i=0;i<project.trafficFilesList.at(index).userEquipments.size();i++)
    {
        createUEPairs.append(QString::number(project.trafficFilesList.at(index).userEquipments.at(i).amountOfPairs));
        createUEPairs.append(".times {LteSimCli.bean(:name=>\"/ltesim/deployment\").create_user_pair(\"");
        createUEPairs.append(project.trafficFilesList.at(index).userEquipments.at(i).pairName);
        createUEPairs.append("\",\"");
        createUEPairs.append(project.trafficFilesList.at(index).userEquipments.at(i).mobilityModelsPair.first);
        createUEPairs.append("\", \"");
        createUEPairs.append(project.trafficFilesList.at(index).userEquipments.at(i).csModelsPair.first);
        createUEPairs.append("\", \"");
        createUEPairs.append(project.trafficFilesList.at(index).userEquipments.at(i).psModelsPair.first);
        createUEPairs.append("\", \"");
        createUEPairs.append(project.trafficFilesList.at(index).userEquipments.at(i).ueTypesPair.first);
        createUEPairs.append("\", \"");
        createUEPairs.append(project.trafficFilesList.at(index).userEquipments.at(i).ueArea.first);
        createUEPairs.append("\", \"");
        createUEPairs.append(project.trafficFilesList.at(index).userEquipments.at(i).mobilityModelsPair.second);
        createUEPairs.append("\", \"");
        createUEPairs.append(project.trafficFilesList.at(index).userEquipments.at(i).csModelsPair.second);
        createUEPairs.append("\", \"");
        createUEPairs.append(project.trafficFilesList.at(index).userEquipments.at(i).psModelsPair.second);
        createUEPairs.append("\", \"");
        createUEPairs.append(project.trafficFilesList.at(index).userEquipments.at(i).ueTypesPair.second);
        createUEPairs.append("\", \"");
        createUEPairs.append(project.trafficFilesList.at(index).userEquipments.at(i).ueArea.second);
        createUEPairs.append("\")}");
        createUEPairs.append("\n");
    }

    contentList.insert(contentList.indexOf("## Setup - Create UE pairs    ##")+3,createUEPairs);

    QString configurePagings;

        for(int i=0;i<project.pagingSettings.names.size();i++)
        {
            configurePagings.append("LteSimCli.bean(:name=>\"/ltesim/paginggenerator/");
            configurePagings.append(project.pagingSettings.names.at(i));
            configurePagings.append("\").startPaging(");
            configurePagings.append(QString::number(project.pagingSettings.rates.at(i)));
            configurePagings.append(");\n");
        }

    if(project.pagingSettings.isUsedInConfiguration)
    contentList.insert(contentList.indexOf("## Setup - Configure paging   ##")+3,configurePagings);

    QString startTraffic;

    if(project.trafficFilesList.at(index).timeData.tab1_attachRate!=0)
    {
        startTraffic.append("LteSimCli.bean(:name=>\"/ltesim/deployment\").start_all_users_with_rate(");
        startTraffic.append(QString::number(project.trafficFilesList.at(index).timeData.tab1_attachRate));
        startTraffic.append(");\n");
    }
    else if(project.trafficFilesList.at(index).timeData.tab2_attachRate!=0)
    {
        startTraffic.append("LteSimCli.bean(:name=>\"/ltesim/deployment\").start_all_users_with_rate(");
        startTraffic.append(QString::number(project.trafficFilesList.at(index).timeData.tab2_attachRate));
        startTraffic.append(");\n");
    }
    else
    {
        startTraffic.append("LteSimCli.bean(:name=>\"/ltesim/deployment\").start_all_users();\n");
    }

    contentList.insert(contentList.indexOf("## Test Case - Start traffic  ##")+3,startTraffic);

    QString statisticsString;

    QString statistics;
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Ue Static Info"))
        statistics.append("Statistics.listUeStaticInfo() \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Model Exp Nas"))
        statistics.append("Statistics.listModelExpNas() \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Model Exp Rrc"))
        statistics.append("Statistics.listModelExpRrc() \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Model Exp Mobility"))
        statistics.append("Statistics.listModelExpMobility() \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Model Exp Throughput"))
        statistics.append("Statistics.listModelExpThroughput() \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Per Ue Throughput"))
        statistics.append("Statistics.listPerUeThroughput() \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Ue Exp Mobility"))
        statistics.append("Statistics.listUeExpMobility() \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Model Exp Ps"))
        statistics.append("Statistics.listModelExpPs() \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Ue Exp Ps"))
        statistics.append("Statistics.listUeExpPs() \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Model Exp Cs"))
        statistics.append("Statistics.listModelExpCs() \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Ue Exp Cs"))
        statistics.append("Statistics.listUeExpCs() \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Write Statistics to file"))
    {
        statistics.append("Statistics.writeStatisticsToFile(");
        statistics.append(project.trafficFilesList.at(index).statisticsData.generalUe);
        statistics.append(",");
        statistics.append(project.trafficFilesList.at(index).statisticsData.generalDelayBetweenPackets);
        statistics.append(",");
        statistics.append(project.trafficFilesList.at(index).statisticsData.generalTotalNumberOfSeconds);
        statistics.append(",");
        statistics.append(project.trafficFilesList.at(index).statisticsData.generalMtuSize);
        statistics.append(",");
        statistics.append(project.trafficFilesList.at(index).statisticsData.generalMeasurementDelta);
        statistics.append(")\n");
    }
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Ipex Protocol Stats"))
        statistics.append("Statistics.printIpexProtocolStats() \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Ipex Tgu Stats"))
        statistics.append("Statistics.printIpexTguStats("+project.trafficFilesList.at(index).statisticsData.ipexTguImsi+") \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Write IPEX to file"))
        statistics.append("Statistics.writeIpexStatisticsToFile("+project.trafficFilesList.at(index).statisticsData.ipexFileName+","+project.trafficFilesList.at(index).statisticsData.ipexSeconds+","+project.trafficFilesList.at(index).statisticsData.ipexMeasurement+") \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Protocol Stats"))
        statistics.append("Statistics.print \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Protocol Rohc Stats"))
        statistics.append("Statistics.printPdcpUProtocolRohcStats() \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Bearer Status Words Stats"))
        statistics.append("Statistics.printPdcpUBearerStatusWordsStats("+project.trafficFilesList.at(index).statisticsData.pdcpuBearerStatusImsi+","+project.trafficFilesList.at(index).statisticsData.pdcpuBearerStatusEpsBearerId+") \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Bearer Rohc Stats"))
        statistics.append("Statistics.printPdcpUBearerRohcStats("+project.trafficFilesList.at(index).statisticsData.pdcpuBearerRohcImsi+","+project.trafficFilesList.at(index).statisticsData.pdcpuBearerRohcEpsBearerId+") \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Bearer Error Stats"))
        statistics.append("Statistics.printPdcpUBearerErrorStats("+project.trafficFilesList.at(index).statisticsData.pdcpuBearerErrorImsi+","+project.trafficFilesList.at(index).statisticsData.pdcpuBearerErrorEpsBearerId+") \n");
    if(project.trafficFilesList.at(index).statisticsData.getStatMapFor("Write PdcpU to file"))
        statistics.append("Statistics.writePdcpUStatisticsToFile("+project.trafficFilesList.at(index).statisticsData.pdcpuFileName+","+project.trafficFilesList.at(index).statisticsData.pdcpuSeconds+","+project.trafficFilesList.at(index).statisticsData.pdcpuMeasurement+") \n");

    if(project.trafficFilesList.at(index).timeData.tab1_statisticsWithRate)
        for(int i=0;i<(QTime(0,0,0).secsTo(project.trafficFilesList.at(index).timeData.spn_time1)-project.trafficFilesList.at(index).timeData.tab1_statsRate);i=i+project.trafficFilesList.at(index).timeData.tab1_statsRate)
        {
            statisticsString.append("\nsleep("+QString::number(project.trafficFilesList.at(index).timeData.tab1_statsRate)+")\n");
            statisticsString.append(statistics);
        }
    else if(project.trafficFilesList.at(index).timeData.tab2_statisticsWithRate)
    {
        for(int i=0;i<(QTime(0,0,0).secsTo(project.trafficFilesList.at(index).timeData.spn_time1)-project.trafficFilesList.at(index).timeData.tab1_statsRate);i=i+project.trafficFilesList.at(index).timeData.tab2_statsRate)
        {
            statisticsString.append("\nsleep("+QString::number(project.trafficFilesList.at(index).timeData.tab2_statsRate)+")\n");
            statisticsString.append(statistics);
        }
    }

    contentList.insert(contentList.indexOf("## Test Case - Statistics     ##")+3,statisticsString);

    QString stopTraffic;

    if(project.trafficFilesList.at(index).timeData.tab1_detachRate!=0)
    {
        stopTraffic.append("LteSimCli.bean(:name=>\"/ltesim/deployment\").stop_all_users_with_rate(");
        stopTraffic.append(QString::number(project.trafficFilesList.at(index).timeData.tab1_detachRate));
        stopTraffic.append(");\n");
    }
    else if(project.trafficFilesList.at(index).timeData.tab2_detachRate!=0)
    {
        stopTraffic.append("LteSimCli.bean(:name=>\"/ltesim/deployment\").stop_all_users_with_rate(");
        stopTraffic.append(QString::number(project.trafficFilesList.at(index).timeData.tab2_detachRate));
        stopTraffic.append(");\n");
    }
    else
    {
        stopTraffic.append("LteSimCli.bean(:name=>\"/ltesim/deployment\").stop_all_users();\n");
    }

    contentList.insert(contentList.indexOf("## Test Case - Stop Traffic   ##")+3,stopTraffic);

    QString endStatistics;

    if(project.trafficFilesList.at(index).timeData.tab2_statisticsWithRate)
        endStatistics.append(statistics);
    if(project.trafficFilesList.at(index).timeData.tab1_statisticsWithRate)
        endStatistics.append(statistics);

    contentList.insert(contentList.indexOf("## Test Case - End Statistics ##")+3,endStatistics);

    contentList.insert(contentList.indexOf("## Test Case - Clean-up       ##")+3,"LteSimCli.bean(:name=>\"/ltesim/deployment\").delete_all_users();\ndie");

    outputString=contentList.join('\n');

    return outputString;
}
