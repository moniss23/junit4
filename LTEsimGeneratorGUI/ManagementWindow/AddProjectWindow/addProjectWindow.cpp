#include "addProjectWindow.h"
#include "ui_addProjectWindow.h"

#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <QFileDialog>

#include <ManagementWindow/ParametersWindow/parameterswindow.h>
#include <ManagementWindow/ProjectManagement/projectmanagement.h>

void msg(QString content);

extern bool paramFilePresent;


AddProjectWindow::AddProjectWindow(AppSettings *appSettings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProjectWindow),
    fileNameRegExp(fileNamePattern),
    fileNameValidator(fileNameRegExp),
    appSettings(appSettings)
{
    ui->setupUi(this);
    this->setWindowTitle("New project");
    ui->defaultLocationRadioButton->setChecked(true);
    ui->fileName->setValidator(&fileNameValidator);
    fileNameValidator.setParent(ui->fileName);
}

AddProjectWindow::~AddProjectWindow() {
    delete ui;
}

// creating a new project
void AddProjectWindow::on_buttonBox_accepted()
{
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

    // check if the name is unique, display alert if it's not
    if(appSettings->projectNameTaken(this->ui->fileName->text())) {
        QMessageBox(QMessageBox::Information,"LTEsimGeneratorGUI","Name already in use. Choose another one.",QMessageBox::Yes).exec();
        return;
    }

    paramFilePresent=true;

    if(this->ui->customLocationRadioButton->isChecked()) {
        emit createNewProject(ui->fileName->text(),ui->lineEdit->text());
    }
    else if(this->ui->defaultLocationRadioButton->isChecked()) {
        emit createNewProject(ui->fileName->text(),QString());//empty is the default one
    }

    ui->fileName->clear();
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


