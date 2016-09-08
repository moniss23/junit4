#include "scriptparsermanager.h"
#include "Data/ProjectSettings/Helpers/ueparametersparser.h"
#include "Data/ProjectSettings/Helpers/mapparser.h"
#include <QRegExp>
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

    int len =0,startIndex =0;

    project.mapRange = getMapRange(scriptContentLines);

    for (int i=0;i<scriptContentLines.size();i++){
        if (scriptContentLines[i].contains("getGeneralParameters()")){
            startIndex=i;
            while ((!(QRegExp("end$").indexIn(scriptContentLines[i])>-1))){
                len++;
                i++;
            }
            project.generalConfiguration = getGeneralConfigurationSettings(scriptContentLines.mid(startIndex,len));
        }
        else if(scriptContentLines[i].contains("default[:model_set_name]")) {
            startIndex=i;
            while ((!(QRegExp("end$").indexIn(scriptContentLines[i])>-1))){
                len++;
                i++;
            }
            project.channelModelSettings = getChannelModelSettingsFromScript(scriptContentLines.mid(startIndex,len));
        }
        else if (scriptContentLines[i].contains("default[:mme_names] =")){
            startIndex=i;
            while ((!(QRegExp("end$").indexIn(scriptContentLines[i])>-1))){
                len++;
                i++;
            }
            project.mmeSettings = getMmeSettings(scriptContentLines.mid(startIndex,len));
        }
        else if(scriptContentLines[i].contains("default[:rec]")) {
            startIndex=i;
            while ((!(QRegExp(" end$").indexIn(scriptContentLines[i])>-1))){
                len++;
                i++;
            }
            cells = getCellsFromScript(scriptContentLines);        }
        else if(scriptContentLines[i].contains("default[:areas]")) {
            startIndex=i;
            while ((!(QRegExp("Common").indexIn(scriptContentLines[i])>-1))){
                len++;
                i++;
            }
            centers = getCentersFromScript(scriptContentLines);
            project.handovers = getHandoversFromScript(scriptContentLines.mid(startIndex,len));
        }
        else if(scriptContentLines[i].contains("default[:dataGenerator]")) {
            startIndex=i;
            while ((!(QRegExp(" end$").indexIn(scriptContentLines[i])>-1))){
                len++;
                i++;
            }
            project.dataGeneratorSettings = getDataGeneratorSettingsFromScript(scriptContentLines.mid(startIndex,len));
        }
        else if(scriptContentLines[i].contains("default[:sgw_names]")) {
            startIndex=i;
            while ((!(QRegExp(" end$").indexIn(scriptContentLines[i])>-1))){
                len++;
                i++;
            }
            project.sgwSettings = getSgwSettings(scriptContentLines.mid(startIndex,len));
        }
        else if (scriptContentLines[i].contains("[:generate_pagings]")){
            startIndex=i;
            while ((!(QRegExp(" end$").indexIn(scriptContentLines[i])>-1))){
                len++;
                i++;
            }
            project.pagingSettings = getPagingSettings(scriptContentLines.mid(startIndex,len));
        }
        else if (scriptContentLines[i].contains("getUbsimConfigParameters()")){
            startIndex=i;
            while ((!(QRegExp(" end$").indexIn(scriptContentLines[i])>-1))){
                len++;
                i++;
            }
            project.ubSimSettings = getUBSimSettings(scriptContentLines.mid(startIndex,len));
        }
        else if (scriptContentLines[i].contains("getGeneralParameters")){
            startIndex=i;
            while ((!(QRegExp(" end$").indexIn(scriptContentLines[i])>-1))){
                len++;
                i++;
            }
            project.generalConfiguration = getGeneralConfigurationSettings(scriptContentLines.mid(startIndex,len));
        }
        else if (scriptContentLines[i].contains("Parameters.getUeParameters()")){
            startIndex=i;
            while ((!(QRegExp(" end$").indexIn(scriptContentLines[i])>-1))){
                len++;
                i++;
            }
            project.ueParameters = getUeParameters(scriptContentLines.mid(startIndex,len));
            project.ucToolSettings = getUCToolSettingsFromScript(scriptContentLines.mid(startIndex,len));
        }
    }
    project.cellsInfo = this->matchCellsToCenters(cells, centers);
}

QVector<Cell> ScriptParserManager::getCellsFromScript(const QStringList scriptContent) {

    QVector<Cell> cells;

    QString cellStartPattern(":cell => \"(.*)\",");
    for (int i = 0;i<scriptContent.size();i++) {
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
    }
    return cells;
}

QVector<Center> ScriptParserManager::getCentersFromScript(const QStringList scriptContent) {

    QVector<Center> centers;

    QString centerStartPattern(":area => \"Center(.*)\",");
    for (int i = 0;i<scriptContent.size();i++)  {
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
    }

    return centers;
}

QVector<Handover> ScriptParserManager::getHandoversFromScript(const QStringList scriptContent) {

    QVector<Handover> handovers;

    QString handoverStartPattern(":area => \"Handover(.*)\",");
    for (int i = 0;i<scriptContent.size();i++) {
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
    }

    return handovers;
}

DataGeneratorSettings ScriptParserManager::getDataGeneratorSettingsFromScript(const QStringList scriptContentLines)
{
    DataGeneratorSettings dataGeneratorSettings;

    for (int i = 0;i<scriptContentLines.size();i++) {
        if(scriptContentLines[i].contains("default[:dataGenerator]")) {
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                dataGeneratorSettings.dataGenerator = quoteRegExp.capturedTexts()[0].remove("\"");
            }
        }
        else if(scriptContentLines[i].contains("default[:userDataGen]")) {
            QRegExp quoteRegExp("\"ipex.*\"");
            int j=0;
            while (scriptContentLines[i+j].contains("ipex")){
                if (quoteRegExp.indexIn(scriptContentLines[i+j])>-1){
                    dataGeneratorSettings.userDataGenerator.append(scriptContentLines[i+j].mid(quoteRegExp.indexIn(scriptContentLines[i+j]),scriptContentLines[i+j].indexOf("\n")));
                }
                j++;
            }
        }
        else if(scriptContentLines[i].contains("default[:ipgwtg_port]")) {
            QRegExp numberRegExp("[0-9]+");
            if (numberRegExp.indexIn(scriptContentLines[i])>-1){
                dataGeneratorSettings.ipgwtgPort= numberRegExp.capturedTexts()[0].toInt();
            }
        }
        else if(scriptContentLines[i].contains("default[:start_isp_simulator]")) {
            if(scriptContentLines[i].contains("true")) {
                dataGeneratorSettings.startIspSimulator = true;
            } else if (scriptContentLines[i].contains("false")) {
                dataGeneratorSettings.startIspSimulator = false;
            }
        }
        else if(scriptContentLines[i].contains("default[:ipgwtg_ipAddress]")) {
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                dataGeneratorSettings.ipgwtg_IP_Address = quoteRegExp.capturedTexts()[0].remove("\"");
            }
        }
        else if(scriptContentLines[i].contains("default[:ipgwtg_inband_signaling]")) {
            if(scriptContentLines[i].contains("true")) {
                dataGeneratorSettings.ipgwtgInbandSignaling = true;
            } else if (scriptContentLines[i].contains("false")) {
                dataGeneratorSettings.ipgwtgInbandSignaling = false;
            }
        }
        else if(scriptContentLines[i].contains("default[:ipgwtg_ftp_sender_connect_put]")) {
            if(scriptContentLines[i].contains("true")) {
                dataGeneratorSettings.ipgwtgFtpSenderConnectPut = true;
            } else {
                dataGeneratorSettings.ipgwtgFtpSenderConnectPut = false;
            }
        }
    }
    return dataGeneratorSettings;
}
SgwSettings ScriptParserManager::getSgwSettings(const QStringList scriptContentLines){

    SgwSettings sgwSettings;

    for (int i = 0;i<scriptContentLines.size();i++)  {
        if(scriptContentLines[i].contains("default[:sgw_names]")) {
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                sgwSettings.name = quoteRegExp.capturedTexts()[0].remove("\"");
            }
        }
        else if (scriptContentLines[i].contains("default[:sgw_ipAddresses]")) {
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                sgwSettings.ipAdress = quoteRegExp.capturedTexts()[0].remove("\"");
            }
        }
        else if (scriptContentLines[i].contains("default[:apn_lists]")) {
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                sgwSettings.apnList=quoteRegExp.capturedTexts()[0].remove("\"");
            }
        }
        else if (scriptContentLines[i].contains("default[:sgw_LDIs]")) {
            QRegExp numberRegExp("[0-9]+");
            if (numberRegExp.indexIn(scriptContentLines[i])>-1){
                sgwSettings.ldi = numberRegExp.capturedTexts()[0].toInt();
            }
        }
        else if (scriptContentLines[i].contains("default[:core_network_gateway]")) {
            if (scriptContentLines[i].contains("true")){
                sgwSettings.coreNetworkGateway=true;
            }
            else{
                sgwSettings.coreNetworkGateway=false;
            }
        }
    }
    return sgwSettings;
}

UCToolSettings ScriptParserManager::getUCToolSettingsFromScript(const QStringList scriptContentLines)
{
    UCToolSettings ucToolSettings;

    for (int i = 0;i<scriptContentLines.size();i++)  {
        if(scriptContentLines[i].contains("default[:uctool_ip]")) {
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                ucToolSettings.ucToolIP = quoteRegExp.capturedTexts()[0];
                ucToolSettings.ucToolIP.remove("\"");
                ucToolSettings.ucToolIP.remove("{");
                ucToolSettings.ucToolIP.remove("}");
            }
        }
        else if(scriptContentLines[i].contains("default[:uctool_cIds]")) {
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                ucToolSettings.ucToolCIds = quoteRegExp.capturedTexts()[0];
                ucToolSettings.ucToolCIds.remove("\"");
                ucToolSettings.ucToolCIds.remove("{");
                ucToolSettings.ucToolCIds.remove("}");
            }
        }
        else if(scriptContentLines[i].contains("default[:uctool_service_ip]")) {
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                ucToolSettings.ucToolServiceIp = quoteRegExp.capturedTexts()[0];
                ucToolSettings.ucToolServiceIp.remove("\"");
                ucToolSettings.ucToolServiceIp.remove("}");
                ucToolSettings.ucToolServiceIp.remove("{");
            }
        }
    }
    return ucToolSettings;
}

ChannelModelSettings ScriptParserManager::getChannelModelSettingsFromScript(const QStringList content) {

    ChannelModelSettings settings;

    for (int i = 0;i<content.size();i++) {
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
    }

    return settings;

}
MmeSettings ScriptParserManager::getMmeSettings(const QStringList scriptContentLines){

    MmeSettings mmeSettings;

    int len;
    for (int i=0;i<scriptContentLines.size();i++) {
        if (scriptContentLines[i].contains("default[:mme_names] =")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.lastIndexIn(scriptContentLines[i])>-1){
                mmeSettings.names = quoteRegExp.capturedTexts();
            }
            for (QString &name:mmeSettings.names){
                name.remove('"');
            }
        }
        else if (scriptContentLines[i].contains("default[:simulate_core] = ")){
            mmeSettings.simulatedCoreNetwork = scriptContentLines[i].contains("true");
        }
        else if (scriptContentLines[i].contains("default[:mme_tais] = ")){
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            mmeSettings.tais = scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len);
        }
        else if (scriptContentLines[i].contains("default[:mmes] = ")){
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            mmeSettings.numberOfMme = QString(scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len)).toInt();
        }
        else if (scriptContentLines[i].contains("default[:mme_s1ap_uris] = ")){
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
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
    }

    return mmeSettings;
}
PagingSettings ScriptParserManager::getPagingSettings(const QStringList scriptContentLines){

    PagingSettings pagingSettings;

    int len;
    for (int i = 0;i<scriptContentLines.size();i++)  {
        if (scriptContentLines[i].contains("[:generate_pagings]")){
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
            if (scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len)=="false"){
                pagingSettings.isUsedInConfiguration = false;

            }
            else if (scriptContentLines[i].mid(scriptContentLines[i].indexOf("[\"")+2,len)=="true"){
                pagingSettings.isUsedInConfiguration = true;
            }
        }
        else if (scriptContentLines[i].contains("[:generators]")){
            len = (scriptContentLines[i].indexOf("\"]"))-(scriptContentLines[i].indexOf("[\"")+2);
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
            if (scriptContentLines[i].contains("true")){
                pagingSettings.bundlePaging=true;
            }
            else if (scriptContentLines[i].contains("false")){
                pagingSettings.bundlePaging = false;
            }
        }
    }
    return pagingSettings;


}

UBSimSettings ScriptParserManager::getUBSimSettings(const QStringList scriptContentLines){

    UBSimSettings ubSimSettings;

    for (int i = 0;i<scriptContentLines.size();i++)  {
        if (scriptContentLines[i].contains("[:ueTypesDir]")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                ubSimSettings.ueTypesDir = quoteRegExp.capturedTexts()[0];
                ubSimSettings.ueTypesDir.remove("\"");
            }
        }
        else if (scriptContentLines[i].contains("[:csTrafficModelsDir]")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                ubSimSettings.csTrafficModelsDir = quoteRegExp.capturedTexts()[0];
                ubSimSettings.csTrafficModelsDir.remove("\"");
                ubSimSettings.csTrafficModelsDir.remove("\'");
            }
        }
        else if (scriptContentLines[i].contains("[:psTrafficModelsDir]")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                ubSimSettings.psTrafficModelsDir = quoteRegExp.capturedTexts()[0];
                ubSimSettings.psTrafficModelsDir.remove("\"");
            }
        }
        else if (scriptContentLines[i].contains("[:mobilityModelsDir]")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                ubSimSettings.mobilityModelsDir = quoteRegExp.capturedTexts()[0];
                ubSimSettings.mobilityModelsDir.remove("\"");
            }
        }
        else if (scriptContentLines[i].contains("[:visualization]")){
            if (scriptContentLines[i].contains("true")){
                ubSimSettings.UBSimGui = true;
            }
            else if (scriptContentLines[i].contains("false")){
                ubSimSettings.UBSimGui = false;
            }
        }
        else if (scriptContentLines[i].contains("[:ubsim_patches]")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i])>-1){
                ubSimSettings.ubsim_patches = quoteRegExp.capturedTexts();
            }
            for (QString patch:ubSimSettings.ubsim_patches){
                patch.remove("\"");
            }
        }
    }
    return ubSimSettings;
}
GeneralConfigurationParameters ScriptParserManager::getGeneralConfigurationSettings(const QStringList scriptContentLines){
    GeneralConfigurationParameters generalConfiguration;

    for (int i = 0;i<scriptContentLines.size();i++) {
        if (scriptContentLines[i].contains("log_dir =")){
            QRegExp regexp;
            if (scriptContentLines[i].contains("#")) {
                regexp.setPattern("= .*#");
            }
            else {
                regexp.setPattern("= .*");
            }
            if (regexp.indexIn(scriptContentLines[i])>-1){
                generalConfiguration.logDir = regexp.capturedTexts()[0];
            }
        }
        else if (scriptContentLines[i].contains("[:coreParameters]")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i]) > -1){
                generalConfiguration.coreParameters = quoteRegExp.capturedTexts()[0];
            }
        }
        else if (scriptContentLines[i].contains("[:jvm_parameters]")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i]) > -1){
                generalConfiguration.jvmParameters = quoteRegExp.capturedTexts()[0];
            }
        }
        else if (scriptContentLines[i].contains("[:logger_handlersSet]")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i]) > -1){
                generalConfiguration.loggerHandlerSet = quoteRegExp.capturedTexts()[0];
            }
        }
        else if (scriptContentLines[i].contains("[:logger_file_count]")){
            QRegExp numberRegExp("[0-9]+");
            if (numberRegExp.indexIn(scriptContentLines[i]) > -1){
                generalConfiguration.loggerFileCount = numberRegExp.capturedTexts()[0].toInt();
            }
        }
        else if (scriptContentLines[i].contains("[:logger_file_sizeLimit]")){
            QRegExp regExp("[0-9]+..[0-9]+");
            if (regExp.indexIn(scriptContentLines[i]) > -1){
                generalConfiguration.loggerFileSizeLimit.first = regExp.capturedTexts()[0].split("**")[0].toInt();
                generalConfiguration.loggerFileSizeLimit.second = regExp.capturedTexts()[0].split("**")[1].toInt();
            }
        }
        else if (scriptContentLines[i].contains("[:logger_file_gzipEnabled]")){
            if (scriptContentLines[i].contains("true")){
                generalConfiguration.loggerFileGzipEnabled = true;
            }
            else if (scriptContentLines[i].contains("false")){
                generalConfiguration.loggerFileGzipEnabled = false;
            }
        }
    }

    return generalConfiguration;
}

MapRange ScriptParserManager::getMapRange(const QStringList scriptContentLines) {
    MapRange mapRange;

    for (int i = 0;i<scriptContentLines.size();i++) {
        if (scriptContentLines[i].contains("default[:southBoundMap]")){
            QRegExp numberRegExp("[0-9]+");
            if (numberRegExp.indexIn(scriptContentLines[i]) > -1){
                mapRange.southBoundMap = numberRegExp.capturedTexts()[0].toInt();
            }
        }
        else if(scriptContentLines[i].contains("default[:northBoundMap]")){
            QRegExp numberRegExp("[0-9]+");
            if (numberRegExp.indexIn(scriptContentLines[i]) > -1){
                mapRange.northBoundMap = numberRegExp.capturedTexts()[0].toInt();
            }
        }
        else if(scriptContentLines[i].contains("default[:westBoundMap]")){
            QRegExp numberRegExp("[0-9]+");
            if (numberRegExp.indexIn(scriptContentLines[i]) > -1){
                mapRange.westBoundMap = numberRegExp.capturedTexts()[0].toInt();
            }
        }
        else if(scriptContentLines[i].contains("default[:eastBoundMap]")){
            QRegExp numberRegExp("[0-9]+");
            if (numberRegExp.indexIn(scriptContentLines[i]) > -1){
                mapRange.eastBoundMap = numberRegExp.capturedTexts()[0].toInt();
            }
        }
    }
    return mapRange;
}

UeParameters ScriptParserManager::getUeParameters(const QStringList &scriptContentLines)
{
    UeParameters ueParameters;

    for (int i = 0;i<scriptContentLines.size();i++) {
        if (scriptContentLines[i].contains("[:start_ue_component]")){
            ueParameters.startUeComponent = scriptContentLines[i].contains("true");
        }
        else if (scriptContentLines[i].contains("[:name]")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i]) > -1){
                ueParameters.name = quoteRegExp.capturedTexts()[0];
                ueParameters.name.remove('"');
            }
        }
        else if (scriptContentLines[i].contains("[:l1l2_managers]")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i]) > -1){
                ueParameters.managers = quoteRegExp.capturedTexts()[0];
                ueParameters.managers.remove('"');
            }
        }
        else if (scriptContentLines[i].contains("[:rrc_pluginFilterPath]")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.indexIn(scriptContentLines[i]) > -1){
                ueParameters.pluginFilterPath = quoteRegExp.capturedTexts()[0];
                ueParameters.pluginFilterPath.remove('"');
            }
        }
        else if (scriptContentLines[i].contains("[:ue_network_capability]")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.lastIndexIn(scriptContentLines[i]) > -1){
                ueParameters.ueNetworkCapability =  quoteRegExp.capturedTexts()[0];
                ueParameters.ueNetworkCapability.remove('"');
            }
        }
        else if (scriptContentLines[i].contains("[:ue_keyDerivationAlgorithm]")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.lastIndexIn(scriptContentLines[i]) > -1){
                ueParameters.ueKeyDerivationAlgorithm =  quoteRegExp.capturedTexts()[0];
                ueParameters.ueKeyDerivationAlgorithm.remove('"');
            }
        }

        else if (scriptContentLines[i].contains("default[:ue_key]")){
            QRegExp quoteRegExp("\".*\"");
            QRegExp commentRegExp("#");
            int count=0;
            if (commentRegExp.indexIn(scriptContentLines[i]) > quoteRegExp.indexIn(scriptContentLines[i])){
                ueParameters.ueKey = quoteRegExp.capturedTexts()[count];
                ueParameters.ueKey.remove('"');
            }
            else{
                count++;
            }
        }
        else if (scriptContentLines[i].contains("[:ue_op]")){
            QRegExp quoteRegExp("\".*\"");
            if (quoteRegExp.lastIndexIn(scriptContentLines[i]) > -1){
                ueParameters.ueOp =  quoteRegExp.capturedTexts()[0];
                ueParameters.ueOp.remove('"');
            }
        }
    }
    return ueParameters;
}
QString ScriptParserManager::GenerateParametersQString(Project &project){
    QString outputTextStream;

    /* ***************** HEADER ***************** */
    QString header = "# LTEsum Parameter Module \n\
# \n\
# Copyright Ericsson AB 2013. \n\
# \n\
# This example shows how to setup and retrieve configuration parameters for LTEsum. \n\
# \n\
# \n\
# Module that contains functions for retrieving configuration values for the LTEsum components. \n\
# \n\
# Copy this file to your home directory with a different name and edit the copy \n\
# to match your environment. \n\
# \n\
# Make sure that your version of parameters.rb is used by one of the following methods: \n\
# \n\
#   Start ltesim_cli with the parameter -params <file> \n\
# \n\
#   Start ltesim_cli in the same folder as your file %parameters.rb \n\
# \n\
#   Add the folder with parameters.rb to the ltesim_cli search path, using the -p parameter \n\
# \n\
#   Load your parameters.rb file in each test script (or in the ltesim_cli) by adding \n\
#   \"LteSimCli.rerequire \'<path to and including parameters.rb>\'\" in the beginning of the script. \n\
# \n\
require \'etc\'\n\
module Parameters \n\
\t# \n\
\t# Retrieve general configuration parameters. \n\
\t#\n";

    // OUTPUT
    outputTextStream.append(header);
    outputTextStream.append(project.generalConfiguration.ParseToScript());
    outputTextStream.append(project.mmeSettings.ParseToScript());
    outputTextStream.append(project.pagingSettings.ParseToScript());
    outputTextStream.append(project.sgwSettings.ParseToScript());
    outputTextStream.append(UeParametersParser::ParseToScript(project.ucToolSettings,project.ueParameters));
    outputTextStream.append(MapParser::ParseMap(project.cellsInfo,project.mapRange,project.handovers,project.ubSimSettings,project.dataGeneratorSettings));
    outputTextStream.append(project.ubSimSettings.ParseToScript());
    outputTextStream.append(project.channelModelSettings.ParseToScript());
    outputTextStream.append("end");
    return outputTextStream;
}
