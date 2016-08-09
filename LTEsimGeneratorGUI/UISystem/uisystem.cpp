#include "uisystem.h"

UISystem::UISystem(AppSettings* appSettings, ProjectManagement* projectUi, ImportProjectWindow* importProject,
                   ParametersWindow* paramWindow, AddProjectWindow* addProjectWindow, Settings* settingsWindow)
{
    this->appSettings = appSettings;
    this->projectUi = projectUi;
    this->importProject = importProject;
    this->paramWindow = paramWindow;
    this->addProjectWindow = addProjectWindow;
    this->settingsWindow = settingsWindow;
}

void UISystem::bindingObjects()
{
    // Open project
    QObject::connect(projectUi,SIGNAL(SpawnWindow_OpenProject(QString)),paramWindow,SLOT(loadProjectAndOpen(QString)));
    QObject::connect(projectUi,SIGNAL(SpawnWindow_OpenProject(QString)),appSettings,SLOT(setProjectName(QString)));//TODO: this is global leftover, get rid of
    QObject::connect(projectUi,SIGNAL(SpawnWindow_OpenProject(QString)),appSettings,SLOT(findProject(QString)));//TODO: should not be needed in final implementation

    // Delete project
    QObject::connect(projectUi,SIGNAL(deleteProject(QString)),appSettings,SLOT(deleteProject(QString)));
    QObject::connect(appSettings, SIGNAL(currentProjects(const std::vector<Project> &)),
                     projectUi,   SLOT(updateProjectLists(const std::vector<Project>&)));

    // Settings
    QObject::connect(projectUi,SIGNAL(SpawnWindow_Settings()), settingsWindow, SLOT(exec()));

    // Import Project
    QObject::connect(projectUi,SIGNAL(SpawnWindow_ImportProject()), importProject, SLOT(getProjectDirectory()));
    QObject::connect(importProject,SIGNAL(selectedProjectDirectory(const QString&)), appSettings, SLOT(importProject(const QString&)));

    // New Project
    QObject::connect(projectUi,SIGNAL(SpawnWindow_NewProject()), addProjectWindow, SLOT(exec()));
    QObject::connect(addProjectWindow,SIGNAL(createNewProject(QString,QString)),appSettings,SLOT(createNewProject(QString,QString)));
    QObject::connect(appSettings,SIGNAL(errorInData(QString)), addProjectWindow, SLOT(showErrorWindow(QString)));
    QObject::connect(appSettings, SIGNAL(currentProjects(std::vector<Project>)), addProjectWindow, SLOT(close()));

    //Add traffic file
    QObject::connect(paramWindow, SIGNAL(AddFile_Traffic(QString)),appSettings, SLOT(addToProject_TrafficFile(QString)));
    QObject::connect(appSettings, SIGNAL(currentProjectChanged(Project)),paramWindow, SLOT(refreshUI(Project)));
    QObject::connect(appSettings,SIGNAL(errorInData(QString)), paramWindow, SLOT(showErrorWindow(QString)));
}
