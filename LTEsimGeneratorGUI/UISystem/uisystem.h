#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "Data/datasystem.h"
#include "ManagementWindow/AddProjectWindow/addProjectWindow.h"
#include "ManagementWindow/ProjectManagement/projectmanagement.h"
#include "ManagementWindow/ProjectManagement/importprojectwindow.h"
#include "ManagementWindow/ParametersWindow/parameterswindow.h"
#include "ManagementWindow/Settings/settings.h"
#include "ManagementWindow/ParametersWindow/renamedialog.h"
#include "Maps/Parameters/SimulatedUe/ipexform.h"
#include "Data/ProjectSettings/datageneratorsettings.h"

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
    void spawnWindow_OpenProject(const QString& projectName);
    void spawnWindow_Ipex(const QString& projectName);

signals:
    void spawnSettingsWindowForProject(const AppGlobalData& data,const Project& project = Project());
    void spawnWindow_OpenProject(const Project& project);
    void spawnWindow_Ipex(const DataGeneratorSettings& dataGeneratorSettings, const QString &projectName);

private:
    DataSystem* dataSystem;
    ProjectManagement projectUi;
    ImportProjectWindow importProject;
    ParametersWindow paramWindow;
    AddProjectWindow addProjectWindow;
    Settings settingsWindow;
    RenameDialog renameDialog;
    IpexForm ipexForm;
};

#endif // UISYSTEM_H
