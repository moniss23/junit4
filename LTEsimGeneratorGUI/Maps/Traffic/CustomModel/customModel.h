#ifndef customModel_H
#define customModel_H

#include <QMainWindow>
#include <QComboBox>

#define AmountOfQci 9
#define MaxOfQciComboBox 24

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

    void setParameters(customModel **customModel);

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

    void on_cancelCustomModelButton_clicked();

    void on_saveCustomModelButton_clicked();

    void on_restoreCustomModelButton_clicked();

private:
    Ui::customModel *ui;
    customModel **custommodel;
    QString name;
    bool qciUsed[AmountOfQci];


    QComboBox *comboBoxForQci[MaxOfQciComboBox];
    QComboBox **pointercomboBoxForQciSyncedPing;
    QComboBox **pointercomboBoxForQciServiceReq;

    QString *QciCurrentText[MaxOfQciComboBox];

    struct customModelPingParameters{
        QString currentQciTextPing;
        int pingQci;
        int pingNumberOfPings;
        int pingInterval;
        int pingMinRecievedPings;
    };

    struct customModelVoipParameters{
        QString currentQciTextVoip;
        int voipQci;
        int voipDuration;
        int voipActivityFactor;
        int voipMaxTransferTime;
        int voipMinPacketsReceivedInTime;
    };

    struct customModelFtpDlParameters{
        QString currentQciTextFtpDl;
        int ftpDlQci;
        int ftpDlFilesize;
        int ftpDlMinThroughput;
    };

    struct customModelFtpUlParameters{
        QString currentQciTextFtpUl;
        int ftpUlQci;
        int ftpUlFilesize;
        int ftpUlMinThroughput;
    };

    struct customModelStreamDlParameters{
        QString currentQciTextStreamDl;
        int streamDlQci;
        int streamDlSpeed;
        int streamDlDuration;
        int streamDlMinThroughput;
    };

    struct customModelStreamUlParameters{
        QString currentQciTextStreamUl;
        int streamUlQci;
        int streamUlSpeed;
        int streamUlDuration;
        int streamUlMinThroughput;
    };

    struct customModelSyncedPingParameters{
        QString currentQciTextSyncedPing[9];
        int SyncedPingQciArray[9];
        int SyncedPingTimeBetweenTasks;
        int SyncedPingNumberOfPings;
        int SyncedPingInterval;
        int SyncedPingMinReceivedPings;
    };

    struct customModelServiceReqParameters{
        QString currentQciTextServiceReq[9];
        int ServiceReqQciArray[9];
        int ServiceReqTimeToWaitForAttach;
        int ServiceReqIntervalBetweenUlData;
    };

    customModelPingParameters CMPingParams;
    customModelVoipParameters CMVoipParams;
    customModelFtpDlParameters CMFtpDlParams;
    customModelFtpUlParameters CMFtpUlParams;
    customModelStreamDlParameters CMStreamDlParams;
    customModelStreamUlParameters CMStreamUlParams;
    customModelSyncedPingParameters CMSyncedPingParams;
    customModelServiceReqParameters CMServiceReqParams;

    void saveCustomModel();
    void refreshQci();
};

#endif // customModel_H
