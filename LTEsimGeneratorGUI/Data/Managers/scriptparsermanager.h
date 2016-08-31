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
#include "Data/project.h"

class ScriptParserManager
{
public:
    ScriptParserManager();
    ~ScriptParserManager();
    void parseFromScript(const QString &scriptContent, Project &project);

    QVector<Cell> getCellsFromScript(int i, const QStringList scriptContent);
    QVector<Center> getCentersFromScript(int i,const QStringList scriptContent);
    QVector<Handover> getHandoversFromScript(int i, const QStringList scriptContent);

    SgwSettings getSgwSettings(int i, const QStringList scriptContentLines);
    UCToolSettings getUCToolSettingsFromScript(int i, QStringList scriptContent);
    ChannelModelSettings getChannelModelSettingsFromScript(int i, const QStringList content);
    DataGeneratorSettings getDataGeneratorSettingsFromScript(int i, QStringList scriptContentLines);
    MmeSettings getMmeSettings(int i, QStringList scriptContentLines);
    PagingSettings getPagingSettings(int i, QStringList scriptContentLines);
    UBSimSettings getUBSimSettings(int i,QStringList scriptContentLines);
private:
    QString findRegexInText(QString pattern, const QString &text, int pos);
};

#endif // SCRIPTPARSERMANAGER_H
