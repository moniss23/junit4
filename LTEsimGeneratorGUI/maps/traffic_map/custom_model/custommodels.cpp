#include "custommodels.h"
#include "ui_custommodels.h"
#include <QMessageBox>
#include "maps/traffic_map/map_traffic.h"
#include "maps/traffic_map/map_traffic_large.h"
#include <QSettings>

extern QStringList savedCM1List;
extern QStringList savedCM2List;
extern QStringList savedCM3List;
extern QStringList savedCM4List;
extern QStringList savedCM5List;
extern QStringList savedCM6List;
extern QStringList savedCM7List;
extern QStringList savedCM8List;
extern QStringList savedCM9List;
extern QStringList savedCM10List;


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

extern QString currentPS;
extern QString currentPS_large;

extern QString curPS1;
extern QString curPS2;
extern QString curPS3;
extern QString curPS4;
extern QString curPS5;
extern QString curPS6;
extern QString curPS7;
extern QString curPS8;
extern QString curPS9;
extern QString curPS10;
extern QString curPS11;
extern QString curPS12;
extern QString curPS13;
extern QString curPS14;
extern QString curPS15;
extern QString curPS16;
extern QString curPS17;
extern QString curPS18;
extern QString curPS19;
extern QString curPS20;

int CM1isActive;
int CM2isActive;
int CM3isActive;
int CM4isActive;
int CM5isActive;
int CM6isActive;
int CM7isActive;
int CM8isActive;
int CM9isActive;
int CM10isActive;

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

}



Custommodels::~Custommodels()
{
    delete ui;
}

void Custommodels::on_checkBox_add_Ping_clicked()
{
    ui->bt_add_Ping->setEnabled(ui->checkBox_add_Ping->isChecked());
}

void Custommodels::on_bt_add_Ping_clicked()
{

    viewAddPing.close();
    viewAddPing.setWindowModality(Qt::WindowModal);
    viewAddPing.setParameters(addping);


//removes used QCI
    //FTPDl
    if(viewAddFtpdl.qciAddFtpDlPointer->currentText() != "" && viewAddPing.qciAddpingPointer->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText()) != (-1)){

       int index = viewAddPing.qciAddpingPointer->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
       viewAddPing.qciAddpingPointer->removeItem(index);

    }
//FtpUl
    if(viewAddFtpul.qciAddFtpUlPointer->currentText() != "" && viewAddPing.qciAddpingPointer->findText(viewAddFtpul.qciAddFtpUlPointer->currentText()) != (-1)){

       int index = viewAddPing.qciAddpingPointer->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
       viewAddPing.qciAddpingPointer->removeItem(index);

    }
//Voip
    if(viewAddVoip.qciAddVoipPointer->currentText() != "" && viewAddPing.qciAddpingPointer->findText(viewAddVoip.qciAddVoipPointer->currentText()) != (-1)){

       int index = viewAddPing.qciAddpingPointer->findText(viewAddVoip.qciAddVoipPointer->currentText());
       viewAddPing.qciAddpingPointer->removeItem(index);

    }
//streamUl
    if(viewAddStreamul.qciAddStreamUlPointer->currentText() != "" && viewAddPing.qciAddpingPointer->findText(viewAddStreamul.qciAddStreamUlPointer->currentText()) != (-1)){

       int index = viewAddPing.qciAddpingPointer->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
       viewAddPing.qciAddpingPointer->removeItem(index);

    }
//stremDl
    if(viewAddStreamdl.qciAddStreamDlPointer->currentText() != "" && viewAddPing.qciAddpingPointer->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText()) != (-1)){

       int index = viewAddPing.qciAddpingPointer->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
       viewAddPing.qciAddpingPointer->removeItem(index);

    }

 //ServiceReq

    if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "1"){
        int index = viewAddPing.qciAddpingPointer->findText("1");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "2"){
        int index = viewAddPing.qciAddpingPointer->findText("2");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "3"){
        int index = viewAddPing.qciAddpingPointer->findText("3");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "4"){
        int index = viewAddPing.qciAddpingPointer->findText("4");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "5"){
        int index = viewAddPing.qciAddpingPointer->findText("5");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "6"){
        int index = viewAddPing.qciAddpingPointer->findText("6");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "7"){
        int index = viewAddPing.qciAddpingPointer->findText("7");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "8"){
        int index = viewAddPing.qciAddpingPointer->findText("8");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "9"){
        int index = viewAddPing.qciAddpingPointer->findText("9");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

//Syncaddping

    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "1"){
        int index = viewAddPing.qciAddpingPointer->findText("1");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "2"){
        int index = viewAddPing.qciAddpingPointer->findText("2");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "3"){
        int index = viewAddPing.qciAddpingPointer->findText("3");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "4"){
        int index = viewAddPing.qciAddpingPointer->findText("4");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "5"){
        int index = viewAddPing.qciAddpingPointer->findText("5");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "6"){
        int index = viewAddPing.qciAddpingPointer->findText("6");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "7"){
        int index = viewAddPing.qciAddpingPointer->findText("7");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "8"){
        int index = viewAddPing.qciAddpingPointer->findText("8");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }

    if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "9"){
        int index = viewAddPing.qciAddpingPointer->findText("9");
        if(index != -1){
        viewAddPing.qciAddpingPointer->removeItem(index);
        }
    }


//adding unused QCI

        if(viewAddPing.qciAddpingPointer->findText("1") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"
                && viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "1"
                && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "1"
                && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "1"){

            viewAddPing.qciAddpingPointer->addItem("1");

        }

        if(viewAddPing.qciAddpingPointer->findText("2") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"
                && viewAddServicereq.qciAddServiceReqQci1->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "2"
                && viewAddServicereq.qciAddServiceReqQci6->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "2"
                && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "2"
                && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "2"){

            viewAddPing.qciAddpingPointer->addItem("2");

        }

        if(viewAddPing.qciAddpingPointer->findText("3") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"
                && viewAddServicereq.qciAddServiceReqQci1->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "3"
                && viewAddServicereq.qciAddServiceReqQci6->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "3"
                && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "3"
                && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "3"){

            viewAddPing.qciAddpingPointer->addItem("3");

        }

        if(viewAddPing.qciAddpingPointer->findText("4") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"
                && viewAddServicereq.qciAddServiceReqQci1->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "4"
                && viewAddServicereq.qciAddServiceReqQci6->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "4"
                && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "4"
                && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "4"){

            viewAddPing.qciAddpingPointer->addItem("4");

        }

        if(viewAddPing.qciAddpingPointer->findText("5") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"
                && viewAddServicereq.qciAddServiceReqQci1->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "5"
                && viewAddServicereq.qciAddServiceReqQci6->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "5"
                && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "5"
                && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "5"){

            viewAddPing.qciAddpingPointer->addItem("5");

        }

        if(viewAddPing.qciAddpingPointer->findText("6") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"
                && viewAddServicereq.qciAddServiceReqQci1->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "6"
                && viewAddServicereq.qciAddServiceReqQci6->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "6"
                && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "6"
                && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "6"){

            viewAddPing.qciAddpingPointer->addItem("6");

        }

        if(viewAddPing.qciAddpingPointer->findText("7") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"
                && viewAddServicereq.qciAddServiceReqQci1->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "7"
                && viewAddServicereq.qciAddServiceReqQci6->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "7"
                && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "7"
                && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "7"){

            viewAddPing.qciAddpingPointer->addItem("7");

        }

        if(viewAddPing.qciAddpingPointer->findText("8") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"
                && viewAddServicereq.qciAddServiceReqQci1->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "8"
                && viewAddServicereq.qciAddServiceReqQci6->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "8"
                && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "8"
                && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "8"){

            viewAddPing.qciAddpingPointer->addItem("8");

        }

        if(viewAddPing.qciAddpingPointer->findText("9") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"
                && viewAddServicereq.qciAddServiceReqQci1->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "9"
                && viewAddServicereq.qciAddServiceReqQci6->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "9"
                && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "9"
                && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "9"){

            viewAddPing.qciAddpingPointer->addItem("9");

        }


    viewAddPing.show();
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

void Custommodels::on_bt_add_Voip_clicked()
{
    viewAddVoip.close();
    viewAddVoip.setWindowModality(Qt::WindowModal);
    viewAddVoip.setParameters(addvoip); 

        //usuwanie uzywanych QCI
            //FTPDl
            if(viewAddFtpdl.qciAddFtpDlPointer->currentText() != "" && viewAddVoip.qciAddVoipPointer->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText()) != (-1)){

               int index = viewAddVoip.qciAddVoipPointer->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
               viewAddVoip.qciAddVoipPointer->removeItem(index);

            }
        //FtpUl
            if(viewAddFtpul.qciAddFtpUlPointer->currentText() != "" && viewAddVoip.qciAddVoipPointer->findText(viewAddFtpul.qciAddFtpUlPointer->currentText()) != (-1)){

               int index = viewAddVoip.qciAddVoipPointer->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
               viewAddVoip.qciAddVoipPointer->removeItem(index);

            }
            //AddPing
                if(viewAddPing.qciAddpingPointer->currentText() != "" && viewAddVoip.qciAddVoipPointer->findText(viewAddPing.qciAddpingPointer->currentText()) != (-1)){

                   int index = viewAddVoip.qciAddVoipPointer->findText(viewAddPing.qciAddpingPointer->currentText());
                   viewAddVoip.qciAddVoipPointer->removeItem(index);

                }
        //streamUl
            if(viewAddStreamul.qciAddStreamUlPointer->currentText() != "" && viewAddVoip.qciAddVoipPointer->findText(viewAddStreamul.qciAddStreamUlPointer->currentText()) != (-1)){

               int index = viewAddVoip.qciAddVoipPointer->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
               viewAddVoip.qciAddVoipPointer->removeItem(index);

            }
        //stremDl
            if(viewAddStreamdl.qciAddStreamDlPointer->currentText() != "" && viewAddVoip.qciAddVoipPointer->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText()) != (-1)){

               int index = viewAddVoip.qciAddVoipPointer->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
               viewAddVoip.qciAddVoipPointer->removeItem(index);

            }

         //ServiceReq

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "1"){
                int index = viewAddVoip.qciAddVoipPointer->findText("1");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "2"){
                int index = viewAddVoip.qciAddVoipPointer->findText("2");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "3"){
                int index = viewAddVoip.qciAddVoipPointer->findText("3");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "4"){
                int index = viewAddVoip.qciAddVoipPointer->findText("4");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "5"){
                int index = viewAddVoip.qciAddVoipPointer->findText("5");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "6"){
                int index = viewAddVoip.qciAddVoipPointer->findText("6");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "7"){
                int index = viewAddVoip.qciAddVoipPointer->findText("7");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "8"){
                int index = viewAddVoip.qciAddVoipPointer->findText("8");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "9"){
                int index = viewAddVoip.qciAddVoipPointer->findText("9");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

        //Syncaddping

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "1"){
                int index = viewAddVoip.qciAddVoipPointer->findText("1");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "2"){
                int index = viewAddVoip.qciAddVoipPointer->findText("2");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "3"){
                int index = viewAddVoip.qciAddVoipPointer->findText("3");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "4"){
                int index = viewAddVoip.qciAddVoipPointer->findText("4");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "5"){
                int index = viewAddVoip.qciAddVoipPointer->findText("5");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "6"){
                int index = viewAddVoip.qciAddVoipPointer->findText("6");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "7"){
                int index = viewAddVoip.qciAddVoipPointer->findText("7");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "8"){
                int index = viewAddVoip.qciAddVoipPointer->findText("8");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "9"){
                int index = viewAddVoip.qciAddVoipPointer->findText("9");
                if(index != -1){
                viewAddVoip.qciAddVoipPointer->removeItem(index);
                }
            }


        //dodawanie niewykorzystywanych QCI

                if(viewAddVoip.qciAddVoipPointer->findText("1") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddPing.qciAddpingPointer->currentText() != "1"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "1"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "1"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "1"){

                    viewAddVoip.qciAddVoipPointer->addItem("1");

                }

                if(viewAddVoip.qciAddVoipPointer->findText("2") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddPing.qciAddpingPointer->currentText() != "2"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "2"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "2"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "2"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "2"){

                    viewAddVoip.qciAddVoipPointer->addItem("2");

                }

                if(viewAddVoip.qciAddVoipPointer->findText("3") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddPing.qciAddpingPointer->currentText() != "3"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "3"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "3"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "3"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "3"){

                    viewAddVoip.qciAddVoipPointer->addItem("3");

                }

                if(viewAddVoip.qciAddVoipPointer->findText("4") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddPing.qciAddpingPointer->currentText() != "4"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "4"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "4"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "4"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "4"){

                    viewAddVoip.qciAddVoipPointer->addItem("4");

                }

                if(viewAddVoip.qciAddVoipPointer->findText("5") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddPing.qciAddpingPointer->currentText() != "5"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "5"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "5"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "5"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "5"){

                    viewAddVoip.qciAddVoipPointer->addItem("5");

                }

                if(viewAddVoip.qciAddVoipPointer->findText("6") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddPing.qciAddpingPointer->currentText() != "6"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "6"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "6"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "6"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "6"){

                    viewAddVoip.qciAddVoipPointer->addItem("6");

                }

                if(viewAddVoip.qciAddVoipPointer->findText("7") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddPing.qciAddpingPointer->currentText() != "7"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "7"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "7"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "7"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "7"){

                    viewAddVoip.qciAddVoipPointer->addItem("7");

                }

                if(viewAddVoip.qciAddVoipPointer->findText("8") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddPing.qciAddpingPointer->currentText() != "8"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "8"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "8"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "8"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "8"){

                    viewAddVoip.qciAddVoipPointer->addItem("8");

                }

                if(viewAddVoip.qciAddVoipPointer->findText("9") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddPing.qciAddpingPointer->currentText() != "9"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "9"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "9"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "9"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "9"){

                    viewAddVoip.qciAddVoipPointer->addItem("9");

                }


    viewAddVoip.show();
}

void Custommodels::on_bt_add_FtpDl_clicked()
{
        viewAddFtpdl.close();
        viewAddFtpdl.setWindowModality(Qt::WindowModal);
        viewAddFtpdl.setParameters(addftpdl);


        //usuwanie uzywanych QCI
            //AddVoip
            if(viewAddVoip.qciAddVoipPointer->currentText() != "" && viewAddFtpdl.qciAddFtpDlPointer->findText(viewAddVoip.qciAddVoipPointer->currentText()) != (-1)){

               int index = viewAddFtpdl.qciAddFtpDlPointer->findText(viewAddVoip.qciAddVoipPointer->currentText());
               viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);

            }
        //FtpUl
            if(viewAddFtpul.qciAddFtpUlPointer->currentText() != "" && viewAddFtpdl.qciAddFtpDlPointer->findText(viewAddFtpul.qciAddFtpUlPointer->currentText()) != (-1)){

               int index = viewAddFtpdl.qciAddFtpDlPointer->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
               viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);

            }
            //AddPing
                if(viewAddPing.qciAddpingPointer->currentText() != "" && viewAddFtpdl.qciAddFtpDlPointer->findText(viewAddPing.qciAddpingPointer->currentText()) != (-1)){

                   int index = viewAddFtpdl.qciAddFtpDlPointer->findText(viewAddPing.qciAddpingPointer->currentText());
                   viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);

                }
        //streamUl
            if(viewAddStreamul.qciAddStreamUlPointer->currentText() != "" && viewAddFtpdl.qciAddFtpDlPointer->findText(viewAddStreamul.qciAddStreamUlPointer->currentText()) != (-1)){

               int index = viewAddFtpdl.qciAddFtpDlPointer->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
               viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);

            }
        //stremDl
            if(viewAddStreamdl.qciAddStreamDlPointer->currentText() != "" && viewAddFtpdl.qciAddFtpDlPointer->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText()) != (-1)){

               int index = viewAddFtpdl.qciAddFtpDlPointer->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
               viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);

            }

         //ServiceReq

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "1"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("1");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "2"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("2");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "3"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("3");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "4"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("4");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "5"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("5");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "6"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("6");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "7"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("7");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "8"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("8");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "9"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("9");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

        //Syncaddping

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "1"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("1");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "2"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("2");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "3"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("3");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "4"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("4");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "5"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("5");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "6"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("6");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "7"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("7");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "8"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("8");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "9"){
                int index = viewAddFtpdl.qciAddFtpDlPointer->findText("9");
                if(index != -1){
                viewAddFtpdl.qciAddFtpDlPointer->removeItem(index);
                }
            }


        //dodawanie niewykorzystywanych QCI

                if(viewAddFtpdl.qciAddFtpDlPointer->findText("1") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddPing.qciAddpingPointer->currentText() != "1"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "1"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "1"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "1"){

                    viewAddFtpdl.qciAddFtpDlPointer->addItem("1");

                }

                if(viewAddFtpdl.qciAddFtpDlPointer->findText("2") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddPing.qciAddpingPointer->currentText() != "2"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "2"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "2"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "2"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "2"){

                    viewAddFtpdl.qciAddFtpDlPointer->addItem("2");

                }

                if(viewAddFtpdl.qciAddFtpDlPointer->findText("3") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddPing.qciAddpingPointer->currentText() != "3"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "3"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "3"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "3"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "3"){

                    viewAddFtpdl.qciAddFtpDlPointer->addItem("3");

                }

                if(viewAddFtpdl.qciAddFtpDlPointer->findText("4") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddPing.qciAddpingPointer->currentText() != "4"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "4"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "4"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "4"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "4"){

                    viewAddFtpdl.qciAddFtpDlPointer->addItem("4");

                }

                if(viewAddFtpdl.qciAddFtpDlPointer->findText("5") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddPing.qciAddpingPointer->currentText() != "5"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "5"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "5"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "5"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "5"){

                    viewAddFtpdl.qciAddFtpDlPointer->addItem("5");

                }

                if(viewAddFtpdl.qciAddFtpDlPointer->findText("6") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddPing.qciAddpingPointer->currentText() != "6"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "6"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "6"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "6"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "6"){

                    viewAddFtpdl.qciAddFtpDlPointer->addItem("6");

                }

                if(viewAddFtpdl.qciAddFtpDlPointer->findText("7") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddPing.qciAddpingPointer->currentText() != "7"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "7"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "7"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "7"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "7"){

                    viewAddFtpdl.qciAddFtpDlPointer->addItem("7");

                }

                if(viewAddFtpdl.qciAddFtpDlPointer->findText("8") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddPing.qciAddpingPointer->currentText() != "8"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "8"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "8"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "8"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "8"){

                    viewAddFtpdl.qciAddFtpDlPointer->addItem("8");

                }

                if(viewAddFtpdl.qciAddFtpDlPointer->findText("9") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddPing.qciAddpingPointer->currentText() != "9"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "9"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "9"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "9"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "9"){

                    viewAddFtpdl.qciAddFtpDlPointer->addItem("9");

                }

        viewAddFtpdl.show();
    }

void Custommodels::on_bt_add_FtpUl_clicked()
{
        viewAddFtpul.close();
        viewAddFtpul.setWindowModality(Qt::WindowModal);
        viewAddFtpul.setParameters(addftpul);


        //usuwanie uzywanych QCI
            //FTPDl
            if(viewAddFtpdl.qciAddFtpDlPointer->currentText() != "" && viewAddFtpul.qciAddFtpUlPointer->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText()) != (-1)){

               int index = viewAddFtpul.qciAddFtpUlPointer->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
               viewAddFtpul.qciAddFtpUlPointer->removeItem(index);

            }
        //AddVoip
            if(viewAddVoip.qciAddVoipPointer->currentText() != "" && viewAddFtpul.qciAddFtpUlPointer->findText(viewAddVoip.qciAddVoipPointer->currentText()) != (-1)){

               int index = viewAddFtpul.qciAddFtpUlPointer->findText(viewAddVoip.qciAddVoipPointer->currentText());
               viewAddFtpul.qciAddFtpUlPointer->removeItem(index);

            }
            //AddPing
                if(viewAddPing.qciAddpingPointer->currentText() != "" && viewAddFtpul.qciAddFtpUlPointer->findText(viewAddPing.qciAddpingPointer->currentText()) != (-1)){

                   int index = viewAddFtpul.qciAddFtpUlPointer->findText(viewAddPing.qciAddpingPointer->currentText());
                   viewAddFtpul.qciAddFtpUlPointer->removeItem(index);

                }
        //streamUl
            if(viewAddStreamul.qciAddStreamUlPointer->currentText() != "" && viewAddFtpul.qciAddFtpUlPointer->findText(viewAddStreamul.qciAddStreamUlPointer->currentText()) != (-1)){

               int index = viewAddFtpul.qciAddFtpUlPointer->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
               viewAddFtpul.qciAddFtpUlPointer->removeItem(index);

            }
        //stremDl
            if(viewAddStreamdl.qciAddStreamDlPointer->currentText() != "" && viewAddFtpul.qciAddFtpUlPointer->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText()) != (-1)){

               int index = viewAddFtpul.qciAddFtpUlPointer->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
               viewAddFtpul.qciAddFtpUlPointer->removeItem(index);

            }

         //ServiceReq

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "1"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("1");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "2"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("2");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "3"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("3");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "4"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("4");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "5"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("5");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "6"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("6");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "7"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("7");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "8"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("8");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "9"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("9");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

        //Syncaddping

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "1"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("1");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "2"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("2");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "3"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("3");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "4"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("4");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "5"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("5");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "6"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("6");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "7"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("7");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "8"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("8");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }

            if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "9"){
                int index = viewAddFtpul.qciAddFtpUlPointer->findText("9");
                if(index != -1){
                viewAddFtpul.qciAddFtpUlPointer->removeItem(index);
                }
            }


        //dodawanie niewykorzystywanych QCI

                if(viewAddFtpul.qciAddFtpUlPointer->findText("1") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "1"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "1"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "1"){

                    viewAddFtpul.qciAddFtpUlPointer->addItem("1");

                }

                if(viewAddFtpul.qciAddFtpUlPointer->findText("2") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "2"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "2"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "2"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "2"){

                    viewAddFtpul.qciAddFtpUlPointer->addItem("2");

                }

                if(viewAddFtpul.qciAddFtpUlPointer->findText("3") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "3"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "3"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "3"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "3"){

                    viewAddFtpul.qciAddFtpUlPointer->addItem("3");

                }

                if(viewAddFtpul.qciAddFtpUlPointer->findText("4") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "4"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "4"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "4"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "4"){

                    viewAddFtpul.qciAddFtpUlPointer->addItem("4");

                }

                if(viewAddFtpul.qciAddFtpUlPointer->findText("5") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "5"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "5"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "5"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "5"){

                    viewAddFtpul.qciAddFtpUlPointer->addItem("5");

                }

                if(viewAddFtpul.qciAddFtpUlPointer->findText("6") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "6"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "6"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "6"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "6"){

                    viewAddFtpul.qciAddFtpUlPointer->addItem("6");

                }

                if(viewAddFtpul.qciAddFtpUlPointer->findText("7") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "7"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "7"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "7"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "7"){

                    viewAddFtpul.qciAddFtpUlPointer->addItem("7");

                }

                if(viewAddFtpul.qciAddFtpUlPointer->findText("8") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "8"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "8"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "8"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "8"){

                    viewAddFtpul.qciAddFtpUlPointer->addItem("8");

                }

                if(viewAddFtpul.qciAddFtpUlPointer->findText("9") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9"
                        && viewAddServicereq.qciAddServiceReqQci1->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "9"
                        && viewAddServicereq.qciAddServiceReqQci6->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "9"
                        && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "9"
                        && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "9"){

                    viewAddFtpul.qciAddFtpUlPointer->addItem("9");

                }



        viewAddFtpul.show();
}

void Custommodels::on_bt_add_StreamDI_clicked()
{
    viewAddStreamdl.close();
    viewAddStreamdl.setWindowModality(Qt::WindowModal);
    viewAddStreamdl.setParameters(addstreamdl);


    //usuwanie uzywanych QCI
              //FTPDl
              if(viewAddFtpdl.qciAddFtpDlPointer->currentText() != "" && viewAddStreamdl.qciAddStreamDlPointer->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText()) != (-1)){

                 int index = viewAddStreamdl.qciAddStreamDlPointer->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
                 viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);

              }
          //FtpUl
              if(viewAddFtpul.qciAddFtpUlPointer->currentText() != "" && viewAddStreamdl.qciAddStreamDlPointer->findText(viewAddFtpul.qciAddFtpUlPointer->currentText()) != (-1)){

                 int index = viewAddStreamdl.qciAddStreamDlPointer->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
                 viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);

              }
              //AddPing
                  if(viewAddPing.qciAddpingPointer->currentText() != "" && viewAddStreamdl.qciAddStreamDlPointer->findText(viewAddPing.qciAddpingPointer->currentText()) != (-1)){

                     int index = viewAddStreamdl.qciAddStreamDlPointer->findText(viewAddPing.qciAddpingPointer->currentText());
                     viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);

                  }
          //streamUl
              if(viewAddStreamul.qciAddStreamUlPointer->currentText() != "" && viewAddStreamdl.qciAddStreamDlPointer->findText(viewAddStreamul.qciAddStreamUlPointer->currentText()) != (-1)){

                 int index = viewAddStreamdl.qciAddStreamDlPointer->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
                 viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);

              }
          //AddVoip
              if(viewAddVoip.qciAddVoipPointer->currentText() != "" && viewAddStreamdl.qciAddStreamDlPointer->findText(viewAddVoip.qciAddVoipPointer->currentText()) != (-1)){

                 int index = viewAddStreamdl.qciAddStreamDlPointer->findText(viewAddVoip.qciAddVoipPointer->currentText());
                 viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);

              }

           //ServiceReq

              if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "1"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("1");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "2"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("2");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "3"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("3");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "4"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("4");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "5"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("5");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "6"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("6");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "7"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("7");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "8"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("8");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "9"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("9");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

          //Syncaddping

              if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "1"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("1");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "2"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("2");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "3"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("3");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "4"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("4");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "5"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("5");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "6"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("6");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "7"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("7");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "8"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("8");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }

              if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "9"){
                  int index = viewAddStreamdl.qciAddStreamDlPointer->findText("9");
                  if(index != -1){
                  viewAddStreamdl.qciAddStreamDlPointer->removeItem(index);
                  }
              }


          //dodawanie niewykorzystywanych QCI

                  if(viewAddStreamdl.qciAddStreamDlPointer->findText("1") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1" && viewAddPing.qciAddpingPointer->currentText() != "1"
                          && viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                          && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "1"
                          && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "1"
                          && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "1"){

                      viewAddStreamdl.qciAddStreamDlPointer->addItem("1");

                  }

                  if(viewAddStreamdl.qciAddStreamDlPointer->findText("2") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2" && viewAddPing.qciAddpingPointer->currentText() != "2"
                          && viewAddServicereq.qciAddServiceReqQci1->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "2"
                          && viewAddServicereq.qciAddServiceReqQci6->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "2"
                          && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "2"
                          && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "2"){

                      viewAddStreamdl.qciAddStreamDlPointer->addItem("2");

                  }

                  if(viewAddStreamdl.qciAddStreamDlPointer->findText("3") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3" && viewAddPing.qciAddpingPointer->currentText() != "3"
                          && viewAddServicereq.qciAddServiceReqQci1->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "3"
                          && viewAddServicereq.qciAddServiceReqQci6->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "3"
                          && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "3"
                          && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "3"){

                      viewAddStreamdl.qciAddStreamDlPointer->addItem("3");

                  }

                  if(viewAddStreamdl.qciAddStreamDlPointer->findText("4") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4" && viewAddPing.qciAddpingPointer->currentText() != "4"
                          && viewAddServicereq.qciAddServiceReqQci1->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "4"
                          && viewAddServicereq.qciAddServiceReqQci6->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "4"
                          && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "4"
                          && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "4"){

                      viewAddStreamdl.qciAddStreamDlPointer->addItem("4");

                  }

                  if(viewAddStreamdl.qciAddStreamDlPointer->findText("5") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5" && viewAddPing.qciAddpingPointer->currentText() != "5"
                          && viewAddServicereq.qciAddServiceReqQci1->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "5"
                          && viewAddServicereq.qciAddServiceReqQci6->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "5"
                          && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "5"
                          && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "5"){

                      viewAddStreamdl.qciAddStreamDlPointer->addItem("5");

                  }

                  if(viewAddStreamdl.qciAddStreamDlPointer->findText("6") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6" && viewAddPing.qciAddpingPointer->currentText() != "6"
                          && viewAddServicereq.qciAddServiceReqQci1->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "6"
                          && viewAddServicereq.qciAddServiceReqQci6->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "6"
                          && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "6"
                          && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "6"){

                      viewAddStreamdl.qciAddStreamDlPointer->addItem("6");

                  }

                  if(viewAddStreamdl.qciAddStreamDlPointer->findText("7") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7" && viewAddPing.qciAddpingPointer->currentText() != "7"
                          && viewAddServicereq.qciAddServiceReqQci1->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "7"
                          && viewAddServicereq.qciAddServiceReqQci6->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "7"
                          && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "7"
                          && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "7"){

                      viewAddStreamdl.qciAddStreamDlPointer->addItem("7");

                  }

                  if(viewAddStreamdl.qciAddStreamDlPointer->findText("8") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8" && viewAddPing.qciAddpingPointer->currentText() != "8"
                          && viewAddServicereq.qciAddServiceReqQci1->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "8"
                          && viewAddServicereq.qciAddServiceReqQci6->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "8"
                          && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "8"
                          && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "8"){

                      viewAddStreamdl.qciAddStreamDlPointer->addItem("8");

                  }

                  if(viewAddStreamdl.qciAddStreamDlPointer->findText("9") == -1 && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9" && viewAddPing.qciAddpingPointer->currentText() != "9"
                          && viewAddServicereq.qciAddServiceReqQci1->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "9"
                          && viewAddServicereq.qciAddServiceReqQci6->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "9"
                          && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "9"
                          && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "9"){

                      viewAddStreamdl.qciAddStreamDlPointer->addItem("9");

                  }


    viewAddStreamdl.show();
}

void Custommodels::on_bt_add_StreamUI_clicked()
{
    viewAddStreamul.close();
    viewAddStreamul.setWindowModality(Qt::WindowModal);
    viewAddStreamul.setParameters(addstreamul);


    //usuwanie uzywanych QCI
        //FTPDl
        if(viewAddFtpdl.qciAddFtpDlPointer->currentText() != "" && viewAddStreamul.qciAddStreamUlPointer->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText()) != (-1)){

           int index = viewAddStreamul.qciAddStreamUlPointer->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
           viewAddStreamul.qciAddStreamUlPointer->removeItem(index);

        }
    //FtpUl
        if(viewAddFtpul.qciAddFtpUlPointer->currentText() != "" && viewAddStreamul.qciAddStreamUlPointer->findText(viewAddFtpul.qciAddFtpUlPointer->currentText()) != (-1)){

           int index = viewAddStreamul.qciAddStreamUlPointer->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
           viewAddStreamul.qciAddStreamUlPointer->removeItem(index);

        }
    //Voip
        if(viewAddVoip.qciAddVoipPointer->currentText() != "" && viewAddStreamul.qciAddStreamUlPointer->findText(viewAddVoip.qciAddVoipPointer->currentText()) != (-1)){

           int index = viewAddStreamul.qciAddStreamUlPointer->findText(viewAddVoip.qciAddVoipPointer->currentText());
           viewAddStreamul.qciAddStreamUlPointer->removeItem(index);

        }
    //AddPing
        if(viewAddPing.qciAddpingPointer->currentText() != "" && viewAddStreamul.qciAddStreamUlPointer->findText(viewAddPing.qciAddpingPointer->currentText()) != (-1)){

           int index = viewAddStreamul.qciAddStreamUlPointer->findText(viewAddPing.qciAddpingPointer->currentText());
           viewAddStreamul.qciAddStreamUlPointer->removeItem(index);

        }
    //stremDl
        if(viewAddStreamdl.qciAddStreamDlPointer->currentText() != "" && viewAddStreamul.qciAddStreamUlPointer->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText()) != (-1)){

           int index = viewAddStreamul.qciAddStreamUlPointer->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
           viewAddStreamul.qciAddStreamUlPointer->removeItem(index);

        }

     //ServiceReq

        if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "1" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "1"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("1");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "2" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "2"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("2");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "3" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "3"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("3");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "4" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "4"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("4");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "5" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "5"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("5");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "6" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "6"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("6");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "7" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "7"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("7");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "8" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "8"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("8");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddServicereq.qciAddServiceReqQci1->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci2->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci3->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci4->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci5->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci6->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci7->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci8->currentText() == "9" || viewAddServicereq.qciAddServiceReqQci9->currentText() == "9"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("9");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

    //Syncaddping

        if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "1" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "1"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("1");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "2" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "2"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("2");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "3" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "3"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("3");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "4" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "4"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("4");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "5" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "5"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("5");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "6" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "6"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("6");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "7" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "7"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("7");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "8" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "8"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("8");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }

        if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci2->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci3->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci4->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci5->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci6->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci7->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci8->currentText() == "9" || viewAddSyncedping.qciAddSyncedPingQci9->currentText() == "9"){
            int index = viewAddStreamul.qciAddStreamUlPointer->findText("9");
            if(index != -1){
            viewAddStreamul.qciAddStreamUlPointer->removeItem(index);
            }
        }


    //dodawanie niewykorzystywanych QCI

            if(viewAddStreamul.qciAddStreamUlPointer->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "1"
                    && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "1"
                    && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "1" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "1"){

                viewAddStreamul.qciAddStreamUlPointer->addItem("1");

            }

            if(viewAddStreamul.qciAddStreamUlPointer->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "2"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "2" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "2"
                    && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "2"
                    && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "2" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "2"){

                viewAddStreamul.qciAddStreamUlPointer->addItem("2");

            }

            if(viewAddStreamul.qciAddStreamUlPointer->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "3"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "3" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "3"
                    && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "3"
                    && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "3" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "3"){

                viewAddStreamul.qciAddStreamUlPointer->addItem("3");

            }

            if(viewAddStreamul.qciAddStreamUlPointer->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "4"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "4" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "4"
                    && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "4"
                    && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "4" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "4"){

                viewAddStreamul.qciAddStreamUlPointer->addItem("4");

            }

            if(viewAddStreamul.qciAddStreamUlPointer->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "5"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "5" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "5"
                    && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "5"
                    && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "5" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "5"){

                viewAddStreamul.qciAddStreamUlPointer->addItem("5");

            }

            if(viewAddStreamul.qciAddStreamUlPointer->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "6"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "6" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "6"
                    && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "6"
                    && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "6" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "6"){

                viewAddStreamul.qciAddStreamUlPointer->addItem("6");

            }

            if(viewAddStreamul.qciAddStreamUlPointer->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "7"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "7" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "7"
                    && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "7"
                    && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "7" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "7"){

                viewAddStreamul.qciAddStreamUlPointer->addItem("7");

            }

            if(viewAddStreamul.qciAddStreamUlPointer->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "8"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "8" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "8"
                    && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "8"
                    && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "8" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "8"){

                viewAddStreamul.qciAddStreamUlPointer->addItem("8");

            }

            if(viewAddStreamul.qciAddStreamUlPointer->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "9"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "9" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "9"
                    && viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "9"
                    && viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "9" && viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "9"){

                viewAddStreamul.qciAddStreamUlPointer->addItem("9");

            }


    viewAddStreamul.show();
}

void Custommodels::on_bt_SyncedPing_clicked()
{
    viewAddSyncedping.close();
    viewAddSyncedping.setWindowModality(Qt::WindowModal);
    viewAddSyncedping.setParameters(addsyncedping);

    //usuwanie uzywanych QCI
        //FTPDl
        if(viewAddFtpdl.qciAddFtpDlPointer->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText()) != (-1)){

           int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
           int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
           int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
           int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
           int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
           int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
           int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
           int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
           int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());


           viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
           viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
           viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
           viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
           viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
           viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
           viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
           viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
           viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);
        }
    //FtpUl
        if(viewAddFtpul.qciAddFtpUlPointer->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddFtpul.qciAddFtpUlPointer->currentText()) != (-1)){

            int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
            int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
            int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
            int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
            int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
            int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
            int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
            int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
            int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());


            viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
            viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
            viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
            viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
            viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
            viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
            viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
            viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
            viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);

        }
    //Voip
        if(viewAddVoip.qciAddVoipPointer->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddVoip.qciAddVoipPointer->currentText()) != (-1)){

            int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddVoip.qciAddVoipPointer->currentText());
            int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddVoip.qciAddVoipPointer->currentText());
            int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddVoip.qciAddVoipPointer->currentText());
            int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddVoip.qciAddVoipPointer->currentText());
            int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddVoip.qciAddVoipPointer->currentText());
            int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddVoip.qciAddVoipPointer->currentText());
            int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddVoip.qciAddVoipPointer->currentText());
            int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddVoip.qciAddVoipPointer->currentText());
            int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddVoip.qciAddVoipPointer->currentText());


            viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
            viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
            viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
            viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
            viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
            viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
            viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
            viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
            viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);

        }
    //streamUl
        if(viewAddStreamul.qciAddStreamUlPointer->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddStreamul.qciAddStreamUlPointer->currentText()) != (-1)){

            int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
            int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
            int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
            int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
            int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
            int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
            int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
            int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
            int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());


            viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
            viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
            viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
            viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
            viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
            viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
            viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
            viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
            viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);

        }
    //stremDl
        if(viewAddStreamdl.qciAddStreamDlPointer->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText()) != (-1)){

            int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
            int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
            int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
            int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
            int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
            int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
            int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
            int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
            int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());


            viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
            viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
            viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
            viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
            viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
            viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
            viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
            viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
            viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);


        }

     //AddPing
        if(viewAddPing.qciAddpingPointer->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddPing.qciAddpingPointer->currentText()) != (-1)){

            int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddPing.qciAddpingPointer->currentText());
            int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddPing.qciAddpingPointer->currentText());
            int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddPing.qciAddpingPointer->currentText());
            int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddPing.qciAddpingPointer->currentText());
            int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddPing.qciAddpingPointer->currentText());
            int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddPing.qciAddpingPointer->currentText());
            int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddPing.qciAddpingPointer->currentText());
            int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddPing.qciAddpingPointer->currentText());
            int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddPing.qciAddpingPointer->currentText());


            viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
            viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
            viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
            viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
            viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
            viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
            viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
            viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
            viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);


        }


        //AddServiceReq


        //QCI1
        if(viewAddServicereq.qciAddServiceReqQci1->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci1->currentText()) != (-1)){

            int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci1->currentText());
            int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddServicereq.qciAddServiceReqQci1->currentText());
            int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddServicereq.qciAddServiceReqQci1->currentText());
            int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddServicereq.qciAddServiceReqQci1->currentText());
            int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddServicereq.qciAddServiceReqQci1->currentText());
            int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddServicereq.qciAddServiceReqQci1->currentText());
            int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddServicereq.qciAddServiceReqQci1->currentText());
            int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddServicereq.qciAddServiceReqQci1->currentText());
            int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddServicereq.qciAddServiceReqQci1->currentText());


            viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
            viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
            viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
            viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
            viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
            viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
            viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
            viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
            viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);


        }
        //QCi2

        if(viewAddServicereq.qciAddServiceReqQci2->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci2->currentText()) != (-1)){

            int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci2->currentText());
            int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddServicereq.qciAddServiceReqQci2->currentText());
            int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddServicereq.qciAddServiceReqQci2->currentText());
            int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddServicereq.qciAddServiceReqQci2->currentText());
            int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddServicereq.qciAddServiceReqQci2->currentText());
            int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddServicereq.qciAddServiceReqQci2->currentText());
            int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddServicereq.qciAddServiceReqQci2->currentText());
            int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddServicereq.qciAddServiceReqQci2->currentText());
            int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddServicereq.qciAddServiceReqQci2->currentText());


            viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
            viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
            viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
            viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
            viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
            viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
            viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
            viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
            viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);


        }

        //Qci3

        if(viewAddServicereq.qciAddServiceReqQci3->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci3->currentText()) != (-1)){

            int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci3->currentText());
            int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddServicereq.qciAddServiceReqQci3->currentText());
            int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddServicereq.qciAddServiceReqQci3->currentText());
            int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddServicereq.qciAddServiceReqQci3->currentText());
            int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddServicereq.qciAddServiceReqQci3->currentText());
            int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddServicereq.qciAddServiceReqQci3->currentText());
            int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddServicereq.qciAddServiceReqQci3->currentText());
            int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddServicereq.qciAddServiceReqQci3->currentText());
            int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddServicereq.qciAddServiceReqQci3->currentText());


            viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
            viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
            viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
            viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
            viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
            viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
            viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
            viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
            viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);


        }
        //Qci4

        if(viewAddServicereq.qciAddServiceReqQci4->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci4->currentText()) != (-1)){

            int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci4->currentText());
            int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddServicereq.qciAddServiceReqQci4->currentText());
            int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddServicereq.qciAddServiceReqQci4->currentText());
            int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddServicereq.qciAddServiceReqQci4->currentText());
            int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddServicereq.qciAddServiceReqQci4->currentText());
            int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddServicereq.qciAddServiceReqQci4->currentText());
            int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddServicereq.qciAddServiceReqQci4->currentText());
            int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddServicereq.qciAddServiceReqQci4->currentText());
            int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddServicereq.qciAddServiceReqQci4->currentText());


            viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
            viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
            viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
            viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
            viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
            viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
            viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
            viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
            viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);


        }

        //Qci5

        if(viewAddServicereq.qciAddServiceReqQci5->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci5->currentText()) != (-1)){

            int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci5->currentText());
            int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddServicereq.qciAddServiceReqQci5->currentText());
            int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddServicereq.qciAddServiceReqQci5->currentText());
            int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddServicereq.qciAddServiceReqQci5->currentText());
            int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddServicereq.qciAddServiceReqQci5->currentText());
            int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddServicereq.qciAddServiceReqQci5->currentText());
            int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddServicereq.qciAddServiceReqQci5->currentText());
            int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddServicereq.qciAddServiceReqQci5->currentText());
            int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddServicereq.qciAddServiceReqQci5->currentText());


            viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
            viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
            viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
            viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
            viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
            viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
            viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
            viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
            viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);


        }

        //Qci6

        if(viewAddServicereq.qciAddServiceReqQci6->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci6->currentText()) != (-1)){

            int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci6->currentText());
            int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddServicereq.qciAddServiceReqQci6->currentText());
            int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddServicereq.qciAddServiceReqQci6->currentText());
            int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddServicereq.qciAddServiceReqQci6->currentText());
            int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddServicereq.qciAddServiceReqQci6->currentText());
            int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddServicereq.qciAddServiceReqQci6->currentText());
            int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddServicereq.qciAddServiceReqQci6->currentText());
            int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddServicereq.qciAddServiceReqQci6->currentText());
            int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddServicereq.qciAddServiceReqQci6->currentText());


            viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
            viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
            viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
            viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
            viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
            viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
            viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
            viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
            viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);


        }

        //Qci7

        if(viewAddServicereq.qciAddServiceReqQci7->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci7->currentText()) != (-1)){

            int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci7->currentText());
            int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddServicereq.qciAddServiceReqQci7->currentText());
            int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddServicereq.qciAddServiceReqQci7->currentText());
            int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddServicereq.qciAddServiceReqQci7->currentText());
            int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddServicereq.qciAddServiceReqQci7->currentText());
            int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddServicereq.qciAddServiceReqQci7->currentText());
            int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddServicereq.qciAddServiceReqQci7->currentText());
            int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddServicereq.qciAddServiceReqQci7->currentText());
            int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddServicereq.qciAddServiceReqQci7->currentText());


            viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
            viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
            viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
            viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
            viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
            viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
            viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
            viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
            viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);


        }

        //Qci8

        if(viewAddServicereq.qciAddServiceReqQci8->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci8->currentText()) != (-1)){

            int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci8->currentText());
            int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddServicereq.qciAddServiceReqQci8->currentText());
            int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddServicereq.qciAddServiceReqQci8->currentText());
            int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddServicereq.qciAddServiceReqQci8->currentText());
            int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddServicereq.qciAddServiceReqQci8->currentText());
            int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddServicereq.qciAddServiceReqQci8->currentText());
            int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddServicereq.qciAddServiceReqQci8->currentText());
            int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddServicereq.qciAddServiceReqQci8->currentText());
            int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddServicereq.qciAddServiceReqQci8->currentText());


            viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
            viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
            viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
            viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
            viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
            viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
            viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
            viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
            viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);


        }

        //Qci9

        if(viewAddServicereq.qciAddServiceReqQci9->currentText() != "" && viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci9->currentText()) != (-1)){

            int index = viewAddSyncedping.qciAddSyncedPingQci1->findText(viewAddServicereq.qciAddServiceReqQci9->currentText());
            int index2 = viewAddSyncedping.qciAddSyncedPingQci2->findText(viewAddServicereq.qciAddServiceReqQci9->currentText());
            int index3 = viewAddSyncedping.qciAddSyncedPingQci3->findText(viewAddServicereq.qciAddServiceReqQci9->currentText());
            int index4 = viewAddSyncedping.qciAddSyncedPingQci4->findText(viewAddServicereq.qciAddServiceReqQci9->currentText());
            int index5 = viewAddSyncedping.qciAddSyncedPingQci5->findText(viewAddServicereq.qciAddServiceReqQci9->currentText());
            int index6 = viewAddSyncedping.qciAddSyncedPingQci6->findText(viewAddServicereq.qciAddServiceReqQci9->currentText());
            int index7 = viewAddSyncedping.qciAddSyncedPingQci7->findText(viewAddServicereq.qciAddServiceReqQci9->currentText());
            int index8 = viewAddSyncedping.qciAddSyncedPingQci8->findText(viewAddServicereq.qciAddServiceReqQci9->currentText());
            int index9 = viewAddSyncedping.qciAddSyncedPingQci9->findText(viewAddServicereq.qciAddServiceReqQci9->currentText());


            viewAddSyncedping.qciAddSyncedPingQci1->removeItem(index);
            viewAddSyncedping.qciAddSyncedPingQci2->removeItem(index2);
            viewAddSyncedping.qciAddSyncedPingQci3->removeItem(index3);
            viewAddSyncedping.qciAddSyncedPingQci4->removeItem(index4);
            viewAddSyncedping.qciAddSyncedPingQci5->removeItem(index5);
            viewAddSyncedping.qciAddSyncedPingQci6->removeItem(index6);
            viewAddSyncedping.qciAddSyncedPingQci7->removeItem(index7);
            viewAddSyncedping.qciAddSyncedPingQci8->removeItem(index8);
            viewAddSyncedping.qciAddSyncedPingQci9->removeItem(index9);


        }


    //dodawanie niewykorzystywanych QCI
        //1

            if(viewAddSyncedping.qciAddSyncedPingQci1->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1"
                    && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"&& viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1"){

                viewAddSyncedping.qciAddSyncedPingQci1->addItem("1");

            }            
            if(viewAddSyncedping.qciAddSyncedPingQci2->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1"){

                viewAddSyncedping.qciAddSyncedPingQci2->addItem("1");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci3->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1"){

                viewAddSyncedping.qciAddSyncedPingQci3->addItem("1");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci4->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1"){

                viewAddSyncedping.qciAddSyncedPingQci4->addItem("1");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci5->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1"){

                viewAddSyncedping.qciAddSyncedPingQci5->addItem("1");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci6->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1"){

                viewAddSyncedping.qciAddSyncedPingQci6->addItem("1");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci7->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1"){

                viewAddSyncedping.qciAddSyncedPingQci7->addItem("1");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci8->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1"){

                viewAddSyncedping.qciAddSyncedPingQci8->addItem("1");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci9->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci1->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci2->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci3->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci4->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci5->currentText() != "1"
                    && viewAddServicereq.qciAddServiceReqQci6->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci7->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci8->currentText() != "1" && viewAddServicereq.qciAddServiceReqQci9->currentText() != "1"){

                viewAddSyncedping.qciAddSyncedPingQci9->addItem("1");

            }

            //2

            if(viewAddSyncedping.qciAddSyncedPingQci1->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                viewAddSyncedping.qciAddSyncedPingQci1->addItem("2");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci2->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                viewAddSyncedping.qciAddSyncedPingQci2->addItem("2");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci3->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                viewAddSyncedping.qciAddSyncedPingQci3->addItem("2");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci4->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                viewAddSyncedping.qciAddSyncedPingQci4->addItem("2");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci5->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                viewAddSyncedping.qciAddSyncedPingQci5->addItem("2");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci6->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                viewAddSyncedping.qciAddSyncedPingQci6->addItem("2");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci7->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                viewAddSyncedping.qciAddSyncedPingQci7->addItem("2");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci8->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                viewAddSyncedping.qciAddSyncedPingQci8->addItem("2");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci9->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                viewAddSyncedping.qciAddSyncedPingQci9->addItem("2");

            }


            //3

            if(viewAddSyncedping.qciAddSyncedPingQci1->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                viewAddSyncedping.qciAddSyncedPingQci1->addItem("3");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci2->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                viewAddSyncedping.qciAddSyncedPingQci2->addItem("3");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci3->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                viewAddSyncedping.qciAddSyncedPingQci3->addItem("3");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci4->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                viewAddSyncedping.qciAddSyncedPingQci4->addItem("3");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci5->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                viewAddSyncedping.qciAddSyncedPingQci5->addItem("3");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci6->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                viewAddSyncedping.qciAddSyncedPingQci6->addItem("3");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci7->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                viewAddSyncedping.qciAddSyncedPingQci7->addItem("3");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci8->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                viewAddSyncedping.qciAddSyncedPingQci8->addItem("3");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci9->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                viewAddSyncedping.qciAddSyncedPingQci9->addItem("3");

            }


            //4

            if(viewAddSyncedping.qciAddSyncedPingQci1->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                viewAddSyncedping.qciAddSyncedPingQci1->addItem("4");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci2->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                viewAddSyncedping.qciAddSyncedPingQci2->addItem("4");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci3->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                viewAddSyncedping.qciAddSyncedPingQci3->addItem("4");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci4->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                viewAddSyncedping.qciAddSyncedPingQci4->addItem("4");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci5->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                viewAddSyncedping.qciAddSyncedPingQci5->addItem("4");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci6->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                viewAddSyncedping.qciAddSyncedPingQci6->addItem("4");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci7->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                viewAddSyncedping.qciAddSyncedPingQci7->addItem("4");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci8->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                viewAddSyncedping.qciAddSyncedPingQci8->addItem("4");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci9->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                viewAddSyncedping.qciAddSyncedPingQci9->addItem("4");

            }


            //5

            if(viewAddSyncedping.qciAddSyncedPingQci1->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                viewAddSyncedping.qciAddSyncedPingQci1->addItem("5");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci2->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                viewAddSyncedping.qciAddSyncedPingQci2->addItem("5");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci3->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                viewAddSyncedping.qciAddSyncedPingQci3->addItem("5");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci4->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                viewAddSyncedping.qciAddSyncedPingQci4->addItem("5");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci5->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                viewAddSyncedping.qciAddSyncedPingQci5->addItem("5");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci6->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                viewAddSyncedping.qciAddSyncedPingQci6->addItem("5");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci7->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                viewAddSyncedping.qciAddSyncedPingQci7->addItem("5");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci8->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                viewAddSyncedping.qciAddSyncedPingQci8->addItem("5");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci9->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                viewAddSyncedping.qciAddSyncedPingQci9->addItem("5");

            }


            //6

            if(viewAddSyncedping.qciAddSyncedPingQci1->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                viewAddSyncedping.qciAddSyncedPingQci1->addItem("6");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci2->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                viewAddSyncedping.qciAddSyncedPingQci2->addItem("6");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci3->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                viewAddSyncedping.qciAddSyncedPingQci3->addItem("6");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci4->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                viewAddSyncedping.qciAddSyncedPingQci4->addItem("6");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci5->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                viewAddSyncedping.qciAddSyncedPingQci5->addItem("6");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci6->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                viewAddSyncedping.qciAddSyncedPingQci6->addItem("6");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci7->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                viewAddSyncedping.qciAddSyncedPingQci7->addItem("6");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci8->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                viewAddSyncedping.qciAddSyncedPingQci8->addItem("6");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci9->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                viewAddSyncedping.qciAddSyncedPingQci9->addItem("6");

            }


            //7

            if(viewAddSyncedping.qciAddSyncedPingQci1->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                viewAddSyncedping.qciAddSyncedPingQci1->addItem("7");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci2->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                viewAddSyncedping.qciAddSyncedPingQci2->addItem("7");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci3->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                viewAddSyncedping.qciAddSyncedPingQci3->addItem("7");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci4->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                viewAddSyncedping.qciAddSyncedPingQci4->addItem("7");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci5->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                viewAddSyncedping.qciAddSyncedPingQci5->addItem("7");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci6->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                viewAddSyncedping.qciAddSyncedPingQci6->addItem("7");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci7->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                viewAddSyncedping.qciAddSyncedPingQci7->addItem("7");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci8->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                viewAddSyncedping.qciAddSyncedPingQci8->addItem("7");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci9->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                viewAddSyncedping.qciAddSyncedPingQci9->addItem("7");

            }


            //8

            if(viewAddSyncedping.qciAddSyncedPingQci1->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                viewAddSyncedping.qciAddSyncedPingQci1->addItem("8");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci2->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                viewAddSyncedping.qciAddSyncedPingQci2->addItem("8");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci3->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                viewAddSyncedping.qciAddSyncedPingQci3->addItem("8");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci4->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                viewAddSyncedping.qciAddSyncedPingQci4->addItem("8");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci5->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                viewAddSyncedping.qciAddSyncedPingQci5->addItem("8");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci6->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                viewAddSyncedping.qciAddSyncedPingQci6->addItem("8");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci7->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                viewAddSyncedping.qciAddSyncedPingQci7->addItem("8");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci8->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                viewAddSyncedping.qciAddSyncedPingQci8->addItem("8");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci9->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                viewAddSyncedping.qciAddSyncedPingQci9->addItem("8");

            }


            //9

            if(viewAddSyncedping.qciAddSyncedPingQci1->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                viewAddSyncedping.qciAddSyncedPingQci1->addItem("9");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci2->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                viewAddSyncedping.qciAddSyncedPingQci2->addItem("9");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci3->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                viewAddSyncedping.qciAddSyncedPingQci3->addItem("9");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci4->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                viewAddSyncedping.qciAddSyncedPingQci4->addItem("9");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci5->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                viewAddSyncedping.qciAddSyncedPingQci5->addItem("9");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci6->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                viewAddSyncedping.qciAddSyncedPingQci6->addItem("9");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci7->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                viewAddSyncedping.qciAddSyncedPingQci7->addItem("9");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci8->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                viewAddSyncedping.qciAddSyncedPingQci8->addItem("9");

            }
            if(viewAddSyncedping.qciAddSyncedPingQci9->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                viewAddSyncedping.qciAddSyncedPingQci9->addItem("9");

            }


    viewAddSyncedping.show();
}

void Custommodels::on_bt_add_ServiceReq_clicked()
{
    viewAddServicereq.close();
    viewAddServicereq.setWindowModality(Qt::WindowModal);
    viewAddServicereq.setParameters(addservicereq);

    //usuwanie uzywanych QCI
          //FTPDl
          if(viewAddFtpdl.qciAddFtpDlPointer->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText()) != (-1)){

             int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
             int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
             int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
             int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
             int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
             int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
             int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
             int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());
             int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddFtpdl.qciAddFtpDlPointer->currentText());


             viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
             viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
             viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
             viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
             viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
             viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
             viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
             viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
             viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);
          }
      //FtpUl
          if(viewAddFtpul.qciAddFtpUlPointer->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddFtpul.qciAddFtpUlPointer->currentText()) != (-1)){

              int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
              int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
              int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
              int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
              int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
              int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
              int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
              int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());
              int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddFtpul.qciAddFtpUlPointer->currentText());


              viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
              viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
              viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
              viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
              viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
              viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
              viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
              viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
              viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);

          }
      //Voip
          if(viewAddVoip.qciAddVoipPointer->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddVoip.qciAddVoipPointer->currentText()) != (-1)){

              int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddVoip.qciAddVoipPointer->currentText());
              int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddVoip.qciAddVoipPointer->currentText());
              int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddVoip.qciAddVoipPointer->currentText());
              int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddVoip.qciAddVoipPointer->currentText());
              int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddVoip.qciAddVoipPointer->currentText());
              int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddVoip.qciAddVoipPointer->currentText());
              int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddVoip.qciAddVoipPointer->currentText());
              int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddVoip.qciAddVoipPointer->currentText());
              int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddVoip.qciAddVoipPointer->currentText());


              viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
              viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
              viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
              viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
              viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
              viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
              viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
              viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
              viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);

          }
      //streamUl
          if(viewAddStreamul.qciAddStreamUlPointer->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddStreamul.qciAddStreamUlPointer->currentText()) != (-1)){

              int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
              int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
              int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
              int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
              int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
              int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
              int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
              int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());
              int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddStreamul.qciAddStreamUlPointer->currentText());


              viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
              viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
              viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
              viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
              viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
              viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
              viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
              viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
              viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);

          }
      //stremDl
          if(viewAddStreamdl.qciAddStreamDlPointer->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText()) != (-1)){

              int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
              int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
              int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
              int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
              int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
              int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
              int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
              int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());
              int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddStreamdl.qciAddStreamDlPointer->currentText());


              viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
              viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
              viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
              viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
              viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
              viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
              viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
              viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
              viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);


          }

       //AddPing
          if(viewAddPing.qciAddpingPointer->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddPing.qciAddpingPointer->currentText()) != (-1)){

              int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddPing.qciAddpingPointer->currentText());
              int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddPing.qciAddpingPointer->currentText());
              int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddPing.qciAddpingPointer->currentText());
              int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddPing.qciAddpingPointer->currentText());
              int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddPing.qciAddpingPointer->currentText());
              int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddPing.qciAddpingPointer->currentText());
              int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddPing.qciAddpingPointer->currentText());
              int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddPing.qciAddpingPointer->currentText());
              int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddPing.qciAddpingPointer->currentText());


              viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
              viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
              viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
              viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
              viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
              viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
              viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
              viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
              viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);


          }

          //AddSyncPing

          //QCI1
          if(viewAddSyncedping.qciAddSyncedPingQci1->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci1->currentText()) != (-1)){

              int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci1->currentText());
              int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddSyncedping.qciAddSyncedPingQci1->currentText());
              int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddSyncedping.qciAddSyncedPingQci1->currentText());
              int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddSyncedping.qciAddSyncedPingQci1->currentText());
              int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddSyncedping.qciAddSyncedPingQci1->currentText());
              int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddSyncedping.qciAddSyncedPingQci1->currentText());
              int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddSyncedping.qciAddSyncedPingQci1->currentText());
              int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddSyncedping.qciAddSyncedPingQci1->currentText());
              int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddSyncedping.qciAddSyncedPingQci1->currentText());


              viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
              viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
              viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
              viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
              viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
              viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
              viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
              viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
              viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);


          }

          //Qci2
          if(viewAddSyncedping.qciAddSyncedPingQci2->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci2->currentText()) != (-1)){

              int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci2->currentText());
              int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddSyncedping.qciAddSyncedPingQci2->currentText());
              int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddSyncedping.qciAddSyncedPingQci2->currentText());
              int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddSyncedping.qciAddSyncedPingQci2->currentText());
              int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddSyncedping.qciAddSyncedPingQci2->currentText());
              int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddSyncedping.qciAddSyncedPingQci2->currentText());
              int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddSyncedping.qciAddSyncedPingQci2->currentText());
              int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddSyncedping.qciAddSyncedPingQci2->currentText());
              int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddSyncedping.qciAddSyncedPingQci2->currentText());


              viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
              viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
              viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
              viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
              viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
              viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
              viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
              viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
              viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);


          }

          //Qci3
          if(viewAddSyncedping.qciAddSyncedPingQci3->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci3->currentText()) != (-1)){

              int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci3->currentText());
              int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddSyncedping.qciAddSyncedPingQci3->currentText());
              int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddSyncedping.qciAddSyncedPingQci3->currentText());
              int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddSyncedping.qciAddSyncedPingQci3->currentText());
              int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddSyncedping.qciAddSyncedPingQci3->currentText());
              int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddSyncedping.qciAddSyncedPingQci3->currentText());
              int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddSyncedping.qciAddSyncedPingQci3->currentText());
              int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddSyncedping.qciAddSyncedPingQci3->currentText());
              int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddSyncedping.qciAddSyncedPingQci3->currentText());


              viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
              viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
              viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
              viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
              viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
              viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
              viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
              viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
              viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);


          }

          //Qci4
          if(viewAddSyncedping.qciAddSyncedPingQci4->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci4->currentText()) != (-1)){

              int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci4->currentText());
              int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddSyncedping.qciAddSyncedPingQci4->currentText());
              int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddSyncedping.qciAddSyncedPingQci4->currentText());
              int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddSyncedping.qciAddSyncedPingQci4->currentText());
              int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddSyncedping.qciAddSyncedPingQci4->currentText());
              int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddSyncedping.qciAddSyncedPingQci4->currentText());
              int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddSyncedping.qciAddSyncedPingQci4->currentText());
              int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddSyncedping.qciAddSyncedPingQci4->currentText());
              int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddSyncedping.qciAddSyncedPingQci4->currentText());


              viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
              viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
              viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
              viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
              viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
              viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
              viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
              viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
              viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);


          }

          //Qci5
          if(viewAddSyncedping.qciAddSyncedPingQci5->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci5->currentText()) != (-1)){

              int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci5->currentText());
              int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddSyncedping.qciAddSyncedPingQci5->currentText());
              int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddSyncedping.qciAddSyncedPingQci5->currentText());
              int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddSyncedping.qciAddSyncedPingQci5->currentText());
              int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddSyncedping.qciAddSyncedPingQci5->currentText());
              int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddSyncedping.qciAddSyncedPingQci5->currentText());
              int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddSyncedping.qciAddSyncedPingQci5->currentText());
              int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddSyncedping.qciAddSyncedPingQci5->currentText());
              int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddSyncedping.qciAddSyncedPingQci5->currentText());


              viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
              viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
              viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
              viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
              viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
              viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
              viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
              viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
              viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);


          }

          //Qci6
          if(viewAddSyncedping.qciAddSyncedPingQci6->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci6->currentText()) != (-1)){

              int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci6->currentText());
              int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddSyncedping.qciAddSyncedPingQci6->currentText());
              int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddSyncedping.qciAddSyncedPingQci6->currentText());
              int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddSyncedping.qciAddSyncedPingQci6->currentText());
              int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddSyncedping.qciAddSyncedPingQci6->currentText());
              int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddSyncedping.qciAddSyncedPingQci6->currentText());
              int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddSyncedping.qciAddSyncedPingQci6->currentText());
              int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddSyncedping.qciAddSyncedPingQci6->currentText());
              int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddSyncedping.qciAddSyncedPingQci6->currentText());


              viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
              viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
              viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
              viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
              viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
              viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
              viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
              viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
              viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);


          }

          //Qci7
          if(viewAddSyncedping.qciAddSyncedPingQci7->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci7->currentText()) != (-1)){

              int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci7->currentText());
              int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddSyncedping.qciAddSyncedPingQci7->currentText());
              int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddSyncedping.qciAddSyncedPingQci7->currentText());
              int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddSyncedping.qciAddSyncedPingQci7->currentText());
              int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddSyncedping.qciAddSyncedPingQci7->currentText());
              int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddSyncedping.qciAddSyncedPingQci7->currentText());
              int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddSyncedping.qciAddSyncedPingQci7->currentText());
              int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddSyncedping.qciAddSyncedPingQci7->currentText());
              int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddSyncedping.qciAddSyncedPingQci7->currentText());


              viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
              viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
              viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
              viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
              viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
              viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
              viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
              viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
              viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);


          }

          //Qci8
          if(viewAddSyncedping.qciAddSyncedPingQci8->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci8->currentText()) != (-1)){

              int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci8->currentText());
              int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddSyncedping.qciAddSyncedPingQci8->currentText());
              int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddSyncedping.qciAddSyncedPingQci8->currentText());
              int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddSyncedping.qciAddSyncedPingQci8->currentText());
              int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddSyncedping.qciAddSyncedPingQci8->currentText());
              int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddSyncedping.qciAddSyncedPingQci8->currentText());
              int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddSyncedping.qciAddSyncedPingQci8->currentText());
              int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddSyncedping.qciAddSyncedPingQci8->currentText());
              int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddSyncedping.qciAddSyncedPingQci8->currentText());


              viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
              viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
              viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
              viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
              viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
              viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
              viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
              viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
              viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);


          }

          //Qci9
          if(viewAddSyncedping.qciAddSyncedPingQci9->currentText() != "" && viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci9->currentText()) != (-1)){

              int index = viewAddServicereq.qciAddServiceReqQci1->findText(viewAddSyncedping.qciAddSyncedPingQci9->currentText());
              int index2 = viewAddServicereq.qciAddServiceReqQci2->findText(viewAddSyncedping.qciAddSyncedPingQci9->currentText());
              int index3 = viewAddServicereq.qciAddServiceReqQci3->findText(viewAddSyncedping.qciAddSyncedPingQci9->currentText());
              int index4 = viewAddServicereq.qciAddServiceReqQci4->findText(viewAddSyncedping.qciAddSyncedPingQci9->currentText());
              int index5 = viewAddServicereq.qciAddServiceReqQci5->findText(viewAddSyncedping.qciAddSyncedPingQci9->currentText());
              int index6 = viewAddServicereq.qciAddServiceReqQci6->findText(viewAddSyncedping.qciAddSyncedPingQci9->currentText());
              int index7 = viewAddServicereq.qciAddServiceReqQci7->findText(viewAddSyncedping.qciAddSyncedPingQci9->currentText());
              int index8 = viewAddServicereq.qciAddServiceReqQci8->findText(viewAddSyncedping.qciAddSyncedPingQci9->currentText());
              int index9 = viewAddServicereq.qciAddServiceReqQci9->findText(viewAddSyncedping.qciAddSyncedPingQci9->currentText());


              viewAddServicereq.qciAddServiceReqQci1->removeItem(index);
              viewAddServicereq.qciAddServiceReqQci2->removeItem(index2);
              viewAddServicereq.qciAddServiceReqQci3->removeItem(index3);
              viewAddServicereq.qciAddServiceReqQci4->removeItem(index4);
              viewAddServicereq.qciAddServiceReqQci5->removeItem(index5);
              viewAddServicereq.qciAddServiceReqQci6->removeItem(index6);
              viewAddServicereq.qciAddServiceReqQci7->removeItem(index7);
              viewAddServicereq.qciAddServiceReqQci8->removeItem(index8);
              viewAddServicereq.qciAddServiceReqQci9->removeItem(index9);


          }


              //dodawanie niewykorzystywanych QCI
                  //1

                      if(viewAddServicereq.qciAddServiceReqQci1->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"){

                          viewAddServicereq.qciAddServiceReqQci1->addItem("1");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci2->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"){

                          viewAddServicereq.qciAddServiceReqQci2->addItem("1");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci3->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"){

                          viewAddServicereq.qciAddServiceReqQci3->addItem("1");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci4->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"){

                          viewAddServicereq.qciAddServiceReqQci4->addItem("1");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci5->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"){

                          viewAddServicereq.qciAddServiceReqQci5->addItem("1");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci6->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"){

                          viewAddServicereq.qciAddServiceReqQci6->addItem("1");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci7->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"){

                          viewAddServicereq.qciAddServiceReqQci7->addItem("1");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci8->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"){

                          viewAddServicereq.qciAddServiceReqQci8->addItem("1");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci9->findText("1") == -1 && viewAddPing.qciAddpingPointer->currentText() != "1" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "1" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "1" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "1" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "1" && viewAddVoip.qciAddVoipPointer->currentText() != "1"){

                          viewAddServicereq.qciAddServiceReqQci9->addItem("1");

                      }

                      //2

                      if(viewAddServicereq.qciAddServiceReqQci1->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                          viewAddServicereq.qciAddServiceReqQci1->addItem("2");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci2->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                          viewAddServicereq.qciAddServiceReqQci2->addItem("2");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci3->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                          viewAddServicereq.qciAddServiceReqQci3->addItem("2");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci4->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                          viewAddServicereq.qciAddServiceReqQci4->addItem("2");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci5->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                          viewAddServicereq.qciAddServiceReqQci5->addItem("2");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci6->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                          viewAddServicereq.qciAddServiceReqQci6->addItem("2");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci7->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                          viewAddServicereq.qciAddServiceReqQci7->addItem("2");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci8->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                          viewAddServicereq.qciAddServiceReqQci8->addItem("2");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci9->findText("2") == -1 && viewAddPing.qciAddpingPointer->currentText() != "2" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "2" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "2" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "2" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "2" && viewAddVoip.qciAddVoipPointer->currentText() != "2"){

                          viewAddServicereq.qciAddServiceReqQci9->addItem("2");

                      }


                      //3

                      if(viewAddServicereq.qciAddServiceReqQci1->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                          viewAddServicereq.qciAddServiceReqQci1->addItem("3");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci2->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                          viewAddServicereq.qciAddServiceReqQci2->addItem("3");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci3->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                          viewAddServicereq.qciAddServiceReqQci3->addItem("3");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci4->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                          viewAddServicereq.qciAddServiceReqQci4->addItem("3");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci5->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                          viewAddServicereq.qciAddServiceReqQci5->addItem("3");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci6->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                          viewAddServicereq.qciAddServiceReqQci6->addItem("3");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci7->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                          viewAddServicereq.qciAddServiceReqQci7->addItem("3");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci8->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                          viewAddServicereq.qciAddServiceReqQci8->addItem("3");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci9->findText("3") == -1 && viewAddPing.qciAddpingPointer->currentText() != "3" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "3" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "3" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "3" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "3" && viewAddVoip.qciAddVoipPointer->currentText() != "3"){

                          viewAddServicereq.qciAddServiceReqQci9->addItem("3");

                      }


                      //4

                      if(viewAddServicereq.qciAddServiceReqQci1->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                          viewAddServicereq.qciAddServiceReqQci1->addItem("4");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci2->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                          viewAddServicereq.qciAddServiceReqQci2->addItem("4");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci3->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                          viewAddServicereq.qciAddServiceReqQci3->addItem("4");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci4->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                          viewAddServicereq.qciAddServiceReqQci4->addItem("4");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci5->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                          viewAddServicereq.qciAddServiceReqQci5->addItem("4");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci6->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                          viewAddServicereq.qciAddServiceReqQci6->addItem("4");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci7->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                          viewAddServicereq.qciAddServiceReqQci7->addItem("4");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci8->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                          viewAddServicereq.qciAddServiceReqQci8->addItem("4");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci9->findText("4") == -1 && viewAddPing.qciAddpingPointer->currentText() != "4" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "4" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "4" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "4" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "4" && viewAddVoip.qciAddVoipPointer->currentText() != "4"){

                          viewAddServicereq.qciAddServiceReqQci9->addItem("4");

                      }


                      //5

                      if(viewAddServicereq.qciAddServiceReqQci1->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                          viewAddServicereq.qciAddServiceReqQci1->addItem("5");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci2->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                          viewAddServicereq.qciAddServiceReqQci2->addItem("5");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci3->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                          viewAddServicereq.qciAddServiceReqQci3->addItem("5");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci4->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                          viewAddServicereq.qciAddServiceReqQci4->addItem("5");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci5->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                          viewAddServicereq.qciAddServiceReqQci5->addItem("5");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci6->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                          viewAddServicereq.qciAddServiceReqQci6->addItem("5");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci7->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                          viewAddServicereq.qciAddServiceReqQci7->addItem("5");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci8->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                          viewAddServicereq.qciAddServiceReqQci8->addItem("5");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci9->findText("5") == -1 && viewAddPing.qciAddpingPointer->currentText() != "5" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "5" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "5" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "5" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "5" && viewAddVoip.qciAddVoipPointer->currentText() != "5"){

                          viewAddServicereq.qciAddServiceReqQci9->addItem("5");

                      }


                      //6

                      if(viewAddServicereq.qciAddServiceReqQci1->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                          viewAddServicereq.qciAddServiceReqQci1->addItem("6");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci2->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                          viewAddServicereq.qciAddServiceReqQci2->addItem("6");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci3->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                          viewAddServicereq.qciAddServiceReqQci3->addItem("6");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci4->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                          viewAddServicereq.qciAddServiceReqQci4->addItem("6");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci5->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                          viewAddServicereq.qciAddServiceReqQci5->addItem("6");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci6->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                          viewAddServicereq.qciAddServiceReqQci6->addItem("6");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci7->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                          viewAddServicereq.qciAddServiceReqQci7->addItem("6");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci8->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                          viewAddServicereq.qciAddServiceReqQci8->addItem("6");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci9->findText("6") == -1 && viewAddPing.qciAddpingPointer->currentText() != "6" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "6" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "6" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "6" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "6" && viewAddVoip.qciAddVoipPointer->currentText() != "6"){

                          viewAddServicereq.qciAddServiceReqQci9->addItem("6");

                      }


                      //7

                      if(viewAddServicereq.qciAddServiceReqQci1->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                          viewAddServicereq.qciAddServiceReqQci1->addItem("7");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci2->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                          viewAddServicereq.qciAddServiceReqQci2->addItem("7");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci3->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                          viewAddServicereq.qciAddServiceReqQci3->addItem("7");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci4->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                          viewAddServicereq.qciAddServiceReqQci4->addItem("7");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci5->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                          viewAddServicereq.qciAddServiceReqQci5->addItem("7");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci6->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                          viewAddServicereq.qciAddServiceReqQci6->addItem("7");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci7->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                          viewAddServicereq.qciAddServiceReqQci7->addItem("7");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci8->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                          viewAddServicereq.qciAddServiceReqQci8->addItem("7");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci9->findText("7") == -1 && viewAddPing.qciAddpingPointer->currentText() != "7" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "7" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "7" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "7" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "7" && viewAddVoip.qciAddVoipPointer->currentText() != "7"){

                          viewAddServicereq.qciAddServiceReqQci9->addItem("7");

                      }


                      //8

                      if(viewAddServicereq.qciAddServiceReqQci1->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                          viewAddServicereq.qciAddServiceReqQci1->addItem("8");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci2->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                          viewAddServicereq.qciAddServiceReqQci2->addItem("8");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci3->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                          viewAddServicereq.qciAddServiceReqQci3->addItem("8");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci4->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                          viewAddServicereq.qciAddServiceReqQci4->addItem("8");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci5->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                          viewAddServicereq.qciAddServiceReqQci5->addItem("8");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci6->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                          viewAddServicereq.qciAddServiceReqQci6->addItem("8");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci7->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                          viewAddServicereq.qciAddServiceReqQci7->addItem("8");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci8->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                          viewAddServicereq.qciAddServiceReqQci8->addItem("8");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci9->findText("8") == -1 && viewAddPing.qciAddpingPointer->currentText() != "8" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "8" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "8" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "8" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "8" && viewAddVoip.qciAddVoipPointer->currentText() != "8"){

                          viewAddServicereq.qciAddServiceReqQci9->addItem("8");

                      }


                      //9

                      if(viewAddServicereq.qciAddServiceReqQci1->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                          viewAddServicereq.qciAddServiceReqQci1->addItem("9");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci2->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                          viewAddServicereq.qciAddServiceReqQci2->addItem("9");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci3->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                          viewAddServicereq.qciAddServiceReqQci3->addItem("9");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci4->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                          viewAddServicereq.qciAddServiceReqQci4->addItem("9");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci5->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                          viewAddServicereq.qciAddServiceReqQci5->addItem("9");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci6->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                          viewAddServicereq.qciAddServiceReqQci6->addItem("9");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci7->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                          viewAddServicereq.qciAddServiceReqQci7->addItem("9");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci8->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                          viewAddServicereq.qciAddServiceReqQci8->addItem("9");

                      }
                      if(viewAddServicereq.qciAddServiceReqQci9->findText("9") == -1 && viewAddPing.qciAddpingPointer->currentText() != "9" && viewAddStreamul.qciAddStreamUlPointer->currentText() != "9" && viewAddFtpdl.qciAddFtpDlPointer->currentText() != "9" && viewAddFtpul.qciAddFtpUlPointer->currentText() != "9" && viewAddStreamdl.qciAddStreamDlPointer->currentText() != "9" && viewAddVoip.qciAddVoipPointer->currentText() != "9"){

                          viewAddServicereq.qciAddServiceReqQci9->addItem("9");

                      }


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
                CM1isActive = 1;
                save1 = true;
               pointer_CM1->setStyleSheet("QLabel { background-color : green; color : white; }");
               this->close();

           }

            if(CMname == "Custom Model 2"){
             //   large = false;
                CM_List.append(CMname);
                CM2isActive = 1;
                save2 = true;
               pointer_CM2->setStyleSheet("QLabel { background-color : green; color : white; }");
               this->close();
            }

            if(CMname == "Custom Model 3"){

               CM_List.append(CMname);
           //    large = false;
               CM3isActive = 1;
               save3 = true;
                pointer_CM3->setStyleSheet("QLabel { background-color : green; color : white; }");
                 this->close();
            }

            if(CMname == "Custom Model 4"){

                CM_List.append(CMname);
             //   large = false;
                CM3isActive = 1;
                save4 = true;
                pointer_CM4->setStyleSheet("QLabel { background-color : green; color : white; }");
                 this->close();
            }

            if(CMname == "Custom Model 5"){

                CM_List.append(CMname);
              //  large = false;
                CM5isActive = 1;
                save5 = true;
                pointer_CM5->setStyleSheet("QLabel { background-color : green; color : white; }");
                 this->close();
            }

            if(CMname == "Custom Model 6"){

                CM_List.append(CMname);
            //    large = false;
                CM6isActive = 1;
                save6 = true;
                pointer_CM6->setStyleSheet("QLabel { background-color : green; color : white; }");
                 this->close();
            }

            if(CMname == "Custom Model 7"){

               CM_List.append(CMname);
             //  large = false;
               CM7isActive = 1;
               save7 = true;
                pointer_CM7->setStyleSheet("QLabel { background-color : green; color : white; }");
                 this->close();
            }

            if(CMname == "Custom Model 8"){

                CM_List.append(CMname);
             //   large = false;
                CM8isActive = 1;
                save8 = true;
                pointer_CM8->setStyleSheet("QLabel { background-color : green; color : white; }");
                 this->close();
            }

            if(CMname == "Custom Model 9"){

                CM_List.append(CMname);
              //  large = false;
                CM9isActive = 1;
                save9 = true;
                pointer_CM9->setStyleSheet("QLabel { background-color : green; color : white; }");
                 this->close();
            }

            if(CMname == "Custom Model 10"){

                CM10isActive = 1;
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
                 CM1isActive = 1;
                pointer_CM1_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 2"){

                 CM_List.append(CMname_large);
                // large = true;
                 CM2isActive = 1;
                pointer_CM2_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 3"){

                 CM_List.append(CMname_large);
             //    large = true;
                 CM3isActive = 1;
                pointer_CM3_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 4"){

                 CM_List.append(CMname_large);
              //   large = true;
                 CM4isActive = 1;
                pointer_CM4_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 5"){

                 CM_List.append(CMname_large);
              //   large = true;
                 CM5isActive = 1;
                pointer_CM5_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 6"){

                 CM_List.append(CMname_large);
               //  large = true;
                 CM6isActive = 1;
                pointer_CM6_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 7"){

                 CM_List.append(CMname_large);
              //   large = true;
                 CM7isActive = 1;
                pointer_CM7_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 8"){

                 CM_List.append(CMname_large);
              //   large = true;
                 CM8isActive = 1;
                pointer_CM8_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 9"){

                 CM_List.append(CMname_large);
              //   large = true;
                 CM9isActive = 1;
                pointer_CM9_large->setStyleSheet("QLabel { background-color : green; color : white; }");

                this->close();

            }
            if(CMname_large == "Custom Model 10"){

                 CM_List.append(CMname_large);
               //  large = true;
                 CM10isActive = 1;
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
        if(curPS1 == CMname || curPS2 == CMname || curPS3 == CMname || curPS4 == CMname || curPS5 == CMname || curPS6 == CMname || curPS7 == CMname || curPS8 == CMname || curPS9 == CMname || curPS10 == CMname){

            QMessageBox::information(this, "Warning", "Custom Model is set as current PS Behavior Mode!\nYou can't delete this!!!\nRemove Custom Model firstly.", 1);

            setParameters();
        }

        else{

        if(CMname == "Custom Model 1"){

            pointer_CM1->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM_List.removeOne(CMname);
            CM1isActive = 0;
            save1 = false;
            this->close();
        }

        if(CMname == "Custom Model 2"){
            CM_List.removeOne(CMname);
            pointer_CM2->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM2isActive = 0;
            save2 = false;
             this->close();
        }

        if(CMname == "Custom Model 3"){
            CM_List.removeOne(CMname);
            CM3isActive = 0;
            pointer_CM3->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            save3 = false;
            this->close();
        }

        if(CMname == "Custom Model 4"){
            CM_List.removeOne(CMname);
            pointer_CM4->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM4isActive = 0;
            save4 = false;
            this->close();
        }

        if(CMname == "Custom Model 5"){
            CM_List.removeOne(CMname);
            pointer_CM5->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM5isActive = 0;
            save5 = false;
            this->close();
        }

        if(CMname == "Custom Model 6"){
            CM_List.removeOne(CMname);
            pointer_CM6->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM6isActive = 0;
            save6 = false;
            this->close();
        }

        if(CMname == "Custom Model 7"){
            CM_List.removeOne(CMname);
            pointer_CM7->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM7isActive = 0;
            save7 = false;
            this->close();
        }

        if(CMname == "Custom Model 8"){
            CM_List.removeOne(CMname);
            pointer_CM8->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM8isActive = 0;
            save8 = false;
            this->close();
        }

        if(CMname == "Custom Model 9"){
            CM_List.removeOne(CMname);
            pointer_CM9->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM9isActive = 0;
            save9 = false;
            this->close();
        }

        if(CMname == "Custom Model 10"){
            CM10isActive = 0;
            CM_List.removeOne(CMname);
            pointer_CM10->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            save10 = false;
            this->close();
             }
}
}
        //large
        if(large == true){

        if(curPS1 == CMname_large || curPS2 == CMname_large || curPS3 == CMname_large || curPS4 == CMname_large || curPS5 == CMname_large || curPS6 == CMname_large || curPS7 == CMname_large || curPS8 == CMname_large || curPS9 == CMname_large || curPS10 == CMname_large || curPS11 == CMname_large || curPS12 == CMname_large || curPS13 == CMname_large || curPS14 == CMname_large || curPS15 == CMname_large || curPS16 == CMname_large || curPS17 == CMname_large || curPS18 == CMname_large || curPS19 == CMname_large || curPS20 == CMname_large){

            QMessageBox::information(this, "Warning", "Custom Model is set as current PS Behavior Mode!\nYou can't delete this!!!\nRemove Custom Model firstly.", 1);

            setParameters();
        }
        else{

        if(CMname_large == "Custom Model 1"){

            pointer_CM1_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM_List.removeOne(CMname_large);
            CM1isActive = 0;
            this->close();
        }

        if(CMname_large == "Custom Model 2"){
            CM_List.removeOne(CMname_large);
            pointer_CM2_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM2isActive = 0;
             this->close();
        }

        if(CMname_large == "Custom Model 3"){
            CM_List.removeOne(CMname_large);
            CM3isActive = 0;
            pointer_CM3_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
             this->close();
        }

        if(CMname_large == "Custom Model 4"){
            CM_List.removeOne(CMname_large);
            pointer_CM4_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM4isActive = 0;
             this->close();
        }

        if(CMname_large == "Custom Model 5"){
            CM_List.removeOne(CMname_large);
            pointer_CM5_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM5isActive = 0;
             this->close();
        }

        if(CMname_large == "Custom Model 6"){
            CM_List.removeOne(CMname_large);
            pointer_CM6_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM6isActive = 0;
             this->close();
        }

        if(CMname_large == "Custom Model 7"){
            CM_List.removeOne(CMname_large);
            pointer_CM7_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM7isActive = 0;
             this->close();
        }

        if(CMname_large == "Custom Model 8"){
            CM_List.removeOne(CMname_large);
            pointer_CM8_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM8isActive = 0;
             this->close();
        }

        if(CMname_large == "Custom Model 9"){
            CM_List.removeOne(CMname_large);
            pointer_CM9_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
            CM9isActive = 0;
             this->close();
        }

        if(CMname_large == "Custom Model 10"){
            CM10isActive = 0;
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
            CM1isActive = 1;
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
             CM2isActive = 1;
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
             CM3isActive = 1;
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
             CM4isActive = 1;
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
             CM5isActive = 1;
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
             CM6isActive = 1;
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
             CM7isActive = 1;
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
             CM8isActive = 1;
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
             CM9isActive = 1;
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
             CM10isActive = 1;
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
             CM1isActive = 1;


         }
     }

      if(CMname_large == "Custom Model 2"){

          if(pointer_CM2_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

              CM_List.append(CMname_large);
              CM2isActive = 1;


          }
      }

      if(CMname_large == "Custom Model 3"){

          if(pointer_CM3_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

              CM_List.append(CMname_large);
              CM3isActive = 1;


          }
      }

      if(CMname_large == "Custom Model 4"){
          if(pointer_CM4_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

              CM_List.append(CMname_large);
              CM4isActive = 1;


          }
      }

      if(CMname_large == "Custom Model 5"){

          if(pointer_CM5_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

              CM_List.append(CMname_large);
              CM5isActive = 1;


          }
      }

      if(CMname_large == "Custom Model 6"){
          if(pointer_CM6_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

              CM_List.append(CMname_large);
              CM6isActive = 1;


          }
      }

      if(CMname_large == "Custom Model 7"){
          if(pointer_CM7_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

              CM_List.append(CMname_large);
              CM7isActive = 1;


          }
      }

      if(CMname_large == "Custom Model 8"){
          if(pointer_CM8_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

              CM_List.append(CMname_large);
              CM8isActive = 1;


          }
      }

      if(CMname_large == "Custom Model 9"){
          if(pointer_CM9_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

              CM_List.append(CMname_large);
              CM9isActive = 1;


          }
      }

      if(CMname_large == "Custom Model 10"){
          if(pointer_CM10_large->styleSheet() == "QLabel { background-color : green; color : white; }"){

              CM_List.append(CMname_large);
              CM10isActive = 1;


          }
      }

    }
}

void Custommodels::on_bt_restore_clicked()
{

    restoreClicked = true;

    if(small == true){
    if(curPS1 == CMname || curPS2 == CMname || curPS3 == CMname || curPS4 == CMname || curPS5 == CMname || curPS6 == CMname || curPS7 == CMname || curPS8 == CMname || curPS9 == CMname || curPS10 == CMname){

        QMessageBox::information(this, "Warning", "Custom Model is set as current PS Behavior Mode!\nYou can't delete this!!!\nRemove Custom Model firstly.", 1);

       setParameters();

    }


    else{

        startParameter();



    if(CMname == "Custom Model 1"){
        CM_List.removeOne(CMname);
        CM1isActive = 0;
        pointer_CM1->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
        readyListCM1.clear();


    }

    if(CMname == "Custom Model 2"){
        CM_List.removeOne(CMname);
        CM2isActive = 0;
        pointer_CM2->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
       readyListCM2.clear();

    }

    if(CMname == "Custom Model 3"){
        CM_List.removeOne(CMname);
        CM3isActive = 0;
        pointer_CM3->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
        readyListCM3.clear();

    }

    if(CMname == "Custom Model 4"){
        CM_List.removeOne(CMname);
        CM4isActive = 0;
        pointer_CM4->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
        readyListCM4.clear();
    }

    if(CMname == "Custom Model 5"){
        CM_List.removeOne(CMname);
        CM5isActive = 0;
        pointer_CM5->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
        readyListCM5.clear();
    }

    if(CMname == "Custom Model 6"){
        CM_List.removeOne(CMname);
        CM6isActive = 0;
        pointer_CM6->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
        readyListCM6.clear();
    }

    if(CMname == "Custom Model 7"){
        CM_List.removeOne(CMname);
        CM7isActive = 0;
        pointer_CM7->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
        readyListCM7.clear();
    }

    if(CMname == "Custom Model 8"){
        CM_List.removeOne(CMname);
        CM8isActive = 0;
        pointer_CM8->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
        readyListCM8.clear();
    }

    if(CMname == "Custom Model 9"){
        CM_List.removeOne(CMname);
        CM9isActive = 0;
        pointer_CM9->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
        readyListCM9.clear();
    }

    if(CMname == "Custom Model 10"){
        CM_List.removeOne(CMname);
        CM10isActive = 0;
        pointer_CM10->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");
        readyListCM10.clear();
        }
    }
}


    //large

    if(large == true){
         if(curPS1 == CMname_large || curPS2 == CMname_large || curPS3 == CMname_large || curPS4 == CMname_large || curPS5 == CMname_large || curPS6 == CMname_large || curPS7 == CMname_large || curPS8 == CMname_large || curPS9 == CMname_large || curPS10 == CMname_large || curPS11 == CMname_large || curPS12 == CMname_large || curPS13 == CMname_large || curPS14 == CMname_large || curPS15 == CMname_large || curPS16 == CMname_large || curPS17 == CMname_large || curPS18 == CMname_large || curPS19 == CMname_large || curPS20 == CMname_large){

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
        CM1isActive = 0;
        pointer_CM1_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");

    }

    if(CMname_large == "Custom Model 2"){
        CM_List.removeOne(CMname_large);
        CM2isActive = 0;
        pointer_CM2_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");

    }

    if(CMname_large == "Custom Model 3"){
        CM_List.removeOne(CMname_large);
        CM3isActive = 0;
        pointer_CM3_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");

    }

    if(CMname_large == "Custom Model 4"){
        CM_List.removeOne(CMname_large);
        CM4isActive = 0;
        pointer_CM4_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");

    }

    if(CMname_large == "Custom Model 5"){
        CM_List.removeOne(CMname_large);
        CM5isActive = 0;
        pointer_CM5_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");

    }

    if(CMname_large == "Custom Model 6"){
        CM_List.removeOne(CMname_large);
        CM6isActive = 0;
        pointer_CM6_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");

    }

    if(CMname_large == "Custom Model 7"){
        CM_List.removeOne(CMname_large);
        CM7isActive = 0;
        pointer_CM7_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");

    }

    if(CMname_large == "Custom Model 8"){
        CM_List.removeOne(CMname_large);
        CM8isActive = 0;
        pointer_CM8_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");

    }

    if(CMname_large == "Custom Model 9"){
        CM_List.removeOne(CMname_large);
        CM9isActive = 0;
        pointer_CM9_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");

    }

    if(CMname == "Custom Model 10"){
        CM_List.removeOne(CMname_large);
        CM10isActive = 0;
        pointer_CM10_large->setStyleSheet("QLabel { background-color : rgb(193, 193, 193); }");

        }
      }
    }
  }

void Custommodels::saveColor(){

    if(small == true){
     CM1Style = pointer_CM1->styleSheet();
     CM2Style = pointer_CM2->styleSheet();
     CM3Style = pointer_CM3->styleSheet();
     CM4Style = pointer_CM4->styleSheet();
     CM5Style = pointer_CM5->styleSheet();
     CM6Style = pointer_CM6->styleSheet();
     CM7Style = pointer_CM7->styleSheet();
     CM8Style = pointer_CM8->styleSheet();
     CM9Style = pointer_CM9->styleSheet();
     CM10Style = pointer_CM10->styleSheet();
    }

    if(large == true){
      CM1Style_large = pointer_CM1_large->styleSheet();
      CM2Style_large = pointer_CM2_large->styleSheet();
      CM3Style_large = pointer_CM3_large->styleSheet();
      CM4Style_large = pointer_CM4_large->styleSheet();
      CM5Style_large = pointer_CM5_large->styleSheet();
      CM6Style_large = pointer_CM6_large->styleSheet();
      CM7Style_large = pointer_CM7_large->styleSheet();
      CM8Style_large = pointer_CM8_large->styleSheet();
      CM9Style_large = pointer_CM9_large->styleSheet();
      CM10Style_large = pointer_CM10_large->styleSheet();
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


//    if(large == true){
//    pointer_CM1_large->setStyleSheet(CM1Style_large);
//    pointer_CM2_large->setStyleSheet(CM2Style_large);
//    pointer_CM3_large->setStyleSheet(CM3Style_large);
//    pointer_CM4_large->setStyleSheet(CM4Style_large);
//    pointer_CM5_large->setStyleSheet(CM5Style_large);
//    pointer_CM6_large->setStyleSheet(CM6Style_large);
//    pointer_CM7_large->setStyleSheet(CM7Style_large);
//    pointer_CM8_large->setStyleSheet(CM8Style_large);
//    pointer_CM9_large->setStyleSheet(CM9Style_large);
//    pointer_CM10_large->setStyleSheet(CM10Style_large);
//    }


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



    qDebug() <<"CM1_List";
    qDebug() <<CM1_List;
    qDebug() <<"CM2_List";
    qDebug() <<CM2_List;
    qDebug() <<"ready CM1";
    qDebug() <<readyListCM1;
    qDebug() <<"ready CM2";
    qDebug() <<readyListCM2;
    qDebug() <<"custommodel FINAL";
    qDebug() <<customModelList;
    }

    if(large == true){
        //zrobic adekwatnie
    }


}

bool Custommodels::toBool(QString value){
        bool b;
        qDebug() <<"Value"<<value;
    if(value == "1"){
         b = true;
           qDebug() <<"b po true "<<b;
    }
    else{
         b = false;
           qDebug() <<"b po false "<<b;
    }
    return b;
    qDebug() <<"b"<<b;

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
