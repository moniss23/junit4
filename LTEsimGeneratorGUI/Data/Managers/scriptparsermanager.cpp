#include <QRegExp>
#include "scriptparsermanager.h"

ScriptParserManager::ScriptParserManager() {}
ScriptParserManager::~ScriptParserManager() {}

QString ScriptParserManager::findRegexInText(QString pattern, const QString &text, int pos) {
    QRegExp regex(pattern);
    regex.setMinimal(true);

    if(regex.indexIn(text) >= 0) {
        QString foundPattern = regex.cap(pos);
        foundPattern.remove(QRegExp("[\"\\],}]"));
        return foundPattern;
    }

    return QString();
}

QVector<Cell> ScriptParserManager::getCellsFromScript(const QString &rbContent) {
    QVector<Cell> cells;
    QStringList rbLines = rbContent.split('\n');

    for(int i=0; i<rbLines.size(); ++i) {
        QString startPattern(":cell => \"(.*)\",");
        if(QRegExp(startPattern).indexIn(rbLines[i]) >= 0) {

            QVector<QString> cellParams = {
                findRegexInText(startPattern, rbLines[i], 1),
                findRegexInText(":site => \"(.*)\"[,]", rbLines[i+1], 1),
                findRegexInText(":pci => (.*)[,]", rbLines[i+2], 1),
                findRegexInText(":position_X => (.*)[,]", rbLines[i+3], 1),
                findRegexInText(":position_Y => (.*)[,]", rbLines[i+4], 1),
                findRegexInText(":earfcnDl => (.*)[,]", rbLines[i+5], 1),
                findRegexInText(":transmitPower => (.*)([,}]|$)", rbLines[i+6], 1),
                findRegexInText(":ulNoiseAndInterference => (.*)([,}]|$)", rbLines[i+7], 1)
            };

            Cell cell;
            cell.setCell(cellParams[0]);
            cell.setSite(cellParams[1]);
            cell.setPci(cellParams[2]);
            cell.setPosition_X(cellParams[3]);
            cell.setPosition_Y(cellParams[4]);
            cell.setEarfcnDl(cellParams[5]);
            cell.setTransmitPower(cellParams[6]);
            cell.setUlNoiseAndInterference(cellParams[7]);
            cells.append(cell);
        }
    }

    return cells;
}

QVector<Center> ScriptParserManager::getCentersFromScript(const QString &rbContent) {
    QVector<Center> centers;
    QStringList rbLines = rbContent.split('\n');

    for(int i=0; i<rbLines.size(); ++i) {
        QString startPattern(":area => \"Center(.*)\",");
        if(QRegExp(startPattern).indexIn(rbLines[i]) >= 0) {

            QVector<QString> centerParams = {
                findRegexInText(startPattern, rbLines[i], 1),
                findRegexInText(":southBoundary => (.*)([,}]|$)", rbLines[i+1], 1),
                findRegexInText(":northBoundary => (.*)([,}]|$)", rbLines[i+2], 1),
                findRegexInText(":westBoundary => (.*)([,}]|$)", rbLines[i+3], 1),
                findRegexInText(":eastBoundary => (.*)([,}]|$)", rbLines[i+4], 1)
            };

            Center center;
            center.setArea("Center" + centerParams[0]);
            center.setSouthBoundary(centerParams[1]);
            center.setNorthBoundary(centerParams[2]);
            center.setWestBoundary(centerParams[3]);
            center.setEastBoundary(centerParams[4]);
            centers.append(center);
        }
    }

    return centers;
}

QVector<Handover> ScriptParserManager::getHandoversFromScript(const QString &rbContent) {
    QVector<Handover> handovers;
    QStringList rbLines = rbContent.split('\n');

    for(int i=0; i<rbLines.size(); ++i) {
        QString startPattern(":area => \"Handover(.*)\",");
        if(QRegExp(startPattern).indexIn(rbLines[i]) >= 0) {

            QVector<QString> handoverParams = {
                findRegexInText(startPattern, rbLines[i], 1),
                findRegexInText(":southBoundary => (.*)([,}]|$)", rbLines[i+1], 1),
                findRegexInText(":northBoundary => (.*)([,}]|$)", rbLines[i+2], 1),
                findRegexInText(":westBoundary => (.*)([,}]|$)", rbLines[i+3], 1),
                findRegexInText(":eastBoundary => (.*)([,}]|$)", rbLines[i+4], 1)
            };

           Handover handover;
            handover.setArea("Handover" + handoverParams[0]);
            handover.setSouthBoundary(handoverParams[1]);
            handover.setNorthBoundary(handoverParams[2]);
            handover.setWestBoundary(handoverParams[3]);
            handover.setEastBoundary(handoverParams[4]);
            handovers.append(handover);
        }
    }

    return handovers;
}

DataGeneratorSettings ScriptParserManager::getDataGeneratorSettingsFromScript(const QString &scriptContent)
{
    DataGeneratorSettings dataGeneratorSettings;
    QStringList scriptContentLines = scriptContent.split("\n");

    int startIndex, endIndex;
    QString value;

    for(int i=0; i<scriptContentLines.size(); ++i) {
        if(scriptContentLines[i].contains("default[:dataGenerator]")) {
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            startIndex = scriptContentLines[i].indexOf("\"");
            startIndex++;
            endIndex = scriptContentLines[i].lastIndexOf("\"");
            value = scriptContentLines[i].mid(startIndex, endIndex - startIndex);
            dataGeneratorSettings.dataGenerator = value;
        }
        else if(scriptContentLines[i].contains("default[:userDataGen]")) {
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            int j = i;
            do {
                startIndex = scriptContentLines[j].indexOf("\"");
                startIndex++;
                endIndex  = scriptContentLines[j].lastIndexOf("\"");
                value = scriptContentLines[j].mid(startIndex, endIndex - startIndex);
                value.chop(2);
                dataGeneratorSettings.userDataGenerator.push_back(value);
            }while(scriptContentLines[j++].contains("+"));
            for(int k = 0; k < dataGeneratorSettings.userDataGenerator.size(); k++) {
            }
        }
        else if(scriptContentLines[i].contains("default[:start_isp_simulator]")) {
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            if(scriptContentLines[i].contains("true")) {
                dataGeneratorSettings.startIspSimulator = true;
            } else {
                dataGeneratorSettings.startIspSimulator = false;
            }
        }
        else if(scriptContentLines[i].contains("default[:ipgwtg_ipAddress]")) {
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            startIndex = scriptContentLines[i].indexOf("\"");
            startIndex++;
            endIndex = scriptContentLines[i].lastIndexOf("\"");
            value = scriptContentLines[i].mid(startIndex, endIndex - startIndex);
            dataGeneratorSettings.ipgwtg_IP_Address = value;
        }
        else if(scriptContentLines[i].contains("default[:ipgwtg_inband_signaling]")) {
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            if(scriptContentLines[i].contains("true")) {
                dataGeneratorSettings.ipgwtgInbandSignaling = true;
            } else {
                dataGeneratorSettings.ipgwtgInbandSignaling = false;
            }
        }
        else if(scriptContentLines[i].contains("default[:ipgwtg_port]")) {
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            startIndex = scriptContentLines[i].indexOf("=");
            startIndex++;
            value = scriptContentLines[i].mid(startIndex, scriptContentLines[i].size() - startIndex);
            dataGeneratorSettings.ipgwtgPort = value.toInt();
        }
        else if(scriptContentLines[i].contains("default[:ipgwtg_ftp_sender_connect_put]")) {
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            if(scriptContentLines[i].contains("true")) {
                dataGeneratorSettings.ipgwtgFtpSenderConnectPut = true;
            } else {
                dataGeneratorSettings.ipgwtgFtpSenderConnectPut = false;
            }
        }
    }
    return dataGeneratorSettings;
}
SgwSettings ScriptParserManager::getSgwSettings(const QString &scriptContent){
    SgwSettings sgwSettings;
    int len;
    QStringList scriptContentLines = scriptContent.split('\n');
    for(int i=0; i<scriptContentLines.size(); ++i) {
        if(scriptContentLines[i].contains("default[:sgw_names]")) {
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            sgwSettings.name = scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len);
        }
        else if (scriptContentLines[i].contains("default[:sgw_ipAddresses]")) {
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            sgwSettings.ipAdress = scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len);
        }
        else if (scriptContentLines[i].contains("default[:apn_lists]")) {
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            QStringList temp = (scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len)).split(",");
            for (int j=0;j<temp.size();j+=2){
                sgwSettings.apnList.append(QPair<QString,QString>(temp[j],temp[j+1]));
                sgwSettings.apnList[j].second.chop(1);
            }
        }
        else if (scriptContentLines[i].contains("default[:sgw_LDIs]")) {
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            sgwSettings.ldi = scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len).toInt();
        }
        else if (scriptContentLines[i].contains("default[:core_network_gateway]")) {
            if (scriptContentLines[i].contains("false")){
                sgwSettings.coreNetworkGateway=false;
            }
            else{
                sgwSettings.coreNetworkGateway=true;
            }
        }
    }
    return sgwSettings;
}

UCToolSettings ScriptParserManager::getUCToolSettingsFromScript(const QString &scriptContent)
{
    UCToolSettings ucToolSettings;
    QStringList scriptContentLines = scriptContent.split("\n");

    int startIndex, endIndex;
    QString value;

    for(int i=0; i<scriptContentLines.size(); ++i) {
        if(scriptContentLines[i].contains("default[:uctool_ip]")) {
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
        startIndex = scriptContentLines[i].indexOf("{");
        startIndex++;
        endIndex = scriptContentLines[i].lastIndexOf("}");
        value = scriptContentLines[i].mid(startIndex, endIndex - startIndex);
        ucToolSettings.ucToolIP = value;
        }
        else if(scriptContentLines[i].contains("default[:uctool_cIds]")) {
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
        startIndex = scriptContentLines[i].indexOf("{");
        startIndex++;
        endIndex = scriptContentLines[i].lastIndexOf("}");
        value = scriptContentLines[i].mid(startIndex, endIndex - startIndex);
        ucToolSettings.ucToolCIds = value;
        }
        else if(scriptContentLines[i].contains("default[:uctool_service_ip]")) {
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
        startIndex = scriptContentLines[i].indexOf("{");
        startIndex++;
        endIndex = scriptContentLines[i].lastIndexOf("}");
        value = scriptContentLines[i].mid(startIndex, endIndex - startIndex);
        ucToolSettings.ucToolServiceIp = value;
        }
    }
    return ucToolSettings;
}

ChannelModelSettings ScriptParserManager::getChannelModelSettingsFromScript(const QString &rbContent) {
    ChannelModelSettings settings;
    QStringList rbLines = rbContent.split('\n');

    for(int i=0; i<rbLines.size(); ++i) {
        if(QRegExp("[:model_set_name] = \"(.*)\"$").indexIn(rbLines[i]) >= 0) {
            settings.setModel_set_name(
                findRegexInText("[:model_set_name] = \"(.*)\"$", rbLines[i], 1));
        }
        else if(QRegExp("[:pdcch_drop_dl_assignment_rate] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setPdcch_drop_dl_assignment_rate(
                findRegexInText("[::pdcch_drop_dl_assignment_rate] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:pdcch_drop_grant_rate] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setPdcch_drop_grant_rate(
                        findRegexInText("[:pdcch_drop_grant_rate] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:pdsch_transport_block_decoded_error_rate] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setPdsch_transport_block_decoded_error_rate(
                        findRegexInText("[:pdsch_transport_block_decoded_error_rate] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:phich_nack_to_ack_error_rate] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setPhich_nack_to_ack_error_rate(
                        findRegexInText("[:phich_nack_to_ack_error_rate] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:phich_drop_harq_feedback_rate] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setPhich_drop_harq_feedback_rate(
                        findRegexInText("[:phich_drop_harq_feedback_rate] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:pusch_transport_block_decoded_error_rate] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setPusch_transport_block_decoded_error_rate(
                        findRegexInText("[:pusch_transport_block_decoded_error_rate] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:pusch_drop_transport_block_rate] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setPusch_drop_transport_block_rate(
                        findRegexInText("[:pusch_drop_transport_block_rate] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:puxch_nack_to_ack_error_rate] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setPuxch_nack_to_ack_error_rate(
                        findRegexInText("[:puxch_nack_to_ack_error_rate] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:puxch_dtx_to_ack_error_rate] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setPuxch_dtx_to_ack_error_rate(
                        findRegexInText("[:puxch_dtx_to_ack_error_rate] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:puxch_ack_to_nack_error_rate] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setPuxch_ack_to_nack_error_rate(
                        findRegexInText("[:puxch_ack_to_nack_error_rate] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:puxch_drop_scheduling_request_rate] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setPuxch_drop_scheduling_request_rate(
                        findRegexInText("[:puxch_drop_scheduling_request_rate] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:dlni_noise] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setDlni_noise(
                        findRegexInText("[:dlni_noise] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:dlni_interference] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setDlni_interference(
                        findRegexInText("[:dlni_interference] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:dl_pathloss_min_pathloss] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setDl_pathloss_min_pathloss(
                        findRegexInText("[:dl_pathloss_min_pathloss] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:dl_pathloss_max_pathloss] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setDl_pathloss_max_pathloss(
                        findRegexInText("[:dl_pathloss_max_pathloss] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:dl_pathloss_time_min_to_max] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setDl_pathloss_time_min_to_max(
                        findRegexInText("[:dl_pathloss_time_min_to_max] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:dl_pathloss_distribute_ues] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setDl_pathloss_time_min_to_max(
                        findRegexInText("[:dl_pathloss_distribute_ues] = (.*)$", rbLines[i], 1));
        }
        else if(QRegExp("[:pathloss_based_feedback_sinr_threshold] = (.*)$").indexIn(rbLines[i]) >= 0) {
            settings.setPathloss_based_feedback_sinr_threshold(
                        findRegexInText("[:pathloss_based_feedback_sinr_threshold] = (.*)$", rbLines[i], 1));
        }
    }

    return settings;
}
