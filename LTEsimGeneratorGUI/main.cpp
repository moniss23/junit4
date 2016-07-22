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

QString defaultNewProjectDir;

int projectC;
unsigned int project_index;

QString* proFileExt;
bool paramFilePresent;
QString *tabChangedParams;

std::vector<Project> projects;

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

extern QString defaultNewProjectDir;

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
    proFileExt = new QString(".proj");
    projectMng = new ProjectManagement(&appSettings);
    setCenterOfApplication(projectMng);

    projectMng->show();

    read_settings_file();
    projectMng->setDefaultDir(defaultNewProjectDir);

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

const char* crypt(const char* plaintext,int text_len,const char* key,int key_len,bool terminatingZero){
    int i, key_pos = 0;
    char* result = new char[text_len + (terminatingZero==1)];

    for(i=0; i<text_len; i++) {
        result[i] = plaintext[i] ^ key[key_pos];
        key_pos = ( key_pos + 1 ) % key_len;
    }

    if(terminatingZero) {
        result[i] = '\0';
    }

    return result;
}

// Read the content of the project file, decrypt it and split into a list
QStringList read_project_file(QString project_name, QString dir){

    dir = (dir == "<default>") ? "projects" : dir;

    QFile project_file(dir + "/" + project_name + "/" + project_name + (*proFileExt));
    project_file.open(QIODevice::ReadOnly);
    QDataStream project_file_stream(&project_file);

    unsigned int length = project_file.bytesAvailable();
    char* ciphertext = new char[length];

    project_file_stream.readRawData(ciphertext,length);
    const char* plaintext = crypt(ciphertext,length,cipher_key.toStdString().c_str(),cipher_key.length());

    project_file.close();
    return QString(plaintext).split('\n');
}

// encrypt the project data and write it into the file
void write_project_file(QString project_name, QString project_content, QString dir){

    dir = (dir == "<default>") ? "projects" : dir;

    QFile project_file(dir + "/" + project_name + "/" + project_name + (*proFileExt));
    project_file.open(QIODevice::WriteOnly);
    QDataStream project_file_stream(&project_file);

    const char* ciphertext = crypt(project_content.toStdString().c_str(),project_content.length(),cipher_key.toStdString().c_str(),cipher_key.length() );
    project_file_stream.writeRawData(ciphertext,project_content.length());

    project_file.close();
}

// wrapper for displaying an alert/information message
void msg(QString content){
    QMessageBox(QMessageBox::Information,"",content,QMessageBox::Yes).exec();
}

void write_projects_file(){
    QFile projects_file("projects.dat");
    projects_file.open(QIODevice::WriteOnly);
    QTextStream projects_file_str(&projects_file);
    projects_file_str << projects.size() << "\n";
    for(size_t i = 0; i < projects.size(); i++) {
        projects_file_str << projects[i].name << "\n";
        projects_file_str << projects[i].fullpath << "\n";
    }
    projects_file.close();
}

// currently unused
void read_projects_file(){
    QFile projects_file("projects.dat");
    projects_file.open(QIODevice::ReadOnly);
    QTextStream projects_file_str(&projects_file);
    QStringList content = projects_file_str.readAll().split("\n");
    projectC = content[0].toInt();
    Project new_project;
    for(int i = 1; i <= projectC; i++)
    {
        new_project.name = content[2 * i - 1];
        new_project.fullpath = content[2 * i];
        projects.push_back(new_project);
    }
}

void write_settings_file(){
    QFile file("settings.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream file_str(&file);

    QString content(defaultNewProjectDir);

    const char* ciphertext = crypt(content.toStdString().c_str(),content.length(),cipher_key.toStdString().c_str(),cipher_key.length() );
    file_str.writeRawData(ciphertext,content.length() );
    file.close();
}

void read_settings_file(){
    QFile file("settings.dat");
    unsigned int length = file.bytesAvailable();
    file.open(QIODevice::ReadOnly);
    char* ciphertext = new char[length];
    QDataStream file_str(&file);
    file_str.readRawData(ciphertext,length);
    const char* plaintext = crypt(ciphertext,length,cipher_key.toStdString().c_str(),cipher_key.length(),true);
    file.close();

    QString content(plaintext);
    QStringList content_list(content.split("\n") );

    defaultNewProjectDir = content_list[0];

}

void viewVector(){
    for(unsigned int i = 0; i < projects.size(); i++)
    {
        qDebug() << projects[i].name << "\t" << projects[i].fullpath;
    }
}

QString get_project_name(QListWidgetItem* item){
    for(unsigned int i = 0; i < projects.size(); i++)
    {
        if(projects[i].widget == item)
        {
            return projects[i].name;
        }
    }
    return "";
}

QString get_project_dir(QListWidgetItem* item){
    for(unsigned int i = 0; i < projects.size(); i++)
    {
        if(projects[i].widget == item)
        {
            return projects[i].fullpath;
        }
    }
    return "";
}

QString get_project_dir(QString project_name){
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
