#ifndef SCRIPTPARSERMANAGER_H
#define SCRIPTPARSERMANAGER_H

#include <QString>
#include <QVector>

#include "Data/Objects/cell.h"
#include "Data/Objects/center.h"
#include "Data/Objects/handover.h"
#include "Data/ProjectSettings/datageneratorsettings.h"

class ScriptParserManager
{
public:
    ScriptParserManager();
    ~ScriptParserManager();

    QVector<Cell> getCellsFromScript(const QString &scriptContent);
    QVector<Center> getCentersFromScript(const QString &scriptContent);
    QVector<Handover> getHandoversFromScript(const QString &scriptContent);
    DataGeneratorSettings getDataGeneratorSettingsFromScript(const QString &scriptContent);
};

#endif // SCRIPTPARSERMANAGER_H
