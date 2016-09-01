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
#include "Data/ProjectSettings/mmesettings.h"
#include "Data/ProjectSettings/pagingsettings.h"
#include "Data/ProjectSettings/ubsimsettings.h"
#include "Data/ProjectSettings/generalconfigurationparameters.h"
#include "Data/project.h"

class ScriptParserManager
{
public:
    ScriptParserManager();
    ~ScriptParserManager();

    void parseFromScript(const QString &scriptContent, Project &project);

    QVector<Cell> getCellsFromScript(const QStringList scriptContent);
    QVector<Center> getCentersFromScript(const QStringList scriptContent);
    QVector<Handover> getHandoversFromScript(const QStringList scriptContent);

    SgwSettings getSgwSettings(const QStringList scriptContentLines);
    UCToolSettings getUCToolSettingsFromScript(const QStringList scriptContent);
    ChannelModelSettings getChannelModelSettingsFromScript(const QStringList content);
    DataGeneratorSettings getDataGeneratorSettingsFromScript(const QStringList scriptContentLines);
    MmeSettings getMmeSettings(const QStringList scriptContentLines);
    PagingSettings getPagingSettings(const QStringList scriptContentLines);
    UBSimSettings getUBSimSettings(const QStringList scriptContentLines);
    GeneralConfigurationParameters getGeneralConfigurationSettings(const QStringList scriptContentLines);
private:
    QVector<QPair<Cell, Center>> matchCellsToCenters(auto cells, auto centers);

    QString findRegexInText(QString pattern, const QString &text, int pos);
};

#endif // SCRIPTPARSERMANAGER_H
