#include "UE_param_form.h"
#include "ui_UE_param_form.h"

#include <QMessageBox>
#include <QSettings>

QString curPS1;
QString curPS2;
QString curPS3;
QString curPS4;
QString curPS5;
QString curPS6;
QString curPS7;
QString curPS8;
QString curPS9;
QString curPS10;
QString curPS11;
QString curPS12;
QString curPS13;
QString curPS14;
QString curPS15;
QString curPS16;
QString curPS17;
QString curPS18;
QString curPS19;
QString curPS20;

QString lastCS;
QString lastPS;
QString lastMM;
int lastSpin;
QString lastTet;
QString lastUE;
bool wasClicked;

QStringList PS_List;

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
        pointerWinTitle_large = window();

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

Form::~Form()
{
    delete ui;
}

void Form::on_buttonBox_accepted()
{
    wasClicked = true;

        if(windowTitle() == "UE Params 1"){

            curPS1 = ui->PSBehaviorMode1->currentText();
        }

        if(windowTitle() == "UE Params 2"){

            curPS2 = ui->PSBehaviorMode1->currentText();
        }

        if(windowTitle() == "UE Params 3"){

            curPS3 = ui->PSBehaviorMode1->currentText();
        }

        if(windowTitle() == "UE Params 4"){

            curPS4 = ui->PSBehaviorMode1->currentText();
        }

        if(windowTitle() == "UE Params 5"){

            curPS5 = ui->PSBehaviorMode1->currentText();
        }

        if(windowTitle() == "UE Params 6"){

            curPS6 = ui->PSBehaviorMode1->currentText();
        }

        if(windowTitle() == "UE Params 7"){

            curPS7 = ui->PSBehaviorMode1->currentText();
        }

        if(windowTitle() == "UE Params 8"){

            curPS8 = ui->PSBehaviorMode1->currentText();
        }

        if(windowTitle() == "UE Params 9"){

            curPS9 = ui->PSBehaviorMode1->currentText();
        }

        if(windowTitle() == "UE Params 10"){

            curPS10 = ui->PSBehaviorMode1->currentText();
        }

        if(windowTitle() == "UE Params 11"){

            curPS11 = ui->PSBehaviorMode1->currentText();

        }
        if(windowTitle() == "UE Params 12"){

            curPS12 = ui->PSBehaviorMode1->currentText();

        }
        if(windowTitle() == "UE Params 13"){

            curPS13 = ui->PSBehaviorMode1->currentText();

        }
        if(windowTitle() == "UE Params 14"){

            curPS14 = ui->PSBehaviorMode1->currentText();

        }
        if(windowTitle() == "UE Params 15"){

            curPS15 = ui->PSBehaviorMode1->currentText();

        }
        if(windowTitle() == "UE Params 16"){

            curPS16 = ui->PSBehaviorMode1->currentText();

        }
        if(windowTitle() == "UE Params 17"){

            curPS17 = ui->PSBehaviorMode1->currentText();

        }
        if(windowTitle() == "UE Params 18"){

            curPS18 = ui->PSBehaviorMode1->currentText();

        }
        if(windowTitle() == "UE Params 19"){

            curPS19 = ui->PSBehaviorMode1->currentText();

        }
        if(windowTitle() == "UE Params 20"){

            curPS20 = ui->PSBehaviorMode1->currentText();

        }

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


QString Form::get_currentCSBehavior()
{
    return ui->CSBehaviorMode1->currentText();
}

QString Form::get_currentPSBehavior()
{
    return ui->PSBehaviorMode1->currentText();
}
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

int Form::getUEPairs()
{
    return uePairsCount;
}

void Form::resetUEPairsCount()
{
    uePairsCount = 0;
}


void Form::resetAccept()
{
    accept = false;
}

QString Form::get_currentArea()
{
    return ui->tet_Area1->text();
}

void Form::set_currentArea(QString value)
{
    ui->tet_Area1->setText(value);
}

bool Form::is_Accepted()
{
    return accept;
}

void Form::getAllValues(){

  lastCS =  ui->CSBehaviorMode1->currentText();
  lastPS = ui->PSBehaviorMode1->currentText();
  lastMM = ui->MobilityModel1->currentText();
  lastSpin =  ui->spinBox->value();
  lastTet = ui->tet_Area1->text();
  lastUE = ui->UEType1->currentText();
}
