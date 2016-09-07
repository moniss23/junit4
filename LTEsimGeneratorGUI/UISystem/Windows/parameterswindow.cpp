#include "parameterswindow.h"
#include "ui_parameterswindow.h"

#include <QMessageBox>
#include <QStringList>
#include <QListWidgetItem>

#include "UISystem/Helpers/rubysyntaxhighlighter.h"

#include "Maps/Traffic/map_traffic.h" //TODO: get rid of that
QStringList parametersFileContentList;// TODO: get rid of that

ParametersWindow::ParametersWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ParametersWindow)
{
    ui->setupUi(this);

    filePreviewChanged = false;

    this->ui->undoButton->setEnabled(false);
    this->ui->redoButton->setEnabled(false);
    this->ui->resetDefaultsButton->setEnabled(true);

    this->ui->filePreview->setReadOnly(false);
    highlighter =  std::make_unique<RubySyntaxHighlighter>(this->ui->filePreview->document());
}

void ParametersWindow::loadProjectAndOpen(const Project &project){

    refreshUI(project);

    //-----------REFACTOR IN PROGRESS------------
    QString parametersFileContent = project.parametersFile.content +"\n";
    parametersFileContentList = parametersFileContent.split('\n');

    show();
}

void ParametersWindow::refreshUI(const Project &project)
{
    currentProject = project;

    //BASIC UI REFRESH
    this->setWindowTitle(project.name);

    ui->projectsList->clear();

    //PARAMETERS FILE
    ui->projectsList->addItem(currentProject.parametersFile.filename);

    //TRAFFIC FILES
    for(auto &&it:currentProject.trafficFilesList){
        new QListWidgetItem(it.filename, ui->projectsList);
    }

    ui->projectsList->item(0)->setSelected(true);
    ui->projectsList->setCurrentRow(0);
}

ParametersWindow::~ParametersWindow()
{
    delete ui;
}

void ParametersWindow::on_actionNew_triggered()
{
}

void ParametersWindow::on_actionAbout_triggered()
{
    viewHelp.show();
}

void ParametersWindow::closeEvent(QCloseEvent *event) {
    emit spawnWindow_ProjectMng();
    event->accept();
}
void ParametersWindow::on_actionOpen_triggered()
{
}

void ParametersWindow::on_actionSave_triggered()
{
}

// "add traffic file" button clicked
void ParametersWindow::on_addTrafficButton_clicked()
{
    emit AddFile_Traffic(currentProject.name, QString());
}

// "remove file" button clicked
void ParametersWindow::on_removeFileButton_clicked()
{

    // if the file is traffic
    if(this->ui->projectsList->currentRow()>0){

        if(QMessageBox::Yes == QMessageBox(QMessageBox::Information, "LTEsimGenerator", "File will be removed from the project:\n"+(this->ui->projectsList->currentItem()->text())+"\n\nAre you sure?", QMessageBox::Yes|QMessageBox::No).exec()){
            emit removeFile_TrafficFile(currentProject.name, this->ui->projectsList->currentItem()->text());
        }
    }
    // if the file is parameters
    else{
        QMessageBox(QMessageBox::Information,"Warning","Can't delete parameters file",QMessageBox::Ok).exec();
        return;
    }
}

// "rename file" button clicked
void ParametersWindow::on_renameFileButton_clicked()
{
    if(this->ui->projectsList->currentItem()->text()=="<none>" || this->ui->projectsList->currentItem()->text()=="<empty>"){
        return;
    }
    emit spawnWindow_RenameFile(ui->projectsList->currentItem()->text(), currentProject.name);
}

// preview a file in the right field
void ParametersWindow::previewFile(QListWidgetItem* current){
    this->ui->filePreview->clear();

    if(this->ui->projectsList->item(0)->text()==current->text()){
        this->ui->filePreview->setText(currentProject.parametersFile.content);
    }
    else{
        for(int i=1; i<=currentProject.trafficFilesList.size(); i++){
            if(this->ui->projectsList->item(i)->text()==current->text()){
                this->ui->filePreview->setText(currentProject.trafficFilesList[i-1].content);
                break;
            }
        }
    }
}

void ParametersWindow::on_projectsList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current == previous || previous == nullptr || current == nullptr) {
        if(current != nullptr) {
            this->previewFile(current);
        }
        return;
    }
    if(filePreviewChanged) {
        if(QMessageBox::Yes == QMessageBox(QMessageBox::Information, "LTEsimGenerator", "File " +
                                           previous->text() + " has been changed. Do you want to save it?\n",
                                           QMessageBox::Yes|QMessageBox::No).exec()){
            emit updateFileContent(currentProject.name, previous->text(), this->ui->filePreview->toPlainText());
            emit saveProjects();
            return;
        }
    }
    filePreviewChanged = false;
    previewFile(current);
}

// file in the project double-clicked
void ParametersWindow::on_projectsList_itemDoubleClicked(QListWidgetItem *item)
{
    (void) item;
    if(this->ui->projectsList->currentRow()==0) {
        emit spawnWindow_ParamMap(currentProject.name);
    }
    else {
        Map_traffic* map_t;
        map_t = new Map_traffic();//TODO:delete old Map_traffic in a future
        map_t->show();
        emit spawnWindow_TrafficMap(currentProject.name, this->ui->projectsList->currentItem()->text());
    }
}

void ParametersWindow::on_resetDefaultsButton_clicked()
{
    // if the file is parameters
    if(this->ui->projectsList->currentRow()==0){
        if(QMessageBox::Yes==QMessageBox(QMessageBox::Question,"LTEsimGenerator","Entire file content will be reverted to default state. All changes will be lost. Proceed?",QMessageBox::Yes|QMessageBox::No).exec()){
            emit setDefaultParametersFileContent(currentProject.name);
            this->ui->resetDefaultsButton->setEnabled(false);
        }
    }
    // if the file is traffic
    else{
        // ask for confirmation
        if(QMessageBox::Yes==QMessageBox(QMessageBox::Question,"LTEsimGenerator","Entire file content will be reverted to default state. All changes will be lost. Proceed?",QMessageBox::Yes|QMessageBox::No).exec()){
            emit setDefaultTrafficFileContent(currentProject.name, this->ui->projectsList->currentItem()->text());
            this->ui->resetDefaultsButton->setEnabled(false);
        }
    }
}

//Currently not is use but prepared for later.
void ParametersWindow::on_filePreview_textChanged()
{
    if(this->ui->filePreview->hasFocus()){
        filePreviewChanged=true;
        this->ui->resetDefaultsButton->setEnabled(true);
    }
}

// "generate file" button is clicked
void ParametersWindow::on_generateFileButton_clicked()
{
    if(this->ui->projectsList->currentRow()==0)
        emit generateParametersScript(currentProject);
    else
        emit generateTrafficScript(currentProject, this->ui->projectsList->currentRow()-1);
}

// "settings" opened
void ParametersWindow::on_actionPath_triggered()
{
    emit spawnWindow_Settings(currentProject.name);
}
void ParametersWindow::on_saveFileButton_clicked()
{
    //TODO: implement file saving on button click
}

void ParametersWindow::msg(const QString &content){
    QMessageBox(QMessageBox::Information,"",content,QMessageBox::Yes).exec();
}

void ParametersWindow::on_saveFileButton_pressed()
{
    if(!filePreviewChanged) return;

    emit updateFileContent(currentProject.name, this->ui->projectsList->currentItem()->text(), this->ui->filePreview->toPlainText());
    emit saveProjects();

    filePreviewChanged = false;
}
