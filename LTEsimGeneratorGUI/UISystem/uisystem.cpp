#include "uisystem.h"
#include <QMessageBox>

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
    QObject::connect(&projectUi,SIGNAL(SpawnWindow_OpenProject(QString)),dataSystem,SLOT(setProjectName(QString)));//TODO: this is global leftover, get rid of
    QObject::connect(&projectUi,SIGNAL(SpawnWindow_OpenProject(QString)),dataSystem,SLOT(findProject(QString)));//TODO: should not be needed in final implementation

    // Delete project
    QObject::connect(&projectUi,SIGNAL(deleteProject(QString)),dataSystem,SLOT(deleteProject(QString)));
    QObject::connect(dataSystem, SIGNAL(currentProjects(const QVector<Project> &)),
                     &projectUi,   SLOT(updateProjectLists(const QVector<Project>&)));

    // Settings
    QObject::connect(dataSystem, SIGNAL(updateSettingsView(QString)), &settingsWindow, SLOT(UpdateNewProjectsLocation(QString)));
    QObject::connect(&settingsWindow, SIGNAL(SetDefaultLocationFor_RB_Files(QString)), &paramWindow, SLOT(set_RB_FilesLocation(QString)));
    QObject::connect(&paramWindow, SIGNAL(updateCurrentProjects_RB_FilesLocation(QString)), &settingsWindow, SLOT(Update_RB_FilesLocation(QString)));
    QObject::connect(this, SIGNAL(spawnSettingsWindowForProject(AppGlobalData,Project)), &settingsWindow, SLOT(ShowForProject(AppGlobalData,Project)));
    QObject::connect(&projectUi, SIGNAL(SpawnWindow_Settings(QString)), this, SLOT(initialiseSettingsWindowSpawn(QString)));
    QObject::connect(&paramWindow, SIGNAL(SpawnWindow_Settings(QString)), this, SLOT(initialiseSettingsWindowSpawn(QString)));
    QObject::connect(&settingsWindow, SIGNAL(SetDefaultLocationForNewProjects(QString)), dataSystem, SLOT(setNewDirForProjects(QString)));

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
    QObject::connect(&paramWindow,SIGNAL(SpawnWindow_RenameFile(QString)),&renameDialog,SLOT(initWindow(QString)));
    QObject::connect(dataSystem,SIGNAL(currentProjectChanged(Project)),&renameDialog,SLOT(close()));
    QObject::connect(&renameDialog,SIGNAL(changedFilename(QString,QString)),&paramWindow,SLOT(getNewNameForFile(QString,QString)));
    QObject::connect(&paramWindow,SIGNAL(checkAndRenameIfFilenameUnique(QString,QString,QString)),dataSystem,SLOT(checkAndRenameIfFilenameUnique(QString,QString,QString)));

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
}

void UISystem::spawnWindow_OpenProject(const QString& projectName) {
    auto project = std::find_if(dataSystem->projects.begin(), dataSystem->projects.end(),[&projectName]
                                                                        (const Project& project)->bool {
        return (project.name == projectName);
    });
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
    }else {
        Project currentProject;
        for(auto project: dataSystem->projects) {
            if(project.name == projectName) {
                currentProject = project;
            }
        }
        emit spawnSettingsWindowForProject(data, currentProject);
    }
}

void UISystem::showErrorWindow(const QString &errorDescription)
{
    QMessageBox(QMessageBox::Information,"",errorDescription,QMessageBox::Yes).exec();
}
