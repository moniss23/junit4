#include "projectmanagement.h"
#include "ui_projectmanagement.h"

#include <QMessageBox>

// constructor
ProjectManagement::ProjectManagement(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ProjectManagement)
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
void ProjectManagement::on_deleteProject_Button_clicked(){
    QListWidgetItem *item = ui->listWidget->currentItem();
    if (item==NULL){
        return;
    }
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

void ProjectManagement::updateProjectLists(const QVector<Project> &projects)
{
    this->projects = projects;
    this->ui->listWidget->clear();
    for(auto &&it:projects){
        new QListWidgetItem(it.name+"\t("+it.fullpath+")", ui->listWidget);
    }
    updateUiState();
}



/***********************************************
*   OLD LOGIC CODE HERE, TODO: DISPOSE
***********************************************/

void ProjectManagement::open_project(){

    if( ui->listWidget->selectedItems().isEmpty()){
      return;
    }

    QListWidgetItem* selected_item = ui->listWidget->currentItem();
    if(selected_item == NULL){
        return;
    }

    QString projectName = selected_item->text().split("\t")[0];
    emit SpawnWindow_OpenProject(projectName);
}

// display project's files in the right view
void ProjectManagement::previewProjectFiles(QListWidgetItem* item){

    // clear the right list
    this->ui->listWidget_2->clear();

    if(item==NULL) return;

    QString ProjectName = item->text().split("\t")[0];

    auto it = std::find_if(std::begin(projects), std::end(projects),
                 [&ProjectName](const Project &val){return val.name == ProjectName;});
    if(it==std::end(projects)) return;

    ui->listWidget_2->addItem(it->parametersFile.fileName);

    QVector<TrafficData> &trafficFiles = it->trafficFilesList;
    for(auto &&trafficFile : trafficFiles){
        ui->listWidget_2->addItem(trafficFile.fileName);
    }

}

void ProjectManagement::updateUiState()
{
    bool objects = (ui->listWidget->count() > 0 );

    this->ui->openProject_Button->setEnabled(objects);
    this->ui->deleteProject_Button->setEnabled(objects);
    this->previewProjectFiles(ui->listWidget->currentItem());
}

