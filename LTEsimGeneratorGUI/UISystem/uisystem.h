#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "AppSettings/appsettings.h"
#include "ManagementWindow/AddProjectWindow/addProjectWindow.h"
#include "ManagementWindow/ProjectManagement/projectmanagement.h"
#include "ManagementWindow/ProjectManagement/importprojectwindow.h"
#include "ManagementWindow/ParametersWindow/parameterswindow.h"
#include "ManagementWindow/Settings/settings.h"

class UISystem : public QObject
{

    Q_OBJECT

public:
    UISystem(AppSettings *data);
    ~UISystem();

    void bindingObjects();

public slots:
    void showErrorWindow(const QString& errorDescription);


private:
    AppSettings* appSettings;
    ProjectManagement projectUi;
    ImportProjectWindow importProject;
    ParametersWindow paramWindow;
    AddProjectWindow addProjectWindow;
    Settings settingsWindow;
};

#endif // UISYSTEM_H
