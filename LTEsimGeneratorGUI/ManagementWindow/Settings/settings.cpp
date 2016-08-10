#include "settings.h"
#include "ui_settings.h"
#include <qfiledialog.h>
#include <QMessageBox>
#include <ManagementWindow/ParametersWindow/parameterswindow.h>

Settings::Settings(QWidget *parent) :
    QDialog(parent), ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowTitle("Settings");
    this->ui->applyButton->setEnabled(false);
}

Settings::~Settings() {
    delete ui;
}

void Settings::ShowForProject(const AppGlobalData &globalProjectData, const Project &project)
{
    bool secondTabActive = !project.name.isEmpty();

    this->ui->projectDirInput->setEnabled(false);
    this->ui->projectsDirRadioButton->setChecked(true);
    this->ui->projectBrowseButton->setEnabled(false);

    if(!secondTabActive) {
        this->ui->settingsTabs->setTabEnabled(1,false);
        this->ui->settingsTabs->setCurrentIndex(0);
    }else {
        this->ui->settingsTabs->setTabEnabled(1,true);
        this->ui->settingsTabs->setCurrentIndex(1);
        if(project.rbOutputDir=="<individually>") {
            this->ui->echaScriptIndividualDirRadioButton->setChecked(true);
        }else {
            this->ui->projectCustomDirRadioButton->setChecked(true);
            this->ui->projectDirInput->setEnabled(true);
            this->ui->projectBrowseButton->setEnabled(true);
            this->ui->projectDirInput->setText(project.rbOutputDir);
        }
    }
    if(globalProjectData.getDefaultNewProjectsPath() == "<default>") {
        this->ui->programsDirRadioButton->setChecked(true);
        this->ui->globalDirInput->setEnabled(false);
        this->ui->globalBrowseButton->setEnabled(false);
    }else {
        this->ui->globalCustomDirRadioButton->setChecked(true);
        this->ui->globalDirInput->setEnabled(true);
        this->ui->globalBrowseButton->setEnabled(true);
        this->ui->globalDirInput->setText(globalProjectData.getDefaultNewProjectsPath());
    }

    this->show();
}

void Settings::on_globalCustomDirRadioButton_toggled(bool checked) {
    this->ui->globalDirInput->setEnabled(checked);
    this->ui->globalBrowseButton->setEnabled(checked);

    this->ui->applyButton->setEnabled(true);
}

void Settings::on_projectCustomDirRadioButton_toggled(bool checked) {
    this->ui->projectDirInput->setEnabled(checked);
    this->ui->projectBrowseButton->setEnabled(checked);

    this->ui->applyButton->setEnabled(true);
}

void Settings::apply_settings(bool shouldClose) {
    QString location, rbLocation;
    // global - if program's directory is selected
    if(this->ui->programsDirRadioButton->isChecked()) {
        location = "<default>";
    }else if(this->ui->globalCustomDirRadioButton->isChecked()) {
        if(this->ui->globalDirInput->text()=="") {
            if(!this->ui->globalTab->isVisible()) {
                this->ui->settingsTabs->setCurrentIndex(0);
            }
            QMessageBox(QMessageBox::Critical,"No directory specified!","You must specify the directory.",QMessageBox::Ok).exec();
            return;
        }
        QDir new_dir(this->ui->globalDirInput->text());
        if(!new_dir.exists()) {
            if(!this->ui->globalTab->isVisible()) {
                this->ui->settingsTabs->setCurrentIndex(0);
            }
            QMessageBox(QMessageBox::Critical,"Directory does not exist!","Selected directory does not seem to exist.\nAre you sure you selected it right?",QMessageBox::Ok).exec();
            return;
        }
        location = this->ui->globalDirInput->text();
    }
    // if "project" tab is active (a project is opened)
    if(this->ui->projectTab->isEnabled()) {
        // project - project's directory is selected
        if(this->ui->projectsDirRadioButton->isChecked()) {
            rbLocation = "<default>";
        }
        // project - custom directory is selected
        if (this->ui->projectCustomDirRadioButton->isChecked()) {
            if(this->ui->projectDirInput->text()=="") {
                if(!this->ui->projectTab->isVisible()) {
                    this->ui->settingsTabs->setCurrentIndex(1);
                }
                QMessageBox(QMessageBox::Critical,"No directory specified!","You must specify the directory.",QMessageBox::Ok).exec();
                return;
            }
            QDir new_proj_dir(this->ui->projectDirInput->text());
            if(!new_proj_dir.exists()) {
                if(!this->ui->projectTab->isVisible()) {
                    this->ui->settingsTabs->setCurrentIndex(1);
                }
                QMessageBox(QMessageBox::Critical,"Directory does not exist!","Selected directory does not seem to exist.\nAre you sure you selected it right?",QMessageBox::Ok).exec();
                return;
            }

        }
        // project - asking individually is selected
        if(this->ui->echaScriptIndividualDirRadioButton->isChecked()) {
            rbLocation="<individually>";
        }
        // if second tab is active, also write project file with new settings
    }

    //emit writeSettings(settings); ===> AppSettings

    emit SetDefaultLocationFor_RB_Files(rbLocation);
    emit SetDefaultLocationForNewProjects(location);

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

// browsing for custom directory
void Settings::on_globalBrowseButton_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString new_dir(dialog.getExistingDirectory(this,tr("Choose directory"),"/"));
    if(new_dir!="") {
        this->ui->globalDirInput->setText(new_dir);
    }
    this->ui->applyButton->setEnabled(false);
}

// restore global defaults
void Settings::on_globalDefaultButton_clicked() {
    if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"Restore all global settings.","This will restore all global settings to defaults. Are you sure?",QMessageBox::Ok|QMessageBox::Cancel).exec()) {
        return;
    }
    appSettings->setDefaultNewProjectDir("<default>");
    this->ui->programsDirRadioButton->setChecked(true);
    this->ui->globalDirInput->clear();
    appSettings->write_settings_file();
    this->ui->applyButton->setEnabled(false);
}

// restore project defaults
void Settings::on_projectDefaultButton_clicked() {

    //emit RestoreDefaultsProjectSettings(projectName);

    if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"Restore all project settings.","This will restore all project settings to defaults. Are you sure?",QMessageBox::Ok|QMessageBox::Cancel).exec()) {
        return;
    }
    //appSettings->getDefaultLocationForRbFiles()="<default>";
    this->ui->projectDirInput->clear();
    this->ui->projectDirInput->setEnabled(false);
    this->ui->projectsDirRadioButton->setChecked(true);
    this->ui->projectBrowseButton->setEnabled(false);
}

// custom dir in the line edit changes
void Settings::on_globalDirInput_textChanged(const QString &arg1) {
    emit SetDefaultLocationForNewProjects(arg1);
    this->ui->applyButton->setEnabled(true);
}

// browsing for a directory for custom .rb output
void Settings::on_projectBrowseButton_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString new_dir(dialog.getExistingDirectory(this,tr("Choose directory"),"/"));
    if(new_dir!="") {
        this->ui->projectDirInput->setText(new_dir);
    }
}
