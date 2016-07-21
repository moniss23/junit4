#ifndef PARAMETERSWINDOW_H
#define PARAMETERSWINDOW_H

#include <QMainWindow>
#include <QWidget>
 #include <QFileDialog>
#include <QString>
#include <QVBoxLayout>

#include "helpdialog.h"
#include "filedialog.h"
#include <QCloseEvent>
#include <QListWidgetItem>
#include "appsettings.h"

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
    void generate_template_prameters();
    void generate_template_traffic();
    void FilesPanel();
    void addButtonToFilePanel();
    void addParamFile();
    void addTrafficFile();
    void loadProject();
    void refreshPreview();
    void save_project(bool);    
    void setParamsCM();

    void setFileDialogAppSettings(AppSettings *value);

private slots:

    void on_actionNew_triggered();

    void on_actionAbout_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void previewTrafficFile();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void previewFile(QListWidgetItem* current);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void switch_button_state_undo(bool available);
    void switch_button_state_redo(bool available);

    void on_pushButton_7_clicked();
    
    void on_textEdit_textChanged();

    void on_pushButton_6_clicked();

    void on_actionPath_triggered();



    void on_radioButton_normalMap_toggled(bool checked);

    void on_radioButton_largeMap_toggled(bool checked);

private:
    Ui::ParametersWindow *ui;
    HelpDialog viewHelp;
    FileDialog createProject;
    AppSettings *appSettings;
};

#endif // PARAMETERSWINDOW_H

