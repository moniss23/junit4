#include "parameterswindow.h"
#include "ui_parameterswindow.h"

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QStringList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QListWidgetItem>

#include <UISystem/Helpers/rubysyntaxhighlighter.h>
#include <Maps/Parameters/MapWindow/mapwindow.h>
#include <Maps/Traffic/map_traffic.h>


QString parametersFileContent;
QStringList parametersFileContentList;
extern Map_traffic* map_t;
QString text1;              // tekst znajdujący się w polu tekstowym
QString pattern;      // tekst, który zamienimy na inny
#include <QDebug>    //THIS WILL STAY TILL THE END OF REFACTOR

ParametersWindow::ParametersWindow(DataSystem *appSettings, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ParametersWindow),
    appSettings(appSettings)
{
    ui->setupUi(this);

    filePreviewChanged = false;

    this->ui->undoButton->setEnabled(false);
    this->ui->redoButton->setEnabled(false);
    this->ui->resetDefaultsButton->setEnabled(false);

    this->ui->filePreview->setReadOnly(false);
    highlighter =  std::make_unique<RubySyntaxHighlighter>(this->ui->filePreview->document());
}

void ParametersWindow::loadProjectAndOpen(const Project &project){

    refreshUI(project);

    //-----------REFACTOR IN PROGRESS------------
    parametersFileContent = project.parametersFile.content;
    parametersFileContent += "\n";

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
    emit SpawnWindow_ProjectMng();
    event->accept();
}
void ParametersWindow::on_actionOpen_triggered()
{
}

void ParametersWindow::on_actionSave_triggered()
{
    emit saveProjects();
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

    emit SpawnWindow_RenameFile(ui->projectsList->currentItem()->text(), currentProject.name);
}

// preview a file in the right field
void ParametersWindow::previewFile(QListWidgetItem* current){
    this->ui->filePreview->clear();

    if(current==NULL || this->ui->projectsList->currentItem()->text()=="<none>" || this->ui->projectsList->currentItem()->text()=="<empty>"){
        this->ui->filePreview->clear();
        return;
    }

    // if the file to preview is parameters
    if(this->ui->projectsList->item(0)->text()==current->text()){
        this->ui->filePreview->setText(currentProject.parametersFile.content);
    }
    // if the file is traffic
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
        }
    }
    filePreviewChanged = false;
    this->previewFile(current);
}

// file in the project double-clicked
void ParametersWindow::on_projectsList_itemDoubleClicked(QListWidgetItem *item)
{
    (void) item;

    if(this->ui->projectsList->currentRow()==0) {
    // parameters file double-clicked
    // create a new map object and display it
        emit SpawnWindow_ParamMap(currentProject.name);
    }
    else {
        map_t = new Map_traffic();
        map_t->show();
    }
}

/*
 * Reset defaults button clicked
 * CURRENTLY NOT IN USE
 */
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

   //highlighter->highlightBlock(this->ui->filePreview->toPlainText());
   return;
}

// "generate file" button is clicked
void ParametersWindow::on_generateFileButton_clicked()
{
    // if default dir is set
    if(currentProject.genScriptDir=="<default>"){

        // if the file is parameters
        if(this->ui->projectsList->currentRow()==0){

            QFile file;
            // if the location of the project is default
            if(currentProject.fullpath=="<default>"){
                file.setFileName("projects/"+currentProject.name+"/"+currentProject.parametersFile.filename);
            }
            // if the project's location is custom
            else{
                QString project_dir=currentProject.fullpath;
                file.setFileName(project_dir+"/"+currentProject.name+"/"+currentProject.parametersFile.filename);
            }

            if(file.exists()){
                if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","File already exists. Overwrite?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
                    return;
                }
            }

            file.open(QIODevice::WriteOnly);
            QTextStream file_str(&file);
            file_str<<currentProject.parametersFile.content;
            file.close();
            msg("File generated:\n"+this->ui->projectsList->item(0)->text());
        } else {// if the file is traffic

            // if the location of the project is default
            if(currentProject.fullpath=="<default>"){

                int file_index=this->ui->projectsList->currentRow()-1;
                QFile file("projects/"+currentProject.name+"/"+this->ui->projectsList->item(file_index+1)->text());
                if(file.exists()){
                    if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","File already exists. Overwrite?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
                        return;
                    }
                }
                file.open(QIODevice::WriteOnly);
                QTextStream file_str(&file);
                file_str<<currentProject.trafficFilesList[file_index].content;
                file.close();
                msg("File generated:\n"+this->ui->projectsList->item(file_index+1)->text());

            }

            // if the location of the project is custom
            else{

                QString project_dir=currentProject.fullpath;

                int file_index=this->ui->projectsList->currentRow()-1;
                QFile file(project_dir+"/"+currentProject.name+"/"+this->ui->projectsList->item(file_index+1)->text());
                if(file.exists()){
                    if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","File already exists. Overwrite?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
                        return;
                    }
                }
                file.open(QIODevice::WriteOnly);
                QTextStream file_str(&file);
                file_str<<currentProject.trafficFilesList[file_index].content;
                file.close();
                msg("File generated:\n"+this->ui->projectsList->item(file_index+1)->text());

            }
        }

    }

    // if the option is "individually"
    else if(currentProject.genScriptDir=="<individually>"){

        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::Directory);
        QString output_dir=dialog.getExistingDirectory(this,tr("Select output directory"),"/");

        // if it's a parameters file
        if(this->ui->projectsList->currentRow()==0){
            QFile ofile(output_dir+"/"+this->ui->projectsList->currentItem()->text());

            if(ofile.exists()){
                if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","File already exists. Overwrite?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
                    return;
                }
            }

            ofile.open(QIODevice::WriteOnly);
            QTextStream ofile_str(&ofile);
            ofile_str<<currentProject.parametersFile.content;
            ofile.close();
        }
        // if it's a traffic file
        else{
            QFile ofile(output_dir+"/"+this->ui->projectsList->currentItem()->text());
            ofile.open(QIODevice::WriteOnly);
            QTextStream ofile_str(&ofile);
            ofile_str<<currentProject.trafficFilesList[this->ui->projectsList->currentRow()-1].content;
            ofile.close();
        }
        msg("File \""+output_dir+"/"+this->ui->projectsList->currentItem()->text()+"\" was successfully created.");

    }
    // if option is custom
    else{

        // if the file is parameters
        if(this->ui->projectsList->currentRow()==0){

            QFile file(currentProject.genScriptDir+"/"+currentProject.parametersFile.filename);
            if(file.exists()){
                if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","File already exists. Overwrite?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
                    return;
                }
            }
            file.open(QIODevice::WriteOnly);
            QTextStream file_str(&file);
            file_str<<currentProject.parametersFile.content;
            file.close();
            msg("File generated:\n"+this->ui->projectsList->item(0)->text());

        }

        // if the file is traffic
        else{

            int file_index=this->ui->projectsList->currentRow()-1;
            QFile file(currentProject.genScriptDir+"/"+this->ui->projectsList->item(file_index+1)->text());
            if(file.exists()){
                if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","File already exists. Overwrite?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
                    return;
                }
            }
            file.open(QIODevice::WriteOnly);
            QTextStream file_str(&file);
            file_str<<currentProject.trafficFilesList[file_index].content;
            file.close();
            msg("File generated:\n"+this->ui->projectsList->item(file_index+1)->text());
        }
    }
}
// "settings" opened
void ParametersWindow::on_actionPath_triggered()
{
    emit SpawnWindow_Settings(currentProject.name);
}
void ParametersWindow::on_saveFileButton_clicked()
{
    //TODO: implement file saving on button click
}

void ParametersWindow::msg(const QString &content){
    QMessageBox(QMessageBox::Information,"",content,QMessageBox::Yes).exec();
}

void ParametersWindow::on_showCellMapButton_clicked()
{
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene();
    view->setScene(scene);

    scene->setSceneRect(-10, -10, 600, 600);
    view->setMinimumSize(600, 600);
    view->show();
}
