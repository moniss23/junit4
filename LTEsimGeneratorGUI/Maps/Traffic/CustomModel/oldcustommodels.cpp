#include "oldcustommodels.h"
#include "ui_custommodels.h"
#include <QMessageBox>
#include <QSettings>
#include <Maps/Traffic/map_traffic.h>

extern my_qlabel *pointerCM[10];

extern QString CMname;

extern QString curPS[20];

bool isCMActive[9];

QStringList CMList;

bool addFtpDLCheckbox;
bool addFtpUlCheckbox;
bool addPingCheckbox;
bool addServiceReqCheckbox;
bool addStreamDlCheckbox;
bool addStreamUlCheckbox;
bool addSyncedPingCheckbox;
bool addVoipCheckbox;

extern bool small;

QStringList customModelList;
QStringList readyCMList[10];

extern QList<QString> PingList;
extern QList<QString> VoipList;
extern QList<QString> SyncedPingList;
extern QList<QString> StreamUlList;
extern QList<QString> StreamDlList;
extern QList<QString> ServiceReqList;
extern QList<QString> FtpUlList;
extern QList<QString> FtpDlList;

bool isSaved[10];
bool restoreClicked;


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

    std::fill(isCMActive, isCMActive + 9, false);
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

        for(unsigned i=0;i<10;i++)
            if(CMname == (QString("Custom Model ") + QString::number(i+1))){
                CMList.append(CMname);
                isCMActive[i]=true;
                isSaved[i] = true;
                pointerCM[i]->setStyleSheet("QLabel { background-color : green; color : white; }");
                this->close();
            }
        addToList();
    }else{
        if(curPS[0] == CMname || curPS[1] == CMname || curPS[2] == CMname || curPS[3] == CMname || curPS[4] == CMname || curPS[5] == CMname || curPS[6] == CMname || curPS[7] == CMname || curPS[8] == CMname || curPS[9] == CMname){

            QMessageBox::information(this, "Warning", "Custom Model is set as current PS Behavior Mode!\nYou can't delete this!!!\nRemove Custom Model firstly.", 1);
            setParameters();
        }else{
            for(unsigned i=0;i<10;i++)
                if(CMname == (QString("Custom Model ") + QString::number(i+1))){
                    pointerCM[i]->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                    CMList.removeOne(CMname);
                    isCMActive[i]=false;
                    isSaved[i] = false;
                    this->close();
                }
        }
        saveParameters();
        addToList();
    }
}


void Custommodels::on_bt_cancel_clicked(){
    if(restoreClicked == true){
        this->close();
    }else{
        for(unsigned i=0;i<10;i++)
            if(CMname == (QString("Custom Model ") + QString::number(i+1))){
                if(isSaved[i] == true){
                    CMList.append(CMname);
                    isCMActive[i]=true;
                }
                setParameters();
                this->close();
            }
    }
}


void Custommodels::on_bt_restore_clicked()
{
    restoreClicked = true;
    if(curPS[0] == CMname || curPS[1] == CMname || curPS[2] == CMname || curPS[3] == CMname || curPS[4] == CMname || curPS[5] == CMname || curPS[6] == CMname || curPS[7] == CMname || curPS[8] == CMname || curPS[9] == CMname)
    {
        QMessageBox::information(this, "Warning", "Custom Model is set as current PS Behavior Mode!\nYou can't delete this!!!\nRemove Custom Model firstly.", 1);
        setParameters();
    }else{
        startParameter();
        for(unsigned i=0;i<10;i++)
            if(CMname == (QString("Custom Model ") + QString::number(i+1))){
                CMList.removeOne(CMname);
                isCMActive[i]=false;
                pointerCM[i]->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
                readyCMList[0].clear();
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
    for(unsigned i=0;i<10;i++)
        if(CMname == (QString("Custom Model ") + QString::number(i+1))){

            pointerCM[i]->setStyleSheet(readyCMList[i].at(2));

            ui->checkBox_add_FtpDl->setChecked(toBool(readyCMList[i].at(4)));
            ui->checkBox_add_Ftpul->setChecked(toBool(readyCMList[i].at(6)));
            ui->checkBox_add_ServiceReq->setChecked(toBool(readyCMList[i].at(10)));
            ui->checkBox_add_Ping->setChecked(toBool(readyCMList[i].at(8)));
            ui->checkBox_add_StreamDI->setChecked(toBool(readyCMList[i].at(12)));
            ui->checkBox_add_StreamUI->setChecked(toBool(readyCMList[i].at(14)));
            ui->checkBox_add_SyncedPing->setChecked(toBool(readyCMList[i].at(16)));
            ui->checkBox_add_Voip->setChecked(toBool(readyCMList[i].at(18)));

            ui->bt_add_FtpDl->setEnabled(toBool(readyCMList[i].at(4)));
            ui->bt_add_FtpUl->setEnabled(toBool(readyCMList[i].at(6)));
            ui->bt_add_ServiceReq->setEnabled(toBool(readyCMList[i].at(10)));
            ui->bt_add_Ping->setEnabled(toBool(readyCMList[i].at(8)));
            ui->bt_add_StreamDI->setEnabled(toBool(readyCMList[i].at(12)));
            ui->bt_add_StreamUI->setEnabled(toBool(readyCMList[i].at(14)));
            ui->bt_SyncedPing->setEnabled(toBool(readyCMList[i].at(16)));
            ui->bt_add_Voip->setEnabled(toBool(readyCMList[i].at(18)));
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

    for(unsigned i=0;i<10;i++)
        if(CMname == (QString("Custom Model ") + QString::number(i+1))){
            CM_Params[i].clear();
            CM_Params[i].append(CMname);
            CM_Params[i].append("StyleSheet:");
            CM_Params[i].append(pointerCM[i]->styleSheet());
            CM_Params[i].append("FtpDlCheckBox:");
            CM_Params[i].append(textAddFtpDlCheckbox);
            CM_Params[i].append("FtpUlCheckBox:");
            CM_Params[i].append(textAddFtpUlCheckbox);
            CM_Params[i].append("AddPingCheckBox:");
            CM_Params[i].append(textAddPingCheckbox);
            CM_Params[i].append("AddServiceReqCheckBox:");
            CM_Params[i].append(textAddServiceReqCheckbox);
            CM_Params[i].append("AddStreamDlCheckBox:");
            CM_Params[i].append(textAddStreamDlCheckbox);
            CM_Params[i].append("AddStreamUlCheckBox:");
            CM_Params[i].append(textAddStreamUlCheckbox);
            CM_Params[i].append("AddSyncedPindCheckBox:");
            CM_Params[i].append(textAddSyncedPingCheckbox);
            CM_Params[i].append("AddVoipCheckBox:");
            CM_Params[i].append(textAddVoipCheckbox);
            CM_Params[i].append(PingList);
            CM_Params[i].append(VoipList);
            CM_Params[i].append(SyncedPingList);
            CM_Params[i].append(ServiceReqList);
            CM_Params[i].append(FtpDlList);
            CM_Params[i].append(FtpUlList);
            CM_Params[i].append(StreamDlList);
            CM_Params[i].append(StreamUlList);

            if(readyCMList[i] != CM_Params[i]){
                readyCMList[i].clear();
                readyCMList[i].append(CM_Params[i]);
            }
        }
    customModelList.clear();
    for(unsigned i=0;i<10;i++){
        customModelList.append(readyCMList[i]);
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
