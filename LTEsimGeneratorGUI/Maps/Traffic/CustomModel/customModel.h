#ifndef customModel_H
#define customModel_H

#include <QMainWindow>
#include <QComboBox>

namespace Ui {
class customModel;
}

class customModel : public QMainWindow
{
    Q_OBJECT

public:
    explicit customModel(QWidget *parent = 0);
    ~customModel();

    void set_custom_name(QString name);


private slots:
    void on_checkBoxPing_clicked();

    void on_checkBoxVoip_clicked();

    void on_checkBoxFTPDl_clicked();

    void on_checkBoxFTPUl_clicked();

    void on_checkBoxStreamDl_clicked();

    void on_checkBoxStreamUl_clicked();

    void on_checkBoxSyncedPing_clicked();

    void on_checkBoxServiceReq_clicked();

    void on_comboBoxPingQci_activated(const QString &arg1);

    void on_comboBoxVoipQci_activated(const QString &arg1);

    void on_comboBoxFTPDlQci_activated(const QString &arg1);

    void on_comboBoxFTPUlQci_activated(const QString &arg1);

    void on_comboBoxStreamDlQci_activated(const QString &arg1);

    void on_comboBoxStreamUlQci_activated(const QString &arg1);

    void on_comboBoxSyncedPingQci1_activated(const QString &arg1);

    void on_comboBoxSyncedPingQci2_activated(const QString &arg1);

    void on_comboBoxSyncedPingQci3_activated(const QString &arg1);

    void on_comboBoxSyncedPingQci4_activated(const QString &arg1);

    void on_comboBoxSyncedPingQci5_activated(const QString &arg1);

    void on_comboBoxSyncedPingQci6_activated(const QString &arg1);

    void on_comboBoxSyncedPingQci7_activated(const QString &arg1);

    void on_comboBoxSyncedPingQci8_activated(const QString &arg1);

    void on_comboBoxSyncedPingQci9_activated(const QString &arg1);

    void on_comboBoxServiceReqQci1_activated(const QString &arg1);

    void on_comboBoxServiceReqQci2_activated(const QString &arg1);

    void on_comboBoxServiceReqQci3_activated(const QString &arg1);

    void on_comboBoxServiceReqQci4_activated(const QString &arg1);

    void on_comboBoxServiceReqQci5_activated(const QString &arg1);

    void on_comboBoxServiceReqQci6_activated(const QString &arg1);

    void on_comboBoxServiceReqQci7_activated(const QString &arg1);

    void on_comboBoxServiceReqQci8_activated(const QString &arg1);

    void on_comboBoxServiceReqQci9_activated(const QString &arg1);

private:
    Ui::customModel *ui;
    QString name;
    bool qciUsed[9];
    QString QciCurrentText[24];

    void refreshPingQci();
    void refreshVoipQci();
    void refreshFTPDlQci();
    void refreshFTPUlQci();
    void refreshStreamDlQci();
    void refreshStreamUlQci();
    void refreshSyncedPingQci();
    void refreshServiceReqQci();
    void refreshQci();
};

#endif // customModel_H
