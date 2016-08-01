#include "addProjectWindow.h"
#include "ui_addProjectWindow.h"

#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <QFileDialog>

#include <ManagementWindow/ParametersWindow/parameterswindow.h>
#include <ManagementWindow/ProjectManagement/projectmanagement.h>

void msg(QString content);

extern ParametersWindow * p;
extern ProjectManagement* projectMng;
extern bool paramFilePresent;

AddProjectWindow::AddProjectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProjectWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("New project");

    this->ui->defaultLocationRadioButton->setChecked(true);
}

AddProjectWindow::~AddProjectWindow() {delete ui;}

void AddProjectWindow::clearInputArea() {
    this->ui->fileName->clear();
    this->ui->fileName->setFocus();
}

void AddProjectWindow::setDefaultDir(QString dir) {
    if(dir=="<default>") {
        this->ui->label_3->setText("(program's directory)");
    }
    else {
        this->ui->label_3->setText("("+dir+")");
    }
}

// creating a new project
void AddProjectWindow::on_buttonBox_accepted()
{
    // alert the user if some data has not been entered
    if(this->ui->fileName->text().length()==0) {  //TODO: better set validator in ui->fileName control
        msg("You must enter the project's name.");
        return;
    }
    if(this->ui->customLocationRadioButton->isChecked() && this->ui->lineEdit->text().length()==0) {
        msg("You must specify the project's location.");
        return;
    }
    if(this->ui->customLocationRadioButton->isChecked()) {
        QDir d(this->ui->lineEdit->text());
        if(!d.exists()) {
            QMessageBox(QMessageBox::Critical,"","Destination folder does not exist.").exec();
            return;
        }
    }

    QString illegal_chars("<>:\"/\\|?*");//TODO: better set validator in ui->fileName control

    // check if the name is unique, display alert if it's not
    if(appSettings->projectNameTaken(this->ui->fileName->text())) {
        QMessageBox(QMessageBox::Information,"LTEsimGeneratorGUI","Name already in use. Choose another one.",QMessageBox::Yes).exec();
        return;
    }

    // assure that the name is legal
    bool name_legal=true;
    QString chars_detected("");
    for(int i=0; i<illegal_chars.length(); i++) {
        if(this->ui->fileName->text().contains(illegal_chars[i])) {
            if(name_legal) {
                name_legal=false;
            }
            chars_detected.append(illegal_chars[i]);
        }
    }
    if(!name_legal) {//TODO: not needed if validator is set
        if(chars_detected.length()==1) {
            QMessageBox(QMessageBox::Information,"LTEsimGeneratorGUI","Illegal character: "+chars_detected,QMessageBox::Yes).exec();
        }
        else {
            QMessageBox(QMessageBox::Information,"LTEsimGeneratorGUI","Illegal characters:\n"+chars_detected,QMessageBox::Yes).exec();
        }
        return;
    }

    // store the project name in a global variable for use by other files and methods
    appSettings->setProjectName(ui->fileName->text());

    paramFilePresent=true;

    //TODO: this should only emit a signal that new project should be created
    // add a new element to the list of projects in project management window
    QListWidgetItem* new_item=new QListWidgetItem(appSettings->getProjectName());

    if(this->ui->customLocationRadioButton->isChecked()) {
        projectMng->addWidgetToListWidget(new_item);
        appSettings->addProject(new_item,this->ui->lineEdit->text());
    }
    else if(this->ui->defaultLocationRadioButton->isChecked()) {
        projectMng->addWidgetToListWidget(new_item);
        appSettings->addProject(new_item,appSettings->getDefaultNewProjectDir());
    }
    appSettings->write_projects_file();

    this->close();
}

void AddProjectWindow::on_buttonBox_rejected() {this->close();}

// "browse" button clicked
void AddProjectWindow::on_browseDirectoryButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    this->ui->lineEdit->setText(dialog.getExistingDirectory(this,tr("Choose project directory"),"/"));
}

// "default" button toggled
void AddProjectWindow::on_defaultLocationRadioButton_toggled(bool checked)
{
    if(checked){
        this->ui->lineEdit->setEnabled(false);
        this->ui->browseDirectoryButton->setEnabled(false);
    }
    else{
        this->ui->lineEdit->setEnabled(true);
        this->ui->browseDirectoryButton->setEnabled(true);
    }
}

void AddProjectWindow::setAppSettings(AppSettings *value) //TODO: should not be needed with new API
{
    appSettings = value;
}


