#include <vector>
#include <iostream>
#include <cstdlib>
#include <QApplication>
#include <ManagementWindow/ParametersWindow/parameterswindow.h>
#include <ManagementWindow/ProjectManagement/projectmanagement.h>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDesktopWidget>
#include <QListWidgetItem>
#include <Maps/Parameters/MapWindow/mapwindow.h>
#include <ManagementWindow/Encryption/encryption.h>
#include <QDesktopWidget>
#include <QListWidgetItem>
#include <ManagementWindow/Settings/settings.h>
#include <Maps/Parameters/MapWindow/mapwindowlarge.h>
#include <Maps/Traffic/map_traffic.h>
#include <Maps/Traffic/map_traffic_large.h>
#include <iostream>
#include <cstdlib>
#include <TestRunner/testrunner.h>
#include <AppSettings/appsettings.h>


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
std::vector<QFile*> trafficFiles;

unsigned int project_index;

bool paramFilePresent;
QString *tabChangedParams;

MapWindow* map_w          = NULL;
MapWindowLarge* map_wl    = NULL;
Map_traffic* map_t        = NULL;
Map_traffic_large* map_tl = NULL;

bool normalMapOpen = false;
bool largeMapOpen = false;

bool changesPresent = false;
bool anyProjectOpen = false;
bool settingsWindowOpen = false;

bool anyChangesInMap = false;

void msg(QString content);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppSettings appSettings;
    projectMng = new ProjectManagement(&appSettings);
    projectMng->show();

    appSettings.read_settings_file();
    projectMng->setDefaultDir(appSettings.getDefaultNewProjectDir());

    tabChangedParams = new QString [8];

    ParametersWindow viewParameters(&appSettings);
    p = &viewParameters;

    //Condition to run tests on Jenkins
    if (argv[1] == QString("TEST"))  {
        TestRunner unitTests(&appSettings);
        unitTests.runTests();

        return 0;
    } else
        return a.exec();

}

// wrapper for displaying an alert/information message
void msg(QString content){
    QMessageBox(QMessageBox::Information,"",content,QMessageBox::Yes).exec();
}



void viewVector(const std::vector<Project> &projects){
    for(unsigned int i = 0; i < projects.size(); i++)
    {
        qDebug() << projects[i].name << "\t" << projects[i].fullpath;
    }
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

Center* getCenterObj(QString name){
    for(unsigned int i = 0; i < centerCount; i++)
    {
        if(centerNames[i].name == name)
        {
            return centerNames[i].obj;
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
