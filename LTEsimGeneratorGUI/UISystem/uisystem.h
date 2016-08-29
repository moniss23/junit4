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
#include "UISystem/DataForms/uctoolform.h"
#include "UISystem/DataForms/sgwform.h"
#include "UISystem/DataForms/mmeform.h"
#include "UISystem/DataForms/channelmodelform.h"

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
    void spawnWindow_ucTool(const QString &projectName);
    void spawnWindow_ParamMap(const QString &projectName);
    void spawnWindow_Sgw(const QString& projectName);
    void spawnWindow_Mme(const QString& projectName);
    void spawnWindow_ChannelModel(const QString& projectName);

signals:
    void spawnSettingsWindowForProject(const AppGlobalData& data,const Project& project = Project());
    void spawnWindow_OpenProject(const Project& project);
    void spawnWindow_Ipex(const DataGeneratorSettings& dataGeneratorSettings, const QString &projectName);
    void spawnWindow_ucTool(const UCToolSettings &ucToolSettings, const QString &projectName);
    void spawnWindow_ParamMap();
    void spawnWindow_Sgw(const SgwSettings& sgwSettings, const QString &projectName);
    void spawnWindow_Mme(const MmeSettings& mmeSettings, const QString &projectName);
    void spawnWindow_ChannelModel(const ChannelModelSettings& channelModelSettings, const QString& projectName);

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
    UCtoolForm ucToolForm;
    SgwForm sgwForm;
    MmeForm mmeForm;
    ChannelModelForm channelModelForm;
};

#endif // UISYSTEM_H
