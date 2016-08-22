#ifndef PARAMETERSWINDOW_H
#define PARAMETERSWINDOW_H

#include <QMainWindow>
#include <QString>

#include "ManagementWindow/Helpdialog/helpdialog.h"
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

    void closeEvent(QCloseEvent *event);

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
    void SpawnWindow_ProjectMng();
    /**
     * @brief AddFile_Traffic signal used to nofity system to add new traffic file
     * @param projectName name of project to add a new file
     * @param fileName name of traffic file to add
     */
    void AddFile_Traffic(const QString &projectName, const QString &fileName);
    void GenerateFile();
    void SaveFile();
    void checkAndRenameIfFilenameUnique(const QString& newFilename, const QString& oldFilename, const QString& projectName);
    void removeFile_TrafficFile(const QString& projectName, const QString& fileName);
    void saveProjects();

    void updateCurrentProjects_RB_FilesLocation(const QString& location);
    void setDefaultParametersFileContent(const QString &projectName);
    void setDefaultTrafficFileContent(const QString &projectName, const QString &trafficName);
    void updateFileContent(const QString& projectName, const QString& fileName, const QString& content);


public slots:
    void loadProjectAndOpen(const Project &project);

    /**
     * @brief refreshUI is used when window needs to refresh state
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
    void on_actionPath_triggered();

    void on_addTrafficButton_clicked();
    void on_removeFileButton_clicked();
    void on_renameFileButton_clicked();
    void on_resetDefaultsButton_clicked();
    void on_generateFileButton_clicked();
    void on_saveFileButton_clicked();

    void on_projectsList_itemDoubleClicked(QListWidgetItem *item);

    void on_projectsList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_filePreview_textChanged();


    /***********************************************
     *  INTERNAL CLASS LOGIC
     ***********************************************/
private:
    void msg(const QString &content);
    void previewFile(QListWidgetItem* current);

private:
    Ui::ParametersWindow *ui;
    HelpDialog viewHelp;
    DataSystem *appSettings;
    Project currentProject;

    bool filePreviewChanged;
};

#endif // PARAMETERSWINDOW_H

