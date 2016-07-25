#include <QApplication>
#include <management_window/parameterswindow.h>
#include <management_window/projectmanagement.h>
#include <QString>
#include <QStringList>
#include <vector>
#include <QFile>
#include <maps/parameters_map/mapwindow.h>
#include <management_window/encryption.h>
#include <QDesktopWidget>
#include <QListWidgetItem>
#include <management_window/settings.h>
#include <maps/parameters_map//mapwindowlarge.h>
#include <maps/traffic_map/map_traffic.h>
#include <maps/traffic_map/map_traffic_large.h>
#include <iostream>
#include <cstdlib>
#include <maps/testrunner.h>
#include "appsettings.h"

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
int trafficFilesCount = 0;

unsigned int project_index;

bool paramFilePresent;
QString *tabChangedParams;

MapWindow* map_w = NULL;
MapWindowLarge* map_wl = NULL;
Map_traffic* map_t = NULL;
Map_traffic_large* map_tl = NULL;

bool normalMapOpen = false;
bool largeMapOpen = false;

bool changesPresent = false;
bool anyProjectOpen = false;
bool settingsWindowOpen = false;

bool anyChangesInMap = false;

void msg(QString content);

void setCenterOfApplication(QWidget* widget)
{
    QDesktopWidget* desktop = QApplication::desktop();

    int centerW = (desktop->width() - widget->width()) / 2;
    int centerH = (desktop->height() - widget->height()) / 2;

    widget->move(centerW, centerH);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppSettings appSettings;
    projectMng = new ProjectManagement(&appSettings);
    setCenterOfApplication(projectMng);

    projectMng->show();

    appSettings.read_settings_file();
    projectMng->setDefaultDir(appSettings.getDefaultNewProjectDir());

    tabChangedParams = new QString [8];

    ParametersWindow viewParameters(&appSettings);
    p = &viewParameters;
    setCenterOfApplication(p);

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
