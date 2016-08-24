#include "settings.h"
#include "ui_settings.h"

#include <QFileDialog>
#include <QMessageBox>

Settings::Settings(QWidget *parent) :
    QDialog(parent), ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowTitle("Settings");
}

Settings::~Settings() {
    delete ui;
}

void Settings::ShowForProject(const AppGlobalData &globalProjectData, const Project &project)
{
    currentProject = project;
    bool secondTabActive = !project.name.isEmpty();

    this->ui->applyButton->setEnabled(false);

    if(!secondTabActive) {
        this->ui->globalDirInput->clear();
        this->ui->settingsTabs->setTabEnabled(1,false);
        this->ui->settingsTabs->setCurrentIndex(0);
        if(globalProjectData.getDefaultNewProjectsPath() == "<default>") {
            this->ui->programsDirRadioButton->setChecked(true);
            this->ui->globalDirInput->setText("<default>");
            this->ui->globalDirInput->setEnabled(false);
            this->ui->globalBrowseButton->setEnabled(false);
        } else {
            this->ui->globalCustomDirRadioButton->setChecked(true);
            this->ui->globalDirInput->setText(globalProjectData.getDefaultNewProjectsPath());
            this->ui->globalBrowseButton->setEnabled(true);
            this->ui->globalDirInput->setFocus();
        }
    }else {
        this->ui->projectDirInput->clear();
        this->ui->settingsTabs->setTabEnabled(1,true);
        this->ui->settingsTabs->setCurrentIndex(1);
        if(currentProject.genScriptDir == "<individually>") {
            this->ui->eachScriptIndividualDirRadioButton->setChecked(true);
            this->ui->projectDirInput->setText("<individually>");
            this->ui->projectDirInput->setEnabled(false);
            this->ui->projectBrowseButton->setEnabled(false);
        }else if(currentProject.genScriptDir == "<default>") {
            this->ui->projectsDirRadioButton->setChecked(true);
            this->ui->projectDirInput->setEnabled(false);
            this->ui->projectDirInput->setText("<default>");
            this->ui->projectBrowseButton->setEnabled(false);
        }else {
            this->ui->projectCustomDirRadioButton->setChecked(true);
            this->ui->projectDirInput->setEnabled(true);
            this->ui->projectBrowseButton->setEnabled(true);
            this->ui->projectDirInput->setText(currentProject.genScriptDir);
        }
    }
    this->show();
}

void Settings::apply_settings(bool shouldClose) {
    QString location;
    // if "global" tab is active
    if(this->ui->settingsTabs->currentIndex() == 0) {
        location = this->ui->globalDirInput->text();
        emit SetGlobalLocationForNewProjects(location);
    }
    // if "project" tab is active (a project is opened)
    if(this->ui->settingsTabs->currentIndex() == 1) {
        location = this->ui->projectDirInput->text();
        emit Set_RB_FilesLocationForProject(currentProject.name, location);
    }

    if(shouldClose) {
        this->close();
    }else {
        this->ui->applyButton->setEnabled(false);
    }
}

// "OK" button clicked
void Settings::on_okButton_clicked() {
    this->apply_settings(true);
}

// "cancel" button clicked
void Settings::on_cancelButton_clicked() {
    this->close();
}

// "apply" button clicked
void Settings::on_applyButton_clicked() {
    this->apply_settings(false);
}


/*
 * GLOBAL SETTINGS FUNCTIONS
 *
 */
void Settings::on_globalBrowseButton_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString directory(dialog.getExistingDirectory(this,tr("Choose directory"),"/"));
    if(directory!="") {
        this->ui->globalDirInput->setText(directory);
        this->ui->applyButton->setEnabled(true);
    }
}

// restore global defaults
void Settings::on_globalDefaultButton_clicked() {
    if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"Restore all global settings.","This will restore all global settings to defaults. Are you sure?",QMessageBox::Ok|QMessageBox::Cancel).exec()) {
        return;
    }
    this->ui->programsDirRadioButton->setChecked(true);
    this->ui->globalDirInput->setText("<default>");
    this->ui->globalDirInput->setEnabled(false);
    this->ui->applyButton->setEnabled(true);
}

// custom dir in the line edit changes
void Settings::on_globalDirInput_textChanged() {
    if(this->ui->globalDirInput->hasFocus()) {
        this->ui->applyButton->setEnabled(true);
    }
}

void Settings::on_globalCustomDirRadioButton_toggled(bool checked)
{
    if(checked == false) {
        return;
    }
    this->ui->globalDirInput->clear();
    this->ui->globalDirInput->setEnabled(true);
    this->ui->globalDirInput->setFocus();
    this->ui->globalBrowseButton->setEnabled(true);
}

void Settings::on_programsDirRadioButton_toggled(bool checked)
{
    if(checked == false) {
        return;
    }
    this->ui->globalDirInput->setText("<default>");
    this->ui->globalDirInput->setEnabled(false);
    this->ui->globalBrowseButton->setEnabled(false);
}


/*
 * PROJECT SETTINGS FUNCTIONS
 *
 */
void Settings::on_projectCustomDirRadioButton_toggled(bool checked) {
    if(checked == false) {
        return;
    }
    this->ui->projectDirInput->clear();
    this->ui->projectDirInput->setEnabled(true);
    this->ui->projectBrowseButton->setEnabled(true);
}

// restore project defaults
void Settings::on_projectDefaultButton_clicked() {
    if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"Restore all project settings.","This will restore all project settings to defaults. Are you sure?",QMessageBox::Ok|QMessageBox::Cancel).exec()) {
        return;
    }
    this->ui->projectsDirRadioButton->setChecked(true);
    this->ui->projectDirInput->setText("<default>");
    this->ui->projectDirInput->setEnabled(false);
    this->ui->projectBrowseButton->setEnabled(false);
    this->ui->applyButton->setEnabled(true);
}


// browsing for a directory for custom .rb output
void Settings::on_projectBrowseButton_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString directory(dialog.getExistingDirectory(this,tr("Choose directory"),"/"));
    if(directory!="") {
        this->ui->projectDirInput->setText(directory);
        this->ui->applyButton->setEnabled(true);
    }
}

void Settings::on_projectsDirRadioButton_toggled(bool checked)
{
    if(checked == false) return;
    this->ui->projectDirInput->setText("<default>");
    this->ui->projectDirInput->setEnabled(false);
    this->ui->projectBrowseButton->setEnabled(false);
    this->ui->applyButton->setEnabled(true);
}

void Settings::on_eachScriptIndividualDirRadioButton_toggled(bool checked)
{
    if(checked == false) return;
    this->ui->projectDirInput->setText("<individually>");
    this->ui->projectDirInput->setEnabled(false);
    this->ui->projectBrowseButton->setEnabled(false);
    this->ui->applyButton->setEnabled(true);
}

void Settings::on_projectDirInput_textChanged()
{
    if(this->ui->projectDirInput->hasFocus()) {
        this->ui->applyButton->setEnabled(true);
    }
}
