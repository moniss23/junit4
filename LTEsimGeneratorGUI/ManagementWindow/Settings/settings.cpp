#include "settings.h"
#include "ui_settings.h"
#include <qfiledialog.h>
#include <QMessageBox>
#include <ManagementWindow/ParametersWindow/parameterswindow.h>


extern QString defaultLocationForRbFiles;
extern int project_index;
extern ParametersWindow* p;

Settings::Settings(AppSettings *appSettings, QWidget *parent, bool secondTabActive) :
    QDialog(parent), ui(new Ui::Settings), appSettings(appSettings)
{
    ui->setupUi(this);

    if(secondTabActive){
        this->ui->projectTab->setEnabled(true);
        this->ui->settingsTabs->setCurrentWidget(this->ui->projectTab);
    }
    else{
        this->ui->projectTab->setEnabled(false);
        this->ui->settingsTabs->setCurrentWidget(this->ui->globalTab);
    }

    if(appSettings->getDefaultNewProjectDir()=="<default>"){
        this->ui->programsDirRadioButton->setChecked(true);
        this->ui->globalDirInput->setEnabled(false);
        this->ui->globalBrowseButton->setEnabled(false);
    }
    else{
        this->ui->globalCustomDirRadioButton->setChecked(true);
        this->ui->globalDirInput->setEnabled(true);
        this->ui->globalBrowseButton->setEnabled(true);
        this->ui->globalDirInput->setText(appSettings->getDefaultNewProjectDir());
    }

    if(secondTabActive){
        if(defaultLocationForRbFiles=="<default>"){
            this->ui->projectsDirRadioButton->setChecked(true);
            this->ui->projectDirInput->setEnabled(false);
            this->ui->projectBrowseButton->setEnabled(false);
        }
        else if(defaultLocationForRbFiles=="<individually>"){
            this->ui->echaScriptIndividualDirRadioButton->setChecked(true);
            this->ui->projectDirInput->setEnabled(false);
            this->ui->projectBrowseButton->setEnabled(false);
        }
        else{
            this->ui->projectCustomDirRadioButton->setChecked(true);
            this->ui->projectDirInput->setEnabled(true);
            this->ui->projectBrowseButton->setEnabled(true);
            this->ui->projectDirInput->setText(defaultLocationForRbFiles);
        }
    }

    else{
        this->ui->projectsDirRadioButton->setChecked(true);
        this->ui->projectDirInput->setEnabled(false);
        this->ui->projectBrowseButton->setEnabled(false);
        this->ui->applyButton->setEnabled(false);
    }

    changesMade=false;

    this->setWindowTitle("Settings");

}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_globalCustomDirRadioButton_toggled(bool checked)
{
    if(checked){
        this->ui->globalDirInput->setEnabled(true);
        this->ui->globalBrowseButton->setEnabled(true);
    }
    else{
        this->ui->globalDirInput->setEnabled(false);
        this->ui->globalBrowseButton->setEnabled(false);
    }

    this->ui->applyButton->setEnabled(true);
}

void Settings::on_projectCustomDirRadioButton_toggled(bool checked)
{
    if(checked){
        this->ui->projectDirInput->setEnabled(true);
        this->ui->projectBrowseButton->setEnabled(true);
    }
    else{
        this->ui->projectDirInput->setEnabled(false);
        this->ui->projectBrowseButton->setEnabled(false);
    }

    this->ui->applyButton->setEnabled(true);
}

void Settings::apply_settings(){

    // global - if program's directory is selected
    if(this->ui->programsDirRadioButton->isChecked()){
        appSettings->setDefaultNewProjectDir("<default>");
    }

    // global - if custom directory is selected
    if(this->ui->globalCustomDirRadioButton->isChecked()){
        if(this->ui->globalDirInput->text()==""){
            if(!this->ui->globalTab->isVisible()){
                this->ui->settingsTabs->setCurrentIndex(0);
            }
            QMessageBox(QMessageBox::Critical,"","You must specify the directory.",QMessageBox::Ok).exec();
            return;
        }
        QDir new_dir(this->ui->globalDirInput->text());
        if(!new_dir.exists()){
            if(!this->ui->globalTab->isVisible()){
                this->ui->settingsTabs->setCurrentIndex(0);
            }
            QMessageBox(QMessageBox::Critical,"","Selected directory does not seem to exist.",QMessageBox::Ok).exec();
            return;
        }
        appSettings->setDefaultNewProjectDir(this->ui->globalDirInput->text());
    }

    // if "project" tab is active (a project is opened)
    if(this->ui->projectTab->isEnabled()){

        // project - project's directory is selected
        if(this->ui->projectsDirRadioButton->isChecked()){
            appSettings->projects[project_index].rbOutputDir="<default>";
            defaultLocationForRbFiles="<default>";
        }

        // project - custom directory is selected
        if(this->ui->projectCustomDirRadioButton->isChecked()){
            if(this->ui->projectDirInput->text()==""){
                if(!this->ui->projectTab->isVisible()){
                    this->ui->settingsTabs->setCurrentIndex(1);
                }
                QMessageBox(QMessageBox::Critical,"","You must specify the directory.",QMessageBox::Ok).exec();
                return;
            }
            QDir new_proj_dir(this->ui->projectDirInput->text());
            if(!new_proj_dir.exists()){
                if(!this->ui->projectTab->isVisible()){
                    this->ui->settingsTabs->setCurrentIndex(1);
                }
                QMessageBox(QMessageBox::Critical,"","Selected directory does not seem to exist.",QMessageBox::Ok).exec();
                return;
            }
            appSettings->projects[project_index].rbOutputDir=this->ui->projectDirInput->text();
            defaultLocationForRbFiles=this->ui->projectDirInput->text();
        }

        // project - asking individually is selected
        if(this->ui->echaScriptIndividualDirRadioButton->isChecked()){
            appSettings->projects[project_index].rbOutputDir="<individually>";
            defaultLocationForRbFiles="<individually>";
        }

    }

    // write global settings file
    appSettings->write_settings_file();

    // if second tab is active, also write project file with new settings
    if(this->ui->projectTab->isEnabled()){
        p->saveProject(false);
    }

}

// "OK" button clicked
void Settings::on_OKButton_clicked()
{
    this->apply_settings();
    this->close();
}

// "cancel" button clicked
void Settings::on_cancelButton_clicked()
{
    this->close();
}

// "apply" button clicked
void Settings::on_applyButton_clicked()
{
    this->apply_settings();
    this->ui->applyButton->setEnabled(false);
}

// browsing for custom directory
void Settings::on_globalBrowseButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString new_dir(dialog.getExistingDirectory(this,tr("Choose directory"),"/"));
    if(new_dir!=""){
        this->ui->globalDirInput->setText(new_dir);
    }
}

// restore global defaults
void Settings::on_globalDefaultButton_clicked()
{
    if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","This will restore all global settings to defaults. Are you sure?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
        return;
    }
    appSettings->setDefaultNewProjectDir("<default>");
    this->ui->programsDirRadioButton->setChecked(true);
    this->ui->globalDirInput->clear();
    appSettings->write_settings_file();
}

// restore project defaults
void Settings::on_projectDefaultButton_clicked()
{
    if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","This will restore all project settings to defaults. Are you sure?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
        return;
    }
    defaultLocationForRbFiles="<default>";
    this->ui->projectDirInput->clear();
    this->ui->projectDirInput->setEnabled(false);
    this->ui->projectsDirRadioButton->setChecked(true);
    this->ui->projectBrowseButton->setEnabled(false);
}

// custom dir in the line edit changes
void Settings::on_globalDirInput_textChanged(const QString &arg1)
{
    (void) arg1;
    this->ui->applyButton->setEnabled(true);
}

// browsing for a directory for custom .rb output
void Settings::on_projectBrowseButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString new_dir(dialog.getExistingDirectory(this,tr("Choose directory"),"/"));
    if(new_dir!=""){
        this->ui->projectDirInput->setText(new_dir);
    }
}
