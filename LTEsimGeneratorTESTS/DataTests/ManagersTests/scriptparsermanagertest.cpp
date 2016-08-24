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
                                  "default[:start_isp_simulator] = false\n"
                                  "default[:ipgwtg_ip] = \"10.10.0.1\"         # IP address of the interface that can reach the PGW\n"
                                  "default[:ipgwtg_inband_signal] = false\n"
                                  "default[:ipgwtg_port] = 64000\n"
                                  "default[:ipgwtg_ftp_sender_connect_put] = false\n";

    dataGeneratorSettings = scriptParserManager.getDataGeneratorSettingsFromScript(scriptContent);

    if(dataGeneratorSettings.dataGenerator == "ipgwtg") QVERIFY(false);
    else if(dataGeneratorSettings.startIspSimulator == true) QVERIFY(false);
    else if(dataGeneratorSettings.ipgwtg_IP_Address == "10.10.0.1") QVERIFY(false);
    else if(dataGeneratorSettings.ipgwtgInbandSignaling == false) QVERIFY(false);
    else if(dataGeneratorSettings.ipgwtgPort == 32000) QVERIFY(false);
    else if(dataGeneratorSettings.ipgwtgFtpSenderConnectPut == true) QVERIFY(false);

    QVERIFY(true);
}

