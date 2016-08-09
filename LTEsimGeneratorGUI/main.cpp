#include <vector>
#include <QApplication>
#include <QString>

#include "AppSettings/appsettings.h"
#include "ManagementWindow/ProjectManagement/projectmanagement.h"
#include "ManagementWindow/AddProjectWindow/addProjectWindow.h"
#include "ManagementWindow/ProjectManagement/importprojectwindow.h"

#include "ManagementWindow/Settings/settings.h"
#include "ManagementWindow/ParametersWindow/parameterswindow.h"
#include "Maps/Parameters/MapWindow/mapwindow.h"
#include "Maps/Traffic/map_traffic.h"
#include "Data/appglobaldata.h"
#include "UISystem/uisystem.h"


ParametersWindow *p;
std::vector<QString*> trafficFilesNames;
unsigned int project_index;
bool paramFilePresent = true;
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

    ProjectManagement projectUi(&appSettings);

    Settings settingsWindow(&appSettings, NULL, false);
    settingsWindow.setWindowModality(Qt::WindowModal);

    ParametersWindow viewParameters(&appSettings);
    p = &viewParameters;

    ImportProjectWindow importProject;
    AddProjectWindow addProjectWindow;

    UISystem UiSystem(&appSettings, &projectUi, &importProject, &viewParameters, &addProjectWindow, &settingsWindow);

    /************************************
     *    BINDING  OBJECTS  TOGETHER    *
     ************************************/
    UiSystem.bindingObjects();


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

