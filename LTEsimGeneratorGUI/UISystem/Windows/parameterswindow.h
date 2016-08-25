﻿#ifndef PARAMETERSWINDOW_H
#define PARAMETERSWINDOW_H

#include <QMainWindow>
#include <QString>
#include <memory>

#include "UISystem/Windows/helpdialog.h"
#include "UISystem/Helpers/rubysyntaxhighlighter.h"
#include "Data/datasystem.h"
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
    /**
     * @brief SpawnWindow_ParamMap signal used to nofity system to show parameters map
     * @param projectName name of current opened project
     */
    void SpawnWindow_ParamMap(const QString &projectName);
    /**
     * @brief SpawnWindow_TrafficMap signal used to nofity system to show traffic map
     */
    void SpawnWindow_TrafficMap();
    /**
     * @brief SpawnWindow_About signal used to nofity system to show window with about program text
     */
    void SpawnWindow_About();
    /**
     * @brief SpawnWindow_Settings signal used to nofity system to show settings window
     * @param projectName name of project which settings are going to be updated, if projectName is empty global settings will be updated
     */
    void SpawnWindow_Settings(const QString& projectName = QString());
    /**
     * @brief SpawnWindow_RenameFile signal used to nofity system to show rename file window
     * @param filename name of file which we rename
     * @param projectName name of project to rename a file
     */
    void SpawnWindow_RenameFile(const QString& filename, const QString& projectName);
    /**
     * @brief SpawnWindow_ProjectMng signal used to nofity system to show project management window
     */
    void SpawnWindow_ProjectMng();
    /**
     * @brief AddFile_Traffic signal used to nofity system to add new traffic file
     * @param projectName name of project to add a new file
     * @param fileName name of traffic file to add
     */
    void AddFile_Traffic(const QString &projectName, const QString &fileName);
    /**
     * @brief GenerateFile signal used to nofity system to generate script
     */
    void GenerateFile();
    /**
     * @brief SaveFile signal used to nofity system to save projects
     */
    void SaveFile();
    /**
     * @brief removeFile_TrafficFile signal used to nofity system to remove traffic file
     * @param projectName name of project to remove a traffic file
     * @param fileName name of traffic file to remove
     */
    void removeFile_TrafficFile(const QString& projectName, const QString& fileName);
    /**
     * @brief saveProjects signal used to nofity system to save projects to file
     */
    void saveProjects();
    /**
     * @brief setDefaultParametersFileContent signal used to nofity system to set default parameters file content
     * @param projectName name of project to set default parameters file content
     */
    void setDefaultParametersFileContent(const QString &projectName);
    /**
     * @brief setDefaultTrafficFileContent signal used to nofity system to set default traffic file content
     * @param projectName name of project to set default traffic file content
     * @param trafficName name of traffic file to be updated
     */
    void setDefaultTrafficFileContent(const QString &projectName, const QString &trafficName);
    /**
     * @brief updateFileContent signal used to nofity system to set new param/traffic file content
     * @param projectName name of project to set new file content
     * @param fileName name of file to be updated
     * @param content new content for a file
     */
    void updateFileContent(const QString& projectName, const QString& fileName, const QString& content);


public slots:
    /**
     * @brief loadProjectAndOpen is used when parametersWindow have to be showed
     * @param project local project instance on which we can work
     */
    void loadProjectAndOpen(const Project &project);
    /**
     * @brief refreshUI is used when window needs to refresh state
     * @param project project that changed
     */
    void refreshUI(const Project& project);

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
    void msg(const QString &content);//TODO: get rid of that. It's used only while generating script.
    /**
     * @brief previewFile is used to refresh file preview
     * @param current current selected item on the list
     */
    void previewFile(QListWidgetItem* current);

private:
    Ui::ParametersWindow *ui;                   ///< GUI form pointer
    HelpDialog viewHelp;                        ///< Local instance of HelpDialog
    DataSystem *appSettings;//TODO:get rid of that. It's used only while constructing map.
    Project currentProject;                     ///< Local instance of project

    std::unique_ptr<RubySyntaxHighlighter> highlighter;


    bool filePreviewChanged;                    ///< Flag which represent changes in file preview editor
};

#endif // PARAMETERSWINDOW_H
