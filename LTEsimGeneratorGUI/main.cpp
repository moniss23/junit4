#include <vector>
#include <QApplication>
#include <QString>
#include <QFile>
#include <QListWidgetItem>

#include "AppSettings/appsettings.h"
#include "ManagementWindow/ParametersWindow/parameterswindow.h"
#include "ManagementWindow/ProjectManagement/projectmanagement.h"
#include "Maps/Parameters/MapWindow/mapwindow.h"
#include "Maps/Parameters/MapWindow/mapwindowlarge.h"
#include "Maps/Traffic/map_traffic.h"
#include "Maps/Traffic/map_traffic_large.h"

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
MapWindowLarge* map_wl    = NULL;
Map_traffic* map_t        = NULL;
Map_traffic_large* map_tl = NULL;

bool changesPresent = false;

void msg(QString content);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppSettings appSettings;
    appSettings.read_settings_file();

    ProjectManagement projectUi(&appSettings);
    projectMng = &projectUi;
    projectUi.show();

    QObject::connect(projectMng,SIGNAL(deleteProject(QString)),&appSettings,SLOT(deleteProject(QString)));
    QObject::connect(&appSettings,SIGNAL(currentProjects(const std::vector<Project> &)),projectMng,SLOT(updateProjectLists(const std::vector<Project>&)));

    ParametersWindow viewParameters(&appSettings);
    p = &viewParameters;

    appSettings.LoadAppData();

    return a.exec();
}

// wrapper for displaying an alert/information message
void msg(QString content){
    QMessageBox(QMessageBox::Information,"",content,QMessageBox::Yes).exec();
}

