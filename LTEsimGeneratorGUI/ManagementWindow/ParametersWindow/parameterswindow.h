#ifndef PARAMETERSWINDOW_H
#define PARAMETERSWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileDialog>
#include <QString>
#include <QVBoxLayout>
#include <QVector>

#include "ManagementWindow/Helpdialog/helpdialog.h"
#include "ManagementWindow/AddProjectWindow/addProjectWindow.h"
#include <QCloseEvent>
#include <QListWidgetItem>
#include "DataSystem/datasystem.h"
#include "Data/project.h"

namespace Ui {
class ParametersWindow;
}

class ParametersWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParametersWindow(DataSystem *appSettings, QWidget *parent = 0);
    ~ParametersWindow();

    void closeEvent(QCloseEvent *);//TODO: Check - remove or move to private
    void refreshPreview();//TODO: Check - remove or move to private
    void saveProject(bool);//TODO: Check - remove or move to private


    /***********************************************
     *  WINDOW PUBLIC API
     ***********************************************/
signals:
    void SpawnWindow_ParamMap();
    void SpawnWindow_TrafficMap();
    void SpawnWindow_About();
    void SpawnWindow_Settings(const QString& projectName = QString());
    void SpawnWindow_RenameFile(const QString& filename);
    void SpawnWindow_RemoveFile(const QString& filename);
    /**
     * @brief AddFile_Traffic signal used to nofity system to add new traffic file
     * @param ProjectName name of project to add a new file
     */
    void AddFile_Traffic(const QString &ProjectName, const QString &fileName);
    void GenerateFile();
    void SaveFile();
    void checkAndRenameIfFilenameUnique(const QString& newFilename, const QString& oldFilename, const QString& projectName);
    void removeFile_TrafficFile(const QString& ProjectName, const QString& FileName);
    void saveProjects();

    void updateCurrentProjects_RB_FilesLocation(const QString& location);


public slots:
    void loadProjectAndOpen(const QString &projectName);

    /**
     * @brief updateFilesList is used when window needs to refresh state
     *
     * @param project project that changed
     */
    void refreshUI(const Project& project);//To refresh view when anyting changes

    void getNewNameForFile(const QString &newFilename, const QString& oldFilename);

    void set_RB_FilesLocation(const QString& location);


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

    void on_resetDefaultsButton_clicked();

    void on_filePreview_textChanged();

    void on_generateFileButton_clicked();

    void on_actionPath_triggered();

    void on_saveFileButton_clicked();

private:
    void msg(QString content);

private:
    Ui::ParametersWindow *ui;
    HelpDialog viewHelp;
    DataSystem *appSettings;

    Project currentProject;
};

#endif // PARAMETERSWINDOW_H

