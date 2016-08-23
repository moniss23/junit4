#include "scriptparsermanager.h"

ScriptParserManager::ScriptParserManager() {}
ScriptParserManager::~ScriptParserManager() {}

QVector<Cell> ScriptParserManager::getCellsFromScript(const QString &scriptContent) {
    QVector<Cell> cells;
    QStringList scriptContentLines = scriptContent.split('\n');

    for(int i=0; i<scriptContentLines.size(); ++i) {
        if(scriptContentLines[i].contains(":cell => \"")) {           // cell found
            QVector<QString> cellParams(8);
            cellParams[0] = scriptContentLines[i].trimmed();   // :cell
            cellParams[1] = scriptContentLines[i+1].trimmed(); // :site
            cellParams[2] = scriptContentLines[i+2].trimmed(); // :pci
            cellParams[3] = scriptContentLines[i+3].trimmed(); // :position_X
            cellParams[4] = scriptContentLines[i+4].trimmed(); // :position_Y
            cellParams[5] = scriptContentLines[i+5].trimmed(); // :earfcnDl
            cellParams[6] = scriptContentLines[i+6].trimmed(); // :transmitPower
            cellParams[7] = scriptContentLines[i+7].trimmed(); // :ulNoiseAndInterference

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
    QStringList scriptContentLines = scriptContent.split('\n');

    for(int i=0; i<scriptContentLines.size(); ++i) {
        if(scriptContentLines[i].contains(":area => \"Center")) {
            QVector<QString> centerParams(5);
            centerParams[0] = scriptContentLines[i].trimmed();   // :area
            centerParams[1] = scriptContentLines[i+1].trimmed(); // :southBoundary
            centerParams[2] = scriptContentLines[i+2].trimmed(); // :northBoundary
            centerParams[3] = scriptContentLines[i+3].trimmed(); // :westBoundary
            centerParams[4] = scriptContentLines[i+4].trimmed(); // :eastBoundary

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
    QStringList scriptContentLines = scriptContent.split('\n');

    for(int i=0; i<scriptContentLines.size(); ++i) {
        if(scriptContentLines[i].contains(":area => \"Handover")) {
            QVector<QString> handoverParams(5);
            handoverParams[0] = scriptContentLines[i].trimmed();   // :area
            handoverParams[1] = scriptContentLines[i+1].trimmed(); // :southBoundary
            handoverParams[2] = scriptContentLines[i+2].trimmed(); // :northBoundary
            handoverParams[3] = scriptContentLines[i+3].trimmed(); // :westBoundary
            handoverParams[4] = scriptContentLines[i+4].trimmed(); // :eastBoundary


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
