#ifndef PROJECTMANAGEMENT_H
#define PROJECTMANAGEMENT_H

#include <QMainWindow>
#include <QString>

#include "AppSettings/appsettings.h"

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
    explicit ProjectManagement(AppSettings *appSettings, QWidget *parent = 0);
    ~ProjectManagement();

    //TODO: delete this public functions as soon as possible
    QListWidgetItem* getCurrentItem();
    void previewProjectFiles(QListWidgetItem* item);


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

private:
    Ui::ProjectManagement *ui;
    AppSettings* appSettings;
};

#endif // PROJECTMANAGEMENT_H
