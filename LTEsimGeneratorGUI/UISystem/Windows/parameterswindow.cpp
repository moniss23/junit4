#include "parameterswindow.h"
#include "ui_parameterswindow.h"
#include <QMessageBox>
#include <QStringList>
#include <QListWidgetItem>

#include "UISystem/Helpers/rubysyntaxhighlighter.h"

ParametersWindow::ParametersWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ParametersWindow),
    filePreviewChanged(false)
{
    ui->setupUi(this);

    ui->projectsList->setAlternatingRowColors(true);
    ui->projectsList->setSelectionMode(QAbstractItemView::SingleSelection);

    this->ui->resetDefaultsButton->setEnabled(true);

    this->ui->filePreview->setReadOnly(false);
    highlighter =  std::make_unique<RubySyntaxHighlighter>(this->ui->filePreview->document());
}

void ParametersWindow::loadProjectAndOpen(const Project &project){

    refreshUI(project);
    setWindowTitle(project.name + " - LTEsimGenerator");
    showMaximized();
}

void ParametersWindow::on_projectsList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current == previous || current == nullptr) {
        return;
    }

    this->ui->filePreview->setReadOnly(this->ui->projectsList->currentRow()!=0);

    if (previous && filePreviewChanged) {

        if(QMessageBox::Yes == QMessageBox(QMessageBox::Information, "LTEsimGenerator", "File " +
                                           previous->text() + " has been changed. Do you want to save it?\n",
                                           QMessageBox::Yes|QMessageBox::No).exec()){
            emit updateFileContent(currentProject.name, previous->text(), this->ui->filePreview->toPlainText());
            filePreviewChanged = false;
            return;
        }
    }
    if (this->ui->projectsList->currentRow()==0) {
        this->ui->actionSave->setEnabled(true);
    }
    else {
        this->ui->actionSave->setEnabled(false);
    }
    previewFile(current);
    filePreviewChanged = false;
}

void ParametersWindow::refreshUI(const Project &project)
{
    int currentIndex=this->ui->projectsList->currentRow();
    currentProject = project;

    //BASIC UI REFRESH
    ui->projectsList->clear();

    //PARAMETERS FILE
    ui->projectsList->addItem(currentProject.parametersFile.filename);

    //TRAFFIC FILES
    for(auto &&it:currentProject.trafficFilesList){
        ui->projectsList->addItem(it.filename);
    }

    // REFRESH ACTIVE WINDOW


    ui->projectsList->setCurrentRow( currentIndex, QItemSelectionModel::ClearAndSelect);
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
void ParametersWindow::on_actionQuit_triggered()
{
    this->close();
}

void ParametersWindow::closeEvent(QCloseEvent *event) {
    emit spawnWindow_ProjectMng();
    event->accept();
}
void ParametersWindow::on_actionOpen_triggered()
{
    if (this->ui->projectsList->currentRow()<=-1) {
        msg("There's no selected file !");
        return;
    }
    else if(this->ui->projectsList->currentRow()==0) {
        emit spawnWindow_ParamMap(currentProject.name);
    }
    else {
        emit spawnWindow_TrafficMap(currentProject.name, this->ui->projectsList->currentItem()->text());
    }
}

void ParametersWindow::on_actionSave_triggered()
{
    if (this->ui->projectsList->currentRow()<=-1) {
        msg("There's no selected file !");
        return;
    }
    if(!filePreviewChanged) return;
    if (this->ui->projectsList->currentRow()==0){
        emit updateFileContent(currentProject.name, this->ui->projectsList->currentItem()->text(), this->ui->filePreview->toPlainText());
    }
    filePreviewChanged = false;
}

// "add traffic file" button clicked
void ParametersWindow::on_addTrafficButton_clicked()
{
    emit AddFile_Traffic(currentProject.name, QString());
    emit setDefaultTrafficFileContent(currentProject.name,currentProject.trafficFilesList.at(currentProject.trafficFilesList.size()-1).filename);
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
                this->ui->filePreview->setText(currentProject.trafficFilesList.at(i-1).content);
                break;
            }
        }
    }
}

// file in the project double-clicked
void ParametersWindow::on_projectsList_itemDoubleClicked(QListWidgetItem *item)
{
    (void) item;
    if(this->ui->projectsList->currentRow()==0) {
        emit spawnWindow_ParamMap(currentProject.name);
    }
    else {
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
    if(filePreviewChanged) {
        if(QMessageBox::Yes==QMessageBox(QMessageBox::Question,"LTEsimGenerator","Do you want to save " +
                                         ui->projectsList->currentItem()->text() + " file before generating script?\n",QMessageBox::Yes|QMessageBox::No).exec()){
            emit updateFileContent(currentProject.name, this->ui->projectsList->currentItem()->text(), this->ui->filePreview->toPlainText());
        }
        filePreviewChanged = false;
    }

    if(this->ui->projectsList->currentRow()==0) {
        emit generateParametersScript(currentProject);
    }
    else
    {
        int index=this->ui->projectsList->currentRow();
        emit setDefaultTrafficFileContent(currentProject.name,currentProject.trafficFilesList.at(currentProject.trafficFilesList.size()-1).filename);
        emit generateTrafficScript(currentProject, index-1);
    }
}

// "settings" opened
void ParametersWindow::on_actionPath_triggered()
{
    emit spawnWindow_Settings(currentProject.name);
}
void ParametersWindow::on_saveFileButton_clicked()
{

    if(!filePreviewChanged) return;

    emit updateFileContent(currentProject.name, this->ui->projectsList->currentItem()->text(), this->ui->filePreview->toPlainText());

    filePreviewChanged = false;

}

void ParametersWindow::msg(const QString &content){
    QMessageBox(QMessageBox::Information,"",content,QMessageBox::Yes).exec();
}


void ParametersWindow::on_generateAllFilesButton_clicked()
{
    if(filePreviewChanged) {
        if(QMessageBox::Yes==QMessageBox(QMessageBox::Question,"LTEsimGenerator","Do you want to save " +
                                         ui->projectsList->currentItem()->text() + " file before generating script?\n",QMessageBox::Yes|QMessageBox::No).exec()){
            emit updateFileContent(currentProject.name, this->ui->projectsList->currentItem()->text(), this->ui->filePreview->toPlainText());
        }
        filePreviewChanged = false;
    }

    emit generateParametersScript(currentProject);
    for(int i=1;i<this->ui->projectsList->count();i++)
        emit generateTrafficScript(currentProject, i-1);
}


void ParametersWindow::on_undoButton_clicked() { this->ui->filePreview->undo(); }
void ParametersWindow::on_redoButton_clicked() { this->ui->filePreview->redo(); }
