#include <vector>
#include <QApplication>
#include <QString>
#include <QFile>
#include <QListWidgetItem>

#include "AppSettings/appsettings.h"
#include "ManagementWindow/Settings/settings.h"
#include "ManagementWindow/ParametersWindow/parameterswindow.h"
#include "ManagementWindow/ProjectManagement/projectmanagement.h"
#include "ManagementWindow/ProjectManagement/importprojectwindow.h"
#include "Maps/Parameters/MapWindow/mapwindow.h"
#include "Maps/Traffic/map_traffic.h"
#include "Data/appglobaldata.h"

//Parameters Old Part
const unsigned int cellCount = 12;
const unsigned int handoverCount = 21;
const unsigned int centerCount = 12;

cellName cellNames[cellCount];
centerName centerNames[centerCount];
handoverName handoverNames[handoverCount];

ParametersWindow *p;
ProjectManagement *projectMng;
std::vector<QString*> trafficFilesNames;
unsigned int project_index;
bool paramFilePresent;

MapWindow* map_w          = NULL;
Map_traffic* map_t        = NULL;

bool changesPresent = false;

void msg(QString content);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /************************************
     *       SETUP   ALL   WINDOWS      *
     ************************************/

    AppSettings appSettings;
    appSettings.read_settings_file();

    ProjectManagement projectUi(&appSettings);
    projectMng = &projectUi;

    Settings settingsWindow(&appSettings, NULL, false);
    settingsWindow.setWindowModality(Qt::WindowModal);

    ParametersWindow viewParameters(&appSettings);
    p = &viewParameters;

    ImportProjectWindow importProject;
    AddProjectWindow addProjectWindow(&appSettings);

    /************************************
     *    BINDING  OBJECTS  TOGETHER    *
     ************************************/
    QObject::connect(&projectUi,SIGNAL(deleteProject(QString)),&appSettings,SLOT(deleteProject(QString)));
    QObject::connect(&appSettings, SIGNAL(currentProjects(const std::vector<Project> &)),
                     &projectUi,   SLOT(updateProjectLists(const std::vector<Project>&)));

    QObject::connect(&projectUi,SIGNAL(SpawnWindow_Settings()), &settingsWindow, SLOT(exec()));

    QObject::connect(&projectUi,SIGNAL(SpawnWindow_ImportProject()), &importProject, SLOT(getProjectDirectory()));
    QObject::connect(&importProject,SIGNAL(selectedProjectDirectory(const QString&)), &appSettings, SLOT(importProject(const QString&)));

    QObject::connect(&projectUi,SIGNAL(SpawnWindow_NewProject()), &addProjectWindow, SLOT(exec()));
    QObject::connect(&addProjectWindow,SIGNAL(createNewProject(QString,QString)),&appSettings,SLOT(createNewProject(QString,QString)));

    //QObject::connect(&appSettings,SIGNAL(errorInData(QString)), );  TODO: IMPLEMENT

    /************************************
     * LOAD DATA AND SHOW GUI INTERFACE *
     ************************************/
    appSettings.LoadAppData();
    projectUi.show();

    return a.exec();
}

// wrapper for displaying an alert/information message
void msg(QString content){
    QMessageBox(QMessageBox::Information,"",content,QMessageBox::Yes).exec();
}

