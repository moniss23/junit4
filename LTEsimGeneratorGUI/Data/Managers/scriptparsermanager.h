#ifndef SCRIPTPARSERMANAGER_H
#define SCRIPTPARSERMANAGER_H

#include <QString>
#include <QVector>

#include "Data/project.h"

/**
 * @brief The ScriptParserManager class is responsible for parsing scripts for our application
 */
class ScriptParserManager
{
public:
    ScriptParserManager();
    ~ScriptParserManager();

    // Methods below try to fetch specified object's fields from given QStringList
    QVector<Cell> getCellsFromScript(const QStringList scriptContent);
    QVector<Center> getCentersFromScript(const QStringList scriptContent);
    QVector<Handover> getHandoversFromScript(const QStringList scriptContent);
    SgwSettings getSgwSettings(const QStringList scriptContentLines);
    MmeSettings getMmeSettings(const QStringList scriptContentLines);
    UeParameters getUeParameters(const QStringList &scriptContentLines);
    UBSimSettings getUBSimSettings(const QStringList scriptContentLines);
    PagingSettings getPagingSettings(const QStringList scriptContentLines);
    MapRange getMapRange(const QStringList scriptContentLines, Project &project);
    UCToolSettings getUCToolSettingsFromScript(const QStringList scriptContent);
    ChannelModelSettings getChannelModelSettingsFromScript(const QStringList content);
    DataGeneratorSettings getDataGeneratorSettingsFromScript(const QStringList scriptContentLines);
    GeneralConfigurationParameters getGeneralConfigurationSettings(const QStringList scriptContentLines);

    /**
     * @brief matchCellsToCenters matches each Cell object to its Center (matching by names)
     * @param cells
     * @param centers
     * @return vector of pairs <Cell, Center>
     */
    QVector<QPair<Cell, Center>> matchCellsToCenters(auto cells, auto centers);

    /**
     * @brief GenerateParametersQString
     * @param project
     * @return Parameters file content (as QString object)
     */
    QString GenerateParametersQString(Project &project);

    /**
     * @brief parseFromScript goes through script, parses each found section and saves it to a project
     * @param scriptContent
     * @param project
     */
    void parseFromScript(const QString &scriptContent, Project &project);

    /**
     * @brief findRegexInText
     * @param pattern
     * @param text
     * @param pos
     * @return string catched by reg. exp. pattern (its pos-th item) in text
     */
    QString findRegexInText(QString pattern, const QString &text, int pos);

    /********************
     * DATA VALIDATION  *
     ********************/
    /**
     * @brief validateData executes validation methods in order to check if parsed script is complete
     * @param project
     * @return error message informing which sections could not be found
     */
    QString validateData(const Project &project);

    bool validateCells(const Project &project);
    bool validateHandovers(const Project &project);
    bool validateMapRange(const Project &project);

};

#endif // SCRIPTPARSERMANAGER_H
