#include "scriptparsermanagertest.h"

ScriptParserManagerTest::ScriptParserManagerTest()
{

}

void ScriptParserManagerTest::initTestCase() {
}

void ScriptParserManagerTest::cleanupTestCase() {
}

void ScriptParserManagerTest::scriptParserManagerTest1_getDataGeneratorSettingsFromScript() {

    qInfo() << "TEST FOR PARSER getDataGeneratorSettingsFromScript METHOD(SUCCESS)";

    ScriptParserManager scriptParserManager;
    DataGeneratorSettings dataGeneratorSettings;

    const QString scriptContent = " default[:dataGenerator] = \"ipgwtg\"\n"
                                  "# Use local IPGWTG\n# Configuration of the ipgwtg user data generator,\n"
                                  "default[:userDataGen] =  \"ipex.isp.sip.offset = 31000\n\" +\n"
                                  "ipex.isp.qci1.port    = 31010\n\" +\n"
                                  "ipex.isp.qci2.port    = 31020\n\" +\n"
                                  "ipex.isp.qci5.port    = 31050\n\"\n"
                                  "default[:start_isp_simulator] = true\n"
                                  "default[:ipgwtg_ipAddress] = \"10.10.0.1\"         # IP address of the interface that can reach the PGW\n"
                                  "default[:ipgwtg_inband_signaling] = false\n"
                                  "default[:ipgwtg_port] = 32000\n"
                                  "default[:ipgwtg_ftp_sender_connect_put] = true\n";

    dataGeneratorSettings = scriptParserManager.getDataGeneratorSettingsFromScript(scriptContent);

    if(dataGeneratorSettings.dataGenerator != "ipgwtg") QVERIFY(false);
    else if(dataGeneratorSettings.startIspSimulator != true) QVERIFY(false);
    else if(dataGeneratorSettings.ipgwtg_IP_Address != "10.10.0.1") QVERIFY(false);
    else if(dataGeneratorSettings.ipgwtgInbandSignaling != false) QVERIFY(false);
    else if(dataGeneratorSettings.ipgwtgPort != 32000) QVERIFY(false);
    else if(dataGeneratorSettings.ipgwtgFtpSenderConnectPut != true) QVERIFY(false);

    QVERIFY(true);
}
void ScriptParserManagerTest::scriptParserManagerTest2_getDataGeneratorSettingsFromScript() {

    qInfo() << "TEST FOR PARSER getDataGeneratorSettingsFromScript METHOD(UNSUCCESSFUL PARSE TEST)";

    ScriptParserManager scriptParserManager;
    DataGeneratorSettings dataGeneratorSettings;

    const QString scriptContent = " default[:dataGeerator] = \"ipgwtg\"\n"
                                  "# Use local IPGWTG\n# Configuration of the ipgwtg user data generator,\n"
                                  "default[:userDataGen] =  \"ipex.isp.sip.o = 31000\n\" +\n"
                                  "ipex.isp.qci1.port    = 31010\n\" +\n"
                                  "ipex.qci2.port    = 31020\n\" +\n"
                                  "ipex.isp.qci5.port    = 31050\n\"\n"
                                  "default[:start_isp_simulator] = true\n"
                                  "default[:ipgwtg_ip] = \"10.10.0.1\"         # IP address of the interface that can reach the PGW\n"
                                  "default[:ipgwtg_inband_signal] = false\n"
                                  "default[:ipgwtg_port] = 64000\n"
                                  "default[:ipgwtg_ftp_sender_connect_put] = false\n";

    dataGeneratorSettings = scriptParserManager.getDataGeneratorSettingsFromScript(scriptContent);

    if(dataGeneratorSettings.dataGenerator == "ipgwtg") QVERIFY(false);
    else if(dataGeneratorSettings.startIspSimulator == false) QVERIFY(false);
    else if(dataGeneratorSettings.ipgwtg_IP_Address == "10.10.0.1") QVERIFY(false);
    else if(dataGeneratorSettings.ipgwtgInbandSignaling == false) QVERIFY(false);
    else if(dataGeneratorSettings.ipgwtgPort == 32000) QVERIFY(false);
    else if(dataGeneratorSettings.ipgwtgFtpSenderConnectPut == true) QVERIFY(false);

    QVERIFY(true);
}
void ScriptParserManagerTest::scriptParserManagerTest3_getSgwSettingsFromScript(){
    qInfo() << "TEST FOR PARSER getSgwSettings METHOD(SUCCESS)";
    ScriptParserManager scriptParserManager;
    SgwSettings sgwSettings;
    const QString scriptContent = "def Parameters.getSgwParameters()\n"
                                  "# Define and return default values\n"
                                  "default = {}\n"
                                  "default[:sgw_names] = [\"sgw224\"]\n"
                                  "default[:sgw_ipAddresses] = [\"127.255.255.1\"]\n"
                                  "default[:apn_lists] = [\"ltesim-core-network,172.17.0.1/16;\"]\n"
                                  "default[:sgw_LDIs] = [\"30\"]\n"
                                  "default[:core_network_gateway] = false\n";
    sgwSettings = scriptParserManager.getSgwSettings(scriptContent);
    if (sgwSettings.name != "sgw224") QVERIFY(false);
    else if (sgwSettings.ipAdress != "127.255.255.1") QVERIFY(false);
    else if (sgwSettings.ldi != 30) QVERIFY(false);
    else if (sgwSettings.coreNetworkGateway != false) QVERIFY(false);
    for (int i=0;i<sgwSettings.apnList.size();i++){
        if (sgwSettings.apnList[i].first!="ltesim-core-network") {
            QVERIFY(false);
        }
        else if (sgwSettings.apnList[i].second!="172.17.0.1/16") {
            QVERIFY(false);
        }
    }

    // if all test passed
    QVERIFY(true);
}
void ScriptParserManagerTest::scriptParserManagerTest4_getSgwSettingsFromScript(){
    qInfo() << "TEST FOR PARSER getSgwSettings METHOD(UNSUCCESSFUL PARSE TEST)";
    ScriptParserManager scriptParserManager;
    SgwSettings sgwSettings;
    const QString scriptContent = "def Parameters.getSgwParameters()\n"
                                  "# Define and return default values\n"
                                  "default = {}\n"
                                  "default[:sgw_names] = [\"1sgw224\"]\n"
                                  "default[:sgw_ipAddresses] = [\"127.256.255.1\"\n"
                                  "default[:apn_lissssts] = [\"ltesim-core-network,172.17.277.1/16;\"]\n"
                                  "default[:sgw_LDIs] = [\"30-2\"]\n"
                                  "default[:core_network_gateway] = true\n";
    sgwSettings = scriptParserManager.getSgwSettings(scriptContent);
    if (sgwSettings.name == "sgw224") QVERIFY(false);
    else if (sgwSettings.ipAdress == "127.255.255.1") QVERIFY(false);
    else if (sgwSettings.ldi == 30) QVERIFY(false);
    else if (sgwSettings.coreNetworkGateway == false) QVERIFY(false);
    for (int i=0;i<sgwSettings.apnList.size();i++){
        if (sgwSettings.apnList[i].first=="ltesim-core-network") {
            QVERIFY(false);
        }
        else if (sgwSettings.apnList[i].second=="172.17.0.1/16") {
            QVERIFY(false);
        }
    }

    // if all test passed
    QVERIFY(true);
}

void ScriptParserManagerTest::scriptParserManagerTest5_getChannelModelSettingsFromScript() {
    qInfo() << "TEST FOR PARSER getChannelModelSettings METHOD(SUCCESS)";

    ScriptParserManager scriptParserManager;
    ChannelModelSettings channelModelSettings;

    const QString scriptContent = "default[:model_set_name] = \"default_error_set\"\n\
                                default[:pdcch_drop_dl_assignment_rate] = 1.0\n\
                                default[:pdcch_drop_grant_rate] = 1.0\n\
                                default[:pdsch_transport_block_decoded_error_rate] = 1.0\n\
                                default[:phich_nack_to_ack_error_rate] = 1.0\n\
                                default[:phich_drop_harq_feedback_rate] = 1.0\n\
                                default[:pusch_transport_block_decoded_error_rate] = 1.0\n\
                                default[:pusch_drop_transport_block_rate] = 1.0\n\
                                default[:puxch_nack_to_ack_error_rate] = 1.0\n\
                                default[:puxch_dtx_to_ack_error_rate] = 1.0\n\
                                default[:puxch_ack_to_nack_error_rate] = 1.0\n\
                                default[:puxch_drop_scheduling_request_rate] = 1.0\n\
                                default[:dlni_noise] = 1.0\n\
                                default[:dlni_interference] = 1.0\n\
                                default[:dl_pathloss_min_pathloss] = 1.00\n\
                                default[:dl_pathloss_max_pathloss] = 20.0\n\
                                default[:dl_pathloss_time_min_to_max] = 1000\n\
                                default[:dl_pathloss_distribute_ues] = true\n\
                                default[:pathloss_based_feedback_sinr_threshold] = 1.0\n";

    channelModelSettings = scriptParserManager.getChannelModelSettingsFromScript(scriptContent);

    if(channelModelSettings.model_set_name != "default_error_set") QVERIFY(false);
    if(channelModelSettings.pdcch_drop_dl_assignment_rate != 1.0) QVERIFY(false);
    if(channelModelSettings.pdcch_drop_grant_rate != 1.0) QVERIFY(false);
    if(channelModelSettings.pdsch_transport_block_decoded_error_rate != 1.0) QVERIFY(false);
    if(channelModelSettings.phich_nack_to_ack_error_rate != 1.0) QVERIFY(false);
    if(channelModelSettings.phich_drop_harq_feedback_rate != 1.0) QVERIFY(false);
    if(channelModelSettings.pusch_transport_block_decoded_error_rate != 1.0) QVERIFY(false);
    if(channelModelSettings.pusch_drop_transport_block_rate != 1.0) QVERIFY(false);
    if(channelModelSettings.puxch_nack_to_ack_error_rate != 1.0) QVERIFY(false);
    if(channelModelSettings.puxch_dtx_to_ack_error_rate != 1.0) QVERIFY(false);
    if(channelModelSettings.puxch_ack_to_nack_error_rate != 1.0) QVERIFY(false);
    if(channelModelSettings.puxch_drop_scheduling_request_rate != 1.0) QVERIFY(false);
    if(channelModelSettings.dlni_noise != 1.0) QVERIFY(false);
    if(channelModelSettings.dlni_interference != 1.0) QVERIFY(false);
    if(channelModelSettings.dl_pathloss_min_pathloss != 1.0) QVERIFY(false);
    if(channelModelSettings.dl_pathloss_max_pathloss != 20.0) QVERIFY(false);
    if(channelModelSettings.dl_pathloss_time_min_to_max != 1000.0) QVERIFY(false);
    if(channelModelSettings.dl_pathloss_distribute_ues != true) QVERIFY(false);
    if(channelModelSettings.pathloss_based_feedback_sinr_threshold != 1.0) QVERIFY(false);
    QVERIFY(true);
}

void ScriptParserManagerTest::scriptParserManagerTest6_getMmeSettingsFromScript(){
    qInfo() << "TEST FOR PARSER getMmeSettings METHOD(SUCCESS)";

    ScriptParserManager scriptParserManager;
    MmeSettings mmeSettings;

    const QString scriptContent = "default[:simulate_core] = false\n"
        "default[:mme_names] = [\"mme1\"]\n"
        "default[:mme_tais] = [\"62F2281200\"]\n"
        "default[:mmes] = 1\n"
        "default[:mme_s1ap_uris] = [\"sctp://127.0.0.1:36412\"]\n"
        "default[:s1ap_pluginFilterPath] = \"/etc/alternatives/ltesim-root/ltesim/internal/ltesim-plugin-filters/com/ericsson/sps/ltesim/s1ap/filter\"\n";
    mmeSettings = scriptParserManager.getMmeSettings(scriptContent);
    if (mmeSettings.name != "mme1")                     QVERIFY(false);
    if (mmeSettings.tais != "62F2281200")               QVERIFY(false);
    if (mmeSettings.uris != "sctp://127.0.0.1:36412")   QVERIFY(false);
    if (mmeSettings.pluginFilterPath !=
            "/etc/alternatives/ltesim-root/ltesim/internal/ltesim-plugin-filters/com/ericsson/sps/ltesim/s1ap/filter" )
                                                        QVERIFY(false);
    QVERIFY(true);
}

void ScriptParserManagerTest::scriptParserManagerTest7_getMmeSettingsFromScript(){
    qInfo() << "TEST FOR PARSER getMmeSettings METHOD(UNSUCCESFUL PARSE TEST)";

    ScriptParserManager scriptParserManager;
    MmeSettings mmeSettings;

    const QString scriptContent = "default[:simulate_core] = false\n"
        "default[:mme_names] = [\"mme1\"\n"
        "default[:mme_tais] = [\"[62F2281200]\"]\n"
        "default[:mmes] = avs\n"
        "default[:mme_s1ap_uris] = [\"sctps://127.0.0.1:36412\"]\n"
        "default[:s1ap_pluginFilterPath] = \"/etc/alternatives/ltesim-root/ltesim/internal/ltesim-plugin-filters/com/ericsson/sps/ltesim/s1ap/filter/\"\n";
    mmeSettings = scriptParserManager.getMmeSettings(scriptContent);
    if (mmeSettings.name == "mme1")                     QVERIFY(false);
    if (mmeSettings.tais == "62F2281200")               QVERIFY(false);
    if (mmeSettings.uris == "sctp://127.0.0.1:36412")   QVERIFY(false);
    if (mmeSettings.pluginFilterPath ==
            "/etc/alternatives/ltesim-root/ltesim/internal/ltesim-plugin-filters/com/ericsson/sps/ltesim/s1ap/filter" )
                                                        QVERIFY(false);
    QVERIFY(true);

}

