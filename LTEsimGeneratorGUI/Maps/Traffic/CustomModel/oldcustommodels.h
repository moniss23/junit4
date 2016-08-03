#ifndef CUSTOMMODELS_H
#define CUSTOMMODELS_H

#include <QWidget>
#include <QString>
#include "addping.h"
#include "addpingform.h"
#include "addvoip.h"
#include "addvoipform.h"
#include "addftpdl.h"
#include "addftpdlform.h"
#include "addftpul.h"
#include "addftpulform.h"
#include "addstreamdl.h"
#include "addstreamdlform.h"
#include "addstreamul.h"
#include "addstreamulform.h"
#include "addsyncedping.h"
#include "addsyncedpingform.h"
#include "addservicereq.h"
#include "addservicereqform.h"
#include "ui_map_traffic.h"
#include <QPushButton>

#include <Maps/Traffic/map_traffic.h>


class my_qlabel;
namespace Ui {
class Custommodels;
}


class Custommodels : public QWidget
{
    Q_OBJECT

public:
    explicit Custommodels(QWidget *parent = 0);
    ~Custommodels();

    Addping *addping;
    Addvoip *addvoip;
    Addftpdl *addftpdl;
    Addftpul *addftpul;
    Addstreamdl *addstreamdl;
    Addstreamul *addstreamul;
    Addsyncedping *addsyncedping;
    Addservicereq *addservicereq;
    my_qlabel *tabCM;

    QCheckBox *pointerAddFtpUlChckBox;
    QCheckBox *pointerAddFtpDlChckBox;
    QCheckBox *pointerAddPingChckBox;
    QCheckBox *pointerAddServiceReqChckBox;
    QCheckBox *pointerAddStreamDlChckBox;
    QCheckBox *pointerAddStreamUlChckBox;
    QCheckBox *pointerAddSyncedPingChckBox;
    QCheckBox *pointerAddVoipChckBox;

    QPushButton *pointerAddFtpUlBt;
    QPushButton *pointerAddFtpDlBt;
    QPushButton *pointerAddPingBt;
    QPushButton *pointerAddServiceReqBt;
    QPushButton *pointerAddStreamDlBt;
    QPushButton *pointerAddStreamUlBt;
    QPushButton *pointerAddSyncedPingBt;
    QPushButton *pointerAddVoipBt;

    QStringList CM_Params[10];

    QList<QString> listStyle;
    QList<QString> listAddPing;
    QList<QString> listAddFtpDl;
    QList<QString> listAddFtpUl;
    QList<QString> listAddServiceReq;
    QList<QString> listAddStreamDl;
    QList<QString> listAddStreamUl;
    QList<QString> listAddSyncedPing;
    QList<QString> listAddVoip;

    void addToList();
    bool toBool(QString value);



    void set_custom_name(QString name);
        void setParameters();
            void startParameter();

private slots:
    void on_checkBox_add_Ping_clicked();

    void on_bt_add_Ping_clicked();

    void on_checkBox_add_Voip_clicked();

    void on_checkBox_add_FtpDl_clicked();

    void on_checkBox_add_Ftpul_clicked();

    void on_checkBox_add_StreamDI_clicked();

    void on_checkBox_add_StreamUI_clicked();

    void on_checkBox_add_SyncedPing_clicked();

    void on_checkBox_add_ServiceReq_clicked();

    void on_bt_add_Voip_clicked();

    void on_bt_add_FtpDl_clicked();

    void on_bt_add_FtpUl_clicked();

    void on_bt_add_StreamDI_clicked();

    void on_bt_add_StreamUI_clicked();

    void on_bt_SyncedPing_clicked();

    void on_bt_add_ServiceReq_clicked();

    void on_bt_save_clicked();

    void on_bt_cancel_clicked();

    void on_bt_restore_clicked();



private:
    Ui::Custommodels *ui;

    QString name;
    AddPingForm viewAddPing;
    AddVoipForm viewAddVoip;
    AddFtpDlForm viewAddFtpdl;
    AddFtpUlForm viewAddFtpul;
    AddStreamDlForm viewAddStreamdl;
    AddStreamUlForm viewAddStreamul;
    AddSyncedPingForm viewAddSyncedping;
    AddServiceReqForm viewAddServicereq;

    void saveColor();
    void saveParameters();




};

#endif // CUSTOMMODELS_H
