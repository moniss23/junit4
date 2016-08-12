#include "parameterswindow.h"
#include "ui_parameterswindow.h"
#include <QTextStream>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QListWidgetItem>
#include <QCloseEvent>
#include <QInputDialog>
#include <cmath>

#include <ManagementWindow/ProjectManagement/projectmanagement.h>
#include <Maps/Parameters/MapWindow/mapwindow.h>
#include <ManagementWindow/Settings/settings.h>
#include <Maps/Traffic/map_traffic.h>


QVector<QStringList> trafficFilesContentLists;
int currentOpenedTrafficFile;
QString parametersFileContent;
QStringList parametersFileContentList;
QVector<QString> trafficFilesContent;
QVector<QString> savedTrafficFilesContent;
bool paramFileModified;
QVector<bool> trafficFilesChanged;
QVector<bool> trafficFilesModified;
bool enableChangeRegistration=true;
bool previewFileInProgress=false;
bool closingInProgress=false;
bool fileAdditionInProgress=false;
bool enteringMapView;
extern QVector<QString*> trafficFilesNames;
extern MapWindow* map_w;
extern Map_traffic* map_t;
extern bool changesPresent;
int nrOfTrafficFiles=0;
void msg(QString content);
QString text1;              // tekst znajdujący się w polu tekstowym
QString pattern;      // tekst, który zamienimy na inny

#include <QDebug> //THIS WILL STAY TILL THE END OF REFACTOR

ParametersWindow::ParametersWindow(DataSystem *appSettings, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ParametersWindow),
    appSettings(appSettings)
{
    ui->setupUi(this);

    changesPresent=false;

    this->ui->undoButton->setEnabled(false);
    this->ui->redoButton->setEnabled(false);
    this->ui->resetDefaultsButton->setEnabled(false);

    this->ui->radioButton_normalMap->setChecked(true);

}

void ParametersWindow::closeEvent (QCloseEvent *event){

    if(enteringMapView){
        event->accept();
    }

    else if(changesPresent){
        int ret=QMessageBox(QMessageBox::Information, "LTEsimGenerator", "There are unsaved changes in the project. Save?", QMessageBox::Cancel|QMessageBox::No|QMessageBox::Yes).exec();

        if(ret==QMessageBox::Cancel){
            event->ignore();
        }
        else{

            enableChangeRegistration=false;
            closingInProgress=true;

            switch(ret){
            case QMessageBox::Yes:

                this->saveProject(false);

                trafficFilesNames.clear();
                nrOfTrafficFiles=0;
                this->ui->projectsList->clear();

                break;

            case QMessageBox::No:

                trafficFilesNames.clear();
                nrOfTrafficFiles=0;
                this->ui->projectsList->clear();

                break;
            }
            event->accept();
        }
    }

    else{

        enableChangeRegistration=false;
        closingInProgress=true;

        trafficFilesNames.clear();
        nrOfTrafficFiles=0;
        this->ui->projectsList->clear();
        this->close();

        event->accept();
    }

}

void ParametersWindow::loadProjectAndOpen(const QString &projectName){

    QVector<Project> &vec = appSettings->projects;
    auto it = std::find_if(vec.begin(), vec.end(), [&projectName](const Project& project)-> bool {
        return (project.name == projectName);
    });

    if(it==vec.end()) {return;}
    Project &GivenProject = *it;
    this->currentProject = GivenProject;



    // reset the vectors
    for(auto it=trafficFilesNames.begin(); it!=trafficFilesNames.end(); it++){
        delete (*it);
    }
    trafficFilesNames.clear();
    trafficFilesContent.clear();
    trafficFilesChanged.clear();
    parametersFileContentList.clear();
    paramFileModified=false;
    trafficFilesModified.clear();

    // set the window title
    this->setWindowTitle(projectName);

    QListWidgetItem* new_item;
    QString line;
    int project_content_line=0;
    int paramFileLen;
    int trafficFileLen;

    // read the project content from the project file
    QStringList project_content=appSettings->read_project_file(projectName,appSettings->getProjectDirectory(projectName));
    // read the default location for output .rb files
    QString ParamFileName = project_content[0];
    this->ui->radioButton_normalMap->setChecked(true);
    // read the name of parameters file and nr of traffic files
    nrOfTrafficFiles=project_content[2].toInt();
    project_content_line=4;


   //-----------REFACTOR IN PROGRESS------------
   //Set first list item to paremeters file name
   qDebug()<<GivenProject.parametersFile.fileName;
   ui->projectsList->addItem(GivenProject.parametersFile.fileName);

   parametersFileContent = GivenProject.parametersFile.content;
   parametersFileContent+="\n";
   //-----------REFACTOR IN PROGRESS------------

   QVector<TrafficData> trafficFilesList;

    // read the traffic file names
    for(int i=0; i<nrOfTrafficFiles; i++){
        line=project_content[i+4];

        //-----------REFACTOR IN PROGRESS---------------
        //Add trafficFile with filename from file.
        emit AddFile_Traffic(currentProject.name, line);

        new_item=new QListWidgetItem(line);
        this->ui->projectsList->addItem(new_item);
        trafficFilesNames.push_back(new QString(line));
        trafficFilesChanged.push_back(false);
        trafficFilesModified.push_back(false);
    }

    project_content_line+=nrOfTrafficFiles;
    // read the content of the parameters file
    paramFileLen=project_content[project_content_line].toInt();
    project_content_line++;
    for(int i=0; i<paramFileLen; i++){
        project_content_line++;
    }

    // insert param file content into a list of lines
    parametersFileContentList=parametersFileContent.split("\n");
    // read the content of all traffic files
    for(int i=0; i<nrOfTrafficFiles; i++){
        trafficFileLen=project_content[project_content_line].toInt();
        project_content_line++;
        trafficFilesContent.push_back("");
        savedTrafficFilesContent.push_back("");
        for(int j=0; j<trafficFileLen; j++){
            trafficFilesContent[i].append(project_content[project_content_line]);
            savedTrafficFilesContent[i].append(project_content[project_content_line]);
            trafficFilesContent[i].append("\n");
            savedTrafficFilesContent[i].append("\n");
            project_content_line++;
        }
    }


    this->ui->projectsList->item(0)->setSelected(true);
    this->ui->projectsList->setCurrentRow(0);


    changesPresent=false;

    if(this->ui->projectsList->item(0)->text().endsWith("*")){
        this->ui->projectsList->item(0)->setText(this->ui->projectsList->item(0)->text().left(this->ui->projectsList->item(0)->text().size()-1));
    }

    if(this->windowTitle().endsWith("*")){
        this->setWindowTitle(this->windowTitle().left(this->windowTitle().length()-1));
    }


    show();
}

void ParametersWindow::refreshUI(const Project &project)
{
    currentProject = project;

    //BASIC UI REFRESH
    this->setWindowTitle(project.name);
    this->ui->radioButton_normalMap->setChecked(true);

    ui->projectsList->clear();

    //PARAMETERS FILE
    ui->projectsList->addItem(currentProject.parametersFile.fileName);

    //TRAFFIC FILES
    for(auto &&it:currentProject.trafficFilesList){
        new QListWidgetItem(it.fileName, ui->projectsList);
    }

    ui->projectsList->item(0)->setSelected(true);
    ui->projectsList->setCurrentRow(0);
}

void ParametersWindow::addTrafficFile()
{
    QString new_file_name;
    QListWidgetItem* new_item;
    bool name_unique=false;
    int i=0;


    // generate unique file name
    while(!name_unique){
        new_file_name="Traffic_"+QString::number(i)+".rb";
        name_unique=true;
        for(auto j=0; j<trafficFilesNames.size(); j++){
            if(new_file_name==trafficFilesNames[j]){
                name_unique=false;
                break;
            }
        }
        i++;
    }



    nrOfTrafficFiles++;

    trafficFilesNames.push_back(new QString(new_file_name));
    trafficFilesChanged.push_back(false);
    trafficFilesModified.push_back(false);

    QStringList new_list;
    trafficFilesContent.push_back("");
    savedTrafficFilesContent.push_back("");
    trafficFilesContentLists.push_back(new_list);
    //source.close();



    new_item=new QListWidgetItem(new_file_name);
    this->ui->projectsList->addItem(new_item);
    new_item->setSelected(true);
    this->ui->projectsList->setCurrentItem(new_item);

    this->previewFile(new_item);

    if(!changesPresent){
        changesPresent=true;
        this->setWindowTitle(this->windowTitle()+"*");
    }
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

void ParametersWindow::saveProject(bool singleFile=false){

    // remove * symbol wherever it is present
    if(this->windowTitle().endsWith("*")){
        this->setWindowTitle(this->windowTitle().left(this->windowTitle().size()-1));
    }

    if(this->ui->projectsList->item(0)->text().endsWith("*")){
        this->ui->projectsList->item(0)->setText(this->ui->projectsList->item(0)->text().left(this->ui->projectsList->item(0)->text().size()-1));
    }

    for(int i=0; i<nrOfTrafficFiles; i++){
        if(this->ui->projectsList->item(i+1)->text().endsWith("*")){
            this->ui->projectsList->item(i+1)->setText(this->ui->projectsList->item(i+1)->text().left(this->ui->projectsList->item(i+1)->text().size()-1));
        }
    }

    for(int i=0; i<nrOfTrafficFiles; i++){
        if(trafficFilesNames[i]->endsWith("*")){
            (*trafficFilesNames[i])=(*trafficFilesNames[i]).left((*trafficFilesNames[i]).length()-1);
        }
    }

    // save the content of currently selected file
    if(this->ui->projectsList->currentRow()==0){

    }
    else{
        int index=this->ui->projectsList->currentRow()-1;
        trafficFilesContent[index]=this->ui->filePreview->toPlainText();
    }

    QString plaintext("");

    // if entire project is to be saved
    if(!singleFile){

        // set all "changed" flags to false
        if(changesPresent){
            changesPresent=false;
        }

        for(auto it=trafficFilesChanged.begin(); it!=trafficFilesChanged.end(); it++){
            (*it)=false;
        }

        // copy all content from temp to actual
        for(int i=0; i<nrOfTrafficFiles; i++){
            savedTrafficFilesContent[i]=trafficFilesContent[i];
        }
    }

    // if only one file is to be saved, only copy that file's content from temp to actual
    else{
            int file_index=this->ui->projectsList->currentRow()-1;
            trafficFilesChanged[file_index]=false;
            savedTrafficFilesContent[file_index]=trafficFilesContent[file_index];
    }

    // add param file name
    plaintext.append(this->currentProject.parametersFile.fileName);
    plaintext.append("\n");

    // add nr of traffic files
    plaintext.append(QString::number(nrOfTrafficFiles));
    plaintext.append("\n");

    // add names of traffic files
    for(int i=0; i<nrOfTrafficFiles; i++){
        (*trafficFilesNames[i])=(this->ui->projectsList->item(i+1)->text());
    }

    for(int i=0; i<nrOfTrafficFiles; i++){
        plaintext.append((*trafficFilesNames[i]));
        plaintext.append("\n");
    }

    // add length and content of traffic files
    for(int i=0; i<nrOfTrafficFiles; i++){
        plaintext.append(QString::number(savedTrafficFilesContent[i].split("\n").length()));
        plaintext.append("\n");
        plaintext.append(savedTrafficFilesContent[i]);
        plaintext.append("\n");
    }

    // encrypt the project data and write it to file
    QString projectName = currentProject.name;
    appSettings->write_project_file(projectName,plaintext,appSettings->get_project_dir(projectName));
}

void ParametersWindow::on_actionOpen_triggered()
{

    if(changesPresent){

        int ret=QMessageBox(QMessageBox::Information, "LTEsimGenerator", "There are unsaved changes in the project. Save?", QMessageBox::Cancel|QMessageBox::No|QMessageBox::Yes).exec();

        switch(ret){
        case QMessageBox::Yes:

            enableChangeRegistration=false;
            closingInProgress=true;

            this->saveProject(true);

            trafficFilesNames.clear();
            nrOfTrafficFiles=0;
            this->ui->projectsList->clear();
            this->close();

            break;

        case QMessageBox::No:

            enableChangeRegistration=false;

            trafficFilesNames.clear();
            nrOfTrafficFiles=0;
            this->ui->projectsList->clear();
            this->close();

            break;

        case QMessageBox::Cancel:

            break;

        }

        changesPresent=false;
        closingInProgress=false;
    }

    else{

        enableChangeRegistration=false;
        closingInProgress=true;

        trafficFilesNames.clear();
        nrOfTrafficFiles=0;
        this->ui->projectsList->clear();
        this->close();

        closingInProgress=false;
    }
}

void ParametersWindow::on_actionSave_triggered()
{
    this->saveProject(true);
}

void ParametersWindow::previewTrafficFile(){
}

// "add traffic file" button clicked
void ParametersWindow::on_addTrafficButton_clicked()
{
    fileAdditionInProgress=true;
    this->addTrafficFile();
    fileAdditionInProgress=false;

    emit AddFile_Traffic(currentProject.name, QString(""));
}

// "remove file" button clicked
void ParametersWindow::on_removeFileButton_clicked()
{

    // if the file is traffic
    if(this->ui->projectsList->currentRow()>0){

        if(QMessageBox::Yes == QMessageBox(QMessageBox::Information, "LTEsimGenerator", "File will be removed from the project:\n"+(this->ui->projectsList->currentItem()->text())+"\n\nAre you sure?", QMessageBox::Yes|QMessageBox::No).exec()){

            // delete file name from the vector
            auto it=trafficFilesNames.begin();
            it+=this->ui->projectsList->currentRow()-1;
            QString* mem=trafficFilesNames[this->ui->projectsList->currentRow()-1];
            trafficFilesNames.erase(it);
            delete mem;

            // delete file content from the vector
            auto it2=trafficFilesContent.begin();
            it2+=this->ui->projectsList->currentRow()-1;
            trafficFilesContent.erase(it2);

            // delete item from the UI list
            delete this->ui->projectsList->takeItem(this->ui->projectsList->currentRow());

            nrOfTrafficFiles--;

            if(!changesPresent){
                changesPresent=true;
                this->setWindowTitle(this->windowTitle()+"*");
            }

        }

    }

    // if the file is parameters
    else{
        return;//PSKAL: YOU DO NOT DELETE PARAMETERS FILE !
    }
}

// "rename file" button clicked
void ParametersWindow::on_renameFileButton_clicked()
{
    if(this->ui->projectsList->currentItem()->text()=="<none>" || this->ui->projectsList->currentItem()->text()=="<empty>"){
        return;
    }

    emit SpawnWindow_RenameFile(ui->projectsList->currentItem()->text());
}

// preview a file in the right field
void ParametersWindow::previewFile(QListWidgetItem* current){

    enableChangeRegistration=false;
    previewFileInProgress=true;

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
        for(int i=1; i<=nrOfTrafficFiles; i++){
            if(this->ui->projectsList->item(i)->text()==current->text()){
                this->ui->filePreview->setText(trafficFilesContent[i-1]);
                break;
            }
        }
    }

    enableChangeRegistration=true;
    previewFileInProgress=false;

}

void ParametersWindow::refreshPreview(){
    this->previewFile(this->ui->projectsList->currentItem());
}

void ParametersWindow::on_projectsList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{

    if(current==previous || closingInProgress || fileAdditionInProgress){
        return;
    }

    // if the previous file was parameters
    if(previous==this->ui->projectsList->item(0)){
        parametersFileContent=this->ui->filePreview->toPlainText();
    }

    // if the file was traffic
    else{

        // find the index of the file which was being previewed and save the content of filePreview widget
        for(int i=1; i<=nrOfTrafficFiles; i++){
            if(previous==this->ui->projectsList->item(i)){
                trafficFilesContent[i-1]=this->ui->filePreview->toPlainText();
                break;
            }
        }

    }

    // if the new file is parameters
    if(current==this->ui->projectsList->item(0)){
        if(paramFileModified){
            this->ui->resetDefaultsButton->setEnabled(true);
        }
        else{
            this->ui->resetDefaultsButton->setEnabled(false);
        }
    }

    else{
        if(trafficFilesModified[this->ui->projectsList->currentRow()-1]){
            this->ui->resetDefaultsButton->setEnabled(true);
        }
        else{
            this->ui->resetDefaultsButton->setEnabled(false);
        }
    }

    this->previewFile(current);

}


// file in the project double-clicked
void ParametersWindow::on_projectsList_itemDoubleClicked(QListWidgetItem *item)
{
    (void) item;

    // parameters file double-clicked
    if(this->ui->projectsList->currentRow()==0){
        enteringMapView=true;
        // if normal map is to be displayed
        // delete current map objects if they are present
        if(map_w!=NULL){
            delete map_w;
            map_w=NULL;
        }


        // create a new map object and display it
        map_w=new MapWindow;
        close();
        map_w->show();
    }

    // traffic file double-clicked
    else if(this->ui->projectsList->currentRow()>0){
        // store the index of the opened traffic file in a global variable
        currentOpenedTrafficFile=this->ui->projectsList->currentRow()-1;
    }
    if(this->ui->projectsList->currentRow()>0){
        // store the index of the opened traffic file in a global variable
        currentOpenedTrafficFile=this->ui->projectsList->currentRow()-1;

        // delete current map objects if they are present
        if(map_t!=NULL){
            delete map_t;
            map_t=NULL;

        }
        map_t =new Map_traffic(appSettings);
        map_t->show();



    }
}

// "defaults" button clicked
void ParametersWindow::on_resetDefaultsButton_clicked()
{
    // if the file is parameters
    if(this->ui->projectsList->currentRow()==0){

        // only proceed if the file was modified relative to template
        if(paramFileModified){

            // ask for confirmation
            if(QMessageBox::Yes==QMessageBox(QMessageBox::Question,"LTEsimGenerator","Entire file content will be reverted to default state. All changes will be lost. Proceed?",QMessageBox::Yes|QMessageBox::No).exec()){

                QString fileContent=appSettings->GetDefaultParametersFileContent();
                this->ui->filePreview->setText(fileContent);
                //parametersFileContent=fileContent;
                // emit ProjectChanged(currentProject);


                paramFileModified=false;
                this->ui->resetDefaultsButton->setEnabled(false);
            }
        }
    }

    // if the file is traffic
    else{

        // only proceed if the file was modified relative to template
        if(trafficFilesModified[this->ui->projectsList->currentRow()-1]){

            // ask for confirmation
            if(QMessageBox::Yes==QMessageBox(QMessageBox::Question,"LTEsimGenerator","Entire file content will be reverted to default state. All changes will be lost. Proceed?",QMessageBox::Yes|QMessageBox::No).exec()){
                QFile file(":/RbFiles/tune_traffic_models.rb");
                file.open((QIODevice::ReadOnly));
                QTextStream s(&file);
                QString fileContent=s.readAll();
                this->ui->filePreview->setText(fileContent);
                trafficFilesContent[this->ui->projectsList->currentRow()-1]=fileContent;
                file.close();
                trafficFilesModified[this->ui->projectsList->currentRow()-1]=false;
                this->ui->resetDefaultsButton->setEnabled(false);
            }
        }
    }

}

void ParametersWindow::on_filePreview_textChanged()
{

    // detect whether previewing of file is in progress
    if(previewFileInProgress){
        return;
    }

    // detect whether closing is in progress
    if(closingInProgress){
        return;
    }

    if(!this->ui->filePreview->hasFocus()){
        return;
    }

    if(!changesPresent){
        changesPresent=true;
    }



    // if it's a param file
    if(this->ui->projectsList->currentRow()==0){
        if(!paramFileModified){
            paramFileModified=true;
            this->ui->resetDefaultsButton->setEnabled(true);
        }

    }

    // if it's a traffic file
    else{
        if(!trafficFilesChanged[this->ui->projectsList->currentRow()-1]){
            trafficFilesChanged[this->ui->projectsList->currentRow()-1]=true;
        }
        if(!trafficFilesModified[this->ui->projectsList->currentRow()-1]){
            trafficFilesModified[this->ui->projectsList->currentRow()-1]=true;
            this->ui->resetDefaultsButton->setEnabled(true);
        }

    }
}

// "generate file" button is clicked
void ParametersWindow::on_generateFileButton_clicked()
{

    // if default dir is set
    if(currentProject.rbOutputDir=="<default>"){

        QString projectName = currentProject.name;

        // if the file is parameters
        if(this->ui->projectsList->currentRow()==0){

            QFile file;
            // if the location of the project is default
            if(currentProject.fullpath=="<default>"){
                file.setFileName("projects/"+currentProject.name+"/"+currentProject.parametersFile.fileName);
            }
            // if the project's location is custom
            else{
                QString project_dir=currentProject.fullpath;
                file.setFileName(project_dir+"/"+currentProject.name+"/"+currentProject.parametersFile.fileName);
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
                file_str<<trafficFilesContent[file_index];
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
                file_str<<trafficFilesContent[file_index];
                file.close();
                msg("File generated:\n"+this->ui->projectsList->item(file_index+1)->text());

            }
        }

    }

    // if the option is "individually"
    else if(currentProject.rbOutputDir=="<individually>"){

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
            ofile_str<<trafficFilesContent[this->ui->projectsList->currentRow()-1];
            ofile.close();
        }
        msg("File \""+output_dir+"/"+this->ui->projectsList->currentItem()->text()+"\" was successfully created.");

    }
    // if option is custom
    else{

        // if the file is parameters
        if(this->ui->projectsList->currentRow()==0){

            QFile file(currentProject.rbOutputDir+"/"+currentProject.parametersFile.fileName);
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
            QFile file(currentProject.rbOutputDir+"/"+this->ui->projectsList->item(file_index+1)->text());
            if(file.exists()){
                if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","File already exists. Overwrite?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
                    return;
                }
            }
            file.open(QIODevice::WriteOnly);
            QTextStream file_str(&file);
            file_str<<trafficFilesContent[file_index];
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

void ParametersWindow::getNewNameForFile(const QString &newFilename, const QString &oldFilename)
{
    emit checkAndRenameIfFilenameUnique(newFilename, oldFilename, currentProject.name);
}
