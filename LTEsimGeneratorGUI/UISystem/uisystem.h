#ifndef UISYSTEM_H
#define UISYSTEM_H

#include "Data/datasystem.h"
#include "UISystem/DataForms/ipexform.h"
#include "UISystem/Windows/addProjectWindow.h"
#include "UISystem/Windows/projectmanagement.h"
#include "UISystem/Windows/importprojectwindow.h"
#include "UISystem/Windows/parameterswindow.h"
#include "UISystem/Windows/settings.h"
#include "UISystem/Windows/renamedialog.h"


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
    void spawnWindow_ParamMap(const QString &projectName);

signals:
    void spawnSettingsWindowForProject(const AppGlobalData& data,const Project& project = Project());
    void spawnWindow_OpenProject(const Project& project);
    void spawnWindow_Ipex(const DataGeneratorSettings& dataGeneratorSettings, const QString &projectName);
    void spawnWindow_ParamMap();

private:
    Project* findProjectByName(const QString &projectName);

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
