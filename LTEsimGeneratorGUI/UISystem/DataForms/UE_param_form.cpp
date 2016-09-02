#include "UE_param_form.h"
#include "ui_UE_param_form.h"

#include <QMessageBox>
#include <QSettings>

QStringList PS_List;
QString curPS[20];
QString lastCS;
QString lastPS;
QString lastMM;
QString lastTet;
QString lastUE;
int lastSpin;
bool wasClicked;

int Form::uePairsCount = 0;

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setFixedSize(sizeHint());
    area1 = ui->tet_Area1;
    combo = new QComboBox();
    accept = false;
    tempPairsCount = 0;

    pointerPS = ui->PSBehaviorMode1;
        pointerWinTitle = window();

        PS_List  <<  "NoPS"
                 <<  "general_10s_50Mbps"
                 <<  "general_infinite_200Mbps"
                 <<  "LteFtpEightBearers"
                 <<  "Use LtePing instead"
                 <<  "LtePing"
                 <<  "LtePingFtpOnDefault"
                 <<  "LtePingFtpDlOnDefault"
                 <<  "LtePingFtpUlOnDefault"
                 <<  "LteFtpGet"
                 <<  "LteFtpPut"
                 <<  "LteInstantMsgOrig"
                 <<  "LteInstantMsgOrig2Pdn"
                 <<  "LteInstantMsgTerm"
                 <<  "LteInstantMsgTerm2Pdn"
                 <<  "LteMobileTv"
                 <<  "LteP2P"
                 <<  "LteP2P2Pdn"
                 <<  "LtePDStreaming"
                 <<  "LtePDStreaming2Pdn"
                 <<  "LteRealTimeStreaming"
                 <<  "LteRealTimeStreaming2Pdn"
                 <<  "LteRealTimeStreamingDynS"
                 <<  "peed"
                 <<  "LteServiceReq"
                 <<  "LteWww"
                 <<  "LteWww2Pdn"
                 <<  "LteBatRealTimeStreaming"
                 <<  "LteBatRealTimeStreamingDLUL"
                 <<  "LteBatPDStreaming"
                 <<  "LteBatWww"
                 <<  "LteBatInstantMessaging"
                 <<  "LteBatP2P"
                 <<  "LteBatPing"
                 <<  "LteBatMobileTv"
                 <<  "LteMMTelAudioVisualOrig2Pdn"
                 <<  "LteMMTelAudioVisualOrig2Pdn50"
                 <<  "LteMMTelAudioVisualTerm2Pdn"
                 <<  "LteMMTelAudioVisualTerm2Pdn50"
                 <<  "LteMMTelStaticBearerPingOnDefault"
                 <<  "LteMMTelStaticBearerFtpDlOnDefault"
                 <<  "LteMMTelDynamicBearerPingOnDefault"
                 <<  "LteMMTelVoip"
                 <<  "LteMMTelVoip50"
                 <<  "LteMMTelVoip2Pdn50"
                 <<  "LteMMTelVoipTerm"
                 <<  "LteMMTelVoipTerm50"
                 <<  "LteMMTelVoipTerm2Pdn50";
}

Form::~Form(){delete ui;}

QString Form::get_currentCSBehavior() {return ui->CSBehaviorMode1->currentText();}
QString Form::get_currentPSBehavior(){return ui->PSBehaviorMode1->currentText();}
QString Form::get_currentArea(){return ui->tet_Area1->text();}
int Form::getUEPairs(){return uePairsCount;}
bool Form::is_Accepted(){return accept;}
void Form::getAllValues(){
  lastCS =  ui->CSBehaviorMode1->currentText();
  lastPS = ui->PSBehaviorMode1->currentText();
  lastMM = ui->MobilityModel1->currentText();
  lastSpin =  ui->spinBox->value();
  lastTet = ui->tet_Area1->text();
  lastUE = ui->UEType1->currentText();
}

void Form::set_currentArea(QString value){ui->tet_Area1->setText(value);}

void Form::resetUEPairsCount(){uePairsCount = 0;}
void Form::resetAccept(){accept = false;}

void Form::countUEPairs()
{
    if (ui->spinBox->value() != 0)
    {
       if (ui->spinBox->value() != tempPairsCount)
       {
           uePairsCount -= tempPairsCount;
           uePairsCount += ui->spinBox->value();
           tempPairsCount = ui->spinBox->value();
       }
    }
}

void Form::on_buttonBox_accepted()
{
    wasClicked = true;
    for(unsigned i=0;i<20;i++)
        if(windowTitle() == (QString("UE Params ") + QString(i)))
            curPS[i] = ui->PSBehaviorMode1->currentText();
    getAllValues();
    accept = true;
    countUEPairs();
    if (getUEPairs() > 1000)
        QMessageBox::information(this, "Warning", "Amout of UE Pairs exceeded 1000.\nFor better optimalization adjust attach/detach rate in Traffic Duration Dialog", QMessageBox::Ok);
    close();
}

void Form::on_buttonBox_rejected()
{
    accept = false;
    ui->CSBehaviorMode1->setCurrentText(lastCS);
    ui->PSBehaviorMode1->setCurrentText(lastPS);
    ui->MobilityModel1->setCurrentText(lastMM);
    ui->spinBox->setValue(lastSpin);
    ui->tet_Area1->setText(lastTet);
    ui->UEType1->setCurrentText(lastUE);
    close();
    //jakieś odrzucenie zmian
}
