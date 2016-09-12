#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "Data/datasystem.h"

#include "UISystem/Windows/addProjectWindow.h"
#include "UISystem/Windows/projectmanagement.h"
#include "UISystem/Windows/importprojectwindow.h"
#include "UISystem/Windows/parameterswindow.h"
#include "UISystem/Windows/settings.h"
#include "UISystem/Windows/renamedialog.h"

#include "UISystem/DataForms/ipexform.h"
#include "UISystem/DataForms/uctoolform.h"
#include "UISystem/DataForms/sgwform.h"
#include "UISystem/DataForms/mmeform.h"
#include "UISystem/DataForms/channelmodelform.h"
#include "UISystem/DataForms/ubsimform.h"
#include "UISystem/DataForms/maprangeform.h"
#include "UISystem/DataForms/custommodelslistform.h"
#include "UISystem/Widgets/mapview.h"
#include "UISystem/Windows/newmapwindow.h"
#include "UISystem/Windows/trafficmap.h"
#include "Maps/Traffic/Statistics/statisticsManager.h"
#include "UISystem/DataForms/pingform.h"
#include "UISystem/DataForms/generalconfigurationform.h"
#include "UISystem/DataForms/voipform.h"
#include "UISystem/DataForms/ftpdlform.h"
#include "UISystem/DataForms/ftpulform.h"
#include "Maps/Traffic/Tuning/tuningTrafficManager.h"
#include "UISystem/DataForms/streamdlform.h"
#include "UISystem/DataForms/streamulform.h"
#include "UISystem/DataForms/syncedpingform.h"

class UISystem : public QObject
{

    Q_OBJECT

public:
    UISystem(DataSystem *data);
    ~UISystem();

    void bindingObjects();

public slots:
    void initialiseSettingsWindowSpawn(const QString& projectName = QString());
    void showErrorWindow(const QString& errorDescription);
    void spawnWindow_OpenProject(const QString& projectName);
    void spawnWindow_Ipex(const QString& projectName);
    void spawnWindow_ucTool(const QString &projectName);
    void spawnWindow_ParamMap(const QString &projectName);
    void spawnWindow_Sgw(const QString& projectName);
    void spawnWindow_Mme(const QString& projectName);
    void spawnWindow_ChannelModel(const QString& projectName);
    void spawnWindow_UBSim(const QString& projectName);
    void spawnWindow_MapView(const QString& projectName);
    void spawnWindow_MapRange(const QString& projectName);
    void spawnWindow_TrafficMap(const QString &projectName, const QString &trafficName);
    void spawnWindow_Statistics(const QString &projectName, const QString &trafficName);
    void spawnWindow_CustomModels(const QString &projectName, const QString &trafficName);
    void spawnWindow_PingForm(const QString &projectName, const QString &trafficName, const int &index);
    void spawnWindow_GeneralConfiguration(const QString &projectName);
    void spawnWindow_VoipForm(const QString &projectName, const QString &trafficName, const int &index);
    void spawnWindow_FtpDlForm(const QString &projectName, const QString &trafficName, const int &index);
    void spawnWindow_FtpUlForm(const QString &projectName, const QString &trafficName, const int &index);
    void spawnWindow_TuningTraffic(const QString &projectName, const QString &trafficName);
    void spawnWindow_StreamDlForm(const QString &projectName, const QString &trafficName, const int &index);
    void spawnWindow_StreamUlForm(const QString &projectName, const QString &trafficName, const int &index);
    void spawnWindow_SyncedPingForm(const QString &projectName, const QString &trafficName, const int &index);

signals:
    void spawnSettingsWindowForProject(const AppGlobalData& data,const Project& project = Project());
    void spawnWindow_OpenProject(const Project& project);
    void spawnWindow_Ipex(const DataGeneratorSettings& dataGeneratorSettings, const QString &projectName);
    void spawnWindow_ucTool(const UCToolSettings &ucToolSettings, const QString &projectName);
    void spawnWindow_ParamMap();
    void spawnWindow_Sgw(const SgwSettings& sgwSettings, const QString &projectName);
    void spawnWindow_Mme(const MmeSettings& mmeSettings,const PagingSettings& pagingSettings, const QString &projectName);
    void spawnWindow_ChannelModel(const ChannelModelSettings& channelModelSettings, const QString& projectName);
    void spawnWindow_UBSim(const UBSimSettings &ubSimSettings,const UeParameters &UeParameters, const QString &projectName);
    void spawnWindow_MapView(const Project &project);
    void spawnWindow_MapWindow(const Project &project);
    void spawnWindow_MapRange(const MapRange& mapRange, const QString &projectName);
    void spawnWindow_TrafficMap(const Project &project, const TrafficFileData &trafficFileData);
    void spawnWindow_Statistics(const QString &projectName, const QString &trafficName, const StatisticsData &statisticsData);
    void spawnWindow_customModels(const QString &projectName, const QString &trafficName, bool *cmUsed);
    void spawnWindow_PingForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed);
    void spawnWindow_GeneralConfiguration(const GeneralConfigurationParameters &generalConfiguration, const QString &projectname);
    void spawnWindow_VoipForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed);
    void spawnWindow_FtpDlForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed);
    void spawnWindow_FtpUlForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed);
    void spawnWindow_tuningTraffic(const QString &projectName, const QString &trafficName);
    void spawnWindow_StreamDlForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed);
    void spawnWindow_StreamUlForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed);
    void spawnWindow_SyncedPingForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed);

private:
    Project* findProjectByName(const QString &projectName);

private:
    DataSystem         *dataSystem;
    ProjectManagement   projectUi;
    ImportProjectWindow importProject;
    ParametersWindow    paramWindow;
    AddProjectWindow    addProjectWindow;
    Settings            settingsWindow;
    RenameDialog        renameDialog;
    IpexForm            ipexForm;
    UCtoolForm          ucToolForm;
    SgwForm             sgwForm;
    MmeForm             mmeForm;
    ChannelModelForm    channelModelForm;
    UBsimForm           ubSimForm;
    MapRangeForm        mapRangeForm;
    NewMapWindow        newMapWindow;
    TrafficMap          trafficMap;
    StatisticsManager statisticsManager;
    CustomModelsListForm customModelsListForm;
    PingForm            pingForm;
    GeneralConfiguration generalConfiguration;
    VoipForm                voipForm;
    FtpDlForm               ftpDlForm;
    FtpUlForm               ftpUlForm;
    TuningTrafficManager tuningTrafficManager;
    StreamDlForm            streamDlForm;
    StreamUlForm            streamUlForm;
    SyncedPingForm          syncedPingForm;
};

#endif // UISYSTEM_H
