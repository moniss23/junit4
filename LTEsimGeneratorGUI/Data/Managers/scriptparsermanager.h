#ifndef SCRIPTPARSERMANAGER_H
#define SCRIPTPARSERMANAGER_H

#include <QString>
#include <QVector>

#include "Data/Objects/cell.h"
#include "Data/Objects/center.h"
#include "Data/Objects/handover.h"

#include "Data/ProjectSettings/sgwsettings.h"
#include "Data/ProjectSettings/uctoolsettings.h"
#include "Data/ProjectSettings/channelmodelsettings.h"
#include "Data/ProjectSettings/datageneratorsettings.h"

class ScriptParserManager
{
public:
    ScriptParserManager();
    ~ScriptParserManager();

    QVector<Cell> getCellsFromScript(const QString &rbContent);
    QVector<Center> getCentersFromScript(const QString &rbContent);
    QVector<Handover> getHandoversFromScript(const QString &rbContent);


    SgwSettings getSgwSettings(const QString &scriptContent);
    UCToolSettings getUCToolSettingsFromScript(const QString &scriptContent);
    ChannelModelSettings getChannelModelSettingsFromScript(const QString &rbContent);
    DataGeneratorSettings getDataGeneratorSettingsFromScript(const QString &scriptContent);

private:
    QString findRegexInText(QString pattern, const QString &text, int pos);
};

#endif // SCRIPTPARSERMANAGER_H
