#include "settings.h"
#include "ui_settings.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QCompleter>
#include <QDirModel>

Settings::Settings(QWidget *parent) :
    QDialog(parent), ui(new Ui::Settings)
{
    ui->setupUi(this);

    QCompleter *completer = new QCompleter(this);
    QDirModel *model = new QDirModel(completer);
    model->setFilter(QDir::AllDirs);
    completer->setModel(model);
    ui->projectDirInput->setCompleter(completer);
    ui->globalDirInput->setCompleter(completer);
}

Settings::~Settings() {
    delete ui;
}

void Settings::Show(const AppGlobalData &appGlobalData, const Project &project)
{
    currentProject = project;
    bool secondTabActive = !project.name.isEmpty();

    this->ui->okButton->setEnabled(false);

    this->ui->globalDirInput->clear();
    this->ui->settingsTabs->setTabEnabled(1,false);
    this->ui->settingsTabs->setCurrentIndex(0);
    if(appGlobalData.getDefaultNewProjectsPath() == "./Projects") {
        this->ui->programsDirRadioButton->setChecked(true);
        this->ui->globalDirInput->setText("./Projects");
        this->ui->globalDirInput->setEnabled(false);
        this->ui->globalBrowseButton->setEnabled(false);
    } else {
        this->ui->globalCustomDirRadioButton->setChecked(true);
        this->ui->globalDirInput->setText(appGlobalData.getDefaultNewProjectsPath());
        this->ui->globalBrowseButton->setEnabled(true);
        this->ui->globalDirInput->setFocus();
    }
    if(secondTabActive) {
        this->ui->projectDirInput->clear();
        this->ui->settingsTabs->setTabEnabled(1,true);
        this->ui->settingsTabs->setCurrentIndex(1);
        if(currentProject.genScriptDir == "<individually>") {
            this->ui->eachScriptIndividualDirRadioButton->setChecked(true);
            this->ui->projectDirInput->setText("<individually>");
            this->ui->projectDirInput->setEnabled(false);
            this->ui->projectBrowseButton->setEnabled(false);
        }else if(currentProject.genScriptDir == "./Projects") {
            this->ui->projectsDirRadioButton->setChecked(true);
            this->ui->projectDirInput->setEnabled(false);
            this->ui->projectDirInput->setText("./Projects");
            this->ui->projectBrowseButton->setEnabled(false);
        }else {
            this->ui->projectCustomDirRadioButton->setChecked(true);
            this->ui->projectDirInput->setEnabled(true);
            this->ui->projectBrowseButton->setEnabled(true);
            this->ui->projectDirInput->setText(currentProject.genScriptDir);
        }
    }
    this->setWindowFlags( Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
    this->show();
}

// "OK" button clicked
void Settings::on_okButton_clicked() {
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
}

// "cancel" button clicked
void Settings::on_cancelButton_clicked() {
    this->close();
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
        this->ui->okButton->setEnabled(true);
    }
}

// restore global defaults
void Settings::on_globalDefaultButton_clicked() {
    if(this->ui->settingsTabs->currentIndex() == 0) {
        if(this->ui->programsDirRadioButton->isChecked()) return;
        this->ui->programsDirRadioButton->setChecked(true);
        this->ui->globalDirInput->setText("./Projects");
        this->ui->globalDirInput->setEnabled(false);
        this->ui->okButton->setEnabled(true);
    } else {
        if(this->ui->projectsDirRadioButton->isChecked()) return;
        this->ui->projectsDirRadioButton->setChecked(true);
        this->ui->projectDirInput->setText("./Projects");
        this->ui->projectDirInput->setEnabled(false);
        this->ui->projectBrowseButton->setEnabled(false);
        this->ui->okButton->setEnabled(true);
    }
}

// custom dir in the line edit changes
void Settings::on_globalDirInput_textChanged() {
    if(this->ui->globalDirInput->hasFocus()) {
        this->ui->okButton->setEnabled(true);
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
    this->ui->globalDirInput->setText("./Projects");
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

// browsing for a directory for custom .rb output
void Settings::on_projectBrowseButton_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString directory(dialog.getExistingDirectory(this,tr("Choose directory"),"/"));
    if(directory!="") {
        this->ui->projectDirInput->setText(directory);
        this->ui->okButton->setEnabled(true);
    }
}

void Settings::on_projectsDirRadioButton_toggled(bool checked)
{
    if(checked == false) return;
    this->ui->projectDirInput->setText("./Projects");
    this->ui->projectDirInput->setEnabled(false);
    this->ui->projectBrowseButton->setEnabled(false);
    this->ui->okButton->setEnabled(true);
}

void Settings::on_eachScriptIndividualDirRadioButton_toggled(bool checked)
{
    if(checked == false) return;
    this->ui->projectDirInput->setText("<individually>");
    this->ui->projectDirInput->setEnabled(false);
    this->ui->projectBrowseButton->setEnabled(false);
    this->ui->okButton->setEnabled(true);
}

void Settings::on_projectDirInput_textChanged()
{
    if(this->ui->projectDirInput->hasFocus()) {
        this->ui->okButton->setEnabled(true);
    }
}
