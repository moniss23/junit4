#ifndef PROJECTMANAGEMENT_H
#define PROJECTMANAGEMENT_H

#include <QMainWindow>
#include <management_window/filedialog.h>
#include <QListWidget>
#include <QListWidgetItem>
#include <vector>
#include <QString>
#include <management_window/encryption.h>

namespace Ui {
class ProjectManagement;
}

class ProjectManagement : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProjectManagement(QWidget *parent = 0);
    ~ProjectManagement();

    void addProject(QListWidgetItem* new_item,QString dir="<default>");

    QListWidgetItem* getCurrentItem();

    void previewProjectFiles(QListWidgetItem* item);
    bool projectNameTaken(QString name);
    QString getProjectDir(QString projectName);
    Project getProjectFromVector(int i);
    void setDefaultDir(QString dir);

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_pushButton_3_clicked();

    void rmrf(QString dir_name);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void open_project();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::ProjectManagement *ui;
    FileDialog createProject;
};

#endif // PROJECTMANAGEMENT_H
