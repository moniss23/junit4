#ifndef SCRIPTPARSERMANAGER_H
#define SCRIPTPARSERMANAGER_H

#include <QString>
#include <QVector>

#include "Data/project.h"

/**
 * @brief The ScriptParserManager class is responsible for parsing script
 */
class ScriptParserManager
{
public:
    /**
     * @brief ScriptParserManager default constructor and destrucor
     */
    ScriptParserManager();
    ~ScriptParserManager();

    /***********************************************
     *   PUBLIC API
     ***********************************************/
    /**
     * @brief parseFromScript parses from script
     * @param scriptContent QString with full script
     * @param project holds data about the project
     */
    void parseFromScript(const QString &scriptContent, Project &project);
    /**
     * @brief getSgwSettings is parsing SgwSettings from script
     * @param scriptContentLines script content in QStringList
     * @return SgwSettings with data from parsing script
     */
    SgwSettings getSgwSettings(const QStringList scriptContentLines);
    /**
     * @brief getUCToolSettingsFromScript is parsing UCToolSettings from script
     * @param scriptContent script content in QStringList
     * @return UCToolSettings with data from parsing script
     */
    UCToolSettings getUCToolSettingsFromScript(const QStringList scriptContent);
    /**
     * @brief getChannelModelSettingsFromScript is parsing ChannelModelSettings from script
     * @param content script content in QStringList
     * @return ChannelModelSettings with data from parsing script
     */
    ChannelModelSettings getChannelModelSettingsFromScript(const QStringList content);
    /**
     * @brief getDataGeneratorSettingsFromScript is parsing DataGeneratorSettings from script
     * @param scriptContentLines script content in QStringList
     * @return DataGeneratorSettings with data from parsing script
     */
    DataGeneratorSettings getDataGeneratorSettingsFromScript(const QStringList scriptContentLines);
    /**
     * @brief getMmeSettings is parsing MmeSettings from script
     * @param scriptContentLines script content in QStringList
     * @return MmeSettings with data from parsing script
     */
    MmeSettings getMmeSettings(const QStringList scriptContentLines);
    /**
     * @brief getPagingSettings is parsing PagingSettings from script
     * @param scriptContentLines script content in QStringList
     * @return PagingSettings with data from parsing script
     */
    PagingSettings getPagingSettings(const QStringList scriptContentLines);
    /**
     * @brief getUBSimSettings is parsing UBSimSettings from script
     * @param scriptContentLines script content in QStringList
     * @return UBSimSettings with data from parsing script
     */
    UBSimSettings getUBSimSettings(const QStringList scriptContentLines);
    /**
     * @brief getGeneralConfigurationSettings is parsing GeneralConfigurationParameters from script
     * @param scriptContentLines script content in QStringList
     * @return GeneralConfigurationParameters with data from parsing script
     */
    GeneralConfigurationParameters getGeneralConfigurationSettings(const QStringList scriptContentLines);
    /**
     * @brief getMapRange is parsing MapRange from script
     * @param scriptContentLines script content in QStringList
     * @param project holds data about the project
     * @return MapRange with data from parsing script
     */
    MapRange getMapRange(const QStringList scriptContentLines, Project &project);
    /**
     * @brief getUeParameters is parsing UeParameters from script
     * @param scriptContentLines script content in QStringList
     * @return UeParameters with data from parsing script
     */
    UeParameters getUeParameters(const QStringList &scriptContentLines);
    /**
     * @brief GenerateParametersQString is generating parameters.rb
     * @param projectholds data about the project
     * @return QString with parameters.rb content
     */
    QString GenerateParametersQString(Project &project);
    /**
     * @brief validateData is used to validate parsed cells and map range data
     * @param project data about the project
     * @return QString with error output
     */
    QString validateData(const Project &project);

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    /**
     * @brief getCellsFromScript is getting cells data from script
     * @param scriptContent script content in QStringList
     * @return QVector<Cell> - cells data
     */
    QVector<Cell> getCellsFromScript(const QStringList scriptContent);
    /**
     * @brief getCentersFromScript is getting centers data from script
     * @param scriptContent script content in QStringList
     * @return  QVector<Center> - cells data
     */
    QVector<Center> getCentersFromScript(const QStringList scriptContent);
    /**
     * @brief getHandoversFromScript is getting handovers data from script
     * @param scriptContent script content in QStringList
     * @return  QVector<Handover> - cells data
     */
    QVector<Handover> getHandoversFromScript(const QStringList scriptContent);
    /**
     * @brief matchCellsToCenters is matching cells to centers
     * @param cells cells to match
     * @param centers centersto match
     * @return QVector<QPair<Cell, Center>> vector of pairs cells and centers
     */
    QVector<QPair<Cell, Center>> matchCellsToCenters(auto cells, auto centers);

    /**
     * @brief findRegexInText is finding patters in text
     * @param pattern patteres to find
     * @param text text to search pattern in
     * @param pos position to start searching pattern
     * @return QString that contains pattern
     */
    QString findRegexInText(QString pattern, const QString &text, int pos);


    // ******** DATA VALIDATION ********* //
    /**
     * @brief validateCells is used to validate parsed cells
     * @param project data about the project
     * @return bool if data are correct
     */
    bool validateCells(const Project &project);
    /**
     * @brief validateHandovers is used to validate parsed handovers
     * @param project data about the project
     * @return  bool if data are correct
     */
    bool validateHandovers(const Project &project);
    /**
     * @brief validateMapRange is used to validate parsed map range
     * @param project data about the project
     * @return  bool if data are correct
     */
    bool validateMapRange(const Project &project);
    // ******** DATA VALIDATION ********* //

};

#endif // SCRIPTPARSERMANAGER_H
