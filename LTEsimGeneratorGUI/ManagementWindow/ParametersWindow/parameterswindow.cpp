#include "parameterswindow.h"
#include "ui_parameterswindow.h"
#include <QTextStream>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QListWidgetItem>
#include <QCloseEvent>
#include <QInputDialog>
#include <cmath>

#include <ManagementWindow/ProjectManagement/projectmanagement.h>
#include <Maps/Parameters/MapWindow/mapwindowlarge.h>
#include <Maps/Parameters/MapWindow/mapwindow.h>
#include <ManagementWindow/Settings/settings.h>
#include <Maps/Traffic/map_traffic.h>
#include <Maps/Traffic/map_traffic_large.h>

// saving traffic map
extern QStringList mapTrafficList;
std::vector<QStringList> trafficFilesContentLists;
int currentOpenedTrafficFile;
QString parametersFileContent;
QStringList parametersFileContentList;
QString parametersFileContentDefault;
QStringList parametersFileContentDefaultList;
QString savedParametersFileContent;
std::vector<QString> trafficFilesContent;
std::vector<QString> savedTrafficFilesContent;
bool paramFileChanged;
bool paramFileModified;
std::vector<bool> trafficFilesChanged;
std::vector<bool> trafficFilesModified;
QString defaultLocationForRbFiles;
bool enableChangeRegistration=true;
bool previewFileInProgress=false;
bool closingInProgress=false;
bool fileAdditionInProgress=false;
bool enteringMapView;
QString lastOpenMap;
extern std::vector<QString*> trafficFilesNames;
extern ParametersWindow* p;
extern bool paramFilePresent;
extern ProjectManagement* projectMng;
extern MapWindow* map_w;
extern MapWindowLarge* map_wl;
extern Map_traffic* map_t;
extern Map_traffic_large* map_tl;
extern bool normalMapOpen;
extern bool largeMapOpen;
extern bool changesPresent;
int nrOfTrafficFiles=0;
void msg(QString content);
QString text1;              // tekst znajdujący się w polu tekstowym
QString pattern;      // tekst, który zamienimy na inny

void ParametersWindow::switch_button_state_undo(bool available){
    this->ui->pushButton_8->setEnabled(available);
}

void ParametersWindow::switch_button_state_redo(bool available){
        this->ui->pushButton_9->setEnabled(available);
}

ParametersWindow::ParametersWindow(AppSettings *appSettings, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ParametersWindow),
    appSettings(appSettings)
{
    ui->setupUi(this);

    changesPresent=false;
    paramFileChanged=false;

    // set undo and redo enabled in the text editor
    this->ui->textEdit->setUndoRedoEnabled(true);

    connect(this->ui->textEdit,
            SIGNAL(undoAvailable(bool)),
            this,
            SLOT(switch_button_state_undo(bool))
            );

    connect(this->ui->textEdit,
            SIGNAL(redoAvailable(bool)),
            this,
            SLOT(switch_button_state_redo(bool))
            );

    this->ui->pushButton_8->setEnabled(false);
    this->ui->pushButton_9->setEnabled(false);
    this->ui->pushButton_7->setEnabled(false);

    this->ui->radioButton_normalMap->setChecked(true);

    // read in the default values for parameters.rb
    parametersFileContentDefault = appSettings->readParametersFile();

    parametersFileContentDefaultList=parametersFileContentDefault.split("\n");
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

                this->save_project(false);

                trafficFilesNames.clear();
                nrOfTrafficFiles=0;
                this->ui->listWidget->clear();

                projectMng->previewProjectFiles(projectMng->getCurrentItem());
                projectMng->show();
                break;

            case QMessageBox::No:

                trafficFilesNames.clear();
                nrOfTrafficFiles=0;
                this->ui->listWidget->clear();

                projectMng->previewProjectFiles(projectMng->getCurrentItem());
                projectMng->show();
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
        this->ui->listWidget->clear();
        this->close();
        projectMng->previewProjectFiles(projectMng->getCurrentItem());
        projectMng->show();

        event->accept();
    }

}

void ParametersWindow::loadProject(){

    // reset the vectors
    for(std::vector<QString*>::iterator it=trafficFilesNames.begin(); it!=trafficFilesNames.end(); it++){
        delete (*it);
    }
    trafficFilesNames.clear();
    trafficFilesContent.clear();
    trafficFilesChanged.clear();
    paramFileChanged=false;
    parametersFileContent="";
    parametersFileContentList.clear();
    paramFileModified=false;
    trafficFilesModified.clear();

    // set the window title
    this->setWindowTitle(appSettings->getProjectFile());

    QListWidgetItem* new_item;
    QString line;
    int project_content_line=0;
    int paramFileLen;
    int trafficFileLen;

    // read the project content from the project file
    QStringList project_content=appSettings->read_project_file(appSettings->getProjectName(),appSettings->getProjectDirectory(appSettings->getProjectName()));

    // read the default location for output .rb files
    defaultLocationForRbFiles=project_content[0];

    // read the type of last open map
    appSettings->setMapType(appSettings->getProjectName(), project_content[1]);
    lastOpenMap=project_content[1];

    if(lastOpenMap=="normal"){
        this->ui->radioButton_normalMap->setChecked(true);
    }
    else{
        this->ui->radioButton_largeMap->setChecked(true);
    }

    // read the name of parameters file and nr of traffic files
    appSettings->setParametersFile(project_content[2]);
    nrOfTrafficFiles=project_content[3].toInt();
    project_content_line=4;

    // if the project is empty
    if(nrOfTrafficFiles==0 && (appSettings->getParametersFile())=="<none>"){
        this->ui->listWidget->addItem("<empty>");
        paramFilePresent=false;
        parametersFileContent="";
    }

    // if the project is not empty
    else{

        // if there is no parameters file
        if((appSettings->getParametersFile())=="<none>"){
            paramFilePresent=false;
            this->ui->listWidget->addItem("<none>");
            parametersFileContent="";
        }

        // if there is a parameters file
        else{
            paramFilePresent=true;
            this->ui->listWidget->addItem(appSettings->getParametersFile());
        }

        // read the traffic file names
        for(int i=0; i<nrOfTrafficFiles; i++){
            line=project_content[i+4];
            new_item=new QListWidgetItem(line);
            this->ui->listWidget->addItem(new_item);
            trafficFilesNames.push_back(new QString(line));
            trafficFilesChanged.push_back(false);
            trafficFilesModified.push_back(false);
        }

        project_content_line+=nrOfTrafficFiles;

        // read the content of the parameters file
        paramFileLen=project_content[project_content_line].toInt();
        project_content_line++;
        for(int i=0; i<paramFileLen; i++){
            parametersFileContent+=project_content[project_content_line];
            savedParametersFileContent+=project_content[project_content_line];
            parametersFileContent+="\n";
            savedParametersFileContent+="\n";
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
    }

    if(paramFilePresent){
        this->ui->listWidget->item(0)->setSelected(true);
        this->ui->listWidget->setCurrentRow(0);
    }
    else if(nrOfTrafficFiles>0){
        this->ui->listWidget->item(1)->setSelected(true);
        this->ui->listWidget->setCurrentRow(1);
    }
    else{
        this->ui->listWidget->item(0);
        this->ui->listWidget->setCurrentRow(0);
    }

    changesPresent=false;
    paramFileChanged=false;

    if(this->ui->listWidget->item(0)->text().endsWith("*")){
        this->ui->listWidget->item(0)->setText(this->ui->listWidget->item(0)->text().left(this->ui->listWidget->item(0)->text().size()-1));
    }

    if(this->windowTitle().endsWith("*")){
        this->setWindowTitle(this->windowTitle().left(this->windowTitle().length()-1));
    }

}

void ParametersWindow::addTrafficFile()
{
    QString new_file_name;
    QListWidgetItem* new_item;
    bool name_unique=false;
    int i=0;
    unsigned int j;

    // replace <empty> with <none> in the zero-th row of listwidget
    if(nrOfTrafficFiles==0 && paramFilePresent==false){
        delete this->ui->listWidget->takeItem(0);
        this->ui->listWidget->addItem("<none>");
    }

    // generate unique file name
    while(!name_unique){
        new_file_name="Traffic_"+QString::number(i)+".rb";
        name_unique=true;
        for(j=0; j<trafficFilesNames.size(); j++){
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
    this->ui->listWidget->addItem(new_item);
    new_item->setSelected(true);
    this->ui->listWidget->setCurrentItem(new_item);

    this->previewFile(new_item);

    if(!changesPresent){
        changesPresent=true;
        this->setWindowTitle(this->windowTitle()+"*");
    }
}

void ParametersWindow::open_file()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Otwórz..."), "/home/", tr("Pliki rb ( *.rb)"));
    QFile file1(fileName);
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
        return;              // if coudn't open file: stop loading file

    text1.clear();

    QTextStream stream(&file1);

    // read all files
    text1 = stream.readAll();
    ui->textEdit->insertPlainText(text1);
    file1.close();

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

void ParametersWindow::save_project(bool singleFile=false){

    // remove * symbol wherever it is present
    if(this->windowTitle().endsWith("*")){
        this->setWindowTitle(this->windowTitle().left(this->windowTitle().size()-1));
    }

    if(this->ui->listWidget->item(0)->text().endsWith("*")){
        this->ui->listWidget->item(0)->setText(this->ui->listWidget->item(0)->text().left(this->ui->listWidget->item(0)->text().size()-1));
    }

    for(int i=0; i<nrOfTrafficFiles; i++){
        if(this->ui->listWidget->item(i+1)->text().endsWith("*")){
            this->ui->listWidget->item(i+1)->setText(this->ui->listWidget->item(i+1)->text().left(this->ui->listWidget->item(i+1)->text().size()-1));
        }
    }

    for(int i=0; i<nrOfTrafficFiles; i++){
        if(trafficFilesNames[i]->endsWith("*")){
            (*trafficFilesNames[i])=(*trafficFilesNames[i]).left((*trafficFilesNames[i]).length()-1);
        }
    }

    // save the content of currently selected file
    if(this->ui->listWidget->currentRow()==0){
        parametersFileContent=this->ui->textEdit->toPlainText();
    }
    else{
        int index=this->ui->listWidget->currentRow()-1;
        trafficFilesContent[index]=this->ui->textEdit->toPlainText();
    }

    QString plaintext("");

    // if entire project is to be saved
    if(!singleFile){

        // set all "changed" flags to false
        if(changesPresent){
            changesPresent=false;
        }
        if(paramFileChanged){
            paramFileChanged=false;
        }
        for(std::vector<bool>::iterator it=trafficFilesChanged.begin(); it!=trafficFilesChanged.end(); it++){
            (*it)=false;
        }

        // copy all content from temp to actual
        savedParametersFileContent=parametersFileContent;
        for(int i=0; i<nrOfTrafficFiles; i++){
            savedTrafficFilesContent[i]=trafficFilesContent[i];
        }
    }

    // if only one file is to be saved, only copy that file's content from temp to actual
    else{

        // if the file to be saved is parameters
        if(this->ui->listWidget->currentRow()==0){
            paramFileChanged=false;
            savedParametersFileContent=parametersFileContent;
        }

        // if the file to be saved is traffic
        else{
            int file_index=this->ui->listWidget->currentRow()-1;
            trafficFilesChanged[file_index]=false;
            savedTrafficFilesContent[file_index]=trafficFilesContent[file_index];
        }
    }

    // add default location for output .rb files
    plaintext.append(defaultLocationForRbFiles);
    plaintext.append("\n");

    // add the type of last open map
    plaintext.append(lastOpenMap);
    plaintext.append("\n");

    // add param file name
    plaintext.append(appSettings->getParametersFile());
    plaintext.append("\n");

    // add nr of traffic files
    plaintext.append(QString::number(nrOfTrafficFiles));
    plaintext.append("\n");

    // add names of traffic files
    for(int i=0; i<nrOfTrafficFiles; i++){
        (*trafficFilesNames[i])=(this->ui->listWidget->item(i+1)->text());
    }

    for(int i=0; i<nrOfTrafficFiles; i++){
        plaintext.append((*trafficFilesNames[i]));
        plaintext.append("\n");
    }

    // add length and content of param file
    plaintext.append(QString::number(savedParametersFileContent.split("\n").length()));
    plaintext.append("\n");
    plaintext.append(savedParametersFileContent);
    plaintext.append("\n");

    // add length and content of traffic files
    for(int i=0; i<nrOfTrafficFiles; i++){
        plaintext.append(QString::number(savedTrafficFilesContent[i].split("\n").length()));
        plaintext.append("\n");
        plaintext.append(savedTrafficFilesContent[i]);
        plaintext.append("\n");
    }

    // encrypt the project data and write it to file
    QString projectName = appSettings->getProjectName();
    appSettings->write_project_file(projectName,
                                    plaintext,
                                    appSettings->get_project_dir(projectName));

}

void ParametersWindow::on_actionOpen_triggered()
{

    if(changesPresent){

        int ret=QMessageBox(QMessageBox::Information, "LTEsimGenerator", "There are unsaved changes in the project. Save?", QMessageBox::Cancel|QMessageBox::No|QMessageBox::Yes).exec();

        switch(ret){
        case QMessageBox::Yes:

            enableChangeRegistration=false;
            closingInProgress=true;

            this->save_project();

            trafficFilesNames.clear();
            nrOfTrafficFiles=0;
            this->ui->listWidget->clear();
            this->close();

            projectMng->previewProjectFiles(projectMng->getCurrentItem());
            projectMng->show();
            break;

        case QMessageBox::No:

            enableChangeRegistration=false;

            trafficFilesNames.clear();
            nrOfTrafficFiles=0;
            this->ui->listWidget->clear();
            this->close();

            projectMng->previewProjectFiles(projectMng->getCurrentItem());
            projectMng->show();
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
        this->ui->listWidget->clear();
        this->close();

        projectMng->previewProjectFiles(projectMng->getCurrentItem());
        projectMng->show();

        closingInProgress=false;
    }
}

void ParametersWindow::on_actionSave_triggered()
{
    this->save_project();
}

void ParametersWindow::previewTrafficFile(){
}

// "add traffic file" button clicked
void ParametersWindow::on_pushButton_2_clicked()
{
    fileAdditionInProgress=true;
    this->addTrafficFile();
    fileAdditionInProgress=false;
}

// "remove file" button clicked
void ParametersWindow::on_pushButton_3_clicked()
{

    // if the file is traffic
    if(this->ui->listWidget->currentRow()>0){

        if(QMessageBox::Yes == QMessageBox(QMessageBox::Information, "LTEsimGenerator", "File will be removed from the project:\n"+(this->ui->listWidget->currentItem()->text())+"\n\nAre you sure?", QMessageBox::Yes|QMessageBox::No).exec()){

            // delete file name from the vector
            std::vector<QString*>::iterator it=trafficFilesNames.begin();
            it+=this->ui->listWidget->currentRow()-1;
            QString* mem=trafficFilesNames[this->ui->listWidget->currentRow()-1];
            trafficFilesNames.erase(it);
            delete mem;

            // delete file content from the vector
            std::vector<QString>::iterator it2=trafficFilesContent.begin();
            it2+=this->ui->listWidget->currentRow()-1;
            trafficFilesContent.erase(it2);

            // delete item from the UI list
            delete this->ui->listWidget->takeItem(this->ui->listWidget->currentRow());

            nrOfTrafficFiles--;

            if(!changesPresent){
                changesPresent=true;
                this->setWindowTitle(this->windowTitle()+"*");
            }

            // if there are no more files, change <none> to <empty>
            if(!paramFilePresent && nrOfTrafficFiles==0){
                this->ui->listWidget->item(0)->setText("<empty>");
            }

        }

    }

    // if the file is parameters
    else{

        if(paramFilePresent){
            if(QMessageBox::Yes==QMessageBox(QMessageBox::Information, "LTEsimGenerator", "File will be removed from the project:\n"+(this->ui->listWidget->currentItem()->text())+"\n\nAre you sure?", QMessageBox::Yes|QMessageBox::No).exec()){

                // set the parameters file to <none>
                appSettings->setParametersFile("<none>");

                // replace the item in UI with <none> or <empty>
                if(nrOfTrafficFiles>0){
                    this->ui->listWidget->item(0)->setText("<none>");
                }
                else{
                    this->ui->listWidget->item(0)->setText("<empty>");
                }

                // reset the bool variable
                paramFilePresent=false;

                parametersFileContent="";

                this->ui->textEdit->clear();

                if(!changesPresent){
                    changesPresent=true;
                    this->setWindowTitle(this->windowTitle()+"*");
                }
            }
        }
    }
}

// "rename file" button clicked
void ParametersWindow::on_pushButton_4_clicked()
{

    if(this->ui->listWidget->currentItem()->text()=="<none>" || this->ui->listWidget->currentItem()->text()=="<empty>"){
        return;
    }

    QString new_name;
    bool ok;
    bool name_unique=false;
    bool name_legal=false;

    new_name=QInputDialog::getText(this,"LTEsimGenerator","Rename file:\n"+this->ui->listWidget->currentItem()->text(),QLineEdit::Normal,this->ui->listWidget->currentItem()->text(),&ok);
    if(!ok){
        return;
    }

    QString illegal_chars("<>:\"/\\|?*");
    QString chars_detected("");

    name_legal=true;
    for(int i=0; i<illegal_chars.length(); i++){
        if(new_name.contains(illegal_chars[i])){
            if(name_legal){
                name_legal=false;
            }
            chars_detected.append(illegal_chars[i]);
        }
    }

    if(name_legal){

        if(!new_name.endsWith(".rb")){
            new_name.append(".rb");
        }

        if(new_name!=this->ui->listWidget->currentItem()->text()){
            name_unique=true;
            if(new_name==(appSettings->getParametersFile())){
                name_unique=false;
            }
            if(name_unique){
                for(int i=0; i<nrOfTrafficFiles; i++){
                    if(new_name==this->ui->listWidget->item(i+1)->text()){
                        name_unique=false;
                        break;
                    }
                }
            }
        }
        else{
            name_unique=true;
        }

    }

    while(!name_unique || !name_legal){

        if(!name_legal){
            if(chars_detected.length()==1){
                QMessageBox(QMessageBox::Information,"LTEsimGeneratorGUI","Illegal character: "+chars_detected,QMessageBox::Yes).exec();
            }
            else{
                QMessageBox(QMessageBox::Information,"LTEsimGeneratorGUI","Illegal characters:\n"+chars_detected,QMessageBox::Yes).exec();
            }
        }

        else{

            QMessageBox msg;
            msg.setText("Name already in use, choose another one.");
            msg.exec();

        }

        new_name=QInputDialog::getText(this,"LTEsimGenerator","Rename file:\n"+this->ui->listWidget->currentItem()->text(),QLineEdit::Normal,new_name,&ok);
        if(!ok){
            return;
        }

        // validation of the entered file name
        chars_detected="";
        name_legal=true;
        for(int i=0; i<illegal_chars.length(); i++){
            if(new_name.contains(illegal_chars[i])){
                if(name_legal){
                    name_legal=false;
                }
                chars_detected.append(illegal_chars[i]);
            }
        }

        if(name_legal){

            if(!new_name.endsWith(".rb")){
                new_name.append(".rb");
            }

            if(new_name!=this->ui->listWidget->currentItem()->text()){
                name_unique=true;
                if(new_name==(appSettings->getParametersFile())){
                    name_unique=false;
                }
                if(name_unique){
                    for(int i=0; i<nrOfTrafficFiles; i++){
                        if(new_name==this->ui->listWidget->item(i+1)->text()){
                            name_unique=false;
                            break;
                        }
                    }
                }
            }
            else{
                name_unique=true;
            }

        }

    }

    if(name_unique && name_legal && new_name!=this->ui->listWidget->currentItem()->text()){

        // update ui
        this->ui->listWidget->currentItem()->setText(new_name);

        // update the parameters file name
        if(this->ui->listWidget->currentRow()==0){
            appSettings->setParametersFile(new_name);
        }

        // update the traffic file name
        else{
            (*trafficFilesNames[this->ui->listWidget->currentRow()-1])=new_name;
        }

        if(!changesPresent){
            changesPresent=true;
            if(!this->windowTitle().endsWith("*")){
                this->setWindowTitle(this->windowTitle()+"*");
            }
        }
    }

}

// preview a file in the right field
void ParametersWindow::previewFile(QListWidgetItem* current){

    enableChangeRegistration=false;
    previewFileInProgress=true;

    if(current==NULL || this->ui->listWidget->currentItem()->text()=="<none>" || this->ui->listWidget->currentItem()->text()=="<empty>"){
        this->ui->textEdit->clear();
        return;
    }

    // if the file to preview is parameters
    if(this->ui->listWidget->item(0)->text()==current->text()){
        this->ui->textEdit->setText(parametersFileContent);
    }

    // if the file is traffic
    else{
        for(int i=1; i<=nrOfTrafficFiles; i++){
            if(this->ui->listWidget->item(i)->text()==current->text()){
                this->ui->textEdit->setText(trafficFilesContent[i-1]);
                break;
            }
        }
    }

    enableChangeRegistration=true;
    previewFileInProgress=false;

}

void ParametersWindow::refreshPreview(){
    this->previewFile(this->ui->listWidget->currentItem());
}

void ParametersWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{

    if(current==previous || closingInProgress || fileAdditionInProgress){
        return;
    }

    // if the previous file was parameters
    if(previous==this->ui->listWidget->item(0)){
        parametersFileContent=this->ui->textEdit->toPlainText();
    }

    // if the file was traffic
    else{

        // find the index of the file which was being previewed and save the content of textedit widget
        for(int i=1; i<=nrOfTrafficFiles; i++){
            if(previous==this->ui->listWidget->item(i)){
                trafficFilesContent[i-1]=this->ui->textEdit->toPlainText();
                break;
            }
        }

    }

    // if the new file is parameters
    if(current==this->ui->listWidget->item(0)){
        if(paramFileModified){
            this->ui->pushButton_7->setEnabled(true);
        }
        else{
            this->ui->pushButton_7->setEnabled(false);
        }
    }

    else{
        if(trafficFilesModified[this->ui->listWidget->currentRow()-1]){
            this->ui->pushButton_7->setEnabled(true);
        }
        else{
            this->ui->pushButton_7->setEnabled(false);
        }
    }

    this->previewFile(current);

}


// file in the project double-clicked
void ParametersWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    (void) item;

    // parameters file double-clicked
    if(this->ui->listWidget->currentRow()==0){
        enteringMapView=true;

        // if normal map is to be displayed
        if(this->ui->radioButton_normalMap->isChecked()){

            // set the flag to true
            largeMapOpen=false;
            normalMapOpen=true;

            // delete current map objects if they are present
            if(map_w!=NULL){
                delete map_w;
                map_w=NULL;

            }
            if(map_wl!=NULL){
                delete map_wl;
                map_wl=NULL;
            }

            // create a new map object and display it
            lastOpenMap="normal";
            map_w=new MapWindow;
            p->close();

            map_w->show();
        }

        // if large map is to be displayed
        else{
            if(lastOpenMap=="normal"){

                if(QMessageBox::No==QMessageBox(QMessageBox::Question,"","Large map can currently be displayed with default values only. Revert to defaults?",QMessageBox::Yes|QMessageBox::No).exec()){
                    return;
                }

                // restore default values
                parametersFileContent=parametersFileContentDefault;
                parametersFileContentList=parametersFileContentDefaultList;
                this->refreshPreview();
            }

            // set the flags
            largeMapOpen=true;
            normalMapOpen=false;
            lastOpenMap="large";

            // delete current map objects if they are present
            if(map_w!=NULL){
                delete map_w;
                map_w=NULL;
            }
            if(map_wl!=NULL){
                delete map_wl;
                map_wl=NULL;
            }

            // create a new map object and display it
            map_wl=new MapWindowLarge;
            p->close();
            map_wl->show();

        }
    }

    // traffic file double-clicked
    else if(this->ui->listWidget->currentRow()>0){

    // store the index of the opened traffic file in a global variable
    currentOpenedTrafficFile=this->ui->listWidget->currentRow()-1;


        // delete current map objects if they are present
        if(map_t!=NULL){
            delete map_t;
            map_t=NULL;

        }

        if(map_tl!=NULL){
            delete map_tl;
            map_tl=NULL;
        }


            if(this->ui->radioButton_largeMap->isChecked() && this->ui->listWidget->currentRow()>0){
                    // delete current map objects if they are present
                    if(map_tl!=NULL){
                        delete map_tl;
                        map_tl=NULL;
                    }


                    //if large traffic map is to be displayed
                        map_tl =new Map_traffic_large;

                        map_tl->show();
                }
            else{

                // same as above, but for traffic map window
                    map_t =new Map_traffic;

                    map_t->show();
            }


    }


}
// "undo" button is clicked
void ParametersWindow::on_pushButton_8_clicked()
{

    this->ui->textEdit->undo();

}

// "redo" button is clicked
void ParametersWindow::on_pushButton_9_clicked()
{
    this->ui->textEdit->redo();
}

// "defaults" button clicked
void ParametersWindow::on_pushButton_7_clicked()
{

    // if the file is parameters
    if(this->ui->listWidget->currentRow()==0){

        // only proceed if the file was modified relative to template
        if(paramFileModified){

            // ask for confirmation
            if(QMessageBox::Yes==QMessageBox(QMessageBox::Question,"LTEsimGenerator","Entire file content will be reverted to default state. All changes will be lost. Proceed?",QMessageBox::Yes|QMessageBox::No).exec()){
                QFile file(":/RbFiles/parameters.rb");
                file.open((QIODevice::ReadOnly));
                QTextStream s(&file);
                QString fileContent=s.readAll();
                this->ui->textEdit->setText(fileContent);
                parametersFileContent=fileContent;
                file.close();
                paramFileModified=false;
                this->ui->pushButton_7->setEnabled(false);
            }
        }
    }

    // if the file is traffic
    else{

        // only proceed if the file was modified relative to template
        if(trafficFilesModified[this->ui->listWidget->currentRow()-1]){

            // ask for confirmation
            if(QMessageBox::Yes==QMessageBox(QMessageBox::Question,"LTEsimGenerator","Entire file content will be reverted to default state. All changes will be lost. Proceed?",QMessageBox::Yes|QMessageBox::No).exec()){
                QFile file(":/RbFiles/tune_traffic_models.rb");
                file.open((QIODevice::ReadOnly));
                QTextStream s(&file);
                QString fileContent=s.readAll();
                this->ui->textEdit->setText(fileContent);
                trafficFilesContent[this->ui->listWidget->currentRow()-1]=fileContent;
                file.close();
                trafficFilesModified[this->ui->listWidget->currentRow()-1]=false;
                this->ui->pushButton_7->setEnabled(false);
            }
        }
    }

}

void ParametersWindow::on_textEdit_textChanged()
{

    // detect whether previewing of file is in progress
    if(previewFileInProgress){
        return;
    }

    // detect whether closing is in progress
    if(closingInProgress){
        return;
    }

    if(!this->ui->textEdit->hasFocus()){
        return;
    }

    if(!changesPresent){
        changesPresent=true;
    }



    // if it's a param file
    if(this->ui->listWidget->currentRow()==0){
        if(!paramFileChanged){
            paramFileChanged=true;
        }
        if(!paramFileModified){
            paramFileModified=true;
            this->ui->pushButton_7->setEnabled(true);
        }

    }

    // if it's a traffic file
    else{
        if(!trafficFilesChanged[this->ui->listWidget->currentRow()-1]){
            trafficFilesChanged[this->ui->listWidget->currentRow()-1]=true;
        }
        if(!trafficFilesModified[this->ui->listWidget->currentRow()-1]){
            trafficFilesModified[this->ui->listWidget->currentRow()-1]=true;
            this->ui->pushButton_7->setEnabled(true);
        }

    }
}

// "generate file" button is clicked
void ParametersWindow::on_pushButton_6_clicked()
{

    // if default dir is set
    if(defaultLocationForRbFiles=="<default>"){

        QString projectName = appSettings->getProjectName();

        // if the file is parameters
        if(this->ui->listWidget->currentRow()==0){

            // if the location of the project is default
            if(appSettings->get_project_dir(projectName)=="<default>"){

                QFile file("projects/"+(appSettings->getProjectName())+"/"+this->ui->listWidget->item(0)->text());
                if(file.exists()){
                    if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","File already exists. Overwrite?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
                        return;
                    }
                }
                file.open(QIODevice::WriteOnly);
                QTextStream file_str(&file);
                file_str<<parametersFileContent;
                file.close();
                msg("File generated:\n"+this->ui->listWidget->item(0)->text());
            }

            // if the project's location is custom
            else{
                QString project_dir=appSettings->get_project_dir(projectName);

                QFile file(project_dir+"/"+(appSettings->getProjectName())+"/"+this->ui->listWidget->item(0)->text());
                if(file.exists()){
                    if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","File already exists. Overwrite?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
                        return;
                    }
                }
                file.open(QIODevice::WriteOnly);
                QTextStream file_str(&file);
                file_str<<parametersFileContent;
                file.close();
                msg("File generated:\n"+this->ui->listWidget->item(0)->text());
            }

        }

        // if the file is traffic
        else{

            // if the location of the project is default
            if(appSettings->get_project_dir(projectName)=="<default>"){

                int file_index=this->ui->listWidget->currentRow()-1;
                QFile file("projects/"+(appSettings->getProjectName())+"/"+this->ui->listWidget->item(file_index+1)->text());
                if(file.exists()){
                    if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","File already exists. Overwrite?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
                        return;
                    }
                }
                file.open(QIODevice::WriteOnly);
                QTextStream file_str(&file);
                file_str<<trafficFilesContent[file_index];
                file.close();
                msg("File generated:\n"+this->ui->listWidget->item(file_index+1)->text());

            }

            // if the location of the project is custom
            else{

                QString project_dir=appSettings->get_project_dir(projectName);

                int file_index=this->ui->listWidget->currentRow()-1;
                QFile file(project_dir+"/"+(appSettings->getProjectName())+"/"+this->ui->listWidget->item(file_index+1)->text());
                if(file.exists()){
                    if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","File already exists. Overwrite?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
                        return;
                    }
                }
                file.open(QIODevice::WriteOnly);
                QTextStream file_str(&file);
                file_str<<trafficFilesContent[file_index];
                file.close();
                msg("File generated:\n"+this->ui->listWidget->item(file_index+1)->text());

            }
        }

    }

    // if the option is "individually"
    else if(defaultLocationForRbFiles=="<individually>"){

        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::Directory);
        QString output_dir=dialog.getExistingDirectory(this,tr("Select output directory"),"/");

        // if it's a parameters file
        if(this->ui->listWidget->currentRow()==0){
            QFile ofile(output_dir+"/"+this->ui->listWidget->currentItem()->text());

            if(ofile.exists()){
                if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","File already exists. Overwrite?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
                    return;
                }
            }

            ofile.open(QIODevice::WriteOnly);
            QTextStream ofile_str(&ofile);
            ofile_str<<parametersFileContent;
            ofile.close();
        }

        // if it's a traffic file
        else{
            QFile ofile(output_dir+"/"+this->ui->listWidget->currentItem()->text());
            ofile.open(QIODevice::WriteOnly);
            QTextStream ofile_str(&ofile);
            ofile_str<<trafficFilesContent[this->ui->listWidget->currentRow()-1];
            ofile.close();
        }
        msg("File \""+output_dir+"/"+this->ui->listWidget->currentItem()->text()+"\" was successfully created.");

    }

    // if option is custom
    else{

        // if the file is parameters
        if(this->ui->listWidget->currentRow()==0){

            QFile file(defaultLocationForRbFiles+"/"+this->ui->listWidget->item(0)->text());
            if(file.exists()){
                if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","File already exists. Overwrite?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
                    return;
                }
            }
            file.open(QIODevice::WriteOnly);
            QTextStream file_str(&file);
            file_str<<parametersFileContent;
            file.close();
            msg("File generated:\n"+this->ui->listWidget->item(0)->text());

        }

        // if the file is traffic
        else{

            int file_index=this->ui->listWidget->currentRow()-1;
            QFile file(defaultLocationForRbFiles+"/"+this->ui->listWidget->item(file_index+1)->text());
            if(file.exists()){
                if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","File already exists. Overwrite?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
                    return;
                }
            }
            file.open(QIODevice::WriteOnly);
            QTextStream file_str(&file);
            file_str<<trafficFilesContent[file_index];
            file.close();
            msg("File generated:\n"+this->ui->listWidget->item(file_index+1)->text());

        }

    }

}

// "settings" opened
void ParametersWindow::on_actionPath_triggered()
{
    Settings settingsWindow(appSettings, this,true);
    settingsWindow.setWindowModality(Qt::WindowModal);
    settingsWindow.exec();
}

void ParametersWindow::on_radioButton_normalMap_toggled(bool checked)
{
    if(checked){
        appSettings->setMapType(appSettings->getProjectName(), "normal");
        changesPresent=true;
    }
}

void ParametersWindow::on_radioButton_largeMap_toggled(bool checked)
{
    if(checked){
        appSettings->setMapType(appSettings->getProjectName(), "large");
        changesPresent=true;
    }
}

void ParametersWindow::setFileDialogAppSettings(AppSettings *value)
{
    createProject.setAppSettings(value);
}
