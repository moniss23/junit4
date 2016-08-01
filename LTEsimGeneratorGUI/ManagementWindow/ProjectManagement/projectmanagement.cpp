#include "projectmanagement.h"
#include "ui_projectmanagement.h"

#include <QFile>
#include <QDir>
#include <vector>
#include <QTextStream>
#include <QListWidget>
#include <QString>
#include <QStringList>
#include <QFileInfoList>
#include <QFileInfo>
#include <QMessageBox>

#include <ManagementWindow/ParametersWindow/parameterswindow.h>
#include <Maps/Parameters/MapWindow/mapwindow.h>
#include <ManagementWindow/Settings/settings.h>
#include <AppSettings/appsettings.h>


extern ParametersWindow* p;//TODO: get rid of that
void msg(QString content);
extern int project_index;//TODO: get rid of that


// constructor - loads the list of detected projects into the window view
ProjectManagement::ProjectManagement(AppSettings *appSettings, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ProjectManagement),
    appSettings(appSettings)
{
    ui->setupUi(this);
    this->setWindowTitle("Project management");


    //TODO: This window should not spawn any other one, it should be a separate subsystem
    createProject.setAppSettings(appSettings);
}

ProjectManagement::~ProjectManagement()
{
    delete ui;
}

/***********************************************
*   AUTOMATIC BINDINGS TO UI BUTTONS CODE HERE
***********************************************/
void ProjectManagement::on_newProject_Button_clicked()
{
    createProject.clearInputArea();
    createProject.setDefaultDir(appSettings->getDefaultNewProjectDir());
    createProject.show();
}

void ProjectManagement::on_openProject_Button_clicked()
{
    this->open_project();
}

// "delete project" button clicked
void ProjectManagement::on_deleteProject_Button_clicked(){
    QListWidgetItem *item = ui->listWidget->currentItem();
         if (item==NULL){
             return;
         }
         QString text = item->text();
         QString projectName=this->ui->listWidget->currentItem()->text().split("\t")[0];
         emit deleteProject(projectName);
}

// "import project" button is clicked
void ProjectManagement::on_importProject_Button_clicked()
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



    //TODO: This should be done by invoking updateProjectLists slot
    // update UI
    this->ui->listWidget->addItem(new_item);
    this->ui->listWidget->setCurrentItem(new_item);
    this->ui->listWidget->item(this->ui->listWidget->currentRow())->setSelected(true);

    // display message
    msg("Project \""+project_name+"\" in "+new_project.fullpath+" successfully imported.");

}

// "settings" button clicked
void ProjectManagement::on_settings_Button_clicked()
{
    Settings settingsWindow(appSettings, this,false);
    settingsWindow.setWindowModality(Qt::WindowModal);
    settingsWindow.exec();
}


/***********************************************
*   AUTOMATIC BINDINGS TO UI ACTIONS CODE HERE
***********************************************/

void ProjectManagement::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    (void) item;
    this->open_project();
}

void ProjectManagement::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(!ui->listWidget->count() or current==NULL){
           return;
    }
    (void) previous;
    this->previewProjectFiles(current);
}


/***********************************************
*   LOGIC CODE HERE
***********************************************/

void ProjectManagement::updateProjectLists(const std::vector<Project> &projects)
{
    this->ui->listWidget->clear();
    for(auto &&it:projects){
        new QListWidgetItem(it.name+"\t("+it.fullpath+")", ui->listWidget);
    }
    if (!ui->listWidget->count()) {
        allowManagingProjects(false);
        return;
    }
    ui->listWidget->setCurrentRow(0);
}



/***********************************************
*   OLD LOGIC CODE HERE, TODO: DISPOSE
***********************************************/
void ProjectManagement::addWidgetToListWidget(QListWidgetItem *new_item) {
    this->ui->listWidget->addItem(new_item);
}

void ProjectManagement::setButtonsStates(QListWidgetItem *new_item) {
    this->previewProjectFiles(new_item);

    this->ui->listWidget->setCurrentItem(new_item);
    this->ui->openProject_Button->setEnabled(true);
    this->ui->deleteProject_Button->setEnabled(true);
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

// display project's files in the right view
void ProjectManagement::previewProjectFiles(QListWidgetItem* item){

    // read the selected project's name and directory from the projects vector
    QString project_name;
    QString project_dir;
    for(unsigned int i=0; i<appSettings->projects.size(); i++){
        if(appSettings->projects[i].name==item->text().split("\t")[0]){
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

QListWidgetItem* ProjectManagement::getCurrentItem(){
    return this->ui->listWidget->currentItem();
}

void ProjectManagement::allowManagingProjects(bool permission)
{
    this->ui->openProject_Button->setEnabled(permission);
    this->ui->deleteProject_Button->setEnabled(permission);
    this->ui->listWidget_2->clear();
}
