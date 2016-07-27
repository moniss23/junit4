#ifndef PROJECTMANAGEMENT_H
#define PROJECTMANAGEMENT_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>

#include "ManagementWindow/Filedialog/filedialog.h"
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


    QListWidgetItem* getCurrentItem();
    void previewProjectFiles(QListWidgetItem* item);
    void setDefaultDir(QString dir);
    void setAppSettings(AppSettings *value);
    void setFileDialogAppSettings(AppSettings *value);
    void addWidgetToListWidget(QListWidgetItem* new_item);
    void setButtonsStates(QListWidgetItem* new_item);

    //TODO: new API to implement
    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
signals:
    void SpawnWindow_NewProject();
    void SpawnWindow_OpenProject();
    void SpawnWindow_ImportProject();
    void DeleteProject(const QString &ProjectName );
    void SpawnWindow_Settings();
public slots:
    void updateProjectLists(std::vector<Project> &projects);


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


private:
     void open_project();

private:
    Ui::ProjectManagement *ui;
    FileDialog createProject;
    AppSettings* appSettings;
};

#endif // PROJECTMANAGEMENT_H
