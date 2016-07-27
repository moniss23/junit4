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

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_pushButton_3_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void open_project();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::ProjectManagement *ui;
    FileDialog createProject;
    AppSettings* appSettings;
};

#endif // PROJECTMANAGEMENT_H
