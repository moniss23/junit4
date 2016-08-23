#include "scriptparsermanager.h"

#include <QDebug>

ScriptParserManager::ScriptParserManager() {}
ScriptParserManager::~ScriptParserManager() {}

QVector<Cell> ScriptParserManager::getCellsFromScript(const QString &scriptContent) {
    QVector<Cell> cells;
    QString pattern = ":cell => \"";
    QStringList scriptLines = scriptContent.split('\n');

    const int cellParamsLines = 7;
    for(int i=0; i+cellParamsLines<scriptLines.size(); ++i) {
        if(scriptLines[i].contains(pattern) && (!scriptLines.contains("#") or
            (scriptLines[i].indexOf(pattern) < scriptLines[i].indexOf("#"))))
        {
            QVector<QString> cellParams(8);
            for(int j=0; j<cellParams.size(); ++j) {
                cellParams[j] = scriptLines[i+j].trimmed();
            }

            for(auto &&param: cellParams) {
                param = param.split(" ")[2];
                param.remove(QChar('"'));
                param.remove(QChar(','));
            }

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
            i += 8;
        }
    }

    return cells;
}

QVector<Center> ScriptParserManager::getCentersFromScript(const QString &scriptContent) {
    QVector<Center> centers;
    QString pattern = ":area => \"Center";
    QStringList scriptLines = scriptContent.split('\n');

    const int centersParamsLines = 4;
    for(int i=0; i+centersParamsLines<scriptLines.size(); ++i) {
        if(scriptLines[i].contains(pattern) && (!scriptLines.contains("#") or
            (scriptLines[i].indexOf(pattern) < scriptLines[i].indexOf("#"))))
        {
            QVector<QString> centerParams(5);
            for(int j=0; j<centerParams.size(); ++j) {
                centerParams[j] = scriptLines[i+j].trimmed();
            }

            for(auto &&param: centerParams) {
                param = param.split(" ")[2];
                param.remove(QChar('"'));
                param.remove(QChar(','));
            }

            Center center;
            center.setArea(centerParams[0]);
            center.setSouthBoundary(centerParams[1]);
            center.setNorthBoundary(centerParams[2]);
            center.setWestBoundary(centerParams[3]);
            center.setEastBoundary(centerParams[4]);

            centers.append(center);
            i += 5;
        }
    }

    return centers;
}

QVector<Handover> ScriptParserManager::getHandoversFromScript(const QString &scriptContent) {
    QVector<Handover> handovers;
    QString pattern = ":area => \"Handover";
    QStringList scriptLines = scriptContent.split('\n');

    const int hoParamsLines = 4;
    for(int i=0; i+hoParamsLines<scriptLines.size(); ++i) {
        if(scriptLines[i].contains(pattern) && (!scriptLines.contains("#") or
            (scriptLines[i].indexOf(pattern) < scriptLines[i].indexOf("#"))))
        {
            QVector<QString> handoverParams(5);
            for(int j=0; j<handoverParams.size(); ++j) {
                handoverParams[j] = scriptLines[i+j].trimmed();
            }

            for(auto &&param: handoverParams) {
                param = param.split(" ")[2];
                param.remove(QChar('"'));
                param.remove(QChar(','));
            }

            Handover handover;
            handover.setArea(handoverParams[0]);
            handover.setSouthBoundary(handoverParams[1]);
            handover.setNorthBoundary(handoverParams[2]);
            handover.setWestBoundary(handoverParams[3]);
            handover.setEastBoundary(handoverParams[4]);

            handovers.append(handover);
            i += 5;
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
