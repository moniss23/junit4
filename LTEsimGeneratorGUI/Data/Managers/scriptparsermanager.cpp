#include "scriptparsermanager.h"

ScriptParserManager::ScriptParserManager() {}
ScriptParserManager::~ScriptParserManager() {}

QVector<Cell> ScriptParserManager::getCellsFromScript(const QString &scriptContent) {
    (void) scriptContent;
    return QVector<Cell>();
}

QVector<Center> ScriptParserManager::getCentersFromScript(const QString &scriptContent) {
    QVector<Center> centers;
    QStringList scriptContentLines = scriptContent.split('\n');

    for(int i=0; i<scriptContentLines.size(); ++i) {
        if(scriptContentLines[i].contains(":area => \"")) { // center struct found
            QVector<QString> centerParams(5);
            centerParams[0] = scriptContentLines[i].trimmed(); // :area => ...
            centerParams[1] = scriptContentLines[i+1].trimmed(); // :southBoundary => ...
            centerParams[2] = scriptContentLines[i+2].trimmed(); // :northBoundary => ...
            centerParams[3] = scriptContentLines[i+3].trimmed(); // :westBoundary => ...
            centerParams[4] = scriptContentLines[i+4].trimmed(); // :eastBoundary => ...

            for(auto param: centerParams) {
                param = param.split(" ")[2];
                param.remove(QChar('"'));
                param.remove(QChar(','));
            }

            Center center;
            center.setArea(centerParams[0]);
            center.setNorthBoundary(centerParams[1]);
            center.setSouthBoundary(centerParams[2]);
            center.setWestBoundary(centerParams[3]);
            center.setEastBoundary(centerParams[4]);

            centers.append(center);
            i += 5;
        }
    }

    return centers;
}

QVector<Handover> ScriptParserManager::getHandoversFromScript(const QString &scriptContent) {
    (void) scriptContent;
    return QVector<Handover>();
}
