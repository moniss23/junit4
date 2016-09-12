#include "uisystem.h"
#include <QMessageBox>

UISystem::UISystem(DataSystem* data) :
    dataSystem(data),
    paramWindow()
{
    settingsWindow.setWindowModality(Qt::WindowModal);
    this->bindingObjects();
    dataSystem->LoadAppData();
    this->projectUi.show();
}

UISystem::~UISystem(){
}

void UISystem::bindingObjects()
{
    // Open project
    QObject::connect(&projectUi,SIGNAL(spawnWindow_OpenProject(QString)),this,SLOT(spawnWindow_OpenProject(QString)));
    QObject::connect(this,SIGNAL(spawnWindow_OpenProject(Project)),&paramWindow,SLOT(loadProjectAndOpen(Project)));
    QObject::connect(&projectUi,SIGNAL(spawnWindow_OpenProject(QString)),dataSystem,SLOT(findProject(QString)));//TODO: should not be needed in final implementation

    //Spawning ProjectManagement after closing ParametersWindow
    QObject::connect(&paramWindow,SIGNAL(spawnWindow_ProjectMng()),dataSystem,SLOT(spawnWindow_ProjectManagement()));
    QObject::connect(dataSystem,SIGNAL(spawnWindow_ProjectMng()),&projectUi,SLOT(show()));

    // Delete project
    QObject::connect(&projectUi,SIGNAL(deleteProject(QString)),dataSystem,SLOT(deleteProject(QString)));
    QObject::connect(dataSystem, SIGNAL(currentProjects(const QVector<Project> &)),
                     &projectUi,   SLOT(updateProjectLists(const QVector<Project>&)));

    // Settings
    QObject::connect(&projectUi, SIGNAL(spawnWindow_Settings(QString)), this, SLOT(initialiseSettingsWindowSpawn(QString)));
    QObject::connect(&paramWindow, SIGNAL(spawnWindow_Settings(QString)), this, SLOT(initialiseSettingsWindowSpawn(QString)));
    QObject::connect(&settingsWindow, SIGNAL(SetGlobalLocationForNewProjects(QString)), dataSystem, SLOT(setGlobalLocationForNewProjects(QString)));
    QObject::connect(&settingsWindow, SIGNAL(Set_RB_FilesLocationForProject(QString,QString)), dataSystem, SLOT(set_RB_FilesLocationForProject(QString,QString)));
    QObject::connect(this, SIGNAL(spawnSettingsWindowForProject(AppGlobalData,Project)), &settingsWindow, SLOT(ShowForProject(AppGlobalData,Project)));

    // Import Project
    //QObject::connect(&projectUi,SIGNAL(spawnWindow_ImportProject()), &importProject, SLOT(getProjectDirectory()));
    //QObject::connect(&importProject,SIGNAL(selectedProjectDirectory(const QString&)), dataSystem, SLOT(importProject(const QString&)));

    // New Projects
    QObject::connect(&projectUi,SIGNAL(spawnWindow_NewProject()), &addProjectWindow, SLOT(exec()));
    QObject::connect(&addProjectWindow,SIGNAL(createNewProject(QString,QString)),dataSystem,SLOT(createNewProject(QString,QString)));
    QObject::connect(dataSystem, SIGNAL(currentProjects(QVector<Project>)), &addProjectWindow, SLOT(close()));

    //Add traffic file
    QObject::connect(&paramWindow, SIGNAL(AddFile_Traffic(QString,QString)),dataSystem, SLOT(addToProject_TrafficFile(QString,QString)));
    QObject::connect(dataSystem, SIGNAL(currentProjectChanged(Project)),&paramWindow, SLOT(refreshUI(Project)));

    //Rename file
    QObject::connect(&paramWindow,SIGNAL(spawnWindow_RenameFile(QString,QString)),&renameDialog,SLOT(initWindow(QString,QString)));
    QObject::connect(dataSystem,SIGNAL(currentProjectChanged(Project)),&renameDialog,SLOT(close()));
    QObject::connect(&renameDialog,SIGNAL(changedFilename(QString,QString,QString)),dataSystem,SLOT(checkAndRenameIfFilenameUnique(QString,QString,QString)));

    //Delete TrafficFile
    QObject::connect(&paramWindow,SIGNAL(removeFile_TrafficFile(QString,QString)),dataSystem,SLOT(removeFile_TrafficFile(QString,QString)));

    //Update file content from filePreview
    QObject::connect(&paramWindow,SIGNAL(updateFileContent(QString,QString,QString)),dataSystem,SLOT(updateFileContent(QString,QString,QString)));


    //Restore default param and traffic files content
    QObject::connect(&paramWindow,SIGNAL(setDefaultParametersFileContent(QString)),dataSystem,SLOT(setDefaultParametersFileContent(QString)));
    QObject::connect(&paramWindow,SIGNAL(setDefaultTrafficFileContent(QString,QString)),dataSystem,SLOT(setDefaultTrafficFileContent(QString,QString)));

    //Error window
    QObject::connect(dataSystem, SIGNAL(errorInData(QString)),this,SLOT(showErrorWindow(QString)));

    //Open Param Map
    QObject::connect(&paramWindow, SIGNAL(spawnWindow_ParamMap(QString)), this, SLOT(spawnWindow_ParamMap(QString)));

    //Open Ipex window
    QObject::connect(this, SIGNAL(spawnWindow_Ipex(DataGeneratorSettings,QString)), &ipexForm, SLOT(loadAndSpawn(DataGeneratorSettings,QString)));
    QObject::connect(&ipexForm, SIGNAL(updateDataGeneratorSettings(DataGeneratorSettings,QString)), dataSystem, SLOT(updateDataGeneratorSettings(DataGeneratorSettings,QString)));
    QObject::connect(&newMapWindow, SIGNAL(spawnWindow_Ipex(QString)), this, SLOT(spawnWindow_Ipex(QString)));

    //Open UCTool window
    QObject::connect(this, SIGNAL(spawnWindow_ucTool(UCToolSettings,QString)), &ucToolForm, SLOT(loadAndOpen(UCToolSettings,QString)));
    QObject::connect(&newMapWindow, SIGNAL(spawnWindow_ucTool(QString)), this, SLOT(spawnWindow_ucTool(QString)));

    //Update UCTool settings
    QObject::connect(&ucToolForm, SIGNAL(updateUCToolSettings(UCToolSettings,QString)), dataSystem, SLOT(updateUCToolSettings(UCToolSettings,QString)));

    //Open ChannelModel window
    QObject::connect(this, SIGNAL(spawnWindow_ChannelModel(ChannelModelSettings,QString)), &channelModelForm, SLOT(loadAndOpen(ChannelModelSettings,QString)));
    QObject::connect(&newMapWindow, SIGNAL(spawnWindow_ChannelModel(QString)), this, SLOT(spawnWindow_ChannelModel(QString)));

    //Update ChannelModelSettings
    QObject::connect(&channelModelForm, SIGNAL(updateChannelModelSettings(ChannelModelSettings,QString)), dataSystem, SLOT(updateChannelModelSettings(ChannelModelSettings,QString)));

    //Update Project IpexData
    QObject::connect(&ipexForm, SIGNAL(updateDataGeneratorSettings(DataGeneratorSettings,QString)), dataSystem, SLOT(updateDataGeneratorSettings(DataGeneratorSettings,QString)));

    //Open Sgw window
    QObject::connect(this, SIGNAL(spawnWindow_Sgw(SgwSettings,QString)), &sgwForm, SLOT(loadAndSpawn(SgwSettings,QString)));
    QObject::connect(&newMapWindow, SIGNAL(spawnWindow_Sgw(QString)), this, SLOT(spawnWindow_Sgw(QString)));

    //Open Mme window
    QObject::connect(this,SIGNAL(spawnWindow_Mme(MmeSettings,PagingSettings,QString)),&mmeForm,SLOT(loadAndSpawn(MmeSettings,PagingSettings,QString)));
    QObject::connect(&newMapWindow, SIGNAL(spawnWindow_Mme(QString)), this, SLOT(spawnWindow_Mme(QString)));

    //Update Mme and Paging
    QObject::connect(&mmeForm,SIGNAL(updateMme(MmeSettings, QString)),dataSystem,SLOT(updateMme(MmeSettings,QString)));
    QObject::connect(&mmeForm,SIGNAL(updatePaging(PagingSettings,QString)),dataSystem,SLOT(updatePaging(PagingSettings,QString)));

    //Update Project SgwData
    QObject::connect(&sgwForm,SIGNAL(updateSgw(SgwSettings,QString)),dataSystem,SLOT(updateSgwSettings(SgwSettings,QString)));

    //Open UBSim
    QObject::connect(&newMapWindow, SIGNAL(spawnWindow_UBSim(QString)), this, SLOT(spawnWindow_UBSim(QString)));
    QObject::connect(this, SIGNAL(spawnWindow_UBSim(UBSimSettings,UeParameters,QString)), &ubSimForm, SLOT(loadAndOpen(UBSimSettings,UeParameters,QString)));

    //Update UBsimSettings
    QObject::connect(&ubSimForm, SIGNAL(updateUBSimSettings(UBSimSettings,QString)), dataSystem, SLOT(updateUBSimSettings(UBSimSettings,QString)));

    //Open Map Range
    QObject::connect(&newMapWindow, SIGNAL(spawnWindow_mapRange(QString)), this, SLOT(spawnWindow_MapRange(QString)));
    QObject::connect(this,SIGNAL(spawnWindow_MapRange(MapRange,QString)),&mapRangeForm,SLOT(loadAndSpawn(MapRange,QString)));

    //Update Map Range
    QObject::connect(&mapRangeForm,SIGNAL(updateMapRange(MapRange,QString)),dataSystem,SLOT(updateMapRange(MapRange,QString)));

    //Open MapView
    QObject::connect(&paramWindow, SIGNAL(spawnWindow_MapView(QString)), this, SLOT(spawnWindow_MapView(QString)));

    //refresh map view
    QObject::connect(dataSystem, SIGNAL(refreshMapView(Project)), &newMapWindow, SLOT(loadAndOpen(Project)));

    //SpawnWindow MapWindow
    QObject::connect(this, SIGNAL(spawnWindow_MapWindow(Project)), &newMapWindow, SLOT(loadAndOpen(Project)));

    //SPawnWindow TrafficMap
    QObject::connect(&paramWindow, SIGNAL(spawnWindow_TrafficMap(QString,QString)), this, SLOT(spawnWindow_TrafficMap(QString,QString)));
    QObject::connect(this, SIGNAL(spawnWindow_TrafficMap(Project,TrafficFileData)), &trafficMap, SLOT(loadAndOpen(Project,TrafficFileData)));

    //SpawnWindow Statistics
    QObject::connect(&trafficMap, SIGNAL(spawnWindow_Statistics(QString,QString)), this, SLOT(spawnWindow_Statistics(QString,QString)));
    QObject::connect(this, SIGNAL(spawnWindow_Statistics(QString,QString,StatisticsData)), &statisticsManager, SLOT(loadAndSpawn(QString,QString,StatisticsData)));

    //Update StatisticsData
    QObject::connect(&statisticsManager, SIGNAL(updateStatisticsData(QString,QString,StatisticsData)), dataSystem, SLOT(updateStatisticsData(QString,QString,StatisticsData)));

    //Generating scripts
    QObject::connect(&paramWindow, SIGNAL(generateParametersScript(Project&)), dataSystem, SLOT(generateParametersScript(Project&)));
    QObject::connect(&paramWindow, SIGNAL(generateTrafficScript(Project,int)), dataSystem, SLOT(generateTrafficScript(Project,int)));

    //Update CoreNetwork and UESimulated
    QObject::connect(&newMapWindow, SIGNAL(updateCoreNetwork(QString,bool)), dataSystem, SLOT(updateSimulatedCoreNetworkState(QString,bool)));
    QObject::connect(&newMapWindow, SIGNAL(updateUEsimulated(QString,bool)), dataSystem, SLOT(updateSimulatedUeState(QString,bool)));

    // Update Cell, Handover
    QObject::connect(&newMapWindow, SIGNAL(removeHandover(Handover,QString)), dataSystem, SLOT(removeHandover(Handover,QString)));
    QObject::connect(&newMapWindow, SIGNAL(updateHandover(Handover,QString)), dataSystem, SLOT(updateHandover(Handover,QString)));
    QObject::connect(&newMapWindow, SIGNAL(removeCell(QPair<Cell,Center>,QString)), dataSystem, SLOT(removeCell(QPair<Cell,Center>,QString)));
    QObject::connect(&newMapWindow, SIGNAL(updateCell(QPair<Cell,Center>,QString,QString)), dataSystem, SLOT(updateCell(QPair<Cell,Center>,QString,QString)));

    // Add new Cell
    QObject::connect(&newMapWindow, SIGNAL(addCell(QString)), dataSystem, SLOT(addCell(QString)));

    //Spawn window Custom Models
    QObject::connect(&trafficMap, SIGNAL(spawnWindow_CustomModels(QString,QString)), this, SLOT(spawnWindow_CustomModels(QString,QString)));
    QObject::connect(this, SIGNAL(spawnWindow_customModels(QString,QString,bool*)), &customModelsListForm, SLOT(open(QString,QString, bool*)));

    //Spawn window ping form
    QObject::connect(&customModelsListForm, SIGNAL(spawnWindow_Ping(QString,QString,int)), this, SLOT(spawnWindow_PingForm(QString,QString,int)));
    QObject::connect(this, SIGNAL(spawnWindow_PingForm(QString,QString,int,bool*)), &pingForm, SLOT(loadAndOpen(QString,QString,int,bool*)));

    //Save ping form
    QObject::connect(&pingForm, SIGNAL(savePingData(QString,QString,int,Ping)), dataSystem, SLOT(savePingData(QString,QString,int,Ping)));
    QObject::connect(dataSystem, SIGNAL(currentCustomModelChanged(CustomModelSettings)), &customModelsListForm, SLOT(currentCustomModelChanged(CustomModelSettings)));

    // Update project
    QObject::connect(&newMapWindow,SIGNAL(saveProjectOnClose(QString)),dataSystem,SLOT(updateProjectOnMapCloseEvent(QString)));
    QObject::connect(dataSystem, SIGNAL(currentCustomModelChanged(CustomModelSettings,bool*)), &customModelsListForm, SLOT(currentCustomModelChanged(CustomModelSettings,bool*)));
    QObject::connect(&customModelsListForm, SIGNAL(loadData(QString,QString,int)), dataSystem, SLOT(updateCustomModel(QString,QString,int)));
}

void UISystem::spawnWindow_OpenProject(const QString& projectName) {
    auto project = findProjectByName(projectName);

    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    emit spawnWindow_OpenProject(*project);
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

void UISystem::spawnWindow_Ipex(const QString& projectName)
{
    auto project = findProjectByName(projectName);

    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    emit spawnWindow_Ipex(project->dataGeneratorSettings, project->name);
    return;
}

void UISystem::spawnWindow_ucTool(const QString& projectName)
{
    auto project = findProjectByName(projectName);

    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    emit spawnWindow_ucTool(project->ucToolSettings, project->name);
    return;
}

void UISystem::spawnWindow_Mme(const QString &projectName){
    auto project = findProjectByName(projectName);

    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    emit spawnWindow_Mme(project->mmeSettings,project->pagingSettings, project->name);
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

void UISystem::spawnWindow_Sgw(const QString &projectName){
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    emit spawnWindow_Sgw(project->sgwSettings, project->name);
    return;
}

void UISystem::spawnWindow_ChannelModel(const QString &projectName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project.");
        return;
    }
    emit spawnWindow_ChannelModel(project->channelModelSettings, project->name);
    return;
}

void UISystem::spawnWindow_UBSim(const QString &projectName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project.");
        return;
    }
    emit spawnWindow_UBSim(project->ubSimSettings,project->ueParameters, project->name);
    return;
}

void UISystem::spawnWindow_MapView(const QString &projectName) {
    auto project = findProjectByName(projectName);
    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project.");
        return;
    }
    emit spawnWindow_MapView(*project);
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
    emit spawnWindow_TrafficMap(*project, *traffic);
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

Project* UISystem::findProjectByName(const QString &projectName)
{
    auto project = std::find_if(dataSystem->projects.begin(), dataSystem->projects.end(),[&projectName]
                                (const Project& project)->bool {
        return (project.name == projectName);
    });
    return project != std::end(dataSystem->projects) ? project : nullptr;
}

void UISystem::showErrorWindow(const QString &errorDescription)
{
    QMessageBox(QMessageBox::Information,"",errorDescription,QMessageBox::Yes).exec();
}
