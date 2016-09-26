#include "addProjectWindow.h"
#include "ui_addProjectWindow.h"

#include <QMessageBox>
#include <QFileDialog>

AddProjectWindow::AddProjectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProjectWindow),
    fileNameRegExp(fileNamePattern),
    fileNameValidator(fileNameRegExp)
{
    ui->setupUi(this);
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
        QMessageBox(QMessageBox::Information,"","You must specify the project's location.",QMessageBox::Yes).exec();
        return;
    }

    if(this->ui->customLocationRadioButton->isChecked()) {
        QDir d(this->ui->lineEdit->text());
        if(!d.exists()) {
            QMessageBox(QMessageBox::Critical,"","Destination folder does not exist.").exec();
            return;
        }
    }

    if(this->ui->customLocationRadioButton->isChecked()) {
        emit createNewProject(ui->fileName->text(),ui->lineEdit->text());
    }
    else if(this->ui->defaultLocationRadioButton->isChecked()) {
        emit createNewProject(ui->fileName->text(),QString());//empty is the default one
    }
    ui->fileName->clear();
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
