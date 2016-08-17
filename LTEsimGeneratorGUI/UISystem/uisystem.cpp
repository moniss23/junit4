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
    QObject::connect(&projectUi,SIGNAL(SpawnWindow_OpenProject(QString)),&paramWindow,SLOT(loadProjectAndOpen(QString)));
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

    //Error window
    QObject::connect(dataSystem, SIGNAL(errorInData(QString)),this,SLOT(showErrorWindow(QString)));
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
