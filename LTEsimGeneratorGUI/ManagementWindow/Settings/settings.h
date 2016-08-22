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
     * @brief SetDefaultLocationForNewProjects set new default location for saving projects
     * @param location QString with new location, if location is empty - global application defaults are used
     */
    void SetDefaultLocationForNewProjects(const QString& location);
    /**
     * @brief SetDefaultLocationFor_RB_Files revert to default location
     * @param rbLocation
     */
    void SetDefaultLocationFor_RB_Files(const QString& rbLocation);
    /**
     * @brief SetLocationFor_RB_Files used to set new location for RB files
     * @param ProjectName QString with name of project for which we change RB location
     * @param location QString with new location, if location is empty - global application defaults are used
     */
    void SetLocationFor_RB_Files(const QString &ProjectName, const QString& location);

public slots:
    /**
     * @brief ShowForProject shows window using data from given project
     * @param globalProjectData application global data, used to make local copy
     * @param project           project for which we can change the settings
     */
    void ShowForProject(const AppGlobalData& globalProjectData , const Project &project = Project());//Project.name.isEmpty() == true
    /**
     * @brief Update_RB_FilesLocation
     * @param location
     */
    void Update_RB_FilesLocation(const QString& location);
    /**
     * @brief UpdateNewProjectsLocation
     * @param location
     */
    void UpdateNewProjectsLocation(const QString& location);


    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_globalBrowseButton_clicked();
    void on_applyButton_clicked();
    void on_globalDefaultButton_clicked();
    void on_projectDefaultButton_clicked();
    void on_projectBrowseButton_clicked();

    void on_globalCustomDirRadioButton_toggled(bool checked);
    void on_projectCustomDirRadioButton_toggled(bool checked);

    void on_globalDirInput_textChanged(const QString &arg1);


    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    void apply_settings(bool shouldClose);

private:
    Ui::Settings *ui;                 ///< GUI form pointer
    AppGlobalData appGlobalData;      ///< Local instance of application data
    QString current_RB_FilesLocation; ///< Local instance of application data
    bool changesMade;                 ///< Is there any changes made by user?
};

#endif // SETTINGS_H
