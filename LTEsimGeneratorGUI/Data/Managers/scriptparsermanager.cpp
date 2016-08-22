#include "scriptparsermanager.h"

ScriptParserManager::ScriptParserManager() {}
ScriptParserManager::~ScriptParserManager() {}

QVector<Cell> ScriptParserManager::getCellsFromScript(const QString &scriptContent) {
    (void) scriptContent;
    return QVector<Cell>();
}

QVector<Center> ScriptParserManager::getCentersFromScript(const QString &scriptContent) {
    (void) scriptContent;
    return QVector<Center>();
}

QVector<Handover> ScriptParserManager::getHandoversFromScript(const QString &scriptContent) {
    (void) scriptContent;
    return QVector<Handover>();
}
