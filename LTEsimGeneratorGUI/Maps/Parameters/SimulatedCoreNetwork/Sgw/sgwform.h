#ifndef SGWFORM_H
#define SGWFORM_H

#include <QWidget>
#include <QMessageBox>
#include <Data/ProjectSettings/sgwsettings.h>
namespace Ui {
class SGWForm;
}

class SGWForm : public QWidget
{
    Q_OBJECT

public:
    explicit SGWForm(QWidget *parent = 0);
    void set_checkboxactive(bool check);
    bool get_checkboxactive();
    void setDefaultParameters();
    ~SGWForm();
private slots:
    void on_tet_sgw_names_returnPressed();
    void on_tet_sgw_ipAddresses_returnPressed();
    void on_tet_sgw_apn_lists_returnPressed();
    void on_tet_sgw_LDIs_returnPressed();

    void on_buttonBox_accepted();

    void on_pbReset_clicked();

    void on_buttonBox_rejected();
    void setChanges();
    void loadAndSpawn(const SgwSettings & sgwSettings, const QString &projectName);
signals:
    void updateSgw(const SgwSettings &sgwSettings,const QString &projectName);
private:
    Ui::SGWForm *ui;
    QMessageBox msg,msgBox;
    SgwSettings sgwSettings;
    QString projectName;
    bool flagConfirmNewValue;
    bool checkboxactive;
    bool wasThereChanges;
    void saveAll();
};

#endif // SGWFORM_H
