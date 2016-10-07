#include "addProjectWindow.h"
#include "ui_addProjectWindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QCompleter>
#include <QDirModel>

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

    QCompleter *completer = new QCompleter(this);
    QDirModel *model = new QDirModel(completer);
    model->setFilter(QDir::AllDirs);
    completer->setModel(model);
    ui->lineEdit->setCompleter(completer);
    ui->fileName->clear();
}

AddProjectWindow::~AddProjectWindow() {
    delete ui;
}

void AddProjectWindow::loadAndOpen()
{
    ui->defaultLocationRadioButton->setChecked(true);
    ui->fileName->clear();
    this->setWindowFlags( Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
    this->show();
}

// creating a new project
void AddProjectWindow::on_buttonBox_accepted()
{
    if(this->ui->defaultLocationRadioButton->isChecked()) {
        emit createNewProject(ui->fileName->text(),ui->lineEdit->text(), false);
    }else {
        emit createNewProject(ui->fileName->text(),ui->lineEdit->text(), true);
    }
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
