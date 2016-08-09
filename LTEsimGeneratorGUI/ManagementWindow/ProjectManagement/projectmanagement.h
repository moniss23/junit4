#ifndef PROJECTMANAGEMENT_H
#define PROJECTMANAGEMENT_H

#include <QMainWindow>
#include <QString>

#include "AppSettings/appsettings.h"
#include "Data/project.h"

namespace Ui {
class ProjectManagement;
}

/**
 * @brief The ProjectManagement class is reponsible for showing and managing projects
 */
class ProjectManagement : public QMainWindow
{
    Q_OBJECT

public:
    ProjectManagement(AppSettings *appSettings, QWidget *parent = 0);
    ~ProjectManagement();

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
signals:
    /**
     * @brief SpawnWindow_NewProject
     */
    void SpawnWindow_NewProject();

    /**
     * @brief SpawnWindow_OpenProject
     * @param ProjectName
     */
    void SpawnWindow_OpenProject(const QString &ProjectName);

    /**
     * @brief SpawnWindow_ImportProject
     */
    void SpawnWindow_ImportProject();

    /**
     * @brief deleteProject
     * @param ProjectName
     */
    void deleteProject(const QString &ProjectName);

    /**
     * @brief SpawnWindow_Settings
     */
    void SpawnWindow_Settings();

public slots:
    /**
     * @brief updateProjectLists
     * @param projects
     */
    void updateProjectLists(const std::vector<Project> &projects);


    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
private slots:
    void on_newProject_Button_clicked();
    void on_openProject_Button_clicked();
    void on_importProject_Button_clicked();
    void on_deleteProject_Button_clicked();
    void on_settings_Button_clicked();
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);


    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
     void open_project();
     void updateUiState();
     void previewProjectFiles(QListWidgetItem* item);

private:
    Ui::ProjectManagement *ui;
    AppSettings* appSettings;
    std::vector<Project> projects; ///> Local copy of Data
};

#endif // PROJECTMANAGEMENT_H
