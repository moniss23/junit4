#ifndef DATASYSTEM_H
#define DATASYSTEM_H

#include <QString>

#include "Data/project.h"

#include "Data/appglobaldata.h"
#include "Data/Managers/filemanager.h"
#include "Data/Managers/scriptparsermanager.h"

class DataSystem : public QObject
{
    Q_OBJECT

public:
    DataSystem();
    ~DataSystem();

    QVector<Project> projects;

signals:
    void currentProjects(const QVector<Project> &projects);
    void currentProjectChanged(const Project &current);
    void errorInData(const QString& errorDescription);
    void returnProject(const Project& project);
    void updateSettingsView(const QString& path);
    void spawnWindow_ProjectMng();
    void update_RB_FilesLocation(const QString& location);
    void refreshMapView(const Project &project);

public slots:

    void LoadAppData();
    void saveProjectsFile();
    void setGlobalLocationForNewProjects(const QString& location);
    void set_RB_FilesLocationForProject(const QString& projectName, const QString& location);

    void findProject(const QString& projectName);
    void createNewProject(const QString &projectName, const QString & directory);
    void deleteProject(const QString);

    void addToProject_TrafficFile(const QString &ProjectName, const QString &fileName);
    void removeFile_TrafficFile(const QString& ProjectName, const QString& fileName);
    void checkAndRenameIfFilenameUnique(const QString &filename, const QString& oldFilename, const QString& projectName);

    void setDefaultTrafficFileContent(const QString &projectName, const QString &trafficName);
    void setDefaultParametersFileContent(const QString &projectName);

    void updateFileContent(const QString& projectName, const QString& fileName, const QString& content);
    void spawnWindow_ProjectManagement();

    void updateDataGeneratorSettings(const DataGeneratorSettings &dataGeneratorSettings, const QString &projectName);
    void updateSgwSettings(const SgwSettings &sgwSettings,const QString &projectName);
    void updateUCToolSettings(const UCToolSettings & ucToolSettings, const QString &projectName);
    void updateChannelModelSettings(const ChannelModelSettings &channelModelSettings, const QString &projectName);
    void updateUBSimSettings(const UBSimSettings &ubSimSettings, const QString &projectName);
    void updateGeneralConfigurationParameters(const GeneralConfigurationParameters &generalConfigurationParameters, const QString &projectName);

    void updateSimulatedCoreNetworkState(const QString& projectName,bool state);
    void updateSimulatedUeState(const QString& projectName,bool state);

    void updateMme(const MmeSettings& mmeSettings, QString projectName);
    void updateMapRange (const MapRange& mapRange,QString projectName);
    void updatePaging(const PagingSettings& pagingSettings, QString projectName);

    void removeHandover(const Handover &handover, const QString &projectName);
    void updateHandover(const Handover &handover, const QString &projectName);
    void removeCell(const QPair<Cell,Center> &cell, const QString &projectName);
    void updateCell(const QPair<Cell,Center> &cell, const QString &projectName);

    //Scripts generation
    void generateParametersScript(Project &project);
    void generateTrafficScript(const Project& project, const int& indexOfFile);

public:
    bool isProjectNameUsed(QString projectName);
    QString getDefaultNewProjectDir() const;
    AppGlobalData getAppGlobalData() const;

private:
    AppGlobalData       appGlobalData;

    FileManager         fileManager;
    ScriptParserManager scriptParserManager;

    void loadProjectsFile();
    void projectsFileSetup();
    QString getDefaultParametersFileContent();
    QString getDefaultTrafficFileContent();

    Project* findProjectByName(const QString &projectName);
    QString generateUniqueTrafficFilename(Project *project);
};

#endif // DATASYSTEM_H
