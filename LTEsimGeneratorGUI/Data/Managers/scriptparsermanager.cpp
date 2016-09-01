#include <QRegExp>
#include "scriptparsermanager.h"

ScriptParserManager::ScriptParserManager() {}
ScriptParserManager::~ScriptParserManager() {}

QString ScriptParserManager::findRegexInText(QString pattern, const QString &text, int pos) {
    QRegExp regex(pattern);
    regex.setMinimal(true);

    if(regex.indexIn(text) >= 0) {
        QString foundPattern = regex.cap(pos);
        foundPattern.remove('"');
        foundPattern.remove(']');
        foundPattern.remove(',');
        foundPattern.remove('}');
        return foundPattern;
    }

    return QString();
}

QVector<QPair<Cell, Center>> ScriptParserManager::matchCellsToCenters(auto cells, auto centers) {
    QVector<QPair<Cell, Center>> cellsInfo;

    for(auto &cell : cells) {
        QString cellNumber = cell.name;
        cellNumber.remove("cell", Qt::CaseInsensitive);

        auto centerFound = std::find_if(centers.begin(), centers.end(), [&cellNumber](auto &center)
        {
            QString centerNumber = center.area;
            centerNumber.remove("Center", Qt::CaseInsensitive);
            return cellNumber == centerNumber;
        });

        if(centerFound != centers.end()) {
            cellsInfo.append(qMakePair(cell, *centerFound));
        }
    }

    return cellsInfo;
}

void ScriptParserManager::parseFromScript(const QString &scriptContent, Project &project){

    QVector<Cell> cells;
    QVector<Center> centers;
    QStringList scriptContentLines = scriptContent.split("\n");

    QString centerStartPattern(":area => \"Center(.*)\",");
    QString handoverStartPattern(":area => \"Handover(.*)\",");

    for (int i=0;i<scriptContentLines.size();i++){
        if(scriptContentLines[i].contains("default[:model_set_name]")) {
            project.channelModelSettings = getChannelModelSettingsFromScript(i,scriptContentLines);
        }
        else if (scriptContentLines[i].contains("default[:mme_names] =")){
            project.mmeSettings = getMmeSettings(i,scriptContentLines);
        }
        else if(scriptContentLines[i].contains("default[:rec]")) {
            cells = getCellsFromScript(i,scriptContentLines);
        }
        else if(scriptContentLines[i].contains("default[:areas]")) {
            centers = getCentersFromScript(i,scriptContentLines);
            project.handovers = getHandoversFromScript(i,scriptContentLines);
        }
        else if(scriptContentLines[i].contains("default[:dataGenerator]")) {
            project.dataGeneratorSettings = getDataGeneratorSettingsFromScript(i,scriptContentLines);
        }
        else if(scriptContentLines[i].contains("default[:sgw_names]")) {
            project.sgwSettings = getSgwSettings(i,scriptContentLines);
        }
        else if(scriptContentLines[i].contains("default[:uctool_ip]")) {
            project.ucToolSettings = getUCToolSettingsFromScript(i,scriptContentLines);
        }
        else if (scriptContentLines[i].contains("[:generate_pagings]")){
            project.pagingSettings = getPagingSettings(i,scriptContentLines);
        }
        else if (scriptContentLines[i].contains("getUbsimConfigParameters()")){
            project.ubSimSettings = getUBSimSettings(i,scriptContentLines);
        }
    }

    project.cellsInfo = this->matchCellsToCenters(cells, centers);
}

QVector<Cell> ScriptParserManager::getCellsFromScript(int i, const QStringList scriptContent) {

    QVector<Cell> cells;

    QString cellStartPattern(":cell => \"(.*)\",");
    while (!(QRegExp("^end").indexIn(scriptContent[i])>-1)){
        if(QRegExp(cellStartPattern).indexIn(scriptContent[i]) >= 0) {

            QVector<QString> cellParams = {
                findRegexInText(cellStartPattern, scriptContent[i], 1),
                findRegexInText(":site => \"(.*)\"[,]", scriptContent[i+1], 1),
                findRegexInText(":pci => (.*)[,]", scriptContent[i+2], 1),
                findRegexInText(":position_X => (.*)[,]", scriptContent[i+3], 1),
                findRegexInText(":position_Y => (.*)[,]", scriptContent[i+4], 1),
                findRegexInText(":earfcnDl => (.*)[,]", scriptContent[i+5], 1),
                findRegexInText(":transmitPower => (.*)([,}]|$)", scriptContent[i+6], 1),
                findRegexInText(":ulNoiseAndInterference => (.*)([,}]|$)", scriptContent[i+7], 1)
            };

            Cell cell;
            cell.name = cellParams[0];
            cell.site = cellParams[1];
            cell.pci = cellParams[2].toInt();
            cell.position_X = cellParams[3].toInt();
            cell.position_Y = cellParams[4].toInt();
            cell.earfcnDl = cellParams[5].toInt();
            cell.transmitPower = cellParams[6].toFloat();
            cell.ulNoiseAndInterference = cellParams[7].toFloat();
            cells.append(cell);
            i+=8;
        }
        else i++;
    }

    return cells;
}

QVector<Center> ScriptParserManager::getCentersFromScript(int i,const QStringList scriptContent) {

    QVector<Center> centers;

    QString centerStartPattern(":area => \"Center(.*)\",");
    while (!scriptContent.contains("Handover") && !(QRegExp("^end").indexIn(scriptContent[i])>-1)) {
        QString startPattern(":area => \"Center(.*)\",");
        if(QRegExp(centerStartPattern).indexIn(scriptContent[i]) >= 0) {

            QVector<QString> centerParams = {
                findRegexInText(startPattern, scriptContent[i], 1),
                findRegexInText(":southBoundary => (.*)([,}]|$)", scriptContent[i+1], 1),
                findRegexInText(":northBoundary => (.*)([,}]|$)", scriptContent[i+2], 1),
                findRegexInText(":westBoundary => (.*)([,}]|$)", scriptContent[i+3], 1),
                findRegexInText(":eastBoundary => (.*)([,}]|$)", scriptContent[i+4], 1)
            };

            Center center;
            center.area = QString("Center" + centerParams[0]);
            center.southBoundary = centerParams[1].toInt();
            center.northBoundary = centerParams[2].toInt();
            center.westBoundary = centerParams[3].toInt();
            center.eastBoundary = centerParams[4].toInt();
            centers.append(center);
            i+=5;
        }
        else i++;
    }

    return centers;
}

QVector<Handover> ScriptParserManager::getHandoversFromScript(int i, const QStringList scriptContent) {

    QVector<Handover> handovers;

    QString handoverStartPattern(":area => \"Handover(.*)\",");
    while (!(QRegExp("^end").indexIn(scriptContent[i])>-1)){
        if(QRegExp(handoverStartPattern).indexIn(scriptContent[i]) >= 0) {

            QVector<QString> handoverParams = {
                findRegexInText(handoverStartPattern, scriptContent[i], 1),
                findRegexInText(":southBoundary => (.*)([,}]|$)", scriptContent[i+1], 1),
                findRegexInText(":northBoundary => (.*)([,}]|$)", scriptContent[i+2], 1),
                findRegexInText(":westBoundary => (.*)([,}]|$)", scriptContent[i+3], 1),
                findRegexInText(":eastBoundary => (.*)([,}]|$)", scriptContent[i+4], 1)
            };

           Handover handover;
            handover.area = QString("Handover" + handoverParams[0]);
            handover.southBoundary = handoverParams[1].toInt();
            handover.northBoundary = handoverParams[2].toInt();
            handover.westBoundary = handoverParams[3].toInt();
            handover.eastBoundary = handoverParams[4].toInt();
            handovers.append(handover);
            i+=5;
        }
        else i++;
    }

    return handovers;
}

DataGeneratorSettings ScriptParserManager::getDataGeneratorSettingsFromScript(int i, QStringList scriptContentLines)
{
    DataGeneratorSettings dataGeneratorSettings;

    int startIndex, endIndex;
    QString value;

    while (!(QRegExp("^end").indexIn(scriptContentLines[i])>-1)){
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
            } else if (scriptContentLines[i].contains("false")) {
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
            } else if (scriptContentLines[i].contains("false")) {
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
        i++;
    }
    return dataGeneratorSettings;
}
SgwSettings ScriptParserManager::getSgwSettings(int i,const QStringList scriptContentLines){

    SgwSettings sgwSettings;

    int len;
    while (!scriptContentLines[i].contains("end")) {
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
        i++;
    }
    return sgwSettings;
}

UCToolSettings ScriptParserManager::getUCToolSettingsFromScript(int i, QStringList scriptContentLines)
{
    UCToolSettings ucToolSettings;

    int startIndex, endIndex;
    QString value;

    while (!scriptContentLines[i].contains ("end") ) {
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
        i++;
    }
    return ucToolSettings;
}

ChannelModelSettings ScriptParserManager::getChannelModelSettingsFromScript(int i,const QStringList content) {

    ChannelModelSettings settings;

    while (!content[i].contains("end")){
        if(QRegExp("\\[:model_set_name\\] = \"(.*)\"$").indexIn(content[i]) >= 0) {
            settings.model_set_name = findRegexInText("\\[:model_set_name\\] = \"(.*)\"$", content[i], 1);
        }
        else if(QRegExp("\\[:pdcch_drop_dl_assignment_rate\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.pdcch_drop_dl_assignment_rate =  findRegexInText(
                        "\\[:pdcch_drop_dl_assignment_rate\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:pdcch_drop_grant_rate\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.pdcch_drop_grant_rate = findRegexInText(
                        "\\[:pdcch_drop_grant_rate\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:pdsch_transport_block_decoded_error_rate\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.pdsch_transport_block_decoded_error_rate =  findRegexInText(
                        "\\[:pdsch_transport_block_decoded_error_rate\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:phich_nack_to_ack_error_rate\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.phich_nack_to_ack_error_rate =  findRegexInText(
                        "\\[:phich_nack_to_ack_error_rate\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:phich_drop_harq_feedback_rate\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.phich_drop_harq_feedback_rate =  findRegexInText(
                        "\\[:phich_drop_harq_feedback_rate\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:pusch_transport_block_decoded_error_rate\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.pusch_transport_block_decoded_error_rate =  findRegexInText(
                        "\\[:pusch_transport_block_decoded_error_rate\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:pusch_drop_transport_block_rate\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.pusch_drop_transport_block_rate = findRegexInText(
                        "\\[:pusch_drop_transport_block_rate\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:puxch_nack_to_ack_error_rate\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.puxch_nack_to_ack_error_rate = findRegexInText(
                        "\\[:puxch_nack_to_ack_error_rate\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:puxch_dtx_to_ack_error_rate\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.puxch_dtx_to_ack_error_rate =  findRegexInText(
                        "\\[:puxch_dtx_to_ack_error_rate\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:puxch_ack_to_nack_error_rate\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.puxch_ack_to_nack_error_rate =  findRegexInText(
                        "\\[:puxch_ack_to_nack_error_rate\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:puxch_drop_scheduling_request_rate\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.puxch_drop_scheduling_request_rate = findRegexInText(
                        "\\[:puxch_drop_scheduling_request_rate\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:dlni_noise\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.dlni_noise =  findRegexInText(
                        "\\[:dlni_noise\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:dlni_interference\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.dlni_interference =  findRegexInText(
                        "\\[:dlni_interference\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:dl_pathloss_min_pathloss\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.dl_pathloss_min_pathloss = findRegexInText(
                        "\\[:dl_pathloss_min_pathloss\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:dl_pathloss_max_pathloss\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.dl_pathloss_max_pathloss = findRegexInText(
                        "\\[:dl_pathloss_max_pathloss\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:dl_pathloss_time_min_to_max\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.dl_pathloss_time_min_to_max =  findRegexInText(
                        "\\[:dl_pathloss_time_min_to_max\\] = (.*)$", content[i], 1).toDouble();
        }
        else if(QRegExp("\\[:dl_pathloss_distribute_ues\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.dl_pathloss_distribute_ues = findRegexInText(
                        "\\[:dl_pathloss_distribute_ues\\] = (.*)$", content[i], 1) == "true" ?
                        true : false;
        }
        else if(QRegExp("\\[:pathloss_based_feedback_sinr_threshold\\] = (.*)$").indexIn(content[i]) >= 0) {
            settings.pathloss_based_feedback_sinr_threshold =  findRegexInText(
                        "\\[:pathloss_based_feedback_sinr_threshold\\] = (.*)$", content[i], 1).toDouble();
        }

        i++;
    }

    return settings;

}
MmeSettings ScriptParserManager::getMmeSettings(int i, QStringList scriptContentLines){

    MmeSettings mmeSettings;

    int len, startIndex;
    while (!scriptContentLines[i].contains("end")){
        if (scriptContentLines[i].contains("default[:mme_names] =")){
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            mmeSettings.name = scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len);
            if (scriptContentLines[i-1].contains("true")){
                mmeSettings.simulatedCoreNetwork = false;
            }
            else if (scriptContentLines[i-1].contains("true")){
                mmeSettings.simulatedCoreNetwork = true;
            }
        }

        else if (scriptContentLines[i].contains("default[:mme_tais] = ")){
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            mmeSettings.tais = scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len);
        }
        else if (scriptContentLines[i].contains("default[:mmes] = ")){
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            mmeSettings.numberOfMme = QString(scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len)).toInt();
        }
        else if (scriptContentLines[i].contains("default[:mme_s1ap_uris] = ")){
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            mmeSettings.uris = scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len);
        }
        else if (scriptContentLines[i].contains("default[:s1ap_pluginFilterPath] = ")){
            len = (scriptContentLines[i].indexOf("\""))-(scriptContentLines[i].lastIndexOf("\"")-4);
            QRegExp pluginRegExp("\".*\"");
            int pos = pluginRegExp.indexIn(scriptContentLines[i]);
            if (pos > -1) {
                mmeSettings.pluginFilterPath = pluginRegExp.capturedTexts()[0].mid(1,pluginRegExp.capturedTexts()[0].length()-2);
            }
        }
        i++;
    }

    return mmeSettings;
}
PagingSettings ScriptParserManager::getPagingSettings(int i,QStringList scriptContentLines){

    PagingSettings pagingSettings;

    int startIndex,len;

    while (!scriptContentLines[i].contains("end")){
        if (scriptContentLines[i].contains("[:generate_pagings]")){
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            if (scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len)=="false"){
                pagingSettings.isUsedInConfiguration = false;

            }
            else if (scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len)=="true"){
                pagingSettings.isUsedInConfiguration = true;

            }
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
        }
        else if (scriptContentLines[i].contains("[:generators]")){
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            QRegExp generatorsRegExp("[0-9]+");
            int pos = generatorsRegExp.indexIn(scriptContentLines[i]);
            if (pos > -1) {
                pagingSettings.generators = generatorsRegExp.capturedTexts()[0].toInt();
            }
        }
        else if (scriptContentLines[i].contains("[:paging_generator_names]")){
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            QStringList generatorNames = (scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len)).split("\", \"");
            for (QString name: generatorNames){
                pagingSettings.names.append(name);
            }
        }
        else if (scriptContentLines[i].contains("[:imsi_ranges]")){
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            QStringList imsiRanges = (scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len)).split("\", \"");
            for (QString range: imsiRanges){
                pagingSettings.imsiRanges.append(range);
            }
        }
        else if (scriptContentLines[i].contains("[:ue_paging_identity]")){
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            if (scriptContentLines[i].contains("IMSI")){
                pagingSettings.uePagingIdentity = "IMSI";
            }
            else if (scriptContentLines[i].contains("STMSI")){
                pagingSettings.uePagingIdentity = "STMSI";
            }
        }
        else if (scriptContentLines[i].contains("[:paging_s1ap_uris]")){
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            QStringList pagingUris = (scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len)).split("\", \"");
            for (QString ur: pagingUris){
                pagingSettings.pagingSlapUris.append(ur);
            }
        }
        else if (scriptContentLines[i].contains("[:bundle_paging]")){
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            if (scriptContentLines[i].contains("true")){
                pagingSettings.bundlePaging=true;
            }
            else if (scriptContentLines[i].contains("false")){
                pagingSettings.bundlePaging = false;
            }
        }
        i++;

    }
    return pagingSettings;


}

UBSimSettings ScriptParserManager::getUBSimSettings(int i, QStringList scriptContentLines){

    UBSimSettings ubSimSettings;

    int startIndex;
    while (!(QRegExp("^end").indexIn(scriptContentLines[i])>-1)) {
        if (scriptContentLines[i].contains("[:ueTypesDir]")){
            QRegExp quoteRegExp("\".*\"");
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                ubSimSettings.ueTypesDir = quoteRegExp.capturedTexts()[0];
            }
        }
        else if (scriptContentLines[i].contains("[:csTrafficModelsDir]")){
            QRegExp quoteRegExp("\".*\"");
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                ubSimSettings.csTrafficModelsDir = quoteRegExp.capturedTexts()[0];
            }
        }
        else if (scriptContentLines[i].contains("[:psTrafficModelsDir]")){
            QRegExp quoteRegExp("\".*\"");
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                ubSimSettings.psTrafficModelsDir = quoteRegExp.capturedTexts()[0];
            }
        }
        else if (scriptContentLines[i].contains("[:mobilityModelsDir]")){
            QRegExp quoteRegExp("\".*\"");
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                ubSimSettings.mobilityModelsDir = quoteRegExp.capturedTexts()[0];
            }
        }
        else if (scriptContentLines[i].contains("[:visualization]")){
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            if (scriptContentLines[i].contains("true")){
                ubSimSettings.UBSimGui = true;
            }
            else if (scriptContentLines[i].contains("false")){
                ubSimSettings.UBSimGui = false;
            }
        }
        else if (scriptContentLines[i].contains("[:ubsim_patches]")){
            QRegExp quoteRegExp("\".*\"");
            if(scriptContentLines[i].contains("#")) {
                startIndex = scriptContentLines[i].indexOf("#");
                scriptContentLines[i].chop(scriptContentLines[i].size() - startIndex);
            }
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                ubSimSettings.ubsim_patches = quoteRegExp.capturedTexts();
            }
        }
        i++;
    }
    return ubSimSettings;
}
