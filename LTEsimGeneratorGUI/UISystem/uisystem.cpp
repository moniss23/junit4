#include "uisystem.h"
#include <QMessageBox>

#include "UISystem/Windows/projectmanagement.h"
#include "UISystem/Windows/parameterswindow.h"
#include "UISystem/DataForms/ipexform.h"
#include "UISystem/DataForms/voipform.h"
#include "UISystem/DataForms/uctoolform.h"
#include "UISystem/DataForms/ueParametersForm.h"
#include "UISystem/DataForms/timeForm.h"

UISystem::UISystem(DataSystem* data) :
    dataSystem(data),
    projectUi(nullptr),paramWindow(nullptr),ipexForm(nullptr),
    ucToolForm(nullptr), ueParametersForm(nullptr), timeForm(nullptr)
{
    createFirstWinow();

    settingsWindow.setWindowModality(Qt::WindowModal);
    this->bindingObjects();
    dataSystem->LoadAppData();
}

UISystem::~UISystem()
{
    delete ipexForm;
    delete ucToolForm;
    delete paramWindow;
    delete projectUi;
    delete ueParametersForm;
    delete timeForm;
}

void UISystem::createFirstWinow()
{
  projectUi = new ProjectManagement();
  bindProjectManagementWindow(projectUi);
  projectUi->show();
}

void UISystem::bindProjectManagementWindow(ProjectManagement *projectMngtWnd)
{
   //refresh when smth changes
   QObject::connect(dataSystem, SIGNAL(currentProjects(const QVector<Project> &)),
                    projectMngtWnd,   SLOT(updateProjectLists(const QVector<Project>&)));

   QObject::connect(projectMngtWnd,SIGNAL(spawnWindow_OpenProject(QString)),this,SLOT(spawnWindow_OpenProject(QString)));

   //Spawning ProjectManagement after closing ParametersWindow
   QObject::connect(dataSystem,SIGNAL(spawnWindow_ProjectMng()),projectMngtWnd,SLOT(show()));

   // Delete project
   QObject::connect(projectMngtWnd,SIGNAL(deleteProject(QString)),dataSystem,SLOT(deleteProject(QString)));

   // Show settings window
   QObject::connect(projectMngtWnd, SIGNAL(spawnWindow_Settings(QString)), this, SLOT(initialiseSettingsWindowSpawn(QString)));

   // New Projects
   QObject::connect(projectMngtWnd,SIGNAL(spawnWindow_NewProject()), &addProjectWindow, SLOT(exec()));
}

void UISystem::bindProjectOvierviewWindow(ParametersWindow *overviewWindow)
{
    //Spawning ProjectManagement after closing ParametersWindow
    QObject::connect(overviewWindow,SIGNAL(spawnWindow_ProjectMng()),dataSystem,SLOT(spawnWindow_ProjectManagement()));

    //Spawn settings window
    QObject::connect(overviewWindow, SIGNAL(spawnWindow_Settings(QString)), this, SLOT(initialiseSettingsWindowSpawn(QString)));

    //Add traffic file
    QObject::connect(overviewWindow, SIGNAL(AddFile_Traffic(QString,QString)),dataSystem, SLOT(addToProject_TrafficFile(QString,QString)));
    QObject::connect(dataSystem, SIGNAL(currentProjectChanged(Project)),overviewWindow, SLOT(refreshUI(Project)));

    //Rename file
    QObject::connect(overviewWindow,SIGNAL(spawnWindow_RenameFile(QString,QString)),&renameDialog,SLOT(initWindow(QString,QString)));

    //Delete TrafficFile
    QObject::connect(overviewWindow,SIGNAL(removeFile_TrafficFile(QString,QString)),dataSystem,SLOT(removeFile_TrafficFile(QString,QString)));

    //Update file content from filePreview
    QObject::connect(overviewWindow,SIGNAL(updateFileContent(QString,QString,QString)),dataSystem,SLOT(updateFileContent(QString,QString,QString)));

    //Restore default param and traffic files content
    QObject::connect(overviewWindow,SIGNAL(setDefaultParametersFileContent(QString)),dataSystem,SLOT(setDefaultParametersFileContent(QString)));
    QObject::connect(overviewWindow,SIGNAL(setDefaultTrafficFileContent(QString,QString)),dataSystem,SLOT(setDefaultTrafficFileContent(QString,QString)));

    //Open Param Map
    QObject::connect(overviewWindow, SIGNAL(spawnWindow_ParamMap(QString)), this, SLOT(spawnWindow_ParamMap(QString)));

    //Open Traffic Map
    QObject::connect(overviewWindow, SIGNAL(spawnWindow_TrafficMap(QString,QString)), this, SLOT(spawnWindow_TrafficMap(QString,QString)));

    //Generating scripts
    QObject::connect(overviewWindow, SIGNAL(generateParametersScript(Project&)), dataSystem, SLOT(generateParametersScript(Project&)));
    QObject::connect(overviewWindow, SIGNAL(generateTrafficScript(Project,int)), dataSystem, SLOT(generateTrafficScript(Project,int)));
}

void UISystem::bindingObjects()
{
    //Error window
    QObject::connect(dataSystem, SIGNAL(errorInData(QString)),this,SLOT(showErrorWindow(QString)));

    // Settings
    QObject::connect(&settingsWindow, SIGNAL(SetGlobalLocationForNewProjects(QString)), dataSystem, SLOT(setGlobalLocationForNewProjects(QString)));
    QObject::connect(&settingsWindow, SIGNAL(Set_RB_FilesLocationForProject(QString,QString)), dataSystem, SLOT(set_RB_FilesLocationForProject(QString,QString)));
    QObject::connect(this, SIGNAL(spawnSettingsWindowForProject(AppGlobalData,Project)), &settingsWindow, SLOT(ShowForProject(AppGlobalData,Project)));

    // Import Project
    //QObject::connect(&projectUi,SIGNAL(spawnWindow_ImportProject()), &importProject, SLOT(getProjectDirectory()));
    //QObject::connect(&importProject,SIGNAL(selectedProjectDirectory(const QString&)), dataSystem, SLOT(importProject(const QString&)));

    // New Projects
    QObject::connect(&addProjectWindow,SIGNAL(createNewProject(QString,QString)),dataSystem,SLOT(createNewProject(QString,QString)));
    QObject::connect(dataSystem, SIGNAL(currentProjects(QVector<Project>)), &addProjectWindow, SLOT(close()));

    //Rename file
    QObject::connect(dataSystem,SIGNAL(currentProjectChanged(Project)),&renameDialog,SLOT(close()));
    QObject::connect(&renameDialog,SIGNAL(changedFilename(QString,QString,QString)),dataSystem,SLOT(checkAndRenameIfFilenameUnique(QString,QString,QString)));

    //Open Ipex window
    QObject::connect(&newMapWindow, SIGNAL(spawnWindow_Ipex(QString,bool)), this, SLOT(spawnWindow_Ipex(QString,bool)));
    QObject::connect(&trafficMap,SIGNAL(spawnWindow_Ipex(QString,bool)),SLOT(spawnWindow_Ipex(QString,bool)));

    //Open UCTool window
    QObject::connect(&newMapWindow, SIGNAL(spawnWindow_ucTool(QString,bool)), this, SLOT(spawnWindow_ucTool(QString,bool)));
    QObject::connect(&trafficMap,SIGNAL(spawnWindow_UCTool(QString,bool)),this,SLOT(spawnWindow_ucTool(QString,bool)));

    //Open ChannelModel window
    QObject::connect(this, SIGNAL(spawnWindow_ChannelModel(ChannelModelSettings,QString,bool)), &channelModelForm, SLOT(loadAndOpen(ChannelModelSettings,QString,bool)));
    QObject::connect(&newMapWindow, SIGNAL(spawnWindow_ChannelModel(QString,bool)), this, SLOT(spawnWindow_ChannelModel(QString,bool)));
    QObject::connect(&trafficMap,SIGNAL(spawnWindow_ChannelModels(QString,bool)),this,SLOT(spawnWindow_ChannelModel(QString,bool)));

    //Update ChannelModelSettings
    QObject::connect(&channelModelForm, SIGNAL(updateChannelModelSettings(ChannelModelSettings,QString)), dataSystem, SLOT(updateChannelModelSettings(ChannelModelSettings,QString)));

    //Open Sgw window
    QObject::connect(this, SIGNAL(spawnWindow_Sgw(SgwSettings,QString,bool)), &sgwForm, SLOT(loadAndSpawn(SgwSettings,QString,bool)));
    QObject::connect(&newMapWindow, SIGNAL(spawnWindow_Sgw(QString,bool)), this, SLOT(spawnWindow_Sgw(QString,bool)));
    QObject::connect(&trafficMap,SIGNAL(spawnWindow_Sgw(QString,bool)),this,SLOT(spawnWindow_Sgw(QString,bool)));

    //Open Mme window
    QObject::connect(this,SIGNAL(spawnWindow_Mme(MmeSettings,QString,bool)),&mmeForm,SLOT(loadAndSpawn(MmeSettings,QString,bool)));
    QObject::connect(&newMapWindow, SIGNAL(spawnWindow_Mme(QString,bool)), this, SLOT(spawnWindow_Mme(QString,bool)));
    QObject::connect(&trafficMap,SIGNAL(spawnWindow_Mme(QString,bool)),this,SLOT(spawnWindow_Mme(QString,bool)));

    //Open Paging widnow
    QObject::connect(this,SIGNAL(spawnWindow_Paging(PagingSettings,QString,bool)),&pagingForm,SLOT(loadAndSpawn(PagingSettings,QString,bool)));
    QObject::connect(&newMapWindow,SIGNAL(spawnWindow_Paging(QString,bool)),this,SLOT(spawnWindow_Paging(QString,bool)));
    QObject::connect(&trafficMap,SIGNAL(spawnWindow_Paging(QString,bool)),this,SLOT(spawnWindow_Paging(QString,bool)));

    //Update Mme and Paging
    QObject::connect(&mmeForm,SIGNAL(updateMme(MmeSettings, QString)),dataSystem,SLOT(updateMme(MmeSettings,QString)));
    QObject::connect(&pagingForm,SIGNAL(updatePaging(PagingSettings,QString)),dataSystem,SLOT(updatePaging(PagingSettings,QString)));

    //Update Project SgwData
    QObject::connect(&sgwForm,SIGNAL(updateSgw(SgwSettings,QString)),dataSystem,SLOT(updateSgwSettings(SgwSettings,QString)));

    //Open General Configuration
    QObject::connect(this,SIGNAL(spawnWindow_GeneralConfiguration(GeneralConfigurationParameters,QString,bool)),&generalConfiguration,SLOT(loadAndOpen(GeneralConfigurationParameters,QString,bool)));
    QObject::connect(&newMapWindow,SIGNAL(spawnWindow_GeneralConfiguration(QString,bool)),this,SLOT(spawnWindow_GeneralConfiguration(QString,bool)));
    QObject::connect(&trafficMap,SIGNAL(spawnWindow_GeneralSettings(QString,bool)),this,SLOT(spawnWindow_GeneralConfiguration(QString,bool)));

    // Update General Configuration
    QObject::connect(&generalConfiguration,SIGNAL(updateGeneralConfiguration(GeneralConfigurationParameters,QString)),dataSystem,SLOT(updateGeneralConfigurationParameters(GeneralConfigurationParameters,QString)));

    //Open UBSim
    QObject::connect(&newMapWindow, SIGNAL(spawnWindow_UBSim(QString,bool)), this, SLOT(spawnWindow_UBSim(QString,bool)));
    QObject::connect(this, SIGNAL(spawnWindow_UBSim(UBSimSettings,UeParameters,QString,bool )), &ubSimForm, SLOT(loadAndOpen(UBSimSettings,UeParameters,QString,bool)));
    QObject::connect(&trafficMap,SIGNAL(spawnWindow_UBsim(QString,bool)),this,SLOT(spawnWindow_UBSim(QString,bool)));

    //Open Ue
    QObject::connect(&newMapWindow,SIGNAL(spawnWindow_Ue(QString,bool)),this, SLOT(spawnWindow_Ue(QString,bool)));
    QObject::connect(&trafficMap,SIGNAL(spawnWindow_Ue(QString,bool)),this,SLOT(spawnWindow_Ue(QString,bool)));
    QObject::connect(this,SIGNAL(spawnWindow_Ue(UeParameters,QString,bool)),&ueForm,SLOT(loadAndOpen(UeParameters,QString,bool)));

    //Update Ue Parameters
    QObject::connect(&ueForm,SIGNAL(updateUeSettings(UeParameters,QString)),dataSystem,SLOT(updateUeComponent(UeParameters,QString)));

    //Enable/Disable UBSim
    QObject::connect(&ueForm,SIGNAL(enableUBSim(bool)),&ubSimForm,SLOT(disableWindow(bool)));
    QObject::connect(&newMapWindow,SIGNAL(setEnabledUBSim(bool)),&ubSimForm,SLOT(disableWindow(bool)));
    QObject::connect(&trafficMap,SIGNAL(setEnabledUBSim(bool)),&ubSimForm,SLOT(disableWindow(bool)));

    //Update UBsimSettings
    QObject::connect(&ubSimForm, SIGNAL(updateUBSimSettings(UBSimSettings,QString)), dataSystem, SLOT(updateUBSimSettings(UBSimSettings,QString)));

    //Open Map Range
    QObject::connect(&newMapWindow, SIGNAL(spawnWindow_mapRange(QString)), this, SLOT(spawnWindow_MapRange(QString)));
    QObject::connect(this,SIGNAL(spawnWindow_MapRange(MapRange,QString)),&mapRangeForm,SLOT(loadAndSpawn(MapRange,QString)));

    //Update Map Range
    QObject::connect(&mapRangeForm,SIGNAL(updateMapRange(MapRange,QString)),dataSystem,SLOT(updateMapRange(MapRange,QString)));

    //Refresh Map in NewMapWindow/TrafficMap
    QObject::connect(dataSystem, SIGNAL(refreshMapView(Project)), &newMapWindow, SLOT(refreshWindow(Project)));
    QObject::connect(dataSystem, SIGNAL(refreshMapView(Project,TrafficFileData*)), &trafficMap, SLOT(refreshWindow(Project,TrafficFileData*)));

    //Refresh ButtonsColor
    QObject::connect(&ubSimForm,SIGNAL(updateUBSimSettings(UBSimSettings,QString)),&newMapWindow,SLOT(updateButtonsColor()));
    QObject::connect(&mmeForm,SIGNAL(updateMme(MmeSettings,QString)),&newMapWindow,SLOT(updateButtonsColor()));
    QObject::connect(&pagingForm,SIGNAL(updatePaging(PagingSettings,QString)),&newMapWindow,SLOT(updateButtonsColor()));
    QObject::connect(&ueForm,SIGNAL(updateUeSettings(UeParameters,QString)),&newMapWindow,SLOT(updateButtonsColor()));
    QObject::connect(&ubSimForm,SIGNAL(updateUBSimSettings(UBSimSettings,QString)),&trafficMap,SLOT(updateButtonsColor()));
    QObject::connect(&mmeForm,SIGNAL(updateMme(MmeSettings,QString)),&trafficMap,SLOT(updateButtonsColor()));
    QObject::connect(&pagingForm,SIGNAL(updatePaging(PagingSettings,QString)),&trafficMap,SLOT(updateButtonsColor()));
    QObject::connect(&ueForm,SIGNAL(updateUeSettings(UeParameters,QString)),&trafficMap,SLOT(updateButtonsColor()));

    //SpawnWindow NewMapWindow/TrafficMap
    QObject::connect(this, SIGNAL(spawnWindow_MapWindow(Project)), &newMapWindow, SLOT(loadAndOpen(Project)));
    QObject::connect(this, SIGNAL(spawnWindow_TrafficMap(Project,TrafficFileData*)), &trafficMap, SLOT(loadAndOpen(Project,TrafficFileData*)));

    //SpawnWindow Statistics
    QObject::connect(&trafficMap, SIGNAL(spawnWindow_Statistics(QString,QString)), this, SLOT(spawnWindow_Statistics(QString,QString)));
    QObject::connect(this, SIGNAL(spawnWindow_Statistics(QString,QString,StatisticsData)), &statisticsForm, SLOT(loadAndSpawn(QString,QString,StatisticsData)));

    //Update StatisticsData
    QObject::connect(&statisticsForm, SIGNAL(updateStatisticsData(QString,QString,StatisticsData)), dataSystem, SLOT(updateStatisticsData(QString,QString,StatisticsData)));

    //Update LTESim ChBoxes
    QObject::connect(&newMapWindow, SIGNAL(updateCoreNetwork(QString,bool)), dataSystem, SLOT(updateSimulatedCoreNetworkState(QString,bool)));
    QObject::connect(&newMapWindow, SIGNAL(updateUEsimulated(QString,bool)), dataSystem, SLOT(updateSimulatedUeState(QString,bool)));
    QObject::connect(&newMapWindow, SIGNAL(updatePaging(QString,bool)), dataSystem, SLOT(updatePagingState(QString,bool)));
    QObject::connect(&newMapWindow, SIGNAL(updateUbSim(QString,bool)),dataSystem,SLOT(updateUBSimState(QString,bool)));
    QObject::connect(&newMapWindow, SIGNAL(updateSgw(QString,bool)),dataSystem,SLOT(updateSgwState(QString,bool)));

    // Update Cell, Handover
    QObject::connect(&newMapWindow, SIGNAL(removeHandover(Handover,QString)), dataSystem, SLOT(removeHandover(Handover,QString)));
    QObject::connect(&newMapWindow, SIGNAL(updateHandover(Handover,QString)), dataSystem, SLOT(updateHandover(Handover,QString)));
    QObject::connect(&newMapWindow, SIGNAL(removeCell(QPair<Cell,Center>,QString)), dataSystem, SLOT(removeCell(QPair<Cell,Center>,QString)));
    QObject::connect(&newMapWindow, SIGNAL(updateCell(QPair<Cell,Center>,QString,QString)), dataSystem, SLOT(updateCell(QPair<Cell,Center>,QString,QString)));

    // Add new Cell/Handover
    QObject::connect(&newMapWindow, SIGNAL(addCell(QString)), dataSystem, SLOT(addCell(QString)));
    QObject::connect(&newMapWindow, SIGNAL(addHandover(QString)), dataSystem, SLOT(addHandover(QString)));

    //Spawn window Custom Models
    QObject::connect(&trafficMap, SIGNAL(spawnWindow_CustomModels(QString,QString)), this, SLOT(spawnWindow_CustomModels(QString,QString)));
    QObject::connect(this, SIGNAL(spawnWindow_customModels(QString,QString,bool*)), &customModelsListForm, SLOT(open(QString,QString,bool*)));

    //Ping form (trafficmap)
    QObject::connect(&customModelsListForm, SIGNAL(spawnWindow_Ping(QString,QString,int)), this, SLOT(spawnWindow_PingForm(QString,QString,int)));
    QObject::connect(this, SIGNAL(spawnWindow_PingForm(QString,QString,int,bool*,int,Ping)), &pingForm, SLOT(loadAndOpen(QString,QString,int,bool*,int,Ping)));
    QObject::connect(&pingForm, SIGNAL(savePingData(QString,QString,int,Ping,int,bool)), dataSystem, SLOT(savePingData(QString,QString,int,Ping,int,bool)));
    QObject::connect(&customModelsListForm, SIGNAL(spawnCustomModelSubclassWindowToModify(QString,QString,QString,int,int)), this, SLOT(spawnCustomModelSubclassWindowToModify(QString,QString,QString,int,int)));

    //Voip form (trafficmap)
    QObject::connect(&customModelsListForm, SIGNAL(spawnWindow_Voip(QString,QString,int)), this, SLOT(spawnWindow_VoipForm(QString,QString,int)));
    QObject::connect(this, SIGNAL(spawnWindow_VoipForm(QString,QString,int,bool*,int,Voip)), &voipForm, SLOT(loadAndOpen(QString,QString,int,bool*,int,Voip)));
    QObject::connect(&voipForm, SIGNAL(saveVoipData(QString,QString,int,Voip,int,bool)), dataSystem, SLOT(saveVoipData(QString,QString,int,Voip,int,bool)));

    //FtpDl form (trafficmap)
    QObject::connect(&customModelsListForm, SIGNAL(spawnWindow_FtpDl(QString,QString,int)), this, SLOT(spawnWindow_FtpDlForm(QString,QString,int)));
    QObject::connect(this, SIGNAL(spawnWindow_FtpDlForm(QString,QString,int,bool*,int,FtpDl)), &ftpDlForm, SLOT(loadAndOpen(QString,QString,int,bool*,int,FtpDl)));
    QObject::connect(&ftpDlForm, SIGNAL(saveFtpDlData(QString,QString,int,FtpDl,int,bool)), dataSystem, SLOT(saveFtpDlData(QString,QString,int,FtpDl,int,bool)));

    //FtpUl form (trafficmap)
    QObject::connect(&customModelsListForm, SIGNAL(spawnWindow_FtpUl(QString,QString,int)), this, SLOT(spawnWindow_FtpUlForm(QString,QString,int)));
    QObject::connect(this, SIGNAL(spawnWindow_FtpUlForm(QString,QString,int,bool*,int,FtpUl)), &ftpUlForm, SLOT(loadAndOpen(QString,QString,int,bool*,int,FtpUl)));
    QObject::connect(&ftpUlForm, SIGNAL(saveFtpUlData(QString,QString,int,FtpUl,int,bool)), dataSystem, SLOT(saveFtpUlData(QString,QString,int,FtpUl,int,bool)));

    //StreamDL form (trafficmap)
    QObject::connect(&customModelsListForm, SIGNAL(spawnWindow_StreamDl(QString,QString,int)), this, SLOT(spawnWindow_StreamDlForm(QString,QString,int)));
    QObject::connect(this, SIGNAL(spawnWindow_StreamDlForm(QString,QString,int,bool*,int,StreamDl)), &streamDlForm, SLOT(loadAndOpen(QString,QString,int,bool*,int,StreamDl)));
    QObject::connect(&streamDlForm, SIGNAL(saveStreamDlData(QString,QString,int,StreamDl,int,bool)), dataSystem, SLOT(saveStreamDlData(QString,QString,int,StreamDl,int,bool)));

    //StreamUL form (trafficmap)
    QObject::connect(&customModelsListForm, SIGNAL(spawnWindow_StreamUl(QString,QString,int)), this, SLOT(spawnWindow_StreamUlForm(QString,QString,int)));
    QObject::connect(this, SIGNAL(spawnWindow_StreamUlForm(QString,QString,int,bool*,int,StreamUl)), &streamUlForm, SLOT(loadAndOpen(QString,QString,int,bool*,int,StreamUl)));
    QObject::connect(&streamUlForm, SIGNAL(saveStreamUlData(QString,QString,int,StreamUl,int,bool)), dataSystem, SLOT(saveStreamUlData(QString,QString,int,StreamUl,int,bool)));

    //SyncedPing form (trafficmap)
    QObject::connect(&customModelsListForm, SIGNAL(spawnWindow_SyncedPing(QString,QString,int)), this, SLOT(spawnWindow_SyncedPingForm(QString,QString,int)));
    QObject::connect(this, SIGNAL(spawnWindow_SyncedPingForm(QString,QString,int,bool*,int,SyncedPing)), &syncedPingForm, SLOT(loadAndOpen(QString,QString,int,bool*,int,SyncedPing)));
    QObject::connect(&syncedPingForm, SIGNAL(saveSyncedPingData(QString,QString,int,SyncedPing,int,bool)), dataSystem, SLOT(saveSyncedPingData(QString,QString,int,SyncedPing,int,bool)));

    //ServiceReq form (trafficmap)
    QObject::connect(&customModelsListForm, SIGNAL(spawnWindow_ServiceReq(QString,QString,int)), this, SLOT(spawnWindow_ServiceReqForm(QString,QString,int)));
    QObject::connect(this, SIGNAL(spawnWindow_ServiceReqForm(QString,QString,int,bool*,int,ServiceReq)), &serviceReqForm, SLOT(loadAndOpen(QString,QString,int,bool*,int,ServiceReq)));
    QObject::connect(&serviceReqForm, SIGNAL(saveServiceReqData(QString,QString,int,ServiceReq,int,bool)), dataSystem, SLOT(saveServiceReqData(QString,QString,int,ServiceReq,int,bool)));

    // Update project
    QObject::connect(&newMapWindow,SIGNAL(saveProjectOnClose(QString)),dataSystem,SLOT(updateProjectOnMapCloseEvent(QString)));
    QObject::connect(&trafficMap, SIGNAL(saveProjectOnMapTrafficClose(QString)), dataSystem, SLOT(updateProjectOnMapCloseEvent(QString)));
    QObject::connect(dataSystem, SIGNAL(currentCustomModelChanged(CustomModelSettings,bool*)), &customModelsListForm, SLOT(currentCustomModelChanged(CustomModelSettings,bool*)));
    QObject::connect(&customModelsListForm, SIGNAL(loadData(QString,QString,int)), dataSystem, SLOT(updateCustomModel(QString,QString,int)));

    QObject::connect(&trafficMap, SIGNAL(saveProjectOnClose(QString)),dataSystem,SLOT(updateProjectOnMapCloseEvent(QString)));

    // Deleting custom model item
    QObject::connect(&customModelsListForm, SIGNAL(deleteCustomModelItem(QString,QString,QString,int,int)), dataSystem, SLOT(deleteCustomModelItem(QString,QString,QString,int,int)));

    //Spawn time form(trafficMap)
    QObject::connect(&trafficMap, SIGNAL(spawnWindow_Time(QString,QString)), this, SLOT(spawnWindow_TimeForm(QString,QString)));

    //Spawn window Tuning Traffic
    QObject::connect(&trafficMap, SIGNAL(spawnWindow_TuningTraffic(QString,QString)), this, SLOT(spawnWindow_TuningTraffic(QString,QString)));
    QObject::connect(this, SIGNAL(spawnWindow_TuningTraffic(QString,QString,std::tuple<QStringList,QStringList,QStringList>,TuningTrafficData)), &tuningTrafficManager, SLOT(loadAndSpawn(QString,QString,std::tuple<QStringList,QStringList,QStringList>,TuningTrafficData)));
    QObject::connect(&tuningTrafficManager, SIGNAL(restoreTuningTrafficData(QString,QString)), this, SLOT(restoreTuningTrafficData(QString,QString))); //something wierd is happening and it does not work
    QObject::connect(this, SIGNAL(restoreTuningTrafficData(TuningTrafficData)), &tuningTrafficManager, SLOT(restoreTuningTrafficData(TuningTrafficData))); //something wierd is happening and it does not work

    QObject::connect(&tuningTrafficManager, SIGNAL(saveTuningTrafficData(QString,QString,TuningTrafficData)), dataSystem, SLOT(saveTuningTraffic(QString,QString,TuningTrafficData)));

    // Add UEs to Traffic Map Scene + update UEs
    QObject::connect(&trafficMap, SIGNAL(addUe(QString,QString)), dataSystem, SLOT(addUe(QString,QString)));
    QObject::connect(&trafficMap, SIGNAL(updateUe(QString,QString,UEData)), dataSystem, SLOT(updateUe(QString,QString,UEData)));
    QObject::connect(&trafficMap, SIGNAL(removeUe(QString,QString,UEData)), dataSystem, SLOT(removeUe(QString,QString,UEData)));
    QObject::connect(&trafficMap, SIGNAL(spawnWindow_ueParams(QString,QString,QString)), this, SLOT(spawnWindow_UeParams(QString,QString,QString)));
    QObject::connect(dataSystem, SIGNAL(updateUeDataInUeRepresentation(UEData)), &trafficMap, SLOT(updateUeDataInUeRepresentation(UEData)));

    // paging rate
    QObject::connect(&trafficMap, SIGNAL(spawnWindow_PagingRate(QString)),this, SLOT(spawnWindow_PagingRate(QString)));
    QObject::connect(this,SIGNAL(spawnWindow_PagingRate(QString,int&)),&pagingRate,SLOT(loadAndSpawn(QString,int&)));
    QObject::connect(&pagingRate,SIGNAL(updatePagingRate(QString,int)),dataSystem,SLOT(updatePagingRate(QString,int)));
    QObject::connect(&pagingForm,SIGNAL(enablePagingRate(bool)),&pagingRate,SLOT(enablePagingRate(bool)));
    QObject::connect(&newMapWindow,SIGNAL(setEnabledPagingRate(bool)),&pagingRate,SLOT(enablePagingRate(bool)));
    QObject::connect(&trafficMap,SIGNAL(setEnabledPagingRate(bool)),&pagingRate,SLOT(enablePagingRate(bool)));
}

void UISystem::spawnWindow_OpenProject(const QString& projectName) {
    auto project = findProjectByName(projectName);

    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }

    if(!paramWindow){
      paramWindow = new ParametersWindow();
      bindProjectOvierviewWindow(paramWindow);
    }
    paramWindow->loadProjectAndOpen(*project);
}

void UISystem::initialiseSettingsWindowSpawn(const QString& projectName) {
    AppGlobalData data = dataSystem->getAppGlobalData();
    if(projectName.isEmpty()) {
        emit spawnSettingsWindowForProject(data);
        return;
    }else {

        auto project = findProjectByName(projectName);

        if(project == nullptr) {
            dataSystem->errorInData("Can't find right project");
            return;
        }
        emit spawnSettingsWindowForProject(data, *project);
        return;
    }
}

void UISystem::spawnWindow_Ipex(const QString& projectName, bool enable)
{
    auto project = findProjectByName(projectName);

    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }

    if(!ipexForm) {
      ipexForm = new IpexForm();
      QObject::connect(ipexForm, SIGNAL(updateDataGeneratorSettings(DataGeneratorSettings,QString)),
                       dataSystem, SLOT(updateDataGeneratorSettings(DataGeneratorSettings,QString)));
    }
    ipexForm->loadAndSpawn(project->dataGeneratorSettings, project->name,enable);

}

void UISystem::spawnWindow_ucTool(const QString& projectName, bool enable)
{
    auto project = findProjectByName(projectName);

    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }

    if(!ucToolForm){
      ucToolForm = new UCtoolForm();
      QObject::connect(ucToolForm, SIGNAL(updateUCToolSettings(UCToolSettings,QString)),
                       dataSystem, SLOT(updateUCToolSettings(UCToolSettings,QString)));
    }
    ucToolForm->loadAndOpen(project->ucToolSettings, project->name,enable);
}

void UISystem::spawnWindow_Mme(const QString &projectName,bool enable){
    auto project = findProjectByName(projectName);

    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    emit spawnWindow_Mme(project->mmeSettings, project->name, enable);
    return;
}
void UISystem::spawnWindow_Paging(const QString &projectName, bool enable){
    auto project = findProjectByName(projectName);

    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    emit spawnWindow_Paging(project->pagingSettings, project->name,enable);
    return;
}

void UISystem::spawnWindow_ParamMap(const QString &projectName)
{
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }

    emit spawnWindow_MapWindow(*project);
}

void UISystem::spawnWindow_Sgw(const QString &projectName,bool enable){
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    emit spawnWindow_Sgw(project->sgwSettings, project->name,enable);
    return;
}

void UISystem::spawnWindow_ChannelModel(const QString &projectName,bool enable) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project.");
        return;
    }
    emit spawnWindow_ChannelModel(project->channelModelSettings, project->name,enable);
    return;
}

void UISystem::spawnWindow_UBSim(const QString &projectName,bool enable) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project.");
        return;
    }
    emit spawnWindow_UBSim(project->ubSimSettings,project->ueParameters, project->name,enable);
    return;
}

void UISystem::spawnWindow_MapRange(const QString &projectName){
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    emit spawnWindow_MapRange(project->mapRange,project -> name);
}

void UISystem::spawnWindow_TrafficMap(const QString &projectName, const QString &trafficName) {
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    emit spawnWindow_TrafficMap(*project, traffic);
}


void UISystem::spawnWindow_Statistics(const QString &projectName, const QString &trafficName)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    emit spawnWindow_Statistics(project->name, traffic->filename, traffic->statisticsData);
}

void UISystem::spawnWindow_CustomModels(const QString &projectName, const QString &trafficName) {
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    emit spawnWindow_customModels(project->name, traffic->filename, traffic->cmUsed);
}

void UISystem::spawnWindow_PingForm(const QString &projectName, const QString &trafficName, const int &index) {
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    emit spawnWindow_PingForm(project->name, traffic->filename, index, traffic->customModels[index].qciUsed);
}
void UISystem::spawnWindow_GeneralConfiguration(const QString &projectName,bool enable){

    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project.");
        return;
    }
    emit spawnWindow_GeneralConfiguration(project->generalConfiguration,project->name,enable);
    return;
}

void UISystem::spawnWindow_VoipForm(const QString &projectName, const QString &trafficName, const int &index) {
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }

    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    emit spawnWindow_VoipForm(project->name, traffic->filename, index, traffic->customModels[index].qciUsed);
}

void UISystem::spawnWindow_FtpDlForm(const QString &projectName, const QString &trafficName, const int &index)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    emit spawnWindow_FtpDlForm(project->name, traffic->filename, index, traffic->customModels[index].qciUsed);
}

void UISystem::spawnWindow_FtpUlForm(const QString &projectName, const QString &trafficName, const int &index)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    emit spawnWindow_FtpUlForm(project->name, traffic->filename, index, traffic->customModels[index].qciUsed);
}

void UISystem::spawnWindow_TuningTraffic(const QString &projectName, const QString &trafficName) {
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    auto tuningTrafficStringLists = dataSystem->getTuningTrafficStringLists(*traffic);
    emit spawnWindow_TuningTraffic(project->name, traffic->filename, tuningTrafficStringLists, traffic->tuningTrafficData);
}

void UISystem::restoreTuningTrafficData(const QString &projectName, const QString &trafficName)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }

    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }

    emit restoreTuningTrafficData(traffic->tuningTrafficData);
}

void UISystem::spawnWindow_ServiceReqForm(const QString &projectName, const QString &trafficName, const int &index)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    emit spawnWindow_ServiceReqForm(project->name, traffic->filename, index, traffic->customModels[index].qciUsed);
}

void UISystem::spawnWindow_SyncedPingForm(const QString &projectName, const QString &trafficName, const int &index)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    emit spawnWindow_SyncedPingForm(project->name, traffic->filename, index, traffic->customModels[index].qciUsed);
}
void UISystem::spawnWindow_Ue(const QString &projectName, bool enable)
{
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project.");
        return;
    }
    emit spawnWindow_Ue(project->ueParameters,project->name,enable);
    return;
}

void UISystem::spawnCustomModelSubclassWindowToModify(const QString &projectName, const QString &trafficName, const QString &item, const int &itemIndex, const int &CMindex)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    if(item == "Ping") {
        emit spawnWindow_PingForm(project->name, traffic->filename, CMindex, traffic->customModels[CMindex].qciUsed, itemIndex, traffic->customModels[CMindex].CMPings[itemIndex]);
    } else if(item == "Voip") {
        emit spawnWindow_VoipForm(project->name, traffic->filename, CMindex, traffic->customModels[CMindex].qciUsed,itemIndex, traffic->customModels[CMindex].CMVoips[itemIndex]);
    } else if(item == "FtpDl") {
        emit spawnWindow_FtpDlForm(project->name, traffic->filename, CMindex, traffic->customModels[CMindex].qciUsed, itemIndex, traffic->customModels[CMindex].CMFtpDls[itemIndex]);
    } else if(item == "FtpUl") {
        emit spawnWindow_FtpUlForm(project->name, traffic->filename, CMindex, traffic->customModels[CMindex].qciUsed, itemIndex, traffic->customModels[CMindex].CMFtpUls[itemIndex]);
    } else if(item == "StreamDl") {
        emit spawnWindow_StreamDlForm(project->name, traffic->filename, CMindex, traffic->customModels[CMindex].qciUsed, itemIndex, traffic->customModels[CMindex].CMStreamDls[itemIndex]);
    } else if(item == "StreamUl") {
        emit spawnWindow_StreamUlForm(project->name, traffic->filename, CMindex, traffic->customModels[CMindex].qciUsed, itemIndex, traffic->customModels[CMindex].CMStreamUls[itemIndex]);
    } else if(item == "SyncedPing") {
        emit spawnWindow_SyncedPingForm(project->name, traffic->filename, CMindex, traffic->customModels[CMindex].qciUsed, itemIndex, traffic->customModels[CMindex].CMSyncedPings[itemIndex]);
    } else if(item == "ServiceReq") {
        emit spawnWindow_ServiceReqForm(project->name, traffic->filename, CMindex, traffic->customModels[CMindex].qciUsed, itemIndex, traffic->customModels[CMindex].CMServiceReqs[itemIndex]);
    }
}

void UISystem::spawnWindow_UeParams(const QString &ueDataName, const QString &projectName, const QString &trafficName)
{
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    auto ueData = std::find_if(std::begin(traffic->userEquipments), std::end(traffic->userEquipments),[&ueDataName]
                               (const UEData& data)->bool{
        return data.pairName == ueDataName;
    });

    if(ueData == std::end(traffic->userEquipments)) {
        dataSystem->errorInData("Can't find right UE\nWrong name probably");
        return;
    }

    if(!ueParametersForm){
      ueParametersForm = new UeParametersForm();

      QObject::connect(ueParametersForm, SIGNAL(saveUEData(QString,QString,QString,UEData)),
                       dataSystem, SLOT(saveUEData(QString,QString,QString,UEData)));
    }
    ueParametersForm->loadAndOpen(project->name, traffic->filename, *ueData, dataSystem->getActiveCustomModels(projectName, trafficName), dataSystem->getCentersAndHandovers(projectName));
}

void UISystem::spawnWindow_TimeForm(const QString &projectName, const QString &trafficName)
{
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    if(!timeForm) {
      timeForm = new TimeForm();

      QObject::connect(timeForm, SIGNAL(saveTimeData(QString,QString,TimeData)),
                       dataSystem, SLOT(saveTimeData(QString,QString,TimeData)));
    }
    timeForm->loadAndOpen(project->name, traffic->filename, traffic->timeData);
}

Project* UISystem::findProjectByName(const QString &projectName)
{
    auto project = std::find_if(dataSystem->projects.begin(), dataSystem->projects.end(),[&projectName]
                                (const Project& project)->bool {
        return (project.name == projectName);
    });
    return project != std::end(dataSystem->projects) ? project : nullptr;
}

void UISystem::spawnWindow_StreamDlForm(const QString &projectName, const QString &trafficName, const int &index)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    emit spawnWindow_StreamDlForm(project->name, traffic->filename, index, traffic->customModels[index].qciUsed); 
}


void UISystem::spawnWindow_StreamUlForm(const QString &projectName, const QString &trafficName, const int &index)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    auto traffic = project->findTrafficFileByName(trafficName);
    if (traffic==nullptr) {
        dataSystem->errorInData("Can't find right trafficFile");
        return;
    }
    emit spawnWindow_StreamUlForm(project->name, traffic->filename, index, traffic->customModels[index].qciUsed);
}

void UISystem::showErrorWindow(const QString &errorDescription)
{
    QMessageBox(QMessageBox::Information,"",errorDescription,QMessageBox::Yes).exec();
}
void UISystem::spawnWindow_PagingRate(const QString &projectName)
{
    auto project = findProjectByName(projectName);
    if (project==nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    emit spawnWindow_PagingRate(project->name,project->pagingSettings.rate);
}

