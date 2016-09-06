#ifndef SCRIPTPARSERMANAGER_H
#define SCRIPTPARSERMANAGER_H

#include <QString>
#include <QVector>

#include "Data/project.h"

class ScriptParserManager
{
public:
    ScriptParserManager();
    ~ScriptParserManager();

    void parseFromScript(const QString &scriptContent, Project &project);

    SgwSettings getSgwSettings(const QStringList scriptContentLines);
    UCToolSettings getUCToolSettingsFromScript(const QStringList scriptContent);
    ChannelModelSettings getChannelModelSettingsFromScript(const QStringList content);
    DataGeneratorSettings getDataGeneratorSettingsFromScript(const QStringList scriptContentLines);
    MmeSettings getMmeSettings(const QStringList scriptContentLines);
    PagingSettings getPagingSettings(const QStringList scriptContentLines);
    UBSimSettings getUBSimSettings(const QStringList scriptContentLines);
    GeneralConfigurationParameters getGeneralConfigurationSettings(const QStringList scriptContentLines);
    MapRange getMapRange(const QStringList scriptContentLines);
    UeParameters getUeParameters(const QStringList &scriptContentLines);
    QString GenerateParametersQString(Project &project);

private:
    QVector<Cell> getCellsFromScript(const QStringList scriptContent);
    QVector<Center> getCentersFromScript(const QStringList scriptContent);
    QVector<Handover> getHandoversFromScript(const QStringList scriptContent);
    QVector<QPair<Cell, Center>> matchCellsToCenters(auto cells, auto centers);

    QString findRegexInText(QString pattern, const QString &text, int pos);
};

#endif // SCRIPTPARSERMANAGER_H
