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

bool normalMapOpen = false;
bool largeMapOpen = false;

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

    projectMng->connect(projectMng,SIGNAL(deleteProject(QString)),&appSettings,SLOT(deleteProject(QString)));
    projectMng->connect(&appSettings,SIGNAL(currentProjects(const std::vector<Project> &)),projectMng,SLOT(updateProjectLists(const std::vector<Project>&)));

    ParametersWindow viewParameters(&appSettings);
    p = &viewParameters;


    return a.exec();
}

// wrapper for displaying an alert/information message
void msg(QString content){
    QMessageBox(QMessageBox::Information,"",content,QMessageBox::Yes).exec();
}


QString get_project_name(QListWidgetItem* item, const std::vector<Project> &projects){
    for(unsigned int i = 0; i < projects.size(); i++)
    {
        if(projects[i].widget == item)
        {
            return projects[i].name;
        }
    }
    return "";
}

QString get_project_dir(QListWidgetItem* item, const std::vector<Project> &projects){
    for(unsigned int i = 0; i < projects.size(); i++)
    {
        if(projects[i].widget == item)
        {
            return projects[i].fullpath;
        }
    }
    return "";
}

QString get_project_dir(QString project_name, const std::vector<Project> &projects){
    for(unsigned int i = 0; i < projects.size(); i++)
    {
        if(projects[i].name == project_name)
        {
            return projects[i].fullpath;
        }
    }
    return "";
}

Cell* getCellObj(QString name){
    for(unsigned int i = 0; i < cellCount; i++)
    {
        if(cellNames[i].name == name)
        {
            return cellNames[i].obj;
        }
    }
    return NULL;
}

Handover* getHandoverObj(QString name){
    for(unsigned int i = 0; i < handoverCount; i++)
    {
        if(handoverNames[i].name == name)
        {
            return handoverNames[i].obj;
        }
    }
    return NULL;
}
