#ifndef ADDPROJECTWINDOW_H
#define ADDPROJECTWINDOW_H

#include <QDialog>
#include <QString>
#include <AppSettings/appsettings.h>
#include <QObject>

namespace Ui {
class AddProjectWindow;
}

class AddProjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddProjectWindow(AppSettings* appSettings, QWidget *parent = 0);
    ~AddProjectWindow();

    void clearInputArea();

    void setDefaultDir(QString dir);

    void setAppSettings(AppSettings *value);

signals:

    //TODO: new API to implement
    //***********************************************/
    void createNewProject(const QString& projectName, const QString& directory);

    //***********************************************
    //***********************************************/

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_browseDirectoryButton_clicked();

    void on_defaultLocationRadioButton_toggled(bool checked);

private:
    Ui::AddProjectWindow *ui;
    AppSettings* appSettings;
};

#endif // ADDPROJECTWINDOW_H
