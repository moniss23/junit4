#ifndef DATASYSTEM_H
#define DATASYSTEM_H

#include <QString>
#include <memory>

#include "Data/project.h"
#include "Data/appglobaldata.h"

class ScriptParserManager;
class FileManager;

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
    void refreshMapView(const Project &project, TrafficFileData* trafficFound);
    void currentCustomModelChanged(const CustomModelSettings &customModelsSettings, bool * cmUsed);

public slots:
    void LoadAppData();
    void saveProjectsFile();
    void setGlobalLocationForNewProjects(const QString& location);
    void set_RB_FilesLocationForProject(const QString& projectName, const QString& location);

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
    void updatePagingState (const QString& projectName,bool state);
    void updateSgwState(const QString& projectName,bool state);
    void updateUBSimState(const QString& projectName,bool state);

    void updateMme(const MmeSettings& mmeSettings, QString projectName);
    void updateMapRange (const MapRange& mapRange,QString projectName);
    void updatePaging(const PagingSettings& pagingSettings, QString projectName);

    // Add, remove, update Cells
    void addCell(const QString &projectName);
    void removeCell(const QPair<Cell,Center> &cell, const QString &projectName);
    void updateCell(const QPair<Cell,Center> &cell, const QString &cellName, const QString &projectName);

    // Add, remove, udpate Handovers
    void addHandover(const QString &projectName);
    void removeHandover(const Handover &handover, const QString &projectName);
    void updateHandover(const Handover &handover, const QString &projectName);

    // Add, update UserEquipments (UE)
    void addUe(const QString &projectName, const QString &trafficFileName);
    void updateUe(const QString &projectName, const QString &trafficName, const UEData &ueData);

    //TrafficFileData saving
    void updateStatisticsData(const QString &projectName, const QString &trafficFileName, const StatisticsData &statisticsData);

    //Scripts generation
    void generateParametersScript(Project &project);
    void generateTrafficScript(const Project& project, const int& indexOfFile);

    //Custom models
    void savePingData(const QString &projectName, const QString &trafficName, const int &CMindex, const Ping &ping, const int &pingIndex, const bool &modification);
    void saveVoipData(const QString &projectName, const QString &trafficName, const int &CMindex, const Voip &voip, const int &voipIndex, const bool &modification);
    void saveFtpDlData(const QString &projectName, const QString &trafficName, const int &CMindex, const FtpDl &ftpDl);
    void saveFtpUlData(const QString &projectName, const QString &trafficName, const int &CMindex, const FtpUl &ftpUl);
    void saveStreamDlData(const QString &projectName, const QString &trafficName, const int &CMindex, const StreamDl &streamDl);
    void saveStreamUlData(const QString &projectName, const QString &trafficName, const int &CMindex, const StreamUl &streamUl);
    void saveSyncedPingData(const QString &projectName, const QString &trafficName, const int &CMindex, const SyncedPing &syncedPing);
    void saveServiceReqData(const QString &projectName, const QString &trafficName, const int &CMindex, const ServiceReq &serviceReq);

    void deleteCustomModelItem(const QString &projectName, const QString &trafficName, const QString &item, const int &itemIndex, const int &CMindex);

    void updateCustomModel(const QString &projectName, const QString &trafficName, const int &index);

    void updateProjectOnMapCloseEvent(const QString &projectName);

public:
    QString getDefaultNewProjectDir() const;
    AppGlobalData getAppGlobalData() const;

private:
    bool isProjectNameUsed(QString projectName);

private:
    AppGlobalData                        appGlobalData;

    std::unique_ptr<FileManager>         fileManager;
    std::unique_ptr<ScriptParserManager> scriptParserManager;

    void loadProjectsFile();
    void projectsFileSetup();
    QString getDefaultTrafficFileContent();

    Project* findProjectByName(const QString &projectName);

    QString generateUniqueCellName(Project *project);
    QString generateUniqueHandoverName(Project *project);
    QString generateUniqueTrafficFilename(Project *project);
};

#endif // DATASYSTEM_H
