#include "custommodels.h"
#include "ui_custommodels.h"
#include <QMessageBox>
#include <QSettings>
#include <Maps/Traffic/map_traffic.h>
#include <Maps/Traffic/map_traffic_large.h>



extern my_qlabel *pointer_CM1;
extern my_qlabel *pointer_CM2;
extern my_qlabel *pointer_CM3;
extern my_qlabel *pointer_CM4;
extern my_qlabel *pointer_CM5;
extern my_qlabel *pointer_CM6;
extern my_qlabel *pointer_CM7;
extern my_qlabel *pointer_CM8;
extern my_qlabel *pointer_CM9;
extern my_qlabel *pointer_CM10;

extern my_qlabel *pointer_CM1_large;
extern my_qlabel *pointer_CM2_large;
extern my_qlabel *pointer_CM3_large;
extern my_qlabel *pointer_CM4_large;
extern my_qlabel *pointer_CM5_large;
extern my_qlabel *pointer_CM6_large;
extern my_qlabel *pointer_CM7_large;
extern my_qlabel *pointer_CM8_large;
extern my_qlabel *pointer_CM9_large;
extern my_qlabel *pointer_CM10_large;

extern QString CMname;
extern QString CMname_large;


extern QString curPS[20];

bool CMisActive[10];

QStringList CM_List;

QString CM1Style;
QString CM2Style;
QString CM3Style;
QString CM4Style;
QString CM5Style;
QString CM6Style;
QString CM7Style;
QString CM8Style;
QString CM9Style;
QString CM10Style;

QString CM1Style_large;
QString CM2Style_large;
QString CM3Style_large;
QString CM4Style_large;
QString CM5Style_large;
QString CM6Style_large;
QString CM7Style_large;
QString CM8Style_large;
QString CM9Style_large;
QString CM10Style_large;

bool addFtpDLCheckbox;
bool addFtpUlCheckbox;
bool addPingCheckbox;
bool addServiceReqCheckbox;
bool addStreamDlCheckbox;
bool addStreamUlCheckbox;
bool addSyncedPingCheckbox;
bool addVoipCheckbox;

extern bool small;
extern bool large;

QStringList customModelList;

QStringList readyListCM1;
QStringList readyListCM2;
QStringList readyListCM3;
QStringList readyListCM4;
QStringList readyListCM5;
QStringList readyListCM6;
QStringList readyListCM7;
QStringList readyListCM8;
QStringList readyListCM9;
QStringList readyListCM10;

extern QList<QString> PingList;
extern QList<QString> VoipList;
extern QList<QString> SyncedPingList;
extern QList<QString> StreamUlList;
extern QList<QString> StreamDlList;
extern QList<QString> ServiceReqList;
extern QList<QString> FtpUlList;
extern QList<QString> FtpDlList;

bool save1;
bool save2;
bool save3;
bool save4;
bool save5;
bool save6;
bool save7;
bool save8;
bool save9;
bool save10;

bool restoreClicked;

extern bool MainSaveWasClicked;

Custommodels::Custommodels(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Custommodels)
{
    ui->setupUi(this);

    addping = new Addping();
    addvoip = new Addvoip();
    addftpdl = new Addftpdl();
    addftpul = new Addftpul();
    addstreamdl = new Addstreamdl();
    addstreamul = new Addstreamul();
    addsyncedping = new Addsyncedping();
    addservicereq = new Addservicereq();


    on_checkBox_add_Ping_clicked();
    on_checkBox_add_Voip_clicked();
    on_checkBox_add_FtpDl_clicked();
    on_checkBox_add_Ftpul_clicked();
    on_checkBox_add_StreamDI_clicked();
    on_checkBox_add_StreamUI_clicked();
    on_checkBox_add_SyncedPing_clicked();
    on_checkBox_add_ServiceReq_clicked();

    pointerAddFtpDlChckBox = ui->checkBox_add_FtpDl;
    pointerAddFtpUlChckBox = ui->checkBox_add_Ftpul;
    pointerAddPingChckBox = ui->checkBox_add_Ping;
    pointerAddServiceReqChckBox = ui->checkBox_add_ServiceReq;
    pointerAddStreamDlChckBox = ui->checkBox_add_StreamDI;
    pointerAddStreamUlChckBox = ui->checkBox_add_StreamUI;
    pointerAddSyncedPingChckBox = ui->checkBox_add_SyncedPing;
    pointerAddVoipChckBox = ui->checkBox_add_Voip;

    pointerAddFtpDlBt = ui->bt_add_FtpDl;
    pointerAddFtpUlBt =ui->bt_add_FtpUl;
    pointerAddPingBt = ui->bt_add_Ping;
    pointerAddServiceReqBt = ui->bt_add_ServiceReq;
    pointerAddStreamDlBt = ui->bt_add_StreamDI;
    pointerAddStreamUlBt = ui->bt_add_StreamUI;
    pointerAddSyncedPingBt = ui->bt_SyncedPing;
    pointerAddVoipBt = ui->bt_add_Voip;

    std::fill(CMisActive, CMisActive + 10, false);
}



Custommodels::~Custommodels()
{
    delete ui;
}

void Custommodels::on_checkBox_add_Ping_clicked()
{
    ui->bt_add_Ping->setEnabled(ui->checkBox_add_Ping->isChecked());
}

void Custommodels::on_checkBox_add_Voip_clicked()
{
    ui->bt_add_Voip->setEnabled(ui->checkBox_add_Voip->isChecked());
}

void Custommodels::on_checkBox_add_FtpDl_clicked()
{
    ui->bt_add_FtpDl->setEnabled(ui->checkBox_add_FtpDl->isChecked());
}

void Custommodels::on_checkBox_add_Ftpul_clicked()
{
    ui->bt_add_FtpUl->setEnabled(ui->checkBox_add_Ftpul->isChecked());
}

void Custommodels::on_checkBox_add_StreamDI_clicked()
{
    ui->bt_add_StreamDI->setEnabled(ui->checkBox_add_StreamDI->isChecked());
}

void Custommodels::on_checkBox_add_StreamUI_clicked()
{
    ui->bt_add_StreamUI->setEnabled(ui->checkBox_add_StreamUI->isChecked());
}

void Custommodels::on_checkBox_add_SyncedPing_clicked()
{
    ui->bt_SyncedPing->setEnabled(ui->checkBox_add_SyncedPing->isChecked());
}

void Custommodels::on_checkBox_add_ServiceReq_clicked()
{
    ui->bt_add_ServiceReq->setEnabled(ui->checkBox_add_ServiceReq->isChecked());
}

void Custommodels::on_bt_add_Ping_clicked()
{
    viewAddPing.close();
    viewAddPing.setWindowModality(Qt::WindowModal);

    viewAddPing.qciAddpingPointer->clear();

    bool qciActive[10];
    std::fill(qciActive, qciActive + 9, true);

    // removes qci used in ftp Dl
    if(viewAddFtpdl.qciAddFtpDlPointer->currentText() != "")
    {
        qciActive[viewAddFtpdl.qciAddFtpDlPointer->currentText().toInt()]=false;
    }

    // removes qci used in FtpUl
    if(viewAddFtpul.qciAddFtpUlPointer->currentText() != "" )
    {
        qciActive[viewAddFtpul.qciAddFtpUlPointer->currentText().toInt()]=false;
    }

    // removes qci used inVoip
    if(viewAddVoip.qciAddVoipPointer->currentText() != "")
    {
        qciActive[viewAddVoip.qciAddVoipPointer->currentText().toInt()]=false;
    }

    // removes qci used instreamUl
    if(viewAddStreamul.qciAddStreamUlPointer->currentText() != "")
    {
        qciActive[viewAddStreamul.qciAddStreamUlPointer->currentText().toInt()]=false;
    }

    // removes qci used instremDl
    if(viewAddStreamdl.qciAddStreamDlPointer->currentText() != "")
    {
        qciActive[viewAddStreamdl.qciAddStreamDlPointer->currentText().toInt()]=false;
    }

    // removes qci used in ServiceReq
    if(viewAddServicereq.qciAddServiceReqQci1->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci1->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci2->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci2->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci3->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci3->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci4->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci4->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci5->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci5->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci6->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci6->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci7->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci7->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci8->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci8->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci9->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci9->currentText().toInt()]=false;
    }

    // removes qci used in Syncaddping
    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci1->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci2->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci3->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci4->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci5->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci6->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci7->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci8->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci9->currentText().toInt()]=false;
    }

    viewAddPing.qciAddpingPointer->addItem("");
    for(int i=1;i<10;i++)
        if(qciActive[i])
            viewAddPing.qciAddpingPointer->addItem(QString().number(i));

    viewAddPing.setParameters(addping);
    viewAddPing.show();
}

void Custommodels::on_bt_add_Voip_clicked()
{

    viewAddVoip.close();
    viewAddVoip.setWindowModality(Qt::WindowModal);

    viewAddVoip.qciAddVoipPointer->clear();

    bool qciActive[10];
    std::fill(qciActive, qciActive + 9, true);

    // removes qci used in ftp Dl
    if(viewAddFtpdl.qciAddFtpDlPointer->currentText() != "")
    {
        qciActive[viewAddFtpdl.qciAddFtpDlPointer->currentText().toInt()]=false;
    }

    // removes qci used in FtpUl
    if(viewAddFtpul.qciAddFtpUlPointer->currentText() != "" )
    {
        qciActive[viewAddFtpul.qciAddFtpUlPointer->currentText().toInt()]=false;
    }

    // removes qci used in Ping
    if(viewAddPing.qciAddpingPointer->currentText() != "")
    {
        qciActive[viewAddPing.qciAddpingPointer->currentText().toInt()]=false;
    }

    // removes qci used instreamUl
    if(viewAddStreamul.qciAddStreamUlPointer->currentText() != "")
    {
        qciActive[viewAddStreamul.qciAddStreamUlPointer->currentText().toInt()]=false;
    }

    // removes qci used instremDl
    if(viewAddStreamdl.qciAddStreamDlPointer->currentText() != "")
    {
        qciActive[viewAddStreamdl.qciAddStreamDlPointer->currentText().toInt()]=false;
    }

    // removes qci used in ServiceReq
    if(viewAddServicereq.qciAddServiceReqQci1->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci1->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci2->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci2->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci3->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci3->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci4->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci4->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci5->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci5->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci6->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci6->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci7->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci7->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci8->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci8->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci9->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci9->currentText().toInt()]=false;
    }

    // removes qci used in Syncaddping
    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci1->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci2->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci3->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci4->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci5->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci6->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci7->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci8->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci9->currentText().toInt()]=false;
    }

    viewAddVoip.qciAddVoipPointer->addItem("");
    for(int i=1;i<10;i++)
        if(qciActive[i])
            viewAddVoip.qciAddVoipPointer->addItem(QString().number(i));

    viewAddVoip.setParameters(addvoip);
    viewAddVoip.show();
}

void Custommodels::on_bt_add_FtpDl_clicked()
{
    viewAddFtpdl.close();
    viewAddFtpdl.setWindowModality(Qt::WindowModal);

    viewAddFtpdl.qciAddFtpDlPointer->clear();

    bool qciActive[10];
    std::fill(qciActive, qciActive + 9, true);

    // removes qci used in Ping
    if(viewAddPing.qciAddpingPointer->currentText() != "")
    {
        qciActive[viewAddPing.qciAddpingPointer->currentText().toInt()]=false;
    }

    // removes qci used in FtpUl
    if(viewAddFtpul.qciAddFtpUlPointer->currentText() != "" )
    {
        qciActive[viewAddFtpul.qciAddFtpUlPointer->currentText().toInt()]=false;
    }

    // removes qci used inVoip
    if(viewAddVoip.qciAddVoipPointer->currentText() != "")
    {
        qciActive[viewAddVoip.qciAddVoipPointer->currentText().toInt()]=false;
    }

    // removes qci used instreamUl
    if(viewAddStreamul.qciAddStreamUlPointer->currentText() != "")
    {
        qciActive[viewAddStreamul.qciAddStreamUlPointer->currentText().toInt()]=false;
    }

    // removes qci used instremDl
    if(viewAddStreamdl.qciAddStreamDlPointer->currentText() != "")
    {
        qciActive[viewAddStreamdl.qciAddStreamDlPointer->currentText().toInt()]=false;
    }

    // removes qci used in ServiceReq
    if(viewAddServicereq.qciAddServiceReqQci1->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci1->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci2->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci2->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci3->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci3->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci4->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci4->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci5->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci5->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci6->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci6->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci7->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci7->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci8->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci8->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci9->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci9->currentText().toInt()]=false;
    }

    // removes qci used in Syncaddping
    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci1->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci2->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci3->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci4->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci5->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci6->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci7->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci8->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci9->currentText().toInt()]=false;
    }

    viewAddFtpdl.qciAddFtpDlPointer->addItem("");
    for(int i=1;i<10;i++)
        if(qciActive[i])
            viewAddFtpdl.qciAddFtpDlPointer->addItem(QString().number(i));

    viewAddFtpdl.setParameters(addftpdl);
    viewAddFtpdl.show();
}

void Custommodels::on_bt_add_FtpUl_clicked()
{
    viewAddFtpul.close();
    viewAddFtpul.setWindowModality(Qt::WindowModal);

    viewAddFtpul.qciAddFtpUlPointer->clear();

    bool qciActive[10];
    std::fill(qciActive, qciActive + 9, true);

    // removes qci used in Ping
    if(viewAddPing.qciAddpingPointer->currentText() != "")
    {
        qciActive[viewAddPing.qciAddpingPointer->currentText().toInt()]=false;
    }

    // removes qci used in ftp Dl
    if(viewAddFtpdl.qciAddFtpDlPointer->currentText() != "")
    {
        qciActive[viewAddFtpdl.qciAddFtpDlPointer->currentText().toInt()]=false;
    }

    // removes qci used inVoip
    if(viewAddVoip.qciAddVoipPointer->currentText() != "")
    {
        qciActive[viewAddVoip.qciAddVoipPointer->currentText().toInt()]=false;
    }

    // removes qci used instreamUl
    if(viewAddStreamul.qciAddStreamUlPointer->currentText() != "")
    {
        qciActive[viewAddStreamul.qciAddStreamUlPointer->currentText().toInt()]=false;
    }

    // removes qci used instremDl
    if(viewAddStreamdl.qciAddStreamDlPointer->currentText() != "")
    {
        qciActive[viewAddStreamdl.qciAddStreamDlPointer->currentText().toInt()]=false;
    }

    // removes qci used in ServiceReq
    if(viewAddServicereq.qciAddServiceReqQci1->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci1->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci2->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci2->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci3->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci3->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci4->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci4->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci5->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci5->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci6->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci6->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci7->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci7->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci8->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci8->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci9->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci9->currentText().toInt()]=false;
    }

    // removes qci used in Syncaddping
    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci1->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci2->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci3->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci4->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci5->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci6->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci7->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci8->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci9->currentText().toInt()]=false;
    }

    viewAddFtpul.qciAddFtpUlPointer->addItem("");
    for(int i=1;i<10;i++)
        if(qciActive[i])
            viewAddFtpul.qciAddFtpUlPointer->addItem(QString().number(i));

    viewAddFtpul.setParameters(addftpul);
    viewAddFtpul.show();
}

void Custommodels::on_bt_add_StreamDI_clicked()
{
    viewAddStreamdl.close();
    viewAddStreamdl.setWindowModality(Qt::WindowModal);

    viewAddStreamdl.qciAddStreamDlPointer->clear();

    bool qciActive[10];
    std::fill(qciActive, qciActive + 9, true);

    // removes qci used in Ping
    if(viewAddPing.qciAddpingPointer->currentText() != "")
    {
        qciActive[viewAddPing.qciAddpingPointer->currentText().toInt()]=false;
    }

    // removes qci used in ftp Dl
    if(viewAddFtpdl.qciAddFtpDlPointer->currentText() != "")
    {
        qciActive[viewAddFtpdl.qciAddFtpDlPointer->currentText().toInt()]=false;
    }

    // removes qci used inVoip
    if(viewAddVoip.qciAddVoipPointer->currentText() != "")
    {
        qciActive[viewAddVoip.qciAddVoipPointer->currentText().toInt()]=false;
    }

    // removes qci used instreamUl
    if(viewAddStreamul.qciAddStreamUlPointer->currentText() != "")
    {
        qciActive[viewAddStreamul.qciAddStreamUlPointer->currentText().toInt()]=false;
    }

    // removes qci used in FtpUl
    if(viewAddFtpul.qciAddFtpUlPointer->currentText() != "" )
    {
        qciActive[viewAddFtpul.qciAddFtpUlPointer->currentText().toInt()]=false;
    }

    // removes qci used in ServiceReq
    if(viewAddServicereq.qciAddServiceReqQci1->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci1->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci2->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci2->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci3->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci3->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci4->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci4->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci5->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci5->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci6->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci6->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci7->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci7->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci8->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci8->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci9->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci9->currentText().toInt()]=false;
    }

    // removes qci used in Syncaddping
    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci1->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci2->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci3->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci4->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci5->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci6->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci7->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci8->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci9->currentText().toInt()]=false;
    }

    viewAddStreamdl.qciAddStreamDlPointer->addItem("");
    for(int i=1;i<10;i++)
        if(qciActive[i])
            viewAddStreamdl.qciAddStreamDlPointer->addItem(QString().number(i));

    viewAddStreamdl.setParameters(addstreamdl);
    viewAddStreamdl.show();
}

void Custommodels::on_bt_add_StreamUI_clicked()
{

    viewAddStreamul.close();
    viewAddStreamul.setWindowModality(Qt::WindowModal);

    viewAddStreamul.qciAddStreamUlPointer->clear();

    bool qciActive[10];
    std::fill(qciActive, qciActive + 9, true);

    // removes qci used in ftp Dl
    if(viewAddFtpdl.qciAddFtpDlPointer->currentText() != "")
    {
        qciActive[viewAddFtpdl.qciAddFtpDlPointer->currentText().toInt()]=false;
    }

    // removes qci used in FtpUl
    if(viewAddFtpul.qciAddFtpUlPointer->currentText() != "" )
    {
        qciActive[viewAddFtpul.qciAddFtpUlPointer->currentText().toInt()]=false;
    }

    // removes qci used in Ping
    if(viewAddPing.qciAddpingPointer->currentText() != "")
    {
        qciActive[viewAddPing.qciAddpingPointer->currentText().toInt()]=false;
    }

    // removes qci used inVoip
    if(viewAddVoip.qciAddVoipPointer->currentText() != "")
    {
        qciActive[viewAddVoip.qciAddVoipPointer->currentText().toInt()]=false;
    }

    // removes qci used instremDl
    if(viewAddStreamdl.qciAddStreamDlPointer->currentText() != "")
    {
        qciActive[viewAddStreamdl.qciAddStreamDlPointer->currentText().toInt()]=false;
    }

    // removes qci used in ServiceReq
    if(viewAddServicereq.qciAddServiceReqQci1->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci1->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci2->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci2->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci3->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci3->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci4->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci4->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci5->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci5->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci6->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci6->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci7->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci7->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci8->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci8->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci9->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci9->currentText().toInt()]=false;
    }

    // removes qci used in Syncaddping
    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci1->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci2->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci3->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci4->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci5->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci6->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci7->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci8->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci9->currentText().toInt()]=false;
    }

    viewAddStreamul.qciAddStreamUlPointer->addItem("");
    for(int i=1;i<10;i++)
        if(qciActive[i])
            viewAddStreamul.qciAddStreamUlPointer->addItem(QString().number(i));

    viewAddStreamul.setParameters(addstreamul);
    viewAddStreamul.show();
}

void Custommodels::on_bt_SyncedPing_clicked()
{
    viewAddSyncedping.close();
    viewAddSyncedping.setWindowModality(Qt::WindowModal);

    viewAddSyncedping.qciAddSyncedPingQci1->clear();
    viewAddSyncedping.qciAddSyncedPingQci2->clear();
    viewAddSyncedping.qciAddSyncedPingQci3->clear();
    viewAddSyncedping.qciAddSyncedPingQci4->clear();
    viewAddSyncedping.qciAddSyncedPingQci5->clear();
    viewAddSyncedping.qciAddSyncedPingQci6->clear();
    viewAddSyncedping.qciAddSyncedPingQci7->clear();
    viewAddSyncedping.qciAddSyncedPingQci8->clear();
    viewAddSyncedping.qciAddSyncedPingQci9->clear();

    bool qciActive[10];
    std::fill(qciActive, qciActive + 9, true);

    // removes qci used in ftp Dl
    if(viewAddFtpdl.qciAddFtpDlPointer->currentText() != "")
    {
        qciActive[viewAddFtpdl.qciAddFtpDlPointer->currentText().toInt()]=false;
    }

    // removes qci used in FtpUl
    if(viewAddFtpul.qciAddFtpUlPointer->currentText() != "" )
    {
        qciActive[viewAddFtpul.qciAddFtpUlPointer->currentText().toInt()]=false;
    }

    // removes qci used in Ping
    if(viewAddPing.qciAddpingPointer->currentText() != "")
    {
        qciActive[viewAddPing.qciAddpingPointer->currentText().toInt()]=false;
    }

    // removes qci used inVoip
    if(viewAddVoip.qciAddVoipPointer->currentText() != "")
    {
        qciActive[viewAddVoip.qciAddVoipPointer->currentText().toInt()]=false;
    }

    // removes qci used instremDl
    if(viewAddStreamdl.qciAddStreamDlPointer->currentText() != "")
    {
        qciActive[viewAddStreamdl.qciAddStreamDlPointer->currentText().toInt()]=false;
    }

    // removes qci used instreamUl
    if(viewAddStreamul.qciAddStreamUlPointer->currentText() != "")
    {
        qciActive[viewAddStreamul.qciAddStreamUlPointer->currentText().toInt()]=false;
    }

    // removes qci used in ServiceReq
    if(viewAddServicereq.qciAddServiceReqQci1->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci1->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci2->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci2->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci3->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci3->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci4->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci4->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci5->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci5->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci6->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci6->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci7->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci7->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci8->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci8->currentText().toInt()]=false;
    }

    if(viewAddServicereq.qciAddServiceReqQci9->currentText() != "")
    {
        qciActive[viewAddServicereq.qciAddServiceReqQci9->currentText().toInt()]=false;
    }

    viewAddSyncedping.qciAddSyncedPingQci1->addItem("");
    viewAddSyncedping.qciAddSyncedPingQci2->addItem("");
    viewAddSyncedping.qciAddSyncedPingQci3->addItem("");
    viewAddSyncedping.qciAddSyncedPingQci4->addItem("");
    viewAddSyncedping.qciAddSyncedPingQci5->addItem("");
    viewAddSyncedping.qciAddSyncedPingQci6->addItem("");
    viewAddSyncedping.qciAddSyncedPingQci7->addItem("");
    viewAddSyncedping.qciAddSyncedPingQci8->addItem("");
    viewAddSyncedping.qciAddSyncedPingQci9->addItem("");
    for(int i=1;i<10;i++)
        if(qciActive[i])
        {
            viewAddSyncedping.qciAddSyncedPingQci1->addItem(QString().number(i));
            viewAddSyncedping.qciAddSyncedPingQci2->addItem(QString().number(i));
            viewAddSyncedping.qciAddSyncedPingQci3->addItem(QString().number(i));
            viewAddSyncedping.qciAddSyncedPingQci4->addItem(QString().number(i));
            viewAddSyncedping.qciAddSyncedPingQci5->addItem(QString().number(i));
            viewAddSyncedping.qciAddSyncedPingQci6->addItem(QString().number(i));
            viewAddSyncedping.qciAddSyncedPingQci7->addItem(QString().number(i));
            viewAddSyncedping.qciAddSyncedPingQci8->addItem(QString().number(i));
            viewAddSyncedping.qciAddSyncedPingQci9->addItem(QString().number(i));
        }

    viewAddSyncedping.setParameters(addsyncedping);
    viewAddSyncedping.show();
}

void Custommodels::on_bt_add_ServiceReq_clicked()
{
    viewAddServicereq.close();
    viewAddServicereq.setWindowModality(Qt::WindowModal);

    viewAddServicereq.qciAddServiceReqQci1->clear();
    viewAddServicereq.qciAddServiceReqQci2->clear();
    viewAddServicereq.qciAddServiceReqQci3->clear();
    viewAddServicereq.qciAddServiceReqQci4->clear();
    viewAddServicereq.qciAddServiceReqQci5->clear();
    viewAddServicereq.qciAddServiceReqQci6->clear();
    viewAddServicereq.qciAddServiceReqQci7->clear();
    viewAddServicereq.qciAddServiceReqQci8->clear();
    viewAddServicereq.qciAddServiceReqQci9->clear();

    bool qciActive[10];
    std::fill(qciActive, qciActive + 9, true);

    // removes qci used in ftp Dl
    if(viewAddFtpdl.qciAddFtpDlPointer->currentText() != "")
    {
        qciActive[viewAddFtpdl.qciAddFtpDlPointer->currentText().toInt()]=false;
    }

    // removes qci used in FtpUl
    if(viewAddFtpul.qciAddFtpUlPointer->currentText() != "" )
    {
        qciActive[viewAddFtpul.qciAddFtpUlPointer->currentText().toInt()]=false;
    }

    // removes qci used in Ping
    if(viewAddPing.qciAddpingPointer->currentText() != "")
    {
        qciActive[viewAddPing.qciAddpingPointer->currentText().toInt()]=false;
    }

    // removes qci used inVoip
    if(viewAddVoip.qciAddVoipPointer->currentText() != "")
    {
        qciActive[viewAddVoip.qciAddVoipPointer->currentText().toInt()]=false;
    }

    // removes qci used instremDl
    if(viewAddStreamdl.qciAddStreamDlPointer->currentText() != "")
    {
        qciActive[viewAddStreamdl.qciAddStreamDlPointer->currentText().toInt()]=false;
    }

    // removes qci used instreamUl
    if(viewAddStreamul.qciAddStreamUlPointer->currentText() != "")
    {
        qciActive[viewAddStreamul.qciAddStreamUlPointer->currentText().toInt()]=false;
    }

    // removes qci used in Syncedping
    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci1->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci2->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci3->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci4->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci5->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci6->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci7->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci8->currentText().toInt()]=false;
    }

    if(viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "")
    {
        qciActive[viewAddSyncedping.qciAddSyncedPingQci9->currentText().toInt()]=false;
    }

    viewAddServicereq.qciAddServiceReqQci1->addItem("");
    viewAddServicereq.qciAddServiceReqQci2->addItem("");
    viewAddServicereq.qciAddServiceReqQci3->addItem("");
    viewAddServicereq.qciAddServiceReqQci4->addItem("");
    viewAddServicereq.qciAddServiceReqQci5->addItem("");
    viewAddServicereq.qciAddServiceReqQci6->addItem("");
    viewAddServicereq.qciAddServiceReqQci7->addItem("");
    viewAddServicereq.qciAddServiceReqQci8->addItem("");
    viewAddServicereq.qciAddServiceReqQci9->addItem("");
    for(int i=1;i<10;i++)
        if(qciActive[i])
        {
            viewAddServicereq.qciAddServiceReqQci1->addItem(QString().number(i));
            viewAddServicereq.qciAddServiceReqQci2->addItem(QString().number(i));
            viewAddServicereq.qciAddServiceReqQci3->addItem(QString().number(i));
            viewAddServicereq.qciAddServiceReqQci4->addItem(QString().number(i));
            viewAddServicereq.qciAddServiceReqQci5->addItem(QString().number(i));
            viewAddServicereq.qciAddServiceReqQci6->addItem(QString().number(i));
            viewAddServicereq.qciAddServiceReqQci7->addItem(QString().number(i));
            viewAddServicereq.qciAddServiceReqQci8->addItem(QString().number(i));
            viewAddServicereq.qciAddServiceReqQci9->addItem(QString().number(i));
        }

    viewAddServicereq.setParameters(addservicereq);
    viewAddServicereq.show();
}

void Custommodels::set_custom_name(QString name)
{
    this->name = name;
}

void Custommodels::on_bt_save_clicked()
{
    restoreClicked = false;

    if(ui->checkBox_add_FtpDl->isChecked() || ui->checkBox_add_Ftpul->isChecked() || ui->checkBox_add_Ping->isChecked()|| ui->checkBox_add_ServiceReq->isChecked() || ui->checkBox_add_StreamDI->isChecked() || ui->checkBox_add_StreamUI->isChecked() || ui->checkBox_add_SyncedPing->isChecked() || ui->checkBox_add_Voip->isChecked()){

        if(small == true){

            if(CMname == "Custom Model 1"){
                // large = false;
                CM_List.append(CMname);
                CMisActive[1]=true;
                save1 = true;
                pointer_CM1->setStyleSheet("QLabel { background-color : green; color : white; }");
                this->close();

            }

            if(CMname == "Custom Model 2"){
                //   large = false;
                CM_List.append(CMname);
                CMisActive[2]=true;;
                save2 = true;
                pointer_CM2->setStyleSheet("QLabel { background-color : green; color : white; }");
                this->close();
            }

            if(CMname == "Custom Model 3"){

                CM_List.append(CMname);
                //    large = false;
                CMisActive[3]=true;
                save3 = true;
                pointer_CM3->setStyleSheet("QLabel { background-color : green; color : white; }");
                this->close();
            }

            if(CMname == "Custom Model 4"){

                CM_List.append(CMname);
                //   large = false;
                CMisActive[3]=true;
                save4 = true;
                pointer_CM4->setStyleSheet("QLabel { background-color : green; color : white; }");
                this->close();
            }

            if(CMname == "Custom Model 5"){

                CM_List.append(CMname);
                //  large = false;
                CMisActive[5]=true;
                save5 = true;
                pointer_CM5->setStyleSheet("QLabel { background-color : green; color : white; }");
                this->close();
            }

            if(CMname == "Custom Model 6"){

                CM_List.append(CMname);
                //    large = false;
                CMisActive[6]=true;
                save6 = true;
                pointer_CM6->setStyleSheet("QLabel { background-color : green; color : white; }");
                this->close();
            }

            if(CMname == "Custom Model 7"){

                CM_List.append(CMname);
                //  large = false;
                CMisActive[7]=true;
                save7 = true;
                pointer_CM7->setStyleSheet("QLabel { background-color : green; color : white; }");
                this->close();
            }

            if(CMname == "Custom Model 8"){

                CM_List.append(CMname);
                //   large = false;
                CMisActive[8]=true;
                save8 = true;
                pointer_CM8->setStyleSheet("QLabel { background-color : green; color : white; }");
                this->close();
            }

            if(CMname == "Custom Model 9"){

                CM_List.append(CMname);
                //  large = false;
                CMisActive[9]=true;
                save9 = true;
                pointer_CM9->setStyleSheet("QLabel { background-color : green; color : white; }");
                this->close();
            }

            if(CMname == "Custom Model 10"){

                CMisActive[10]=true;
                //   large = false;
                CM_List.append(CMname);
                save10 = true;
                pointer_CM10->setStyleSheet("QLabel { background-color : green; color : white; }");
                this->close();
            }
        }

        //large
        if(large == true){

            if(CMname_large == "Custom Model 1"){

                CM_List.append(CMname_large);
                //  large = true;
                CMisActive[1]=true;
                pointer_CM1_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 2"){

                CM_List.append(CMname_large);
                // large = true;
                CMisActive[2]=true;;
                pointer_CM2_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 3"){

                CM_List.append(CMname_large);
                //    large = true;
                CMisActive[3]=true;
                pointer_CM3_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 4"){

                CM_List.append(CMname_large);
                //   large = true;
                CMisActive[4]=true;
                pointer_CM4_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 5"){

                CM_List.append(CMname_large);
                //   large = true;
                CMisActive[5]=true;
                pointer_CM5_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 6"){

                CM_List.append(CMname_large);
                //  large = true;
                CMisActive[6]=true;
                pointer_CM6_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 7"){

                CM_List.append(CMname_large);
                //   large = true;
                CMisActive[7]=true;
                pointer_CM7_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 8"){

                CM_List.append(CMname_large);
                //   large = true;
                CMisActive[8]=true;
                pointer_CM8_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 9"){

                CM_List.append(CMname_large);
                //   large = true;
                CMisActive[9]=true;
                pointer_CM9_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 10"){

                CM_List.append(CMname_large);
                //  large = true;
                CMisActive[10]=true;
                pointer_CM10_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
        }

        // saveColor();
        // saveParameters();
        addToList();


    }

    else{

        if(small == true){
            if(curPS[0] == CMname || curPS[1] == CMname || curPS[2] == CMname || curPS[3] == CMname || curPS[4] == CMname || curPS[5] == CMname || curPS[6] == CMname || curPS[7] == CMname || curPS[8] == CMname || curPS[9] == CMname){

                QMessageBox::information(this, "Warning", "Custom Model is set as current PS Behavior Mode!\nYou can't delete this!!!\nRemove Custom Model firstly.", 1);

                setParameters();
            }

            else{

                if(CMname == "Custom Model 1"){

                    pointer_CM1->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CM_List.removeOne(CMname);
                    CMisActive[1]=false;
                    save1 = false;
                    this->close();
                }

                if(CMname == "Custom Model 2"){
                    CM_List.removeOne(CMname);
                    pointer_CM2->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMisActive[2]=false;
                    save2 = false;
                    this->close();
                }

                if(CMname == "Custom Model 3"){
                    CM_List.removeOne(CMname);
                    CMisActive[3]=false;
                    pointer_CM3->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    save3 = false;
                    this->close();
                }

                if(CMname == "Custom Model 4"){
                    CM_List.removeOne(CMname);
                    pointer_CM4->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMisActive[4]=false;
                    save4 = false;
                    this->close();
                }

                if(CMname == "Custom Model 5"){
                    CM_List.removeOne(CMname);
                    pointer_CM5->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMisActive[5]=false;
                    save5 = false;
                    this->close();
                }

                if(CMname == "Custom Model 6"){
                    CM_List.removeOne(CMname);
                    pointer_CM6->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMisActive[6]=false;
                    save6 = false;
                    this->close();
                }

                if(CMname == "Custom Model 7"){
                    CM_List.removeOne(CMname);
                    pointer_CM7->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMisActive[7]=false;
                    save7 = false;
                    this->close();
                }

                if(CMname == "Custom Model 8"){
                    CM_List.removeOne(CMname);
                    pointer_CM8->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMisActive[8]=false;
                    save8 = false;
                    this->close();
                }

                if(CMname == "Custom Model 9"){
                    CM_List.removeOne(CMname);
                    pointer_CM9->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMisActive[9]=false;
                    save9 = false;
                    this->close();
                }

                if(CMname == "Custom Model 10"){
                    CMisActive[10]=false;
                    CM_List.removeOne(CMname);
                    pointer_CM10->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    save10 = false;
                    this->close();
                }
            }
        }
        //large
        if(large == true){

            if(curPS[0] == CMname_large || curPS[1] == CMname_large || curPS[2] == CMname_large || curPS[3] == CMname_large || curPS[4] == CMname_large || curPS[5] == CMname_large || curPS[6] == CMname_large || curPS[7] == CMname_large || curPS[8] == CMname_large || curPS[9] == CMname_large || curPS[11] == CMname_large || curPS[12] == CMname_large || curPS[13] == CMname_large || curPS[14] == CMname_large || curPS[15] == CMname_large || curPS[16] == CMname_large || curPS[17] == CMname_large || curPS[18] == CMname_large || curPS[19] == CMname_large || curPS[20] == CMname_large){

                QMessageBox::information(this, "Warning", "Custom Model is set as current PS Behavior Mode!\nYou can't delete this!!!\nRemove Custom Model firstly.", 1);

                setParameters();
            }
            else{

                if(CMname_large == "Custom Model 1"){

                    pointer_CM1_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CM_List.removeOne(CMname_large);
                    CMisActive[1]=false;
                    this->close();
                }

                if(CMname_large == "Custom Model 2"){
                    CM_List.removeOne(CMname_large);
                    pointer_CM2_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMisActive[2]=false;
                    this->close();
                }

                if(CMname_large == "Custom Model 3"){
                    CM_List.removeOne(CMname_large);
                    CMisActive[3]=false;
                    pointer_CM3_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    this->close();
                }

                if(CMname_large == "Custom Model 4"){
                    CM_List.removeOne(CMname_large);
                    pointer_CM4_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMisActive[4]=false;
                    this->close();
                }

                if(CMname_large == "Custom Model 5"){
                    CM_List.removeOne(CMname_large);
                    pointer_CM5_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMisActive[5]=false;
                    this->close();
                }

                if(CMname_large == "Custom Model 6"){
                    CM_List.removeOne(CMname_large);
                    pointer_CM6_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMisActive[6]=false;
                    this->close();
                }

                if(CMname_large == "Custom Model 7"){
                    CM_List.removeOne(CMname_large);
                    pointer_CM7_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMisActive[7]=false;
                    this->close();
                }

                if(CMname_large == "Custom Model 8"){
                    CM_List.removeOne(CMname_large);
                    pointer_CM8_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMisActive[8]=false;
                    this->close();
                }

                if(CMname_large == "Custom Model 9"){
                    CM_List.removeOne(CMname_large);
                    pointer_CM9_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMisActive[9]=false;
                    this->close();
                }

                if(CMname_large == "Custom Model 10"){
                    CMisActive[10]=false;
                    CM_List.removeOne(CMname_large);
                    pointer_CM10_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    this->close();
                }
            }
        }


        saveParameters();
        addToList();

    }



}

void Custommodels::on_bt_cancel_clicked()
{


    if(small == true){

        if(restoreClicked == true){
            this->close();
        }

        else{
            if(CMname == "Custom Model 1"){
                if(save1 == true){

                    CM_List.append(CMname);
                    CMisActive[1]=true;
                    setParameters();
                    this->close();

                }
                else{
                    startParameter();
                    this->close();

                }
            }

            if(CMname == "Custom Model 2"){

                if(save2 == true){

                    CM_List.append(CMname);
                    CMisActive[2]=true;;
                    setParameters();
                    this->close();

                }
                else{
                    startParameter();
                    this->close();

                }
            }

            if(CMname == "Custom Model 3"){

                if(save3 == true){

                    CM_List.append(CMname);
                    CMisActive[3]=true;
                    setParameters();
                    this->close();

                }
                else{
                    startParameter();
                    this->close();

                }
            }

            if(CMname == "Custom Model 4"){
                if(save4 == true){

                    CM_List.append(CMname);
                    CMisActive[4]=true;
                    setParameters();
                    this->close();


                }
                else{
                    startParameter();
                    this->close();

                }
            }

            if(CMname == "Custom Model 5"){

                if(save5 == true){

                    CM_List.append(CMname);
                    CMisActive[5]=true;
                    setParameters();
                    this->close();


                }
                else{
                    startParameter();
                    this->close();

                }
            }

            if(CMname == "Custom Model 6"){
                if(save6 == true){

                    CM_List.append(CMname);
                    CMisActive[6]=true;
                    setParameters();
                    this->close();


                }
                else{
                    startParameter();
                    this->close();

                }
            }

            if(CMname == "Custom Model 7"){
                if(save7 == true){

                    CM_List.append(CMname);
                    CMisActive[7]=true;
                    setParameters();
                    this->close();


                }
                else{
                    startParameter();
                    this->close();

                }
            }

            if(CMname == "Custom Model 8"){
                if(save8 == true){

                    CM_List.append(CMname);
                    CMisActive[8]=true;
                    setParameters();
                    this->close();


                }
                else{
                    startParameter();
                    this->close();

                }
            }

            if(CMname == "Custom Model 9"){
                if(save9 == true){

                    CM_List.append(CMname);
                    CMisActive[9]=true;
                    setParameters();
                    this->close();


                }
                else{
                    startParameter();
                    this->close();

                }
            }

            if(CMname == "Custom Model 10"){
                if(save10 ==  true){

                    CM_List.append(CMname);
                    CMisActive[10]=true;
                    setParameters();
                    this->close();

                }
                else{
                    startParameter();
                    this->close();

                }
            }
        }
    }




    //large

    if(large == true){
        if(CMname_large == "Custom Model 1"){
            if(pointer_CM1_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

                CM_List.append(CMname_large);
                CMisActive[1]=true;


            }
        }

        if(CMname_large == "Custom Model 2"){

            if(pointer_CM2_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

                CM_List.append(CMname_large);
                CMisActive[2]=true;;


            }
        }

        if(CMname_large == "Custom Model 3"){

            if(pointer_CM3_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

                CM_List.append(CMname_large);
                CMisActive[3]=true;


            }
        }

        if(CMname_large == "Custom Model 4"){
            if(pointer_CM4_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

                CM_List.append(CMname_large);
                CMisActive[4]=true;


            }
        }

        if(CMname_large == "Custom Model 5"){

            if(pointer_CM5_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

                CM_List.append(CMname_large);
                CMisActive[5]=true;


            }
        }

        if(CMname_large == "Custom Model 6"){
            if(pointer_CM6_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

                CM_List.append(CMname_large);
                CMisActive[6]=true;


            }
        }

        if(CMname_large == "Custom Model 7"){
            if(pointer_CM7_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

                CM_List.append(CMname_large);
                CMisActive[7]=true;


            }
        }

        if(CMname_large == "Custom Model 8"){
            if(pointer_CM8_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

                CM_List.append(CMname_large);
                CMisActive[8]=true;


            }
        }

        if(CMname_large == "Custom Model 9"){
            if(pointer_CM9_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

                CM_List.append(CMname_large);
                CMisActive[9]=true;


            }
        }

        if(CMname_large == "Custom Model 10"){
            if(pointer_CM10_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

                CM_List.append(CMname_large);
                CMisActive[10]=true;


            }
        }

    }
}

void Custommodels::on_bt_restore_clicked()
{
    restoreClicked = true;

    if(small == true){
        if(curPS[0] == CMname || curPS[1] == CMname || curPS[2] == CMname || curPS[3] == CMname || curPS[4] == CMname || curPS[5] == CMname || curPS[6] == CMname || curPS[7] == CMname || curPS[8] == CMname || curPS[9] == CMname)
        {
            QMessageBox::information(this, "Warning", "Custom Model is set as current PS Behavior Mode!\nYou can't delete this!!!\nRemove Custom Model firstly.", 1);
            setParameters();
        }
        else{
            startParameter();
            if(CMname == "Custom Model 1"){
                CM_List.removeOne(CMname);
                CMisActive[1]=false;
                pointer_CM1->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                readyListCM1.clear();
            }

            if(CMname == "Custom Model 2"){
                CM_List.removeOne(CMname);
                CMisActive[2]=false;
                pointer_CM2->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                readyListCM2.clear();
            }

            if(CMname == "Custom Model 3"){
                CM_List.removeOne(CMname);
                CMisActive[3]=false;
                pointer_CM3->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                readyListCM3.clear();
            }

            if(CMname == "Custom Model 4"){
                CM_List.removeOne(CMname);
                CMisActive[4]=false;
                pointer_CM4->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                readyListCM4.clear();
            }

            if(CMname == "Custom Model 5"){
                CM_List.removeOne(CMname);
                CMisActive[5]=false;
                pointer_CM5->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                readyListCM5.clear();
            }

            if(CMname == "Custom Model 6"){
                CM_List.removeOne(CMname);
                CMisActive[6]=false;
                pointer_CM6->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                readyListCM6.clear();
            }

            if(CMname == "Custom Model 7"){
                CM_List.removeOne(CMname);
                CMisActive[7]=false;
                pointer_CM7->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                readyListCM7.clear();
            }

            if(CMname == "Custom Model 8"){
                CM_List.removeOne(CMname);
                CMisActive[8]=false;
                pointer_CM8->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                readyListCM8.clear();
            }

            if(CMname == "Custom Model 9"){
                CM_List.removeOne(CMname);
                CMisActive[9]=false;
                pointer_CM9->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                readyListCM9.clear();
            }

            if(CMname == "Custom Model 10"){
                CM_List.removeOne(CMname);
                CMisActive[10]=false;
                pointer_CM10->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                readyListCM10.clear();
            }
        }
    }


    //large
    if(large == true){
        if(curPS[0] == CMname_large || curPS[1] == CMname_large || curPS[2] == CMname_large || curPS[3] == CMname_large || curPS[4] == CMname_large || curPS[5] == CMname_large || curPS[6] == CMname_large || curPS[7] == CMname_large || curPS[8] == CMname_large || curPS[9] == CMname_large || curPS[11] == CMname_large || curPS[12] == CMname_large || curPS[13] == CMname_large || curPS[14] == CMname_large || curPS[15] == CMname_large || curPS[16] == CMname_large || curPS[17] == CMname_large || curPS[18] == CMname_large || curPS[19] == CMname_large || curPS[20] == CMname_large)
        {
            QMessageBox::information(this, "Warning", "Custom Model is set as current PS Behavior Mode!\nYou can't delete this!!!\nRemove Custom Model firstly.", 1);
            setParameters();
        }
        else{
            ui->bt_add_Ping->setEnabled(false);
            ui->bt_add_Voip->setEnabled(false);
            ui->bt_add_FtpUl->setEnabled(false);
            ui->bt_add_FtpDl->setEnabled(false);
            ui->bt_add_StreamDI->setEnabled(false);
            ui->bt_add_StreamUI->setEnabled(false);
            ui->bt_SyncedPing->setEnabled(false);
            ui->bt_add_ServiceReq->setEnabled(false);
            ui->checkBox_add_FtpDl->setChecked(false);
            ui->checkBox_add_Voip->setChecked(false);
            ui->checkBox_add_Ftpul->setChecked(false);
            ui->checkBox_add_Ping->setChecked(false);
            ui->checkBox_add_StreamDI->setChecked(false);
            ui->checkBox_add_StreamUI->setChecked(false);
            ui->checkBox_add_ServiceReq->setChecked(false);
            ui->checkBox_add_SyncedPing->setChecked(false);

            if(CMname_large == "Custom Model 1"){
                CM_List.removeOne(CMname_large);
                CMisActive[1]=false;
                pointer_CM1_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            }

            if(CMname_large == "Custom Model 2"){
                CM_List.removeOne(CMname_large);
                CMisActive[2]=false;
                pointer_CM2_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            }

            if(CMname_large == "Custom Model 3"){
                CM_List.removeOne(CMname_large);
                CMisActive[3]=false;
                pointer_CM3_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            }

            if(CMname_large == "Custom Model 4"){
                CM_List.removeOne(CMname_large);
                CMisActive[4]=false;
                pointer_CM4_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            }

            if(CMname_large == "Custom Model 5"){
                CM_List.removeOne(CMname_large);
                CMisActive[5]=false;
                pointer_CM5_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            }

            if(CMname_large == "Custom Model 6"){
                CM_List.removeOne(CMname_large);
                CMisActive[6]=false;
                pointer_CM6_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            }

            if(CMname_large == "Custom Model 7"){
                CM_List.removeOne(CMname_large);
                CMisActive[7]=false;
                pointer_CM7_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            }

            if(CMname_large == "Custom Model 8"){
                CM_List.removeOne(CMname_large);
                CMisActive[8]=false;
                pointer_CM8_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            }

            if(CMname_large == "Custom Model 9"){
                CM_List.removeOne(CMname_large);
                CMisActive[9]=false;
                pointer_CM9_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            }

            if(CMname == "Custom Model 10"){
                CM_List.removeOne(CMname_large);
                CMisActive[10]=false;
                pointer_CM10_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            }
        }
    }
}

void Custommodels::saveParameters(){

    addFtpDLCheckbox = ui->checkBox_add_FtpDl->isChecked();
    addFtpUlCheckbox = ui->checkBox_add_Ftpul->isChecked();
    addPingCheckbox = ui->checkBox_add_Ping->isChecked();
    addServiceReqCheckbox = ui->checkBox_add_ServiceReq->isChecked();
    addStreamDlCheckbox = ui->checkBox_add_StreamDI->isChecked();
    addStreamUlCheckbox = ui->checkBox_add_StreamUI->isChecked();
    addSyncedPingCheckbox = ui->checkBox_add_SyncedPing->isChecked();
    addVoipCheckbox = ui->checkBox_add_Voip->isChecked();
}

void Custommodels::setParameters(){

    if(small == true){

        if(CMname =="Custom Model 1"){

            pointer_CM1->setStyleSheet(readyListCM1.at(2));

            ui->checkBox_add_FtpDl->setChecked(toBool(readyListCM1.at(4)));
            ui->checkBox_add_Ftpul->setChecked(toBool(readyListCM1.at(6)));
            ui->checkBox_add_ServiceReq->setChecked(toBool(readyListCM1.at(10)));
            ui->checkBox_add_Ping->setChecked(toBool(readyListCM1.at(8)));
            ui->checkBox_add_StreamDI->setChecked(toBool(readyListCM1.at(12)));
            ui->checkBox_add_StreamUI->setChecked(toBool(readyListCM1.at(14)));
            ui->checkBox_add_SyncedPing->setChecked(toBool(readyListCM1.at(16)));
            ui->checkBox_add_Voip->setChecked(toBool(readyListCM1.at(18)));

            ui->bt_add_FtpDl->setEnabled(toBool(readyListCM1.at(4)));
            ui->bt_add_FtpUl->setEnabled(toBool(readyListCM1.at(6)));
            ui->bt_add_ServiceReq->setEnabled(toBool(readyListCM1.at(10)));
            ui->bt_add_Ping->setEnabled(toBool(readyListCM1.at(8)));
            ui->bt_add_StreamDI->setEnabled(toBool(readyListCM1.at(12)));
            ui->bt_add_StreamUI->setEnabled(toBool(readyListCM1.at(14)));
            ui->bt_SyncedPing->setEnabled(toBool(readyListCM1.at(16)));
            ui->bt_add_Voip->setEnabled(toBool(readyListCM1.at(18)));


        }

        if(CMname == "Custom Model 2"){


            pointer_CM2->setStyleSheet(readyListCM2.at(2));

            ui->checkBox_add_FtpDl->setChecked(toBool(readyListCM2.at(4)));
            ui->checkBox_add_Ftpul->setChecked(toBool(readyListCM2.at(6)));
            ui->checkBox_add_ServiceReq->setChecked(toBool(readyListCM2.at(10)));
            ui->checkBox_add_Ping->setChecked(toBool(readyListCM2.at(8)));
            ui->checkBox_add_StreamDI->setChecked(toBool(readyListCM2.at(12)));
            ui->checkBox_add_StreamUI->setChecked(toBool(readyListCM2.at(14)));
            ui->checkBox_add_SyncedPing->setChecked(toBool(readyListCM2.at(16)));
            ui->checkBox_add_Voip->setChecked(toBool(readyListCM2.at(18)));

            ui->bt_add_FtpDl->setEnabled(toBool(readyListCM2.at(4)));
            ui->bt_add_FtpUl->setEnabled(toBool(readyListCM2.at(6)));
            ui->bt_add_ServiceReq->setEnabled(toBool(readyListCM2.at(10)));
            ui->bt_add_Ping->setEnabled(toBool(readyListCM2.at(8)));
            ui->bt_add_StreamDI->setEnabled(toBool(readyListCM2.at(12)));
            ui->bt_add_StreamUI->setEnabled(toBool(readyListCM2.at(14)));
            ui->bt_SyncedPing->setEnabled(toBool(readyListCM2.at(16)));
            ui->bt_add_Voip->setEnabled(toBool(readyListCM2.at(18)));


        }

        if(CMname == "Custom Model 3"){


            pointer_CM3->setStyleSheet(readyListCM3.at(2));

            ui->checkBox_add_FtpDl->setChecked(toBool(readyListCM3.at(4)));
            ui->checkBox_add_Ftpul->setChecked(toBool(readyListCM3.at(6)));
            ui->checkBox_add_ServiceReq->setChecked(toBool(readyListCM3.at(10)));
            ui->checkBox_add_Ping->setChecked(toBool(readyListCM3.at(8)));
            ui->checkBox_add_StreamDI->setChecked(toBool(readyListCM3.at(12)));
            ui->checkBox_add_StreamUI->setChecked(toBool(readyListCM3.at(14)));
            ui->checkBox_add_SyncedPing->setChecked(toBool(readyListCM3.at(16)));
            ui->checkBox_add_Voip->setChecked(toBool(readyListCM3.at(18)));

            ui->bt_add_FtpDl->setEnabled(toBool(readyListCM3.at(4)));
            ui->bt_add_FtpUl->setEnabled(toBool(readyListCM3.at(6)));
            ui->bt_add_ServiceReq->setEnabled(toBool(readyListCM3.at(10)));
            ui->bt_add_Ping->setEnabled(toBool(readyListCM3.at(8)));
            ui->bt_add_StreamDI->setEnabled(toBool(readyListCM3.at(12)));
            ui->bt_add_StreamUI->setEnabled(toBool(readyListCM3.at(14)));
            ui->bt_SyncedPing->setEnabled(toBool(readyListCM3.at(16)));
            ui->bt_add_Voip->setEnabled(toBool(readyListCM3.at(18)));

        }

        if(CMname == "Custom Model 4"){

            pointer_CM4->setStyleSheet(readyListCM4.at(2));

            ui->checkBox_add_FtpDl->setChecked(toBool(readyListCM4.at(4)));
            ui->checkBox_add_Ftpul->setChecked(toBool(readyListCM4.at(6)));
            ui->checkBox_add_ServiceReq->setChecked(toBool(readyListCM4.at(10)));
            ui->checkBox_add_Ping->setChecked(toBool(readyListCM4.at(8)));
            ui->checkBox_add_StreamDI->setChecked(toBool(readyListCM4.at(12)));
            ui->checkBox_add_StreamUI->setChecked(toBool(readyListCM4.at(14)));
            ui->checkBox_add_SyncedPing->setChecked(toBool(readyListCM4.at(16)));
            ui->checkBox_add_Voip->setChecked(toBool(readyListCM4.at(18)));

            ui->bt_add_FtpDl->setEnabled(toBool(readyListCM4.at(4)));
            ui->bt_add_FtpUl->setEnabled(toBool(readyListCM4.at(6)));
            ui->bt_add_ServiceReq->setEnabled(toBool(readyListCM4.at(10)));
            ui->bt_add_Ping->setEnabled(toBool(readyListCM4.at(8)));
            ui->bt_add_StreamDI->setEnabled(toBool(readyListCM4.at(12)));
            ui->bt_add_StreamUI->setEnabled(toBool(readyListCM4.at(14)));
            ui->bt_SyncedPing->setEnabled(toBool(readyListCM4.at(16)));
            ui->bt_add_Voip->setEnabled(toBool(readyListCM4.at(18)));

        }
        if(CMname == "Custom Model 5"){

            pointer_CM5->setStyleSheet(readyListCM5.at(2));

            ui->checkBox_add_FtpDl->setChecked(toBool(readyListCM5.at(4)));
            ui->checkBox_add_Ftpul->setChecked(toBool(readyListCM5.at(6)));
            ui->checkBox_add_ServiceReq->setChecked(toBool(readyListCM5.at(10)));
            ui->checkBox_add_Ping->setChecked(toBool(readyListCM5.at(8)));
            ui->checkBox_add_StreamDI->setChecked(toBool(readyListCM5.at(12)));
            ui->checkBox_add_StreamUI->setChecked(toBool(readyListCM5.at(14)));
            ui->checkBox_add_SyncedPing->setChecked(toBool(readyListCM5.at(16)));
            ui->checkBox_add_Voip->setChecked(toBool(readyListCM5.at(18)));

            ui->bt_add_FtpDl->setEnabled(toBool(readyListCM5.at(4)));
            ui->bt_add_FtpUl->setEnabled(toBool(readyListCM5.at(6)));
            ui->bt_add_ServiceReq->setEnabled(toBool(readyListCM5.at(10)));
            ui->bt_add_Ping->setEnabled(toBool(readyListCM5.at(8)));
            ui->bt_add_StreamDI->setEnabled(toBool(readyListCM5.at(12)));
            ui->bt_add_StreamUI->setEnabled(toBool(readyListCM5.at(14)));
            ui->bt_SyncedPing->setEnabled(toBool(readyListCM5.at(16)));
            ui->bt_add_Voip->setEnabled(toBool(readyListCM5.at(18)));
        }
        if(CMname == "Custom Model 6"){

            pointer_CM6->setStyleSheet(readyListCM6.at(2));

            ui->checkBox_add_FtpDl->setChecked(toBool(readyListCM6.at(4)));
            ui->checkBox_add_Ftpul->setChecked(toBool(readyListCM6.at(6)));
            ui->checkBox_add_ServiceReq->setChecked(toBool(readyListCM6.at(10)));
            ui->checkBox_add_Ping->setChecked(toBool(readyListCM6.at(8)));
            ui->checkBox_add_StreamDI->setChecked(toBool(readyListCM6.at(12)));
            ui->checkBox_add_StreamUI->setChecked(toBool(readyListCM6.at(14)));
            ui->checkBox_add_SyncedPing->setChecked(toBool(readyListCM6.at(16)));
            ui->checkBox_add_Voip->setChecked(toBool(readyListCM6.at(18)));

            ui->bt_add_FtpDl->setEnabled(toBool(readyListCM6.at(4)));
            ui->bt_add_FtpUl->setEnabled(toBool(readyListCM6.at(6)));
            ui->bt_add_ServiceReq->setEnabled(toBool(readyListCM6.at(10)));
            ui->bt_add_Ping->setEnabled(toBool(readyListCM6.at(8)));
            ui->bt_add_StreamDI->setEnabled(toBool(readyListCM6.at(12)));
            ui->bt_add_StreamUI->setEnabled(toBool(readyListCM6.at(14)));
            ui->bt_SyncedPing->setEnabled(toBool(readyListCM6.at(16)));
            ui->bt_add_Voip->setEnabled(toBool(readyListCM6.at(18)));
        }
        if(CMname == "Custom Model 7"){

            pointer_CM7->setStyleSheet(readyListCM7.at(2));

            ui->checkBox_add_FtpDl->setChecked(toBool(readyListCM7.at(4)));
            ui->checkBox_add_Ftpul->setChecked(toBool(readyListCM7.at(6)));
            ui->checkBox_add_ServiceReq->setChecked(toBool(readyListCM7.at(10)));
            ui->checkBox_add_Ping->setChecked(toBool(readyListCM7.at(8)));
            ui->checkBox_add_StreamDI->setChecked(toBool(readyListCM7.at(12)));
            ui->checkBox_add_StreamUI->setChecked(toBool(readyListCM7.at(14)));
            ui->checkBox_add_SyncedPing->setChecked(toBool(readyListCM7.at(16)));
            ui->checkBox_add_Voip->setChecked(toBool(readyListCM7.at(18)));

            ui->bt_add_FtpDl->setEnabled(toBool(readyListCM7.at(4)));
            ui->bt_add_FtpUl->setEnabled(toBool(readyListCM7.at(6)));
            ui->bt_add_ServiceReq->setEnabled(toBool(readyListCM7.at(10)));
            ui->bt_add_Ping->setEnabled(toBool(readyListCM7.at(8)));
            ui->bt_add_StreamDI->setEnabled(toBool(readyListCM7.at(12)));
            ui->bt_add_StreamUI->setEnabled(toBool(readyListCM7.at(14)));
            ui->bt_SyncedPing->setEnabled(toBool(readyListCM7.at(16)));
            ui->bt_add_Voip->setEnabled(toBool(readyListCM7.at(18)));

        }
        if(CMname == "Custom Model 8"){

            pointer_CM8->setStyleSheet(readyListCM8.at(2));

            ui->checkBox_add_FtpDl->setChecked(toBool(readyListCM8.at(4)));
            ui->checkBox_add_Ftpul->setChecked(toBool(readyListCM8.at(6)));
            ui->checkBox_add_ServiceReq->setChecked(toBool(readyListCM8.at(10)));
            ui->checkBox_add_Ping->setChecked(toBool(readyListCM8.at(8)));
            ui->checkBox_add_StreamDI->setChecked(toBool(readyListCM8.at(12)));
            ui->checkBox_add_StreamUI->setChecked(toBool(readyListCM8.at(14)));
            ui->checkBox_add_SyncedPing->setChecked(toBool(readyListCM8.at(16)));
            ui->checkBox_add_Voip->setChecked(toBool(readyListCM8.at(18)));

            ui->bt_add_FtpDl->setEnabled(toBool(readyListCM8.at(4)));
            ui->bt_add_FtpUl->setEnabled(toBool(readyListCM8.at(6)));
            ui->bt_add_ServiceReq->setEnabled(toBool(readyListCM8.at(10)));
            ui->bt_add_Ping->setEnabled(toBool(readyListCM8.at(8)));
            ui->bt_add_StreamDI->setEnabled(toBool(readyListCM8.at(12)));
            ui->bt_add_StreamUI->setEnabled(toBool(readyListCM8.at(14)));
            ui->bt_SyncedPing->setEnabled(toBool(readyListCM8.at(16)));
            ui->bt_add_Voip->setEnabled(toBool(readyListCM8.at(18)));

        }
        if(CMname == "Custom Model 9"){

            pointer_CM9->setStyleSheet(readyListCM9.at(2));

            ui->checkBox_add_FtpDl->setChecked(toBool(readyListCM9.at(4)));
            ui->checkBox_add_Ftpul->setChecked(toBool(readyListCM9.at(6)));
            ui->checkBox_add_ServiceReq->setChecked(toBool(readyListCM9.at(10)));
            ui->checkBox_add_Ping->setChecked(toBool(readyListCM9.at(8)));
            ui->checkBox_add_StreamDI->setChecked(toBool(readyListCM9.at(12)));
            ui->checkBox_add_StreamUI->setChecked(toBool(readyListCM9.at(14)));
            ui->checkBox_add_SyncedPing->setChecked(toBool(readyListCM9.at(16)));
            ui->checkBox_add_Voip->setChecked(toBool(readyListCM9.at(18)));

            ui->bt_add_FtpDl->setEnabled(toBool(readyListCM9.at(4)));
            ui->bt_add_FtpUl->setEnabled(toBool(readyListCM9.at(6)));
            ui->bt_add_ServiceReq->setEnabled(toBool(readyListCM9.at(10)));
            ui->bt_add_Ping->setEnabled(toBool(readyListCM9.at(8)));
            ui->bt_add_StreamDI->setEnabled(toBool(readyListCM9.at(12)));
            ui->bt_add_StreamUI->setEnabled(toBool(readyListCM9.at(14)));
            ui->bt_SyncedPing->setEnabled(toBool(readyListCM9.at(16)));
            ui->bt_add_Voip->setEnabled(toBool(readyListCM9.at(18)));

        }
        if(CMname == "Custom Model 10"){

            pointer_CM10->setStyleSheet(readyListCM10.at(2));

            ui->checkBox_add_FtpDl->setChecked(toBool(readyListCM10.at(4)));
            ui->checkBox_add_Ftpul->setChecked(toBool(readyListCM10.at(6)));
            ui->checkBox_add_ServiceReq->setChecked(toBool(readyListCM10.at(10)));
            ui->checkBox_add_Ping->setChecked(toBool(readyListCM10.at(8)));
            ui->checkBox_add_StreamDI->setChecked(toBool(readyListCM10.at(12)));
            ui->checkBox_add_StreamUI->setChecked(toBool(readyListCM10.at(14)));
            ui->checkBox_add_SyncedPing->setChecked(toBool(readyListCM10.at(16)));
            ui->checkBox_add_Voip->setChecked(toBool(readyListCM10.at(18)));

            ui->bt_add_FtpDl->setEnabled(toBool(readyListCM10.at(4)));
            ui->bt_add_FtpUl->setEnabled(toBool(readyListCM10.at(6)));
            ui->bt_add_ServiceReq->setEnabled(toBool(readyListCM10.at(10)));
            ui->bt_add_Ping->setEnabled(toBool(readyListCM10.at(8)));
            ui->bt_add_StreamDI->setEnabled(toBool(readyListCM10.at(12)));
            ui->bt_add_StreamUI->setEnabled(toBool(readyListCM10.at(14)));
            ui->bt_SyncedPing->setEnabled(toBool(readyListCM10.at(16)));
            ui->bt_add_Voip->setEnabled(toBool(readyListCM10.at(18)));
        }
    }
}

void Custommodels::addToList(){

    QString textAddFtpDlCheckbox = QString::number(ui->checkBox_add_FtpDl->isChecked());
    QString textAddFtpUlCheckbox = QString::number(ui->checkBox_add_Ftpul->isChecked());
    QString textAddServiceReqCheckbox = QString::number(ui->checkBox_add_ServiceReq->isChecked());
    QString textAddPingCheckbox = QString::number(ui->checkBox_add_Ping->isChecked());
    QString textAddStreamDlCheckbox = QString::number(ui->checkBox_add_StreamDI->isChecked());
    QString textAddStreamUlCheckbox = QString::number(ui->checkBox_add_StreamUI->isChecked());
    QString textAddSyncedPingCheckbox = QString::number(ui->checkBox_add_SyncedPing->isChecked());
    QString textAddVoipCheckbox = QString::number(ui->checkBox_add_Voip->isChecked());



    if(small == true){
        if(CMname == "Custom Model 1"){
            CM1_List.clear();
            CM1_List.append(CMname);
            CM1_List.append("StyleSheet:");
            CM1_List.append(pointer_CM1->styleSheet());
            CM1_List.append("FtpDlCheckBox:");
            CM1_List.append(textAddFtpDlCheckbox);
            CM1_List.append("FtpUlCheckBox:");
            CM1_List.append(textAddFtpUlCheckbox);
            CM1_List.append("AddPingCheckBox:");
            CM1_List.append(textAddPingCheckbox);
            CM1_List.append("AddServiceReqCheckBox:");
            CM1_List.append(textAddServiceReqCheckbox);
            CM1_List.append("AddStreamDlCheckBox:");
            CM1_List.append(textAddStreamDlCheckbox);
            CM1_List.append("AddStreamUlCheckBox:");
            CM1_List.append(textAddStreamUlCheckbox);
            CM1_List.append("AddSyncedPindCheckBox:");
            CM1_List.append(textAddSyncedPingCheckbox);
            CM1_List.append("AddVoipCheckBox:");
            CM1_List.append(textAddVoipCheckbox);
            CM1_List.append(PingList);
            CM1_List.append(VoipList);
            CM1_List.append(SyncedPingList);
            CM1_List.append(ServiceReqList);
            CM1_List.append(FtpDlList);
            CM1_List.append(FtpUlList);
            CM1_List.append(StreamDlList);
            CM1_List.append(StreamUlList);

            if(readyListCM1 != CM1_List){
                readyListCM1.clear();
                readyListCM1.append(CM1_List);
            }

        }
        if(CMname == "Custom Model 2"){
            CM2_List.clear();
            CM2_List.append(CMname);
            CM2_List.append("StyleSheet:");
            CM2_List.append(pointer_CM2->styleSheet());
            CM2_List.append("FtpDlCheckBox:");
            CM2_List.append(textAddFtpDlCheckbox);
            CM2_List.append("FtpUlCheckBox:");
            CM2_List.append(textAddFtpUlCheckbox);
            CM2_List.append("AddPingCheckBox:");
            CM2_List.append(textAddPingCheckbox);
            CM2_List.append("AddServiceReqCheckBox:");
            CM2_List.append(textAddServiceReqCheckbox);
            CM2_List.append("AddStreamDlCheckBox:");
            CM2_List.append(textAddStreamDlCheckbox);
            CM2_List.append("AddStreamUlCheckBox:");
            CM2_List.append(textAddStreamUlCheckbox);
            CM2_List.append("AddSyncedPindCheckBox:");
            CM2_List.append(textAddSyncedPingCheckbox);
            CM2_List.append("AddVoipCheckBox:");
            CM2_List.append(textAddVoipCheckbox);
            CM2_List.append(PingList);
            CM2_List.append(VoipList);
            CM2_List.append(SyncedPingList);
            CM2_List.append(ServiceReqList);
            CM2_List.append(FtpDlList);
            CM2_List.append(FtpUlList);
            CM2_List.append(StreamDlList);
            CM2_List.append(StreamUlList);


            if(CM2_List != readyListCM2){
                readyListCM2.clear();
                readyListCM2.append(CM2_List);
            }
        }
        if(CMname == "Custom Model 3"){

            CM3_List.clear();
            CM3_List.append(CMname);
            CM3_List.append("StyleSheet:");
            CM3_List.append(pointer_CM3->styleSheet());
            CM3_List.append("FtpDlCheckBox:");
            CM3_List.append(textAddFtpDlCheckbox);
            CM3_List.append("FtpUlCheckBox:");
            CM3_List.append(textAddFtpUlCheckbox);
            CM3_List.append("AddPingCheckBox:");
            CM3_List.append(textAddPingCheckbox);
            CM3_List.append("AddServiceReqCheckBox:");
            CM3_List.append(textAddServiceReqCheckbox);
            CM3_List.append("AddStreamDlCheckBox:");
            CM3_List.append(textAddStreamDlCheckbox);
            CM3_List.append("AddStreamUlCheckBox:");
            CM3_List.append(textAddStreamUlCheckbox);
            CM3_List.append("AddSyncedPindCheckBox:");
            CM3_List.append(textAddSyncedPingCheckbox);
            CM3_List.append("AddVoipCheckBox:");
            CM3_List.append(textAddVoipCheckbox);
            CM3_List.append(PingList);
            CM3_List.append(VoipList);
            CM3_List.append(SyncedPingList);
            CM3_List.append(ServiceReqList);
            CM3_List.append(FtpDlList);
            CM3_List.append(FtpUlList);
            CM3_List.append(StreamDlList);
            CM3_List.append(StreamUlList);


            if(CM3_List != readyListCM3){
                readyListCM3.clear();
                readyListCM3.append(CM3_List);
            }
        }

        if(CMname == "Custom Model 4"){
            CM4_List.clear();
            CM4_List.append(CMname);
            CM4_List.append("StyleSheet:");
            CM4_List.append(pointer_CM4->styleSheet());
            CM4_List.append("FtpDlCheckBox:");
            CM4_List.append(textAddFtpDlCheckbox);
            CM4_List.append("FtpUlCheckBox:");
            CM4_List.append(textAddFtpUlCheckbox);
            CM4_List.append("AddPingCheckBox:");
            CM4_List.append(textAddPingCheckbox);
            CM4_List.append("AddServiceReqCheckBox:");
            CM4_List.append(textAddServiceReqCheckbox);
            CM4_List.append("AddStreamDlCheckBox:");
            CM4_List.append(textAddStreamDlCheckbox);
            CM4_List.append("AddStreamUlCheckBox:");
            CM4_List.append(textAddStreamUlCheckbox);
            CM4_List.append("AddSyncedPindCheckBox:");
            CM4_List.append(textAddSyncedPingCheckbox);
            CM4_List.append("AddVoipCheckBox:");
            CM4_List.append(textAddVoipCheckbox);
            CM4_List.append(PingList);
            CM4_List.append(VoipList);
            CM4_List.append(SyncedPingList);
            CM4_List.append(ServiceReqList);
            CM4_List.append(FtpDlList);
            CM4_List.append(FtpUlList);
            CM4_List.append(StreamDlList);
            CM4_List.append(StreamUlList);


            if(CM4_List != readyListCM4){
                readyListCM4.clear();
                readyListCM4.append(CM4_List);
            }
        }
        if(CMname == "Custom Model 5"){
            CM5_List.clear();
            CM5_List.append(CMname);
            CM5_List.append("StyleSheet:");
            CM5_List.append(pointer_CM5->styleSheet());
            CM5_List.append("FtpDlCheckBox:");
            CM5_List.append(textAddFtpDlCheckbox);
            CM5_List.append("FtpUlCheckBox:");
            CM5_List.append(textAddFtpUlCheckbox);
            CM5_List.append("AddPingCheckBox:");
            CM5_List.append(textAddPingCheckbox);
            CM5_List.append("AddServiceReqCheckBox:");
            CM5_List.append(textAddServiceReqCheckbox);
            CM5_List.append("AddStreamDlCheckBox:");
            CM5_List.append(textAddStreamDlCheckbox);
            CM5_List.append("AddStreamUlCheckBox:");
            CM5_List.append(textAddStreamUlCheckbox);
            CM5_List.append("AddSyncedPindCheckBox:");
            CM5_List.append(textAddSyncedPingCheckbox);
            CM5_List.append("AddVoipCheckBox:");
            CM5_List.append(textAddVoipCheckbox);
            CM5_List.append(PingList);
            CM5_List.append(VoipList);
            CM5_List.append(SyncedPingList);
            CM5_List.append(ServiceReqList);
            CM5_List.append(FtpDlList);
            CM5_List.append(FtpUlList);
            CM5_List.append(StreamDlList);
            CM5_List.append(StreamUlList);


            if(CM5_List != readyListCM5){
                readyListCM5.clear();
                readyListCM5.append(CM5_List);
            }

        }
        if(CMname == "Custom Model 6"){
            CM6_List.clear();
            CM6_List.append(CMname);
            CM6_List.append("StyleSheet:");
            CM6_List.append(pointer_CM6->styleSheet());
            CM6_List.append("FtpDlCheckBox:");
            CM6_List.append(textAddFtpDlCheckbox);
            CM6_List.append("FtpUlCheckBox:");
            CM6_List.append(textAddFtpUlCheckbox);
            CM6_List.append("AddPingCheckBox:");
            CM6_List.append(textAddPingCheckbox);
            CM6_List.append("AddServiceReqCheckBox:");
            CM6_List.append(textAddServiceReqCheckbox);
            CM6_List.append("AddStreamDlCheckBox:");
            CM6_List.append(textAddStreamDlCheckbox);
            CM6_List.append("AddStreamUlCheckBox:");
            CM6_List.append(textAddStreamUlCheckbox);
            CM6_List.append("AddSyncedPindCheckBox:");
            CM6_List.append(textAddSyncedPingCheckbox);
            CM6_List.append("AddVoipCheckBox:");
            CM6_List.append(textAddVoipCheckbox);
            CM6_List.append(PingList);
            CM6_List.append(VoipList);
            CM6_List.append(SyncedPingList);
            CM6_List.append(ServiceReqList);
            CM6_List.append(FtpDlList);
            CM6_List.append(FtpUlList);
            CM6_List.append(StreamDlList);
            CM6_List.append(StreamUlList);


            if(CM6_List != readyListCM6){
                readyListCM6.clear();
                readyListCM6.append(CM6_List);
            }
        }
        if(CMname == "Custom Model 7"){
            CM7_List.clear();
            CM7_List.append(CMname);
            CM7_List.append("StyleSheet:");
            CM7_List.append(pointer_CM7->styleSheet());
            CM7_List.append("FtpDlCheckBox:");
            CM7_List.append(textAddFtpDlCheckbox);
            CM7_List.append("FtpUlCheckBox:");
            CM7_List.append(textAddFtpUlCheckbox);
            CM7_List.append("AddPingCheckBox:");
            CM7_List.append(textAddPingCheckbox);
            CM7_List.append("AddServiceReqCheckBox:");
            CM7_List.append(textAddServiceReqCheckbox);
            CM7_List.append("AddStreamDlCheckBox:");
            CM7_List.append(textAddStreamDlCheckbox);
            CM7_List.append("AddStreamUlCheckBox:");
            CM7_List.append(textAddStreamUlCheckbox);
            CM7_List.append("AddSyncedPindCheckBox:");
            CM7_List.append(textAddSyncedPingCheckbox);
            CM7_List.append("AddVoipCheckBox:");
            CM7_List.append(textAddVoipCheckbox);
            CM7_List.append(PingList);
            CM7_List.append(VoipList);
            CM7_List.append(SyncedPingList);
            CM7_List.append(ServiceReqList);
            CM7_List.append(FtpDlList);
            CM7_List.append(FtpUlList);
            CM7_List.append(StreamDlList);
            CM7_List.append(StreamUlList);


            if(CM7_List != readyListCM7){
                readyListCM7.clear();
                readyListCM7.append(CM7_List);
            }
        }
        if(CMname == "Custom Model 8"){
            CM8_List.clear();
            CM8_List.append(CMname);
            CM8_List.append("StyleSheet:");
            CM8_List.append(pointer_CM8->styleSheet());
            CM8_List.append("FtpDlCheckBox:");
            CM8_List.append(textAddFtpDlCheckbox);
            CM8_List.append("FtpUlCheckBox:");
            CM8_List.append(textAddFtpUlCheckbox);
            CM8_List.append("AddPingCheckBox:");
            CM8_List.append(textAddPingCheckbox);
            CM8_List.append("AddServiceReqCheckBox:");
            CM8_List.append(textAddServiceReqCheckbox);
            CM8_List.append("AddStreamDlCheckBox:");
            CM8_List.append(textAddStreamDlCheckbox);
            CM8_List.append("AddStreamUlCheckBox:");
            CM8_List.append(textAddStreamUlCheckbox);
            CM8_List.append("AddSyncedPindCheckBox:");
            CM8_List.append(textAddSyncedPingCheckbox);
            CM8_List.append("AddVoipCheckBox:");
            CM8_List.append(textAddVoipCheckbox);
            CM8_List.append(PingList);
            CM8_List.append(VoipList);
            CM8_List.append(SyncedPingList);
            CM8_List.append(ServiceReqList);
            CM8_List.append(FtpDlList);
            CM8_List.append(FtpUlList);
            CM8_List.append(StreamDlList);
            CM8_List.append(StreamUlList);


            if(CM8_List != readyListCM8){
                readyListCM8.clear();
                readyListCM8.append(CM8_List);
            }
        }
        if(CMname == "Custom Model 9"){
            CM9_List.clear();
            CM9_List.append(CMname);
            CM9_List.append("StyleSheet:");
            CM9_List.append(pointer_CM9->styleSheet());
            CM9_List.append("FtpDlCheckBox:");
            CM9_List.append(textAddFtpDlCheckbox);
            CM9_List.append("FtpUlCheckBox:");
            CM9_List.append(textAddFtpUlCheckbox);
            CM9_List.append("AddPingCheckBox:");
            CM9_List.append(textAddPingCheckbox);
            CM9_List.append("AddServiceReqCheckBox:");
            CM9_List.append(textAddServiceReqCheckbox);
            CM9_List.append("AddStreamDlCheckBox:");
            CM9_List.append(textAddStreamDlCheckbox);
            CM9_List.append("AddStreamUlCheckBox:");
            CM9_List.append(textAddStreamUlCheckbox);
            CM9_List.append("AddSyncedPindCheckBox:");
            CM9_List.append(textAddSyncedPingCheckbox);
            CM9_List.append("AddVoipCheckBox:");
            CM9_List.append(textAddVoipCheckbox);
            CM9_List.append(PingList);
            CM9_List.append(VoipList);
            CM9_List.append(SyncedPingList);
            CM9_List.append(ServiceReqList);
            CM9_List.append(FtpDlList);
            CM9_List.append(FtpUlList);
            CM9_List.append(StreamDlList);
            CM9_List.append(StreamUlList);


            if(CM9_List != readyListCM9){
                readyListCM9.clear();
                readyListCM9.append(CM9_List);
            }
        }

        if(CMname == "Custom Model 10"){
            CM10_List.clear();
            CM10_List.append(CMname);
            CM10_List.append("StyleSheet:");
            CM10_List.append(pointer_CM10->styleSheet());
            CM10_List.append("FtpDlCheckBox:");
            CM10_List.append(textAddFtpDlCheckbox);
            CM10_List.append("FtpUlCheckBox:");
            CM10_List.append(textAddFtpUlCheckbox);
            CM10_List.append("AddPingCheckBox:");
            CM10_List.append(textAddPingCheckbox);
            CM10_List.append("AddServiceReqCheckBox:");
            CM10_List.append(textAddServiceReqCheckbox);
            CM10_List.append("AddStreamDlCheckBox:");
            CM10_List.append(textAddStreamDlCheckbox);
            CM10_List.append("AddStreamUlCheckBox:");
            CM10_List.append(textAddStreamUlCheckbox);
            CM10_List.append("AddSyncedPindCheckBox:");
            CM10_List.append(textAddSyncedPingCheckbox);
            CM10_List.append("AddVoipCheckBox:");
            CM10_List.append(textAddVoipCheckbox);
            CM10_List.append(PingList);
            CM10_List.append(VoipList);
            CM10_List.append(SyncedPingList);
            CM10_List.append(ServiceReqList);
            CM10_List.append(FtpDlList);
            CM10_List.append(FtpUlList);
            CM10_List.append(StreamDlList);
            CM10_List.append(StreamUlList);


            if(CM10_List != readyListCM10){
                readyListCM10.clear();
                readyListCM10.append(CM10_List);
            }
        }

        customModelList.clear();
        customModelList.append(readyListCM1);
        customModelList.append(readyListCM2);
        customModelList.append(readyListCM3);
        customModelList.append(readyListCM4);
        customModelList.append(readyListCM5);
        customModelList.append(readyListCM6);
        customModelList.append(readyListCM7);
        customModelList.append(readyListCM8);
        customModelList.append(readyListCM9);
        customModelList.append(readyListCM10);

    }
}

bool Custommodels::toBool(QString value){
    return value == QString("1");
}

void Custommodels::startParameter(){

    ui->bt_add_Ping->setEnabled(false);
    ui->bt_add_Voip->setEnabled(false);
    ui->bt_add_FtpUl->setEnabled(false);
    ui->bt_add_FtpDl->setEnabled(false);
    ui->bt_add_StreamDI->setEnabled(false);
    ui->bt_add_StreamUI->setEnabled(false);
    ui->bt_SyncedPing->setEnabled(false);
    ui->bt_add_ServiceReq->setEnabled(false);
    ui->checkBox_add_FtpDl->setChecked(false);
    ui->checkBox_add_Voip->setChecked(false);
    ui->checkBox_add_Ftpul->setChecked(false);
    ui->checkBox_add_Ping->setChecked(false);
    ui->checkBox_add_StreamDI->setChecked(false);
    ui->checkBox_add_StreamUI->setChecked(false);
    ui->checkBox_add_ServiceReq->setChecked(false);
    ui->checkBox_add_SyncedPing->setChecked(false);
}
