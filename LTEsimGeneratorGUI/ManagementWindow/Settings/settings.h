#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <AppSettings/appsettings.h>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(AppSettings *appSettings, QWidget *parent = 0, bool secondTabActive = true);
    ~Settings();

    //TODO: new API to implement
    //***********************************************/
signals:
    void RestoreDefaultsSettings();
    void SetDefaultLocationForNewProjects();
    void SetLocationFor_RB_Files();
    //***********************************************
    //***********************************************/

private slots:
    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_4_toggled(bool checked);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void apply_settings();

private:
    Ui::Settings *ui;
    bool changesMade;
    AppSettings *appSettings;
};

#endif // SETTINGS_H
