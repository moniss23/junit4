#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "Data/datasystem.h"

#include "UISystem/Windows/addProjectWindow.h"
#include "UISystem/Windows/importprojectwindow.h"
#include "UISystem/Windows/settings.h"
#include "UISystem/Windows/renamedialog.h"
#include "UISystem/DataForms/sgwform.h"
#include "UISystem/DataForms/mmeform.h"
#include "UISystem/DataForms/channelmodelform.h"
#include "UISystem/DataForms/ubsimform.h"
#include "UISystem/DataForms/ueform.h"
#include "UISystem/DataForms/maprangeform.h"
#include "UISystem/DataForms/custommodelslistform.h"
#include "UISystem/Widgets/mapview.h"
#include "UISystem/Windows/newmapwindow.h"
#include "UISystem/Windows/trafficmap.h"
#include "UISystem/DataForms/pingform.h"
#include "UISystem/DataForms/generalconfigurationform.h"
#include "UISystem/DataForms/ftpdlform.h"
#include "UISystem/DataForms/ftpulform.h"
#include "UISystem/DataForms/pagingform.h"
#include "Data/ProjectSettings/pagingsettings.h"
#include "UISystem/DataForms/tuningTrafficManager.h"
#include "UISystem/DataForms/streamdlform.h"
#include "UISystem/DataForms/streamulform.h"
#include "UISystem/DataForms/syncedpingform.h"
#include "UISystem/DataForms/servicereqform.h"
#include "UISystem/DataForms/voipform.h"
#include "UISystem/DataForms/statisticsForm.h"
#include "UISystem/Windows/pagingrate.h"

class ProjectManagement;
class ParametersWindow;
class IpexForm;
class UCtoolForm;
class UeParametersForm;
class TimeForm;

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
    void spawnWindow_Ipex(const QString& projectName,bool enable);
    void spawnWindow_ucTool(const QString &projectName,bool enable);
    void spawnWindow_ParamMap(const QString &projectName);
    void spawnWindow_Sgw(const QString& projectName,bool enable);
    void spawnWindow_Mme(const QString& projectName,bool enable);
    void spawnWindow_Paging(const QString &projectName,bool enable);
    void spawnWindow_ChannelModel(const QString& projectName,bool enable);
    void spawnWindow_UBSim(const QString& projectName,bool enable);
    void spawnWindow_Ue(const QString &projectName,bool enable);

    void spawnWindow_MapRange(const QString& projectName);
    void spawnWindow_TrafficMap(const QString &projectName, const QString &trafficName);
    void spawnWindow_Statistics(const QString &projectName, const QString &trafficName);
    void spawnWindow_CustomModels(const QString &projectName, const QString &trafficName);
    void spawnWindow_PingForm(const QString &projectName, const QString &trafficName, const int &index);
    void spawnWindow_GeneralConfiguration(const QString &projectName,bool enable);
    void spawnWindow_VoipForm(const QString &projectName, const QString &trafficName, const int &index);
    void spawnWindow_FtpDlForm(const QString &projectName, const QString &trafficName, const int &index);
    void spawnWindow_FtpUlForm(const QString &projectName, const QString &trafficName, const int &index);
    void spawnWindow_TuningTraffic(const QString &projectName, const QString &trafficName);
    void restoreTuningTrafficData(const QString &projectName, const QString &trafficName); //something wierd is happening and it does not work
    void spawnWindow_StreamDlForm(const QString &projectName, const QString &trafficName, const int &index);
    void spawnWindow_StreamUlForm(const QString &projectName, const QString &trafficName, const int &index);
    void spawnWindow_SyncedPingForm(const QString &projectName, const QString &trafficName, const int &index);
    void spawnWindow_ServiceReqForm(const QString &projectName, const QString &trafficName, const int &index);
    void spawnCustomModelSubclassWindowToModify(const QString &projectName, const QString &trafficName, const QString &item, const int &index, const int &CMindex);
    void spawnWindow_UeParams(const QString &ueDataName, const QString& projectName, const QString& trafficName);
    void spawnWindow_PagingRate(const QString &projectName);
    void spawnWindow_TimeForm(const QString &projectName, const QString &trafficName);

signals:
    void spawnSettingsWindowForProject(const AppGlobalData& data,const Project& project = Project());
    void spawnWindow_ParamMap();
    void spawnWindow_Sgw(const SgwSettings& sgwSettings, const QString &projectName, bool enable);
    void spawnWindow_Mme(const MmeSettings& mmeSettings, const QString &projectName, bool enable);
    void spawnWindow_Paging(const PagingSettings &paging, const QString &projectName, bool enable);
    void spawnWindow_ChannelModel(const ChannelModelSettings& channelModelSettings, const QString& projectName,bool enable);
    void spawnWindow_UBSim(const UBSimSettings &ubSimSettings,const UeParameters &UeParameters, const QString &projectName,bool enable);
    void spawnWindow_Ue(const UeParameters &ueParamaters, const QString &projectName, bool enable);
    void spawnWindow_MapWindow(const Project &project);
    void spawnWindow_MapRange(const MapRange& mapRange, const QString &projectName);
    void spawnWindow_TrafficMap(const Project &project, TrafficFileData *trafficFileData);
    void spawnWindow_Statistics(const QString &projectName, const QString &trafficName, const StatisticsData &statisticsData);
    void spawnWindow_TuningTraffic(const QString &projectName, const QString &trafficName, const std::tuple<QStringList,QStringList,QStringList> &tuningTrafficStringLists, const TuningTrafficData tuningTrafficData);
    void restoreTuningTrafficData(const TuningTrafficData &tuningTrafficData); //something wierd is happening and it does not work
    void spawnWindow_customModels(const QString &projectName, const QString &trafficName, bool *cmUsed);
    void spawnWindow_PingForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed, const int &pingIndex = 0, const Ping &ping = Ping());
    void spawnWindow_VoipForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed, const int &voipIndex = 0, const Voip &voip = Voip());
    void spawnWindow_GeneralConfiguration(const GeneralConfigurationParameters &generalConfiguration, const QString &projectname,bool enable);  
    void spawnWindow_FtpDlForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed, const int &ftpDlIndex = 0, const FtpDl &ftpDl = FtpDl());
    void spawnWindow_FtpUlForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed, const int &ftpUlIndex = 0, const FtpUl &ftpUl = FtpUl());
    void spawnWindow_StreamDlForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed, const int &streamDlIndex = 0, const StreamDl &streamDl = StreamDl());
    void spawnWindow_StreamUlForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed, const int &streamUlIndex = 0, const StreamUl &streamUl = StreamUl());
    void spawnWindow_SyncedPingForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed, const int &syncedPingIndex = 0, const SyncedPing &syncedPing = SyncedPing());
    void spawnWindow_ServiceReqForm(const QString &projectName, const QString &trafficName, const int &index, bool * qciUsed, const int &serviceReqIndex = 0, const ServiceReq &serviceReq = ServiceReq());
    void spawnWindow_PagingRate(const QString &projeName,QStringList generators,QVector<int> rates);
private:
    void createFirstWinow();
    void bindProjectManagementWindow(ProjectManagement *projectMngtWnd);
    void bindProjectOvierviewWindow(ParametersWindow   *overviewWindow);

    Project* findProjectByName(const QString &projectName);

private:
    DataSystem             *dataSystem;
    ProjectManagement      *projectUi;
    ImportProjectWindow     importProject;
    ParametersWindow       *paramWindow;
    AddProjectWindow        addProjectWindow;
    Settings                settingsWindow;
    RenameDialog            renameDialog;
    IpexForm               *ipexForm;
    UCtoolForm             *ucToolForm;
    SgwForm                 sgwForm;
    MmeForm                 mmeForm;
    ChannelModelForm        channelModelForm;
    UBsimForm               ubSimForm;
    MapRangeForm            mapRangeForm;
    NewMapWindow            newMapWindow;
    TrafficMap              trafficMap;
    CustomModelsListForm    customModelsListForm;
    PingForm                pingForm;
    GeneralConfiguration    generalConfiguration;
    VoipForm                voipForm;
    FtpDlForm               ftpDlForm;
    FtpUlForm               ftpUlForm;
    TuningTrafficManager    tuningTrafficManager;
    StreamDlForm            streamDlForm;
    StreamUlForm            streamUlForm;
    SyncedPingForm          syncedPingForm;
    ServiceReqForm          serviceReqForm;
    PagingForm              pagingForm;
    StatisticsForm          statisticsForm;
    UeForm                  ueForm;
    UeParametersForm       *ueParametersForm;
    PagingRate              pagingRate;
    TimeForm               *timeForm;
};

#endif // UISYSTEM_H
