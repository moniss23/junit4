#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include "Data/appglobaldata.h"
#include "Data/project.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();


    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
signals:
    /**
     * @brief SetGlobalLocationForNewProjects set new global location for saving projects
     * @param location QString with new location, if location is empty - global application defaults are used
     */
    void SetGlobalLocationForNewProjects(const QString& location);
    /**
     * @brief Set_RB_FilesLocationForProject set new RB files location for project
     * @param projectName, QString with projectName, which genScriptDir var will be updated
     * @param location QString with new location
     */
    void Set_RB_FilesLocationForProject(const QString &projectName, const QString& location);
    /**
     * @brief SetLocationFor_RB_Files used to set new location for RB files
     * @param ProjectName QString with name of project for which we change RB location
     * @param location QString with new location, if location is empty - global application defaults are used
     */
    void SetLocationFor_RB_Files(const QString &ProjectName, const QString& location);

public slots:
    /**
     * @brief ShowForProject shows window using data from given project
     * @param appGlobalData application global data, used to make local copy
     * @param project is a project for which we can change the settings, project.name.isEmpty() means global settings
     */
    void Show(const AppGlobalData& appGlobalData , const Project &project = Project());//Project.name.isEmpty() == true


    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
private slots:
    void on_projectCustomDirRadioButton_toggled(bool checked);
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_globalBrowseButton_clicked();
    void on_globalDefaultButton_clicked();
    void on_projectBrowseButton_clicked();
    void on_globalCustomDirRadioButton_toggled(bool checked);
    void on_globalDirInput_textChanged();
    void on_eachScriptIndividualDirRadioButton_toggled(bool checked);
    void on_programsDirRadioButton_toggled(bool checked);
    void on_projectsDirRadioButton_toggled(bool checked);
    void on_projectDirInput_textChanged();

    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/    
private:
    Ui::Settings *ui;                 ///< GUI form pointer
    Project currentProject;           ///< Local project instance
};

#endif // SETTINGS_H
