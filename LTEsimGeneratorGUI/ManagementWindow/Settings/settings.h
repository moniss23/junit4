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
    void on_globalCustomDirRadioButton_toggled(bool checked);

    void on_projectCustomDirRadioButton_toggled(bool checked);

    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_globalBrowseButton_clicked();

    void on_applyButton_clicked();

    void on_globalDefaultButton_clicked();

    void on_projectDefaultButton_clicked();

    void on_globalDirInput_textChanged(const QString &arg1);

    void on_projectBrowseButton_clicked();

    void apply_settings();

    void on_radioButton_clicked();

private:
    Ui::Settings *ui;
    bool changesMade;
    AppSettings *appSettings;
};

#endif // SETTINGS_H
