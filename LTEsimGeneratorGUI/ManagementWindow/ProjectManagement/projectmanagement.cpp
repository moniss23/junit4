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
#include <AppSettings/appsettings.h>


extern ParametersWindow* p;//TODO: get rid of that
void msg(QString content);
extern int project_index;//TODO: get rid of that


// constructor
ProjectManagement::ProjectManagement(AppSettings *appSettings, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ProjectManagement),
    appSettings(appSettings)
{
    ui->setupUi(this);
    this->setWindowTitle("Project management");
}

ProjectManagement::~ProjectManagement()
{
    delete ui;
}

/***********************************************
*   AUTOMATIC BINDINGS TO UI BUTTONS CODE HERE
***********************************************/

// "new project" button clicked
void ProjectManagement::on_newProject_Button_clicked()
{
    emit SpawnWindow_NewProject();
}

void ProjectManagement::on_openProject_Button_clicked()
{
    this->open_project();
}

// "delete project" button clicked
void ProjectManagement::on_deleteProject_Button_clicked() {
    QListWidgetItem *item = ui->listWidget->currentItem();
    if (item==NULL) {
        return;
    }

    shouldDeleteProject = false;

    QMessageBox msgBox(QMessageBox::Warning,"Delete a project.","Do you really want to delete this project?\nIt will be lost forever.");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Yes) {
        QString text = item->text();
        QString projectName = text.split("\t")[0];
        emit deleteProject(projectName);
    }
}

// "import project" button is clicked
void ProjectManagement::on_importProject_Button_clicked()
{
    emit SpawnWindow_ImportProject();
}

// "settings" button clicked
void ProjectManagement::on_settings_Button_clicked()
{
    emit SpawnWindow_Settings();
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
    (void) previous;

    if(current==NULL || !ui->listWidget->count()){
        return;
    }

    updateUiState();
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
    updateUiState();
}



/***********************************************
*   OLD LOGIC CODE HERE, TODO: DISPOSE
***********************************************/
void ProjectManagement::addWidgetToListWidget(QListWidgetItem *new_item) {
    this->ui->listWidget->addItem(new_item);
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
            if(appSettings->projects[i].name==selected_item->text()){
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

    // clear the right list
    this->ui->listWidget_2->clear();

    if(item==NULL) return;


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


void ProjectManagement::updateUiState()
{
    bool objects = (ui->listWidget->count() > 0 );

    this->ui->openProject_Button->setEnabled(objects);
    this->ui->deleteProject_Button->setEnabled(objects);
    this->previewProjectFiles(ui->listWidget->currentItem());
}
