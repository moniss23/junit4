#include "projectmanagement.h"
#include "ui_projectmanagement.h"
#include <QFile>
#include <QDir>
#include <vector>
#include <QTextStream>
#include <QListWidgetItem>
#include <QListWidget>
#include <QList>
#include <QString>
#include <QStringList>
#include <QFileInfoList>
#include <QFileInfo>
#include <QMessageBox>
#include <QLayout>
#include <QDebug>

#include <ManagementWindow/ParametersWindow/parameterswindow.h>
#include <ManagementWindow/Encryption/encryption.h>
#include <Maps/Parameters/MapWindow/mapwindow.h>
#include <ManagementWindow/Settings/settings.h>
#include <AppSettings/appsettings.h>


extern ParametersWindow* p;

extern QString* proFileExt;


extern bool changesPresent;
extern bool lastMapOpenWasNormal;

bool deletionInProgress=false;

std::vector<QListWidgetItem*> list_items;
unsigned int listC=0;

extern MapWindow* map_w;
extern Settings* settingsWindowPW;
extern Settings* settingsWindowPM;

void msg(QString content);
void viewVector(const std::vector<Project> &projects);

extern int project_index;

// constructor - loads the list of detected projects into the window view
ProjectManagement::ProjectManagement(AppSettings *appSettings, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ProjectManagement),
    appSettings(appSettings)
{
    ui->setupUi(this);

    this->setWindowTitle("Project management");

    // settings appSettings reference to FileDialog
    setFileDialogAppSettings(appSettings);


    std::vector<QListWidgetItem*> widget_vector = appSettings->loadSettings();

    for(const auto &it : widget_vector) {
        this->ui->listWidget->addItem(it);
    }


    // enable or disable buttons accordingly
    if(appSettings->projects.size()>0){
        this->ui->listWidget->item(0)->setSelected(true);
        this->ui->listWidget->setCurrentRow(0);
        this->ui->pushButton->setEnabled(true);
        this->ui->pushButton_3->setEnabled(true);
    }
    else{
        this->ui->pushButton->setEnabled(false);
        this->ui->pushButton_3->setEnabled(false);
    }

    viewVector(appSettings->projects);

    appSettings->write_projects_file();

}

ProjectManagement::~ProjectManagement()
{
    delete ui;
}

QString ProjectManagement::getProjectDir(QString projectName){
    for(unsigned int i=0; i<appSettings->projects.size(); i++){
        if(appSettings->projects[i].name==projectName){
            return appSettings->projects[i].fullpath;
        }
    }
    return "";
}

void ProjectManagement::setDefaultDir(QString dir){
    this->createProject.setDefaultDir(dir);
}

QListWidgetItem* ProjectManagement::getCurrentItem(){
    return this->ui->listWidget->currentItem();
}

void ProjectManagement::addProject(QListWidgetItem* new_item,QString dir){

    this->ui->listWidget->addItem(new_item);

    Project new_project;
    new_project.name=new_item->text();
    new_project.fullpath=dir;
    new_project.widget=new_item;
    appSettings->projects.push_back(new_project);

    // if the project is to be saved in default directory
    if(dir=="<default>"){

        // create the project subdirectory
        QDir projectDir;
        projectDir.setPath("projects");
        projectDir.mkdir(appSettings->getProjectName());

        // append the settings, the name and content of parameters.rb template to project file
        QString project_content("<default>\nnormal\nParameters.rb\n0\n");
        QFile param_template(":/RbFiles/parameters.rb");
        param_template.open(QIODevice::ReadOnly);
        QTextStream param_template_str(&param_template);
        QString param_template_content=param_template_str.readAll();
        project_content+=itoa(param_template_content.split("\n").size());
        project_content+="\n";
        project_content+=param_template_content;
        project_content+="\n";
        param_template.close();

        // write the project file
        appSettings->write_project_file(new_item->text(),project_content,this->getProjectDir(new_item->text()));

    }

    // if the project is to be saved in custom directory
    else{

        QDir proj_dir;
        proj_dir.setPath(dir);
        proj_dir.mkdir(appSettings->getProjectName());

        // append the settings, the name and content of parameters.rb template to project file
        QString project_content("<default>\nnormal\nParameters.rb\n0\n");
        QFile param_template(":/RbFiles/parameters.rb");
        param_template.open(QIODevice::ReadOnly);
        QTextStream param_template_str(&param_template);
        QString param_template_content=param_template_str.readAll();
        project_content+=itoa(param_template_content.split("\n").size());
        project_content+="\n";
        project_content+=param_template_content;
        project_content+="\n";
        param_template.close();

        // write the project file
        appSettings->write_project_file(new_item->text(),project_content,dir);

    }

    this->previewProjectFiles(new_item);

    this->ui->listWidget->setCurrentItem(new_item);

    if(!this->ui->pushButton->isEnabled()){
        this->ui->pushButton->setEnabled(true);
    }
    if(!this->ui->pushButton_3->isEnabled()){
        this->ui->pushButton_3->setEnabled(true);
    }
}

void ProjectManagement::open_project(){

    QListWidgetItem* selected_item;

    // check which item in the list is selected
    if(!(this->ui->listWidget->selectedItems().isEmpty())){
        selected_item=this->ui->listWidget->selectedItems()[0];
    }
    else{
        selected_item=NULL;
    }

    // if some item is selected
    if(selected_item!=NULL){

        // obtain the name of the select project from the widget
        appSettings->setProjectName(selected_item->text().split("\t")[0]);

        // obtain the project's index in projects vector
        for(unsigned int i=0; i<appSettings->projects.size(); i++){
            if(appSettings->projects[i].widget==selected_item){
                project_index=i;
                break;
            }
        }

        this->close();

        p->show();

        p->loadProject();

    }
}

// when the "load project" button is clicked
void ProjectManagement::on_pushButton_clicked()
{
    this->open_project();
}

// when the "new project" button is clicked
void ProjectManagement::on_pushButton_2_clicked()
{
    createProject.clearInputArea();
    createProject.setDefaultDir(appSettings->getDefaultNewProjectDir());
    createProject.show();
}

// display project's files in the right view
void ProjectManagement::previewProjectFiles(QListWidgetItem* item){

    if(deletionInProgress)
        return;

    // read the selected project's name and directory from the projects vector
    QString project_name;
    QString project_dir;
    for(unsigned int i=0; i<appSettings->projects.size(); i++){
        if(appSettings->projects[i].widget==item){
            project_name=appSettings->projects[i].name;
            project_dir=appSettings->projects[i].fullpath;
            break;
        }
    }

    // clear the right list
    this->ui->listWidget_2->clear();

    QStringList project_data = appSettings->read_project_file(project_name,project_dir);

    QString parameters_file(project_data[2]);

    int traffic_files_count=project_data[3].toInt();

    QString file_name;

    // if the project file is empty, update the right list
    if(parameters_file=="<none>" && traffic_files_count==0){
        this->ui->listWidget_2->addItem("<empty>");
    }

    // if the project file is not empty
    else{
        this->ui->listWidget_2->addItem(parameters_file);
        for(int i=0; i<traffic_files_count; i++){
            file_name=project_data[4+i];
            this->ui->listWidget_2->addItem(file_name);
        }
    }

}

void ProjectManagement::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    (void) previous;
    this->previewProjectFiles(current);
}

// recursively remove entire directory and its content
void ProjectManagement::rmrf(QString dir_name){

    // prepare the list of the directory's content
    QDir directory("projects/"+dir_name);
    QFileInfoList dir_content=directory.entryInfoList();

    // traverse the list
    for(int i=0; i<dir_content.size(); i++){

        // if an element is a file, delete it
        if(dir_content[i].isFile()){
            directory.remove(dir_content[i].fileName());
        }

        // if an element is a directory, call rmrf() on it recursively, then delete it
        else if(dir_content[i].isDir()){

            // if it's parent dir or present dir, skip it
            if(dir_content[i].fileName()!="." && dir_content[i].fileName()!=".."){

                rmrf(dir_name+"/"+dir_content[i].fileName());
                directory.rmdir(dir_content[i].fileName());

            }

        }

    }

    directory.rmdir(directory.absolutePath());

}

// "delete project" button clicked
void ProjectManagement::on_pushButton_3_clicked(){

    deletionInProgress=true;

    if(appSettings->projects.size()>0 && QMessageBox::Yes==QMessageBox(QMessageBox::Question, "LTEsimGenerator", "Entire project will be deleted:\n"+this->ui->listWidget->currentItem()->text()+"\n\nThis cannot be reversed.\n\nAre you sure?", QMessageBox::No|QMessageBox::Yes).exec()){

        QString projectName;

        // remove the item from UI
        projectName=this->ui->listWidget->currentItem()->text().split("\t")[0];
        delete this->ui->listWidget->takeItem(this->ui->listWidget->currentRow());
        this->ui->listWidget_2->clear();

        // delete the project directory along with its entire content
        rmrf(projectName);

        // delete element from projects vector
        std::vector<Project>::iterator it;
        for(it=appSettings->projects.begin(); it!=appSettings->projects.end(); it++){
            if(projectName==(*it).name){
                break;
            }
        }
        appSettings->projects.erase(it);

        // decrement project counter

        if(appSettings->projects.size()>0){
            deletionInProgress=false;
            previewProjectFiles(this->ui->listWidget->currentItem());
            deletionInProgress=true;
        }
        else{
            this->ui->listWidget_2->clear();
            this->ui->pushButton->setEnabled(false);
            this->ui->pushButton_3->setEnabled(false);
        }

    }

    deletionInProgress=false;
}

void ProjectManagement::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    (void) item;
    this->open_project();
}

// "import project" button is clicked
void ProjectManagement::on_pushButton_4_clicked()
{

    // open a dialog to find the project's dir
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString import_dir=dialog.getExistingDirectory(this,tr("Find project directory"),"/");
    if(import_dir==""){
        return;
    }

    // verify validity of the project
    QStringList import_dir_exploded=import_dir.split("/");
    QString project_name(import_dir_exploded[import_dir_exploded.length()-1]);
    QFile import_file(import_dir+"/"+project_name+ appSettings->getProFileExt());
    if(!import_file.exists()){
        QMessageBox(QMessageBox::Critical,"","\""+import_dir+"\" does not seem to be a valid project directory.",QMessageBox::Ok).exec();
        return;
    }

    // create the project element for the vector
    Project new_project;
    new_project.name=project_name;
    QString vector_dir;

    int i=0;
    for(; i<import_dir_exploded.length()-2; i++){
        vector_dir+=import_dir_exploded[i];
        vector_dir+="/";
    }
    vector_dir+=import_dir_exploded[i];
    new_project.fullpath=vector_dir;

    // check if the project is already on the list
    for(size_t i=0; i<appSettings->projects.size(); i++){
        if(appSettings->projects[i].name==new_project.name && appSettings->projects[i].fullpath==new_project.fullpath){
            msg("Project is already present.");
            return;
        }
    }

    // if it's not, append it to the vector
    QListWidgetItem* new_item=new QListWidgetItem(project_name+"\t"+vector_dir);
    new_project.widget=new_item;
    appSettings->projects.push_back(new_project);

    // update the projects.dat file
    appSettings->write_projects_file();

    // update UI
    this->ui->listWidget->addItem(new_item);
    this->ui->listWidget->setCurrentItem(new_item);
    this->ui->listWidget->item(this->ui->listWidget->currentRow())->setSelected(true);

    // display message
    msg("Project \""+project_name+"\" in "+new_project.fullpath+" successfully imported.");

}

// "settings" button clicked
void ProjectManagement::on_pushButton_5_clicked()
{
    Settings settingsWindow(appSettings, this,false);
    settingsWindow.setWindowModality(Qt::WindowModal);
    settingsWindow.exec();
}

//Setting reference to AppSettings for FileDIalog
void ProjectManagement::setFileDialogAppSettings(AppSettings *value) {
    createProject.setAppSettings(value);
}
