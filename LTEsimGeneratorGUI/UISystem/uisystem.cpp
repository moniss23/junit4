#include "uisystem.h"
#include <QMessageBox>

UISystem::UISystem(AppSettings* data) :
    appSettings(data),
    paramWindow(appSettings)
{
    settingsWindow.setWindowModality(Qt::WindowModal);
    this->bindingObjects();
    appSettings->LoadAppData();
    this->projectUi.show();
}

UISystem::~UISystem(){
}

void UISystem::bindingObjects()
{
    // Open project
    QObject::connect(&projectUi,SIGNAL(SpawnWindow_OpenProject(QString)),&paramWindow,SLOT(loadProjectAndOpen(QString)));
    QObject::connect(&projectUi,SIGNAL(SpawnWindow_OpenProject(QString)),appSettings,SLOT(setProjectName(QString)));//TODO: this is global leftover, get rid of
    QObject::connect(&projectUi,SIGNAL(SpawnWindow_OpenProject(QString)),appSettings,SLOT(findProject(QString)));//TODO: should not be needed in final implementation

    // Delete project
    QObject::connect(&projectUi,SIGNAL(deleteProject(QString)),appSettings,SLOT(deleteProject(QString)));
    QObject::connect(appSettings, SIGNAL(currentProjects(const QVector<Project> &)),
                     &projectUi,   SLOT(updateProjectLists(const QVector<Project>&)));

    // Settings
    QObject::connect(this, SIGNAL(spawnSettingsWindowForProject(AppGlobalData,Project)), &settingsWindow, SLOT(ShowForProject(AppGlobalData,Project)));
    QObject::connect(&projectUi, SIGNAL(SpawnWindow_Settings(QString)), this, SLOT(initialiseSettingsWindowSpawn(QString)));
    QObject::connect(&paramWindow, SIGNAL(SpawnWindow_Settings(QString)), this, SLOT(initialiseSettingsWindowSpawn(QString)));

    // Import Project
    QObject::connect(&projectUi,SIGNAL(SpawnWindow_ImportProject()), &importProject, SLOT(getProjectDirectory()));
    QObject::connect(&importProject,SIGNAL(selectedProjectDirectory(const QString&)), appSettings, SLOT(importProject(const QString&)));

    // New Project
    QObject::connect(&projectUi,SIGNAL(SpawnWindow_NewProject()), &addProjectWindow, SLOT(exec()));
    QObject::connect(&addProjectWindow,SIGNAL(createNewProject(QString,QString)),appSettings,SLOT(createNewProject(QString,QString)));
    QObject::connect(appSettings, SIGNAL(currentProjects(QVector<Project>)), &addProjectWindow, SLOT(close()));

    //Add traffic file
    QObject::connect(&paramWindow, SIGNAL(AddFile_Traffic(QString,QString)),appSettings, SLOT(addToProject_TrafficFile(QString,QString)));
    QObject::connect(appSettings, SIGNAL(currentProjectChanged(Project)),&paramWindow, SLOT(refreshUI(Project)));

    //Rename file
    QObject::connect(&paramWindow,SIGNAL(SpawnWindow_RenameFile(QString)),&renameDialog,SLOT(initWindow(QString)));
    QObject::connect(appSettings,SIGNAL(currentProjectChanged(Project)),&renameDialog,SLOT(close()));
    QObject::connect(&renameDialog,SIGNAL(changedFilename(QString,QString)),&paramWindow,SLOT(getNewNameForFile(QString,QString)));
    QObject::connect(&paramWindow,SIGNAL(checkAndRenameIfFilenameUnique(QString,QString,QString)),appSettings,SLOT(checkAndRenameIfFilenameUnique(QString,QString,QString)));

    //Error window
    QObject::connect(appSettings, SIGNAL(errorInData(QString)),this,SLOT(showErrorWindow(QString)));
}

void UISystem::initialiseSettingsWindowSpawn(const QString& projectName) {
    AppGlobalData data = appSettings->getAppGlobalData();
    if(projectName.isEmpty()) {
        emit spawnSettingsWindowForProject(data);
    }else {
        Project currentProject;
        for(auto project: appSettings->projects) {
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
