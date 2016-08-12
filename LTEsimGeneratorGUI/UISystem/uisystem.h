#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "DataSystem/datasystem.h"
#include "ManagementWindow/AddProjectWindow/addProjectWindow.h"
#include "ManagementWindow/ProjectManagement/projectmanagement.h"
#include "ManagementWindow/ProjectManagement/importprojectwindow.h"
#include "ManagementWindow/ParametersWindow/parameterswindow.h"
#include "ManagementWindow/Settings/settings.h"
#include "ManagementWindow/ParametersWindow/renamedialog.h"

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

signals:
    void spawnSettingsWindowForProject(const AppGlobalData& data,const Project& currentProject = Project());

private:
    DataSystem* dataSystem;
    ProjectManagement projectUi;
    ImportProjectWindow importProject;
    ParametersWindow paramWindow;
    AddProjectWindow addProjectWindow;
    Settings settingsWindow;
    RenameDialog renameDialog;
};

#endif // UISYSTEM_H
