#include <QApplication>
#include <management_window/parameterswindow.h>
#include <management_window/projectmanagement.h>
#include <QString>
#include <QStringList>
#include <QDir>
#include <vector>
#include <QFile>
#include <maps/parameters_map/mapwindow.h>
#include <management_window/encryption.h>
#include <QDesktopWidget>
#include <QDebug>
#include <QListWidgetItem>
#include <management_window/settings.h>
#include <maps/parameters_map//mapwindowlarge.h>
#include <maps/traffic_map/map_traffic.h>
#include <maps/traffic_map/map_traffic_large.h>

const unsigned int cellCount=12;
const unsigned int handoverCount=21;
const unsigned int centerCount=12;

cellName cellNames[cellCount];
centerName centerNames[centerCount];
handoverName handoverNames[handoverCount];

QString* dir;
ParametersWindow *p;
ProjectManagement *projectMng;

QString* parametersFile;
QString* projectFile;
QString* projectName;
QDir* projectDir;
std::vector<QString*> trafficFilesNames;
std::vector<QFile*> trafficFiles;
int trafficFilesCount=0;

QString defaultNewProjectDir;

int projectC;
unsigned int project_index;

QString* proFileExt;
bool paramFilePresent;
QString *tabChangedParams;

std::vector<Project> projects;

MapWindow* map_w=NULL;
MapWindowLarge* map_wl=NULL;
Map_traffic* map_t =NULL;
Map_traffic_large* map_tl = NULL;

bool normalMapOpen=false;
bool largeMapOpen=false;

bool changesPresent=false;
bool anyProjectOpen=false;
bool settingsWindowOpen=false;

bool anyChangesInMap=false;

void msg(QString content);

extern QString defaultNewProjectDir;

void setCenterOfApplication(QWidget* widget)
{
    QDesktopWidget* desktop = QApplication::desktop();

    int my_width=widget->width();
    int my_height=widget->height();

    int width = desktop->width();
    int height = desktop->height();

    int centerW = (width/2) - (my_width/2);
    int centerH = (height/2) - (my_height/2);
    widget->move(centerW, centerH);
}

int main(int argc, char *argv[])
{
    projectName=new QString;

    QApplication a(argc, argv);
    dir = new QString ("kamil");
    proFileExt=new QString(".proj");
    parametersFile=new QString;
    projectFile=new QString;
    projectMng=new ProjectManagement;    
    setCenterOfApplication(projectMng);

    projectMng->show();

    read_settings_file();
    projectMng->setDefaultDir(defaultNewProjectDir);

    tabChangedParams = new QString [8];

    ParametersWindow viewParameters;
    p=&viewParameters;
    setCenterOfApplication(p);


    return a.exec();
}

const char* crypt(const char* plaintext,int text_len,const char* key,int key_len,bool terminatingZero){
    int key_pos=0;
    int len,i;
    if(terminatingZero){
        len=text_len+1;
    }
    else{
        len=text_len;
    }
    char* result=new char[len];
    for(i=0; i<text_len; i++){
        result[i]=plaintext[i]^key[key_pos];
        key_pos=(key_pos+1)%key_len;
    }
    if(terminatingZero){
        result[i]='\0';
    }
    return result;
}

// read the content of the project file, decrypt it and split it into a list
QStringList read_project_file(QString project_name,QString dir){

    if(dir=="<default>"){

        qDebug()<<"entering default case";

        QFile project_file("projects/"+project_name+"/"+project_name+(*proFileExt));
        project_file.open(QIODevice::ReadOnly);        
        unsigned int length=project_file.bytesAvailable();
        char* ciphertext=new char[length];

        QDataStream project_file_stream(&project_file);

        project_file_stream.readRawData(ciphertext,length);

        const char* plaintext=crypt(ciphertext,length,cipher_key.toStdString().c_str(),cipher_key.length());

        QString project_data(plaintext);

        project_file.close();
        return project_data.split('\n');

    }

    else{

        qDebug()<<"entering custom case";

        QFile project_file(dir+"/"+project_name+"/"+project_name+(*proFileExt));

        qDebug()<<"file name: "<<project_file.fileName();

        project_file.open(QIODevice::ReadOnly);
        unsigned int length=project_file.bytesAvailable();
        char* ciphertext=new char[length];

        QDataStream project_file_stream(&project_file);

        project_file_stream.readRawData(ciphertext,length);

        const char* plaintext=crypt(ciphertext,length,cipher_key.toStdString().c_str(),cipher_key.length());

        QString project_data(plaintext);

        project_file.close();
        return project_data.split('\n');

    }

}

// encrypt the project data and write it into the file
void write_project_file(QString project_name,QString project_content,QString dir){

    if(dir==QString("<default>")){

        QFile project_file("projects/"+project_name+"/"+project_name+(*proFileExt));
        project_file.open(QIODevice::WriteOnly);
        QDataStream project_file_stream(&project_file);

        const char* ciphertext=crypt(project_content.toStdString().c_str(),project_content.length(),cipher_key.toStdString().c_str(),cipher_key.length());
        project_file_stream.writeRawData(ciphertext,project_content.length());

        project_file.close();

    }

    else{

        QFile project_file(dir+"/"+project_name+"/"+project_name+(*proFileExt));
        project_file.open(QIODevice::WriteOnly);
        QDataStream project_file_stream(&project_file);

        const char* ciphertext=crypt(project_content.toStdString().c_str(),project_content.length(),cipher_key.toStdString().c_str(),cipher_key.length());
        project_file_stream.writeRawData(ciphertext,project_content.length());

        project_file.close();

    }
}

// wrapper for displaying an alert/information message
void msg(QString content){
    QMessageBox(QMessageBox::Information,"",content,QMessageBox::Yes).exec();
}

void write_projects_file(){
    QFile projects_file("projects.dat");
    projects_file.open(QIODevice::WriteOnly);
    QTextStream projects_file_str(&projects_file);
    projects_file_str<<projects.size()<<"\n";
    for(int i=0; i<projects.size(); i++){
        projects_file_str<<projects[i].name<<"\n";
        projects_file_str<<projects[i].fullpath<<"\n";
    }
    projects_file.close();
}

// currently unused
void read_projects_file(){
    QFile projects_file("projects.dat");
    projects_file.open(QIODevice::ReadOnly);
    QTextStream projects_file_str(&projects_file);
    QStringList content=projects_file_str.readAll().split("\n");
    projectC=content[0].toInt();
    Project new_project;
    for(int i=1; i<=projectC; i++){
        new_project.name=content[2*i-1];
        new_project.fullpath=content[2*i];
        projects.push_back(new_project);
    }
}

void write_settings_file(){
    QFile file("settings.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream file_str(&file);

    QString content(defaultNewProjectDir);
    qDebug()<<"writing settings file:\n"<<content;

    const char* ciphertext=crypt(content.toStdString().c_str(),content.length(),cipher_key.toStdString().c_str(),cipher_key.length());
    file_str.writeRawData(ciphertext,content.length());
    file.close();
}

void read_settings_file(){
    QFile file("settings.dat");
    unsigned int length=file.bytesAvailable();
    file.open(QIODevice::ReadOnly);
    char* ciphertext=new char[length];
    QDataStream file_str(&file);
    file_str.readRawData(ciphertext,length);
    const char* plaintext=crypt(ciphertext,length,cipher_key.toStdString().c_str(),cipher_key.length(),true);
    file.close();

    QString content(plaintext);
    qDebug()<<"reading settings file:\n"<<content;
    QStringList content_list(content.split("\n"));

    defaultNewProjectDir=content_list[0];

}

void viewVector(){
    for(unsigned int i=0; i<projects.size(); i++){
        qDebug()<<projects[i].name<<"\t"<<projects[i].fullpath;
    }
}

QString get_project_name(QListWidgetItem* item){
    for(unsigned int i=0; i<projects.size(); i++){
        if(projects[i].widget==item){
            return projects[i].name;
        }
    }
    return "";
}

QString get_project_dir(QListWidgetItem* item){
    for(unsigned int i=0; i<projects.size(); i++){
        if(projects[i].widget==item){
            return projects[i].fullpath;
        }
    }
    return "";
}

QString get_project_dir(QString project_name){
    for(unsigned int i=0; i<projects.size(); i++){
        if(projects[i].name==project_name){
            return projects[i].fullpath;
        }
    }
    return "";
}

Cell* getCellObj(QString name){
    for(unsigned int i=0; i<cellCount; i++){
        if(cellNames[i].name==name){
            return cellNames[i].obj;
        }
    }
    return NULL;
}

Center* getCenterObj(QString name){
    for(unsigned int i=0; i<centerCount; i++){
        if(centerNames[i].name==name){
            return centerNames[i].obj;
        }
    }
    return NULL;
}

Handover* getHandoverObj(QString name){
    for(unsigned int i=0; i<handoverCount; i++){
        if(handoverNames[i].name==name){
            return handoverNames[i].obj;
        }
    }
    return NULL;
}
