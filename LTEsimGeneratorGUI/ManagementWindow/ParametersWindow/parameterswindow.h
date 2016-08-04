#ifndef PARAMETERSWINDOW_H
#define PARAMETERSWINDOW_H

#include <QMainWindow>
#include <QWidget>
 #include <QFileDialog>
#include <QString>
#include <QVBoxLayout>

#include "ManagementWindow/Helpdialog/helpdialog.h"
#include "ManagementWindow/AddProjectWindow/addProjectWindow.h"
#include <QCloseEvent>
#include <QListWidgetItem>
#include "AppSettings/appsettings.h"
#include "Data/project.h"

namespace Ui {
class ParametersWindow;
}

class ParametersWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParametersWindow(AppSettings *appSettings, QWidget *parent = 0);
    ~ParametersWindow();
    void closeEvent(QCloseEvent *);
    void open_file();                        // open file
    void addParamFile();
    void addTrafficFile();
    void refreshPreview();
    void saveProject(bool);
    void setParamsCM();

    void setFileDialogAppSettings(AppSettings *value);


    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
signals:
    void SpawnWindow_ParamMap();
    void SpawnWindow_TrafficMap();
    void SpawnWindow_About();
    void SpawnWindow_Settings();
    void SpawnWindow_RenameFile(const QString& filename);
    void SpawnWindow_RemoveFile(const QString& filename);
    void AddFile_Traffic();
    void GenerateFile();
    void SaveFile();


public slots:
    void loadProjectAndOpen(const QString &projectName);
    //void updateFilesList(const Project& project);

    /***********************************************
     *  BINDINGS TO UI BUTTONS AND LISTS
     ***********************************************/
private slots:
    void on_actionNew_triggered();

    void on_actionAbout_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void previewTrafficFile();

    void on_addTrafficButton_clicked();

    void on_removeFileButton_clicked();

    void on_renameFileButton_clicked();

    void previewFile(QListWidgetItem* current);

    void on_projectsList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_projectsList_itemDoubleClicked(QListWidgetItem *item);

    void on_undoButton_clicked();

    void on_redoButton_clicked();

    void switch_button_state_undo(bool available);
    void switch_button_state_redo(bool available);

    void on_resetDefaultsButton_clicked();

    void on_filePreview_textChanged();

    void on_generateFileButton_clicked();

    void on_actionPath_triggered();

    void on_saveFileButton_clicked();

private:
    Ui::ParametersWindow *ui;
    HelpDialog viewHelp;
    AppSettings *appSettings;
};

#endif // PARAMETERSWINDOW_H

