#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "AppSettings/appsettings.h"
#include "ManagementWindow/AddProjectWindow/addProjectWindow.h"
#include "ManagementWindow/ProjectManagement/projectmanagement.h"
#include "ManagementWindow/ProjectManagement/importprojectwindow.h"
#include "ManagementWindow/ParametersWindow/parameterswindow.h"
#include "ManagementWindow/Settings/settings.h"

class UISystem
{
public:
    UISystem(AppSettings* appSettings, ProjectManagement* projectUi, ImportProjectWindow* importProject,
             ParametersWindow* paramWindow, AddProjectWindow* addProjectWindow, Settings* settingsWindow);

    void bindingObjects();

private:
    AppSettings* appSettings;
    ProjectManagement* projectUi;
    ImportProjectWindow* importProject;
    ParametersWindow* paramWindow;
    AddProjectWindow* addProjectWindow;
    Settings* settingsWindow;
};

#endif // UISYSTEM_H
