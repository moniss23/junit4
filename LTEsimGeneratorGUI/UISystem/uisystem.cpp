#include "uisystem.h"
#include <QMessageBox>

#include "Maps/Parameters/MapWindow/mapwindow.h"

extern MapWindow* map_w;

UISystem::UISystem(DataSystem* data) :
    dataSystem(data),
    paramWindow(dataSystem)
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
    QObject::connect(&projectUi,SIGNAL(SpawnWindow_OpenProject(QString)),this,SLOT(spawnWindow_OpenProject(QString)));
    QObject::connect(this,SIGNAL(spawnWindow_OpenProject(Project)),&paramWindow,SLOT(loadProjectAndOpen(Project)));
    QObject::connect(&projectUi,SIGNAL(SpawnWindow_OpenProject(QString)),dataSystem,SLOT(findProject(QString)));//TODO: should not be needed in final implementation

    //Spawning ProjectManagement after closing ParametersWindow
    QObject::connect(&paramWindow,SIGNAL(SpawnWindow_ProjectMng()),dataSystem,SLOT(SpawnWindow_ProjectManagement()));
    QObject::connect(dataSystem,SIGNAL(SpawnWindow_ProjectMng()),&projectUi,SLOT(show()));

    // Spawning Sgw in Parameters map
    QObject::connect(this, SIGNAL(spawnSgwWindow(SgwSettings,QString)), &sgwForm, SLOT(loadAndSpawn(SgwSettings,QString)));
    // Update SgwSettings in DataSystem
    QObject::connect(&sgwForm,SIGNAL(updateSgw(SgwSettings,QString)),dataSystem,SLOT(updateSgwSettings(SgwSettings,QString)));
    // Enable/Disable Core Network
    QObject::connect(map_w,SIGNAL(coreNetworkEnabled(bool)),&sgwForm,SLOT(coreNetworkEnabled(bool)));

    // Delete project
    QObject::connect(&projectUi,SIGNAL(deleteProject(QString)),dataSystem,SLOT(deleteProject(QString)));
    QObject::connect(dataSystem, SIGNAL(currentProjects(const QVector<Project> &)),
                     &projectUi,   SLOT(updateProjectLists(const QVector<Project>&)));

    // Settings
    QObject::connect(&projectUi, SIGNAL(SpawnWindow_Settings(QString)), this, SLOT(initialiseSettingsWindowSpawn(QString)));
    QObject::connect(&paramWindow, SIGNAL(SpawnWindow_Settings(QString)), this, SLOT(initialiseSettingsWindowSpawn(QString)));
    QObject::connect(&settingsWindow, SIGNAL(SetGlobalLocationForNewProjects(QString)), dataSystem, SLOT(setGlobalLocationForNewProjects(QString)));
    QObject::connect(&settingsWindow, SIGNAL(Set_RB_FilesLocationForProject(QString,QString)), dataSystem, SLOT(set_RB_FilesLocationForProject(QString,QString)));
    QObject::connect(this, SIGNAL(spawnSettingsWindowForProject(AppGlobalData,Project)), &settingsWindow, SLOT(ShowForProject(AppGlobalData,Project)));

    // Import Project
    QObject::connect(&projectUi,SIGNAL(SpawnWindow_ImportProject()), &importProject, SLOT(getProjectDirectory()));
    QObject::connect(&importProject,SIGNAL(selectedProjectDirectory(const QString&)), dataSystem, SLOT(importProject(const QString&)));

    // New Project
    QObject::connect(&projectUi,SIGNAL(SpawnWindow_NewProject()), &addProjectWindow, SLOT(exec()));
    QObject::connect(&addProjectWindow,SIGNAL(createNewProject(QString,QString)),dataSystem,SLOT(createNewProject(QString,QString)));
    QObject::connect(dataSystem, SIGNAL(currentProjects(QVector<Project>)), &addProjectWindow, SLOT(close()));

    //Add traffic file
    QObject::connect(&paramWindow, SIGNAL(AddFile_Traffic(QString,QString)),dataSystem, SLOT(addToProject_TrafficFile(QString,QString)));
    QObject::connect(dataSystem, SIGNAL(currentProjectChanged(Project)),&paramWindow, SLOT(refreshUI(Project)));

    //Rename file
    QObject::connect(&paramWindow,SIGNAL(SpawnWindow_RenameFile(QString,QString)),&renameDialog,SLOT(initWindow(QString,QString)));
    QObject::connect(dataSystem,SIGNAL(currentProjectChanged(Project)),&renameDialog,SLOT(close()));
    QObject::connect(&renameDialog,SIGNAL(changedFilename(QString,QString,QString)),dataSystem,SLOT(checkAndRenameIfFilenameUnique(QString,QString,QString)));

    //Delete TrafficFile
    QObject::connect(&paramWindow,SIGNAL(removeFile_TrafficFile(QString,QString)),dataSystem,SLOT(removeFile_TrafficFile(QString,QString)));

    //Update file content from filePreview
    QObject::connect(&paramWindow,SIGNAL(updateFileContent(QString,QString,QString)),dataSystem,SLOT(updateFileContent(QString,QString,QString)));

    //Save Projects
    QObject::connect(&paramWindow,SIGNAL(saveProjects()),dataSystem,SLOT(saveProjectsFile()));

    //Restore default param and traffic files content
    QObject::connect(&paramWindow,SIGNAL(setDefaultParametersFileContent(QString)),dataSystem,SLOT(setDefaultParametersFileContent(QString)));
    QObject::connect(&paramWindow,SIGNAL(setDefaultTrafficFileContent(QString,QString)),dataSystem,SLOT(setDefaultTrafficFileContent(QString,QString)));

    //Error window
    QObject::connect(dataSystem, SIGNAL(errorInData(QString)),this,SLOT(showErrorWindow(QString)));

    //Open Param Map
    QObject::connect(&paramWindow, SIGNAL(SpawnWindow_ParamMap(QString)), this, SLOT(spawnWindow_ParamMap(QString)));

    //Open Ipex window
    QObject::connect(this, SIGNAL(spawnWindow_Ipex(DataGeneratorSettings,QString)), &ipexForm, SLOT(loadAndSpawn(DataGeneratorSettings,QString)));

    //Update Project Data
    QObject::connect(&ipexForm, SIGNAL(updateDataGeneratorSettings(DataGeneratorSettings,QString)), dataSystem, SLOT(updateDataGeneratorSettings(DataGeneratorSettings,QString)));

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
void UISystem::spawnWindow_ParamMap(const QString &projectName)
{
    auto project = findProjectByName(projectName);

    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    if(map_w!=NULL){
        delete map_w;
        map_w=NULL;
    }
    map_w = new MapWindow(*project);
    QObject::connect(map_w, SIGNAL(SpawnWindow_Ipex(QString)), this, SLOT(spawnWindow_Ipex(QString)));
    QObject::connect(map_w,SIGNAL(spawnSgwWindow(QString)),this,SLOT(spawnWindow_Sgw(QString)));
    map_w->show();
}

void UISystem::spawnWindow_Sgw(const QString &projectName){
    auto project = std::find_if(dataSystem->projects.begin(), dataSystem->projects.end(),[&projectName]
                                (const Project& project)->bool {
        return (project.name == projectName);
    });
    if(project == nullptr) {
        dataSystem->errorInData("Can't find right project");
        return;
    }
    emit spawnSgwWindow(project->sgwSettings, project->name);
    return;
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
