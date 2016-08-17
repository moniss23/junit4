#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <DataSystem/datasystem.h>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    //TODO: new API to implement
    //***********************************************/

signals:
    void SetDefaultLocationFor_RB_Files(const QString& rbLocation);
    void SetDefaultLocationForNewProjects(const QString& location);//location.isEmpty == true -> set default (restore)
    void SetLocationFor_RB_Files(const QString &ProjectName, const QString& location); //location.isEmpty() ==> set default

public slots:
    void ShowForProject(const AppGlobalData& globalProjectData , const Project &project = Project());//Project.name.isEmpty() == true
    void Update_RB_FilesLocation(const QString& location);
    void UpdateNewProjectsLocation(const QString& location);
    //***********************************************
    //***********************************************/

private slots:
    void on_globalCustomDirRadioButton_toggled(bool checked);

    void on_projectCustomDirRadioButton_toggled(bool checked);

    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_globalBrowseButton_clicked();

    void on_applyButton_clicked();

    void on_globalDefaultButton_clicked();

    void on_projectDefaultButton_clicked();

    void on_globalDirInput_textChanged(const QString &arg1);

    void on_projectBrowseButton_clicked();

    void apply_settings(bool shouldClose);

private:
    Ui::Settings *ui;
    AppGlobalData appGlobalData;
    QString current_RB_FilesLocation;
    bool changesMade;
};

#endif // SETTINGS_H
