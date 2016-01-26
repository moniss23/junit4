#include "settings.h"
#include "ui_settings.h"
#include <qfiledialog.h>
#include <QMessageBox>
#include <management_window/encryption.h>
#include <management_window/parameterswindow.h>

extern QString defaultNewProjectDir;
extern QString defaultLocationForRbFiles;
extern int project_index;
extern std::vector<Project> projects;
extern ParametersWindow* p;

Settings::Settings(QWidget *parent,bool secondTabActive) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    if(secondTabActive){
        this->ui->tab_2->setEnabled(true);
        this->ui->tabWidget->setCurrentWidget(this->ui->tab_2);
    }
    else{
        this->ui->tab_2->setEnabled(false);
        this->ui->tabWidget->setCurrentWidget(this->ui->tab);
    }

    if(defaultNewProjectDir=="<default>"){
        this->ui->radioButton->setChecked(true);
        this->ui->lineEdit->setEnabled(false);
        this->ui->pushButton->setEnabled(false);
    }
    else{
        this->ui->radioButton_2->setChecked(true);
        this->ui->lineEdit->setEnabled(true);
        this->ui->pushButton->setEnabled(true);
        this->ui->lineEdit->setText(defaultNewProjectDir);
    }

    if(secondTabActive){
        if(defaultLocationForRbFiles=="<default>"){
            this->ui->radioButton_3->setChecked(true);
            this->ui->lineEdit_2->setEnabled(false);
            this->ui->pushButton_2->setEnabled(false);
        }
        else if(defaultLocationForRbFiles=="<individually>"){
            this->ui->radioButton_5->setChecked(true);
            this->ui->lineEdit_2->setEnabled(false);
            this->ui->pushButton_2->setEnabled(false);
        }
        else{
            this->ui->radioButton_4->setChecked(true);
            this->ui->lineEdit_2->setEnabled(true);
            this->ui->pushButton_2->setEnabled(true);
            this->ui->lineEdit_2->setText(defaultLocationForRbFiles);
        }
    }

    else{
        this->ui->radioButton_3->setChecked(true);
        this->ui->lineEdit_2->setEnabled(false);
        this->ui->pushButton_2->setEnabled(false);
        this->ui->pushButton_5->setEnabled(false);
    }

    changesMade=false;

    this->setWindowTitle("Settings");

}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_radioButton_2_toggled(bool checked)
{
    if(checked){
        this->ui->lineEdit->setEnabled(true);
        this->ui->pushButton->setEnabled(true);
    }
    else{
        this->ui->lineEdit->setEnabled(false);
        this->ui->pushButton->setEnabled(false);
    }

    this->ui->pushButton_5->setEnabled(true);
}

void Settings::on_radioButton_4_toggled(bool checked)
{
    if(checked){
        this->ui->lineEdit_2->setEnabled(true);
        this->ui->pushButton_2->setEnabled(true);
    }
    else{
        this->ui->lineEdit_2->setEnabled(false);
        this->ui->pushButton_2->setEnabled(false);
    }

    this->ui->pushButton_5->setEnabled(true);
}

void Settings::apply_settings(){

    // global - if program's directory is selected
    if(this->ui->radioButton->isChecked()){
        defaultNewProjectDir="<default>";
    }

    // global - if custom directory is selected
    if(this->ui->radioButton_2->isChecked()){
        if(this->ui->lineEdit->text()==""){
            if(!this->ui->tab->isVisible()){
                this->ui->tabWidget->setCurrentIndex(0);
            }
            QMessageBox(QMessageBox::Critical,"","You must specify the directory.",QMessageBox::Ok).exec();
            return;
        }
        QDir new_dir(this->ui->lineEdit->text());
        if(!new_dir.exists()){
            if(!this->ui->tab->isVisible()){
                this->ui->tabWidget->setCurrentIndex(0);
            }
            QMessageBox(QMessageBox::Critical,"","Selected directory does not seem to exist.",QMessageBox::Ok).exec();
            return;
        }
        defaultNewProjectDir=this->ui->lineEdit->text();
    }

    // if "project" tab is active (a project is opened)
    if(this->ui->tab_2->isEnabled()){

        // project - project's directory is selected
        if(this->ui->radioButton_3->isChecked()){
            projects[project_index].rbOutputDir="<default>";
            defaultLocationForRbFiles="<default>";
        }

        // project - custom directory is selected
        if(this->ui->radioButton_4->isChecked()){
            if(this->ui->lineEdit_2->text()==""){
                if(!this->ui->tab_2->isVisible()){
                    this->ui->tabWidget->setCurrentIndex(1);
                }
                QMessageBox(QMessageBox::Critical,"","You must specify the directory.",QMessageBox::Ok).exec();
                return;
            }
            QDir new_proj_dir(this->ui->lineEdit_2->text());
            if(!new_proj_dir.exists()){
                if(!this->ui->tab_2->isVisible()){
                    this->ui->tabWidget->setCurrentIndex(1);
                }
                QMessageBox(QMessageBox::Critical,"","Selected directory does not seem to exist.",QMessageBox::Ok).exec();
                return;
            }
            projects[project_index].rbOutputDir=this->ui->lineEdit_2->text();
            defaultLocationForRbFiles=this->ui->lineEdit_2->text();
        }

        // project - asking individually is selected
        if(this->ui->radioButton_5->isChecked()){
            projects[project_index].rbOutputDir="<individually>";
            defaultLocationForRbFiles="<individually>";
        }

    }

    // write global settings file
    write_settings_file();

    // if second tab is active, also write project file with new settings
    if(this->ui->tab_2->isEnabled()){
        p->save_project(false);
    }

}

// "OK" button clicked
void Settings::on_pushButton_3_clicked()
{
    this->apply_settings();
    this->close();
}

// "cancel" button clicked
void Settings::on_pushButton_4_clicked()
{
    this->close();
}

// "apply" button clicked
void Settings::on_pushButton_5_clicked()
{
    this->apply_settings();
    this->ui->pushButton_5->setEnabled(false);
}

// browsing for custom directory
void Settings::on_pushButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString new_dir(dialog.getExistingDirectory(this,tr("Choose directory"),"/"));
    if(new_dir!=""){
        this->ui->lineEdit->setText(new_dir);
    }
}    

// restore global defaults
void Settings::on_pushButton_7_clicked()
{
    if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","This will restore all global settings to defaults. Are you sure?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
        return;
    }
    defaultNewProjectDir="<default>";
    this->ui->radioButton->setChecked(true);
    this->ui->lineEdit->clear();
    write_settings_file();
}

// restore project defaults
void Settings::on_pushButton_6_clicked()
{
    if(QMessageBox::Cancel==QMessageBox(QMessageBox::Question,"","This will restore all project settings to defaults. Are you sure?",QMessageBox::Ok|QMessageBox::Cancel).exec()){
        return;
    }
    defaultLocationForRbFiles="<default>";
    this->ui->lineEdit_2->clear();
    this->ui->lineEdit_2->setEnabled(false);
    this->ui->radioButton_3->setChecked(true);
    this->ui->pushButton_2->setEnabled(false);
}

// custom dir in the line edit changes
void Settings::on_lineEdit_textChanged(const QString &arg1)
{
    this->ui->pushButton_5->setEnabled(true);
}

// browsing for a directory for custom .rb output
void Settings::on_pushButton_2_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString new_dir(dialog.getExistingDirectory(this,tr("Choose directory"),"/"));
    if(new_dir!=""){
        this->ui->lineEdit_2->setText(new_dir);
    }
}
