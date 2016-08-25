#ifndef PROJECTMANAGEMENT_H
#define PROJECTMANAGEMENT_H

#include <QMainWindow>
#include <QString>

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
    ProjectManagement(QWidget *parent = 0);
    ~ProjectManagement();

    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
signals:
    /**
     * @brief SpawnWindow_NewProject - when user wants to add a project
     */
    void spawnWindow_NewProject();

    /**
     * @brief SpawnWindow_OpenProject - when user wants to open given project
     * @param ProjectName
     */
    void spawnWindow_OpenProject(const QString &ProjectName);

    /**
     * @brief SpawnWindow_ImportProject - used when user wants to import other project
     */
    void spawnWindow_ImportProject();

    /**
     * @brief deleteProject - used
     * @param ProjectName name of project to delete
     */
    void deleteProject(const QString &ProjectName);

    /**
     * @brief SpawnWindow_Settings
     */
    void spawnWindow_Settings(const QString& projectName = QString());

public slots:
    /**
     * @brief updateProjectLists
     * @param projects
     */
    void updateProjectLists(const QVector<Project> &projects);


    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
private slots:
    void on_newProject_Button_clicked();
    void on_openProject_Button_clicked();
    void on_importProject_Button_clicked();
    void on_deleteProject_Button_clicked();
    void on_settings_Button_clicked();
    void on_listWidget_currentItemChanged(QListWidgetItem *current);
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
    QVector<Project> projects; ///> Local copy of Data
};

#endif // PROJECTMANAGEMENT_H
