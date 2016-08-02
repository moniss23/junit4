#ifndef PROJECTMANAGEMENT_H
#define PROJECTMANAGEMENT_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include "ManagementWindow/AddProjectWindow/addProjectWindow.h"
#include "AppSettings/appsettings.h"


namespace Ui {
class ProjectManagement;
}

class ProjectManagement : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProjectManagement(AppSettings *appSettings, QWidget *parent = 0);
    ~ProjectManagement();

    //TODO: delete this public functions as soon as possible
    QListWidgetItem* getCurrentItem();
    void addWidgetToListWidget(QListWidgetItem* new_item);
    void previewProjectFiles(QListWidgetItem* item);


    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
signals:
    void SpawnWindow_NewProject();
    void SpawnWindow_OpenProject();
    void SpawnWindow_ImportProject();
    void deleteProject(const QString &ProjectName );
    void SpawnWindow_Settings();

public slots:
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
    bool shouldDeleteProject;

};

#endif // PROJECTMANAGEMENT_H
