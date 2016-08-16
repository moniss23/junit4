#include "customModel.h"
#include "ui_customModel.h"

#define SyncedPingComboBoxOffset 6
#define ServiceReqComboBoxOffset 15


customModel::customModel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::customModel)
{
    ui->setupUi(this);

    for(auto &primaryQciUsed:qciUsed)
        primaryQciUsed=false;

    comboBoxForQci[0]=ui->comboBoxPingQci;
    comboBoxForQci[1]=ui->comboBoxVoipQci;
    comboBoxForQci[2]=ui->comboBoxFTPDlQci;
    comboBoxForQci[3]=ui->comboBoxFTPUlQci;
    comboBoxForQci[4]=ui->comboBoxStreamDlQci;
    comboBoxForQci[5]=ui->comboBoxStreamUlQci;
    comboBoxForQci[6]=ui->comboBoxSyncedPingQci1;
    comboBoxForQci[7]=ui->comboBoxSyncedPingQci2;
    comboBoxForQci[8]=ui->comboBoxSyncedPingQci3;
    comboBoxForQci[9]=ui->comboBoxSyncedPingQci4;
    comboBoxForQci[10]=ui->comboBoxSyncedPingQci5;
    comboBoxForQci[11]=ui->comboBoxSyncedPingQci6;
    comboBoxForQci[12]=ui->comboBoxSyncedPingQci7;
    comboBoxForQci[13]=ui->comboBoxSyncedPingQci8;
    comboBoxForQci[14]=ui->comboBoxSyncedPingQci9;
    comboBoxForQci[15]=ui->comboBoxServiceReqQci1;
    comboBoxForQci[16]=ui->comboBoxServiceReqQci2;
    comboBoxForQci[17]=ui->comboBoxServiceReqQci3;
    comboBoxForQci[18]=ui->comboBoxServiceReqQci4;
    comboBoxForQci[19]=ui->comboBoxServiceReqQci5;
    comboBoxForQci[20]=ui->comboBoxServiceReqQci6;
    comboBoxForQci[21]=ui->comboBoxServiceReqQci7;
    comboBoxForQci[22]=ui->comboBoxServiceReqQci8;
    comboBoxForQci[23]=ui->comboBoxServiceReqQci9;

    //pointer used in setParameters and saveCustomModel
    pointercomboBoxForQciSyncedPing=&comboBoxForQci[SyncedPingComboBoxOffset];

    //pointer used in setParameters and saveCustomModel
    pointercomboBoxForQciServiceReq=&comboBoxForQci[ServiceReqComboBoxOffset];

    //pointers used in refreshQci
    QciCurrentText[0]=&(CMPingParams.currentQciTextPing);
    QciCurrentText[1]=&(CMVoipParams.currentQciTextVoip);
    QciCurrentText[2]=&(CMFtpDlParams.currentQciTextFtpDl);
    QciCurrentText[3]=&(CMFtpUlParams.currentQciTextFtpUl);
    QciCurrentText[4]=&(CMStreamDlParams.currentQciTextStreamDl);
    QciCurrentText[5]=&(CMStreamUlParams.currentQciTextStreamUl);
    for(unsigned i=0;i<AmountOfQci;i++)
        QciCurrentText[i+SyncedPingComboBoxOffset]=&(CMSyncedPingParams.currentQciTextSyncedPing[i]);
    for(unsigned i=0;i<AmountOfQci;i++)
        QciCurrentText[i+ServiceReqComboBoxOffset]=&(CMServiceReqParams.currentQciTextServiceReq[i]);

    ui->lineEditPingInterval->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->lineEditPingNumberOfPings->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->lineEditPingMinReceivedPings->setValidator(new QIntValidator(0, INT_MAX, this));

    ui->lineEditVoipActivityFactor->setValidator(new QIntValidator(0, 100, this));
    ui->lineEditVoipDuration->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->lineEditVoipMaxTransferTime->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->lineEditVoipMinPacketsReceivedInTime->setValidator(new QIntValidator(0, 100, this));

    ui->lineEditFTPDlFilesize->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->lineEditFTPDlMinThroughput->setValidator(new QIntValidator(0, INT_MAX, this));

    ui->lineEditFTPUlFilesize->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->lineEditFTPUlMinThroughput->setValidator(new QIntValidator(0, INT_MAX, this));

    ui->lineEditStreamDlDuration->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->lineEditStreamDlMinThroughput->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->lineEditStreamDlSpeed->setValidator(new QIntValidator(0, INT_MAX, this));

    ui->lineEditStreamUlDuration->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->lineEditStreamUlMinThroughput->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->lineEditStreamUlSpeed->setValidator(new QIntValidator(0, INT_MAX, this));

    ui->lineEditSyncedPingInterval->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->lineEditSyncedPingMinReceivedPings->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->lineEditSyncedPingNumberOfPings->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->lineEditSyncedPingTimeBetweenTasks->setValidator(new QIntValidator(0, INT_MAX, this));

    ui->lineEditServiceReqIntervalBetweenUIData->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->lineEditServiceReqTimeToWaitForAttach->setValidator(new QIntValidator(0, INT_MAX, this));

    on_saveCustomModelButton_clicked();
}

customModel::~customModel()
{
    delete ui;
}

void customModel::set_custom_name(QString name)
{
    this->name = name;
}

void customModel::on_checkBoxPing_clicked()
{
    bool isPingActive=ui->checkBoxPing->isChecked();
    comboBoxForQci[0]->setEnabled(isPingActive);
    ui->lineEditPingNumberOfPings->setEnabled(isPingActive);
    ui->lineEditPingInterval->setEnabled(isPingActive);
    ui->lineEditPingMinReceivedPings->setEnabled(isPingActive);
}

void customModel::on_checkBoxVoip_clicked()
{
    bool isVoipActive=ui->checkBoxVoip->isChecked();
    ui->comboBoxVoipQci->setEnabled(isVoipActive);
    ui->lineEditVoipActivityFactor->setEnabled(isVoipActive);
    ui->lineEditVoipDuration->setEnabled(isVoipActive);
    ui->lineEditVoipMaxTransferTime->setEnabled(isVoipActive);
    ui->lineEditVoipMinPacketsReceivedInTime->setEnabled(isVoipActive);
}

void customModel::on_checkBoxFTPDl_clicked()
{
    bool isFTPDlActive=ui->checkBoxFTPDl->isChecked();
    ui->comboBoxFTPDlQci->setEnabled(isFTPDlActive);
    ui->lineEditFTPDlFilesize->setEnabled(isFTPDlActive);
    ui->lineEditFTPDlMinThroughput->setEnabled(isFTPDlActive);
}

void customModel::on_checkBoxFTPUl_clicked()
{
    bool isFTPUlActive=ui->checkBoxFTPUl->isChecked();
    ui->comboBoxFTPUlQci->setEnabled(isFTPUlActive);
    ui->lineEditFTPUlFilesize->setEnabled(isFTPUlActive);
    ui->lineEditFTPUlMinThroughput->setEnabled(isFTPUlActive);
}

void customModel::on_checkBoxStreamDl_clicked()
{
    bool isStreamDlActive=ui->checkBoxStreamDl->isChecked();
    ui->comboBoxStreamDlQci->setEnabled(isStreamDlActive);
    ui->lineEditStreamDlDuration->setEnabled(isStreamDlActive);
    ui->lineEditStreamDlMinThroughput->setEnabled(isStreamDlActive);
    ui->lineEditStreamDlSpeed->setEnabled(isStreamDlActive);
}

void customModel::on_checkBoxStreamUl_clicked()
{
    bool isStreamUlActive=ui->checkBoxStreamUl->isChecked();
    ui->comboBoxStreamUlQci->setEnabled(isStreamUlActive);
    ui->lineEditStreamUlDuration->setEnabled(isStreamUlActive);
    ui->lineEditStreamUlMinThroughput->setEnabled(isStreamUlActive);
    ui->lineEditStreamUlSpeed->setEnabled(isStreamUlActive);
}

void customModel::on_checkBoxSyncedPing_clicked()
{
    bool isSyncedPingActive=ui->checkBoxSyncedPing->isChecked();
    ui->comboBoxSyncedPingQci1->setEnabled(isSyncedPingActive);
    ui->comboBoxSyncedPingQci2->setEnabled(isSyncedPingActive);
    ui->comboBoxSyncedPingQci3->setEnabled(isSyncedPingActive);
    ui->comboBoxSyncedPingQci4->setEnabled(isSyncedPingActive);
    ui->comboBoxSyncedPingQci5->setEnabled(isSyncedPingActive);
    ui->comboBoxSyncedPingQci6->setEnabled(isSyncedPingActive);
    ui->comboBoxSyncedPingQci7->setEnabled(isSyncedPingActive);
    ui->comboBoxSyncedPingQci8->setEnabled(isSyncedPingActive);
    ui->comboBoxSyncedPingQci9->setEnabled(isSyncedPingActive);
    ui->lineEditSyncedPingInterval->setEnabled(isSyncedPingActive);
    ui->lineEditSyncedPingMinReceivedPings->setEnabled(isSyncedPingActive);
    ui->lineEditSyncedPingNumberOfPings->setEnabled(isSyncedPingActive);
    ui->lineEditSyncedPingTimeBetweenTasks->setEnabled(isSyncedPingActive);
}

void customModel::on_checkBoxServiceReq_clicked()
{
    bool isServiceReqActive=ui->checkBoxServiceReq->isChecked();
    ui->comboBoxServiceReqQci1->setEnabled(isServiceReqActive);
    ui->comboBoxServiceReqQci2->setEnabled(isServiceReqActive);
    ui->comboBoxServiceReqQci3->setEnabled(isServiceReqActive);
    ui->comboBoxServiceReqQci4->setEnabled(isServiceReqActive);
    ui->comboBoxServiceReqQci5->setEnabled(isServiceReqActive);
    ui->comboBoxServiceReqQci6->setEnabled(isServiceReqActive);
    ui->comboBoxServiceReqQci7->setEnabled(isServiceReqActive);
    ui->comboBoxServiceReqQci8->setEnabled(isServiceReqActive);
    ui->comboBoxServiceReqQci9->setEnabled(isServiceReqActive);
    ui->lineEditServiceReqIntervalBetweenUIData->setEnabled(isServiceReqActive);
    ui->lineEditServiceReqTimeToWaitForAttach->setEnabled(isServiceReqActive);
}

void customModel::refreshQci()
{
    for(unsigned j=0;j<MaxOfQciComboBox;j++)
    {
        if(comboBoxForQci[j]->currentText()!="")
        {
            qciUsed[QciCurrentText[j]->toInt()-1]=false;
            QString temp=(comboBoxForQci[j]->currentText());

            comboBoxForQci[j]->clear();
            comboBoxForQci[j]->addItem("");
            for(unsigned i=0;i<AmountOfQci;i++)
            {
                if(!qciUsed[i])
                {
                    comboBoxForQci[j]->addItem(QString::number(i+1));
                }
            }
            qciUsed[QciCurrentText[j]->toInt()-1]=true;
            comboBoxForQci[j]->setCurrentText(temp);
        }else{
            comboBoxForQci[j]->clear();
            comboBoxForQci[j]->addItem("");
            for(unsigned i=0;i<AmountOfQci;i++)
            {
                if(!qciUsed[i])
                    comboBoxForQci[j]->addItem(QString::number(i+1));
            }
        }
    }
}

void customModel::on_comboBoxPingQci_activated(const QString &arg1)
{
    if( CMPingParams.currentQciTextPing!="")
    {
        qciUsed[ CMPingParams.currentQciTextPing.toInt()-1]=false;
    }
    CMPingParams.currentQciTextPing=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxVoipQci_activated(const QString &arg1)
{
    if(CMVoipParams.currentQciTextVoip !="")
    {
        qciUsed[CMVoipParams.currentQciTextVoip.toInt()-1]=false;
    }
    CMVoipParams.currentQciTextVoip=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxFTPDlQci_activated(const QString &arg1)
{
    if(CMFtpDlParams.currentQciTextFtpDl!="")
    {
        qciUsed[CMFtpDlParams.currentQciTextFtpDl.toInt()-1]=false;
    }
    CMFtpDlParams.currentQciTextFtpDl=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxFTPUlQci_activated(const QString &arg1)
{
    if(CMFtpUlParams.currentQciTextFtpUl!="")
    {
        qciUsed[CMFtpUlParams.currentQciTextFtpUl.toInt()-1]=false;
    }
    CMFtpUlParams.currentQciTextFtpUl=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxStreamDlQci_activated(const QString &arg1)
{
    if(CMStreamDlParams.currentQciTextStreamDl!="")
    {
        qciUsed[CMStreamDlParams.currentQciTextStreamDl.toInt()-1]=false;
    }
    CMStreamDlParams.currentQciTextStreamDl=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxStreamUlQci_activated(const QString &arg1)
{
    if(CMStreamUlParams.currentQciTextStreamUl!="")
    {
        qciUsed[CMStreamUlParams.currentQciTextStreamUl.toInt()-1]=false;
    }
    CMStreamUlParams.currentQciTextStreamUl=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci1_activated(const QString &arg1)
{
    if(CMSyncedPingParams.currentQciTextSyncedPing[0]!="")
    {
        qciUsed[CMSyncedPingParams.currentQciTextSyncedPing[0].toInt()-1]=false;
    }
    CMSyncedPingParams.currentQciTextSyncedPing[0]=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci2_activated(const QString &arg1)
{
    if(CMSyncedPingParams.currentQciTextSyncedPing[1]!="")
    {
        qciUsed[CMSyncedPingParams.currentQciTextSyncedPing[1].toInt()-1]=false;
    }
    if(arg1!="")
        CMSyncedPingParams.currentQciTextSyncedPing[1]=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci3_activated(const QString &arg1)
{
    if(CMSyncedPingParams.currentQciTextSyncedPing[2]!="")
    {
        qciUsed[CMSyncedPingParams.currentQciTextSyncedPing[2].toInt()-1]=false;
    }
    CMSyncedPingParams.currentQciTextSyncedPing[2]=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci4_activated(const QString &arg1)
{
    if(CMSyncedPingParams.currentQciTextSyncedPing[3]!="")
    {
        qciUsed[CMSyncedPingParams.currentQciTextSyncedPing[3].toInt()-1]=false;
    }
    CMSyncedPingParams.currentQciTextSyncedPing[3]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci5_activated(const QString &arg1)
{
    if(CMSyncedPingParams.currentQciTextSyncedPing[4]!="")
    {
        qciUsed[CMSyncedPingParams.currentQciTextSyncedPing[4].toInt()-1]=false;
    }
    CMSyncedPingParams.currentQciTextSyncedPing[4]=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci6_activated(const QString &arg1)
{
    if(CMSyncedPingParams.currentQciTextSyncedPing[5]!="")
    {
        qciUsed[CMSyncedPingParams.currentQciTextSyncedPing[5].toInt()-1]=false;
    }
    CMSyncedPingParams.currentQciTextSyncedPing[5]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci7_activated(const QString &arg1)
{
    if(CMSyncedPingParams.currentQciTextSyncedPing[6]!="")
    {
        qciUsed[CMSyncedPingParams.currentQciTextSyncedPing[6].toInt()-1]=false;
    }
    CMSyncedPingParams.currentQciTextSyncedPing[6]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci8_activated(const QString &arg1)
{
    if(CMSyncedPingParams.currentQciTextSyncedPing[7]!="")
    {
        qciUsed[CMSyncedPingParams.currentQciTextSyncedPing[7].toInt()-1]=false;
    }
    CMSyncedPingParams.currentQciTextSyncedPing[7]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci9_activated(const QString &arg1)
{
    if(CMSyncedPingParams.currentQciTextSyncedPing[8]!="")
    {
        qciUsed[CMSyncedPingParams.currentQciTextSyncedPing[8].toInt()-1]=false;
    }
    CMSyncedPingParams.currentQciTextSyncedPing[8]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci1_activated(const QString &arg1)
{
    if(CMServiceReqParams.currentQciTextServiceReq[0]!="")
    {
        qciUsed[CMServiceReqParams.currentQciTextServiceReq[0].toInt()-1]=false;
    }
    CMServiceReqParams.currentQciTextServiceReq[0]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci2_activated(const QString &arg1)
{
    if(CMServiceReqParams.currentQciTextServiceReq[1]!="")
    {
        qciUsed[CMServiceReqParams.currentQciTextServiceReq[1].toInt()-1]=false;
    }
    CMServiceReqParams.currentQciTextServiceReq[1]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci3_activated(const QString &arg1)
{
    if(CMServiceReqParams.currentQciTextServiceReq[2]!="")
    {
        qciUsed[CMServiceReqParams.currentQciTextServiceReq[2].toInt()-1]=false;
    }
    CMServiceReqParams.currentQciTextServiceReq[2]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci4_activated(const QString &arg1)
{
    if(CMServiceReqParams.currentQciTextServiceReq[3]!="")
    {
        qciUsed[CMServiceReqParams.currentQciTextServiceReq[3].toInt()-1]=false;
    }
    CMServiceReqParams.currentQciTextServiceReq[3]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci5_activated(const QString &arg1)
{
    if(CMServiceReqParams.currentQciTextServiceReq[4]!="")
    {
        qciUsed[CMServiceReqParams.currentQciTextServiceReq[4].toInt()-1]=false;
    }
    CMServiceReqParams.currentQciTextServiceReq[4]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci6_activated(const QString &arg1)
{
    if(CMServiceReqParams.currentQciTextServiceReq[5]!="")
    {
        qciUsed[CMServiceReqParams.currentQciTextServiceReq[5].toInt()-1]=false;
    }
    CMServiceReqParams.currentQciTextServiceReq[5]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci7_activated(const QString &arg1)
{
    if(CMServiceReqParams.currentQciTextServiceReq[6]!="")
    {
        qciUsed[CMServiceReqParams.currentQciTextServiceReq[6].toInt()-1]=false;
    }
    CMServiceReqParams.currentQciTextServiceReq[6]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci8_activated(const QString &arg1)
{
    if(CMServiceReqParams.currentQciTextServiceReq[7]!="")
    {
        qciUsed[CMServiceReqParams.currentQciTextServiceReq[7].toInt()-1]=false;
    }
    CMServiceReqParams.currentQciTextServiceReq[7]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci9_activated(const QString &arg1)
{
    if(CMServiceReqParams.currentQciTextServiceReq[8]!="")
    {
        qciUsed[CMServiceReqParams.currentQciTextServiceReq[8].toInt()-1]=false;
    }
    CMServiceReqParams.currentQciTextServiceReq[8]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_cancelCustomModelButton_clicked()
{
    this->close();
}

void customModel::on_saveCustomModelButton_clicked()
{
    saveCustomModel();
    this->close();
}

void customModel::setParameters(customModel **customModel){

    this->custommodel = customModel;

    ui->lineEditPingNumberOfPings->setText(QString::number(CMPingParams.pingNumberOfPings));
    ui->lineEditPingInterval->setText(QString::number(CMPingParams.pingInterval));
    ui->lineEditPingMinReceivedPings->setText(QString::number(CMPingParams.pingMinRecievedPings));

    ui->lineEditVoipDuration->setText(QString::number( CMVoipParams.voipDuration));
    ui->lineEditVoipActivityFactor->setText(QString::number( CMVoipParams.voipActivityFactor));
    ui->lineEditVoipMaxTransferTime->setText(QString::number( CMVoipParams.voipMaxTransferTime));
    ui->lineEditVoipMinPacketsReceivedInTime->setText(QString::number( CMVoipParams.voipMinPacketsReceivedInTime));

    ui->lineEditFTPDlFilesize->setText(QString::number( CMFtpDlParams.ftpDlFilesize));
    ui->lineEditFTPDlMinThroughput->setText(QString::number( CMFtpDlParams.ftpDlMinThroughput));

    ui->lineEditFTPUlFilesize->setText(QString::number( CMFtpUlParams.ftpUlFilesize));
    ui->lineEditFTPUlMinThroughput->setText(QString::number( CMFtpUlParams.ftpUlMinThroughput));

    ui->lineEditStreamDlSpeed->setText(QString::number( CMStreamDlParams.streamDlSpeed));
    ui->lineEditStreamDlDuration->setText(QString::number( CMStreamDlParams.streamDlDuration));
    ui->lineEditStreamDlMinThroughput->setText(QString::number( CMStreamDlParams.streamDlMinThroughput));

    ui->lineEditStreamUlSpeed->setText(QString::number( CMStreamUlParams.streamUlSpeed));
    ui->lineEditStreamUlDuration->setText(QString::number( CMStreamUlParams.streamUlDuration));
    ui->lineEditStreamUlMinThroughput->setText(QString::number( CMStreamUlParams.streamUlMinThroughput));

    ui->lineEditSyncedPingTimeBetweenTasks->setText(QString::number( CMSyncedPingParams.SyncedPingTimeBetweenTasks));
    ui->lineEditSyncedPingNumberOfPings->setText(QString::number( CMSyncedPingParams.SyncedPingNumberOfPings));
    ui->lineEditSyncedPingInterval->setText(QString::number( CMSyncedPingParams.SyncedPingInterval));
    ui->lineEditSyncedPingMinReceivedPings->setText(QString::number( CMSyncedPingParams.SyncedPingMinReceivedPings));

    ui->lineEditServiceReqIntervalBetweenUIData->setText(QString::number( CMServiceReqParams.ServiceReqTimeToWaitForAttach));
    ui->lineEditServiceReqIntervalBetweenUIData->setText(QString::number( CMServiceReqParams.ServiceReqIntervalBetweenUlData));

    if( CMPingParams.pingQci==0)
        ui->comboBoxPingQci->setCurrentText("");
    else
        ui->comboBoxPingQci->setCurrentText(QString::number( CMPingParams.pingQci));

    if( CMVoipParams.voipQci==0)
        ui->comboBoxVoipQci->setCurrentText("");
    else
        ui->comboBoxVoipQci->setCurrentText(QString::number( CMVoipParams.voipQci));

    if( CMFtpDlParams.ftpDlQci==0)
        ui->comboBoxFTPDlQci->setCurrentText("");
    else
        ui->comboBoxFTPDlQci->setCurrentText(QString::number( CMFtpDlParams.ftpDlQci));

    if( CMFtpUlParams.ftpUlQci==0)
        ui->comboBoxFTPUlQci->setCurrentText("");
    else
        ui->comboBoxFTPUlQci->setCurrentText(QString::number( CMFtpUlParams.ftpUlQci));

    if( CMStreamDlParams.streamDlQci==0)
        ui->comboBoxStreamDlQci->setCurrentText("");
    else
        ui->comboBoxStreamDlQci->setCurrentText(QString::number( CMStreamDlParams.streamDlQci));

    if( CMStreamUlParams.streamUlQci==0)
        ui->comboBoxStreamUlQci->setCurrentText("");
    else
        ui->comboBoxStreamUlQci->setCurrentText(QString::number( CMStreamUlParams.streamUlQci));

    for(unsigned i=0;i<AmountOfQci;i++)
    {
        if( CMSyncedPingParams.SyncedPingQciArray[i]==0)
            pointercomboBoxForQciSyncedPing[i]->setCurrentText("");
        else
            pointercomboBoxForQciSyncedPing[i]->setCurrentText(QString::number( CMSyncedPingParams.SyncedPingQciArray[i]));
    }
    for(unsigned i=0;i<AmountOfQci;i++)
    {
        if( CMServiceReqParams.ServiceReqQciArray[i]==0)
            pointercomboBoxForQciServiceReq[i]->setCurrentText("");
        else
            pointercomboBoxForQciServiceReq[i]->setCurrentText(QString::number( CMServiceReqParams.ServiceReqQciArray[i]));
    }
}

void customModel::saveCustomModel()
{
    CMPingParams.pingQci=ui->comboBoxPingQci->currentText().toInt();
    CMPingParams.pingNumberOfPings=ui->lineEditPingNumberOfPings->text().toInt();
    CMPingParams.pingInterval=ui->lineEditPingInterval->text().toInt();
    CMPingParams.pingMinRecievedPings=ui->lineEditPingMinReceivedPings->text().toInt();

    CMVoipParams.voipQci=ui->comboBoxVoipQci->currentText().toInt();
    CMVoipParams.voipDuration=ui->lineEditVoipDuration->text().toInt();
    CMVoipParams.voipActivityFactor=ui->lineEditVoipActivityFactor->text().toInt();
    CMVoipParams.voipMaxTransferTime=ui->lineEditVoipMaxTransferTime->text().toInt();
    CMVoipParams.voipMinPacketsReceivedInTime=ui->lineEditVoipMinPacketsReceivedInTime->text().toInt();

    CMFtpDlParams.ftpDlQci=ui->comboBoxFTPDlQci->currentText().toInt();
    CMFtpDlParams.ftpDlFilesize=ui->lineEditFTPDlFilesize->text().toInt();
    CMFtpDlParams.ftpDlMinThroughput=ui->lineEditFTPDlMinThroughput->text().toInt();

    CMFtpUlParams.ftpUlQci=ui->comboBoxFTPUlQci->currentText().toInt();
    CMFtpUlParams.ftpUlFilesize=ui->lineEditFTPUlFilesize->text().toInt();
    CMFtpUlParams.ftpUlMinThroughput=ui->lineEditFTPUlMinThroughput->text().toInt();

    CMStreamDlParams.streamDlQci=ui->comboBoxStreamDlQci->currentText().toInt();
    CMStreamDlParams.streamDlSpeed=ui->lineEditStreamDlSpeed->text().toInt();
    CMStreamDlParams.streamDlDuration=ui->lineEditStreamDlDuration->text().toInt();
    CMStreamDlParams.streamDlMinThroughput=ui->lineEditStreamDlMinThroughput->text().toInt();

    CMStreamUlParams.streamUlQci=ui->comboBoxStreamUlQci->currentText().toInt();
    CMStreamUlParams.streamUlSpeed=ui->lineEditStreamUlSpeed->text().toInt();
    CMStreamUlParams.streamUlDuration=ui->lineEditStreamUlDuration->text().toInt();
    CMStreamUlParams.streamUlMinThroughput=ui->lineEditStreamUlMinThroughput->text().toInt();

    for(unsigned i=0;i<AmountOfQci;i++)
        CMSyncedPingParams.SyncedPingQciArray[i]=pointercomboBoxForQciSyncedPing[i]->currentText().toInt();

    CMSyncedPingParams.SyncedPingTimeBetweenTasks=ui->lineEditSyncedPingTimeBetweenTasks->text().toInt();
    CMSyncedPingParams.SyncedPingNumberOfPings=ui->lineEditSyncedPingNumberOfPings->text().toInt();
    CMSyncedPingParams.SyncedPingInterval=ui->lineEditSyncedPingInterval->text().toInt();
    CMSyncedPingParams.SyncedPingMinReceivedPings=ui->lineEditSyncedPingMinReceivedPings->text().toInt();

    for(unsigned i=0;i<AmountOfQci;i++)
        CMServiceReqParams.ServiceReqQciArray[i]=pointercomboBoxForQciServiceReq[i]->currentText().toInt();

    CMServiceReqParams.ServiceReqTimeToWaitForAttach=ui->lineEditServiceReqIntervalBetweenUIData->text().toInt();
    CMServiceReqParams.ServiceReqIntervalBetweenUlData=ui->lineEditServiceReqIntervalBetweenUIData->text().toInt();
}

void customModel::on_restoreCustomModelButton_clicked()
{
    ui->comboBoxPingQci->setCurrentText("");
    ui->lineEditPingNumberOfPings->setText("0");
    ui->lineEditPingInterval->setText("0");
    ui->lineEditPingMinReceivedPings->setText("0");

    ui->comboBoxVoipQci->setCurrentText("");
    ui->lineEditVoipDuration->setText("0");
    ui->lineEditVoipActivityFactor->setText("0");
    ui->lineEditVoipMaxTransferTime->setText("0");
    ui->lineEditVoipMinPacketsReceivedInTime->setText("0");

    ui->comboBoxFTPDlQci->setCurrentText("");
    ui->lineEditFTPDlFilesize->setText("0");
    ui->lineEditFTPDlMinThroughput->setText("0");

    ui->comboBoxFTPUlQci->setCurrentText("");
    ui->lineEditFTPUlFilesize->setText("0");
    ui->lineEditFTPUlMinThroughput->setText("0");

    ui->comboBoxStreamDlQci->setCurrentText("");
    ui->lineEditStreamDlSpeed->setText("0");
    ui->lineEditStreamDlDuration->setText("0");
    ui->lineEditStreamDlMinThroughput->setText("0");

    ui->comboBoxStreamUlQci->setCurrentText("");
    ui->lineEditStreamUlSpeed->setText("0");
    ui->lineEditStreamUlDuration->setText("0");
    ui->lineEditStreamUlMinThroughput->setText("0");

    ui->comboBoxSyncedPingQci1->setCurrentText("");
    ui->comboBoxSyncedPingQci2->setCurrentText("");
    ui->comboBoxSyncedPingQci3->setCurrentText("");
    ui->comboBoxSyncedPingQci4->setCurrentText("");
    ui->comboBoxSyncedPingQci5->setCurrentText("");
    ui->comboBoxSyncedPingQci6->setCurrentText("");
    ui->comboBoxSyncedPingQci7->setCurrentText("");
    ui->comboBoxSyncedPingQci8->setCurrentText("");
    ui->comboBoxSyncedPingQci9->setCurrentText("");
    ui->lineEditSyncedPingTimeBetweenTasks->setText("0");
    ui->lineEditSyncedPingNumberOfPings->setText("0");
    ui->lineEditSyncedPingInterval->setText("0");
    ui->lineEditSyncedPingMinReceivedPings->setText("0");

    ui->comboBoxServiceReqQci1->setCurrentText("");
    ui->comboBoxServiceReqQci2->setCurrentText("");
    ui->comboBoxServiceReqQci3->setCurrentText("");
    ui->comboBoxServiceReqQci4->setCurrentText("");
    ui->comboBoxServiceReqQci5->setCurrentText("");
    ui->comboBoxServiceReqQci6->setCurrentText("");
    ui->comboBoxServiceReqQci7->setCurrentText("");
    ui->comboBoxServiceReqQci8->setCurrentText("");
    ui->comboBoxServiceReqQci9->setCurrentText("");
    ui->lineEditServiceReqIntervalBetweenUIData->setText("0");
    ui->lineEditServiceReqIntervalBetweenUIData->setText("0");

    if(ui->checkBoxPing->isChecked())
    {
        ui->checkBoxPing->setChecked(false);
        ui->comboBoxPingQci->setEnabled(false);
        ui->lineEditPingNumberOfPings->setEnabled(false);
        ui->lineEditPingInterval->setEnabled(false);
        ui->lineEditPingMinReceivedPings->setEnabled(false);
    }

    if(ui->checkBoxVoip->isChecked())
    {
        ui->checkBoxVoip->setChecked(false);
        ui->comboBoxVoipQci->setEnabled(false);
        ui->lineEditVoipActivityFactor->setEnabled(false);
        ui->lineEditVoipDuration->setEnabled(false);
        ui->lineEditVoipMaxTransferTime->setEnabled(false);
        ui->lineEditVoipMinPacketsReceivedInTime->setEnabled(false);
    }

    if(ui->checkBoxFTPDl->isChecked())
    {
        ui->checkBoxFTPDl->setChecked(false);
        ui->comboBoxFTPDlQci->setEnabled(false);
        ui->lineEditFTPDlFilesize->setEnabled(false);
        ui->lineEditFTPDlMinThroughput->setEnabled(false);
    }

    if(ui->checkBoxFTPUl->isChecked())
    {
        ui->checkBoxFTPUl->setChecked(false);
        ui->comboBoxFTPUlQci->setEnabled(false);
        ui->lineEditFTPUlFilesize->setEnabled(false);
        ui->lineEditFTPUlMinThroughput->setEnabled(false);
    }

    if(ui->checkBoxStreamDl->isChecked())
    {
        ui->checkBoxStreamDl->setChecked(false);
        ui->comboBoxStreamDlQci->setEnabled(false);
        ui->lineEditStreamDlDuration->setEnabled(false);
        ui->lineEditStreamDlMinThroughput->setEnabled(false);
        ui->lineEditStreamDlSpeed->setEnabled(false);
    }

    if(ui->checkBoxStreamUl->isChecked())
    {
        ui->checkBoxStreamUl->setChecked(false);
        ui->comboBoxStreamUlQci->setEnabled(false);
        ui->lineEditStreamUlDuration->setEnabled(false);
        ui->lineEditStreamUlMinThroughput->setEnabled(false);
        ui->lineEditStreamUlSpeed->setEnabled(false);
    }

    if(ui->checkBoxSyncedPing->isChecked())
    {
        ui->checkBoxSyncedPing->setChecked(false);
        ui->comboBoxSyncedPingQci1->setEnabled(false);
        ui->comboBoxSyncedPingQci2->setEnabled(false);
        ui->comboBoxSyncedPingQci3->setEnabled(false);
        ui->comboBoxSyncedPingQci4->setEnabled(false);
        ui->comboBoxSyncedPingQci5->setEnabled(false);
        ui->comboBoxSyncedPingQci6->setEnabled(false);
        ui->comboBoxSyncedPingQci7->setEnabled(false);
        ui->comboBoxSyncedPingQci8->setEnabled(false);
        ui->comboBoxSyncedPingQci9->setEnabled(false);
        ui->lineEditSyncedPingInterval->setEnabled(false);
        ui->lineEditSyncedPingMinReceivedPings->setEnabled(false);
        ui->lineEditSyncedPingNumberOfPings->setEnabled(false);
        ui->lineEditSyncedPingTimeBetweenTasks->setEnabled(false);
    }

    if(ui->checkBoxServiceReq->isChecked())
    {
        ui->checkBoxServiceReq->setChecked(false);
        ui->comboBoxServiceReqQci1->setEnabled(false);
        ui->comboBoxServiceReqQci2->setEnabled(false);
        ui->comboBoxServiceReqQci3->setEnabled(false);
        ui->comboBoxServiceReqQci4->setEnabled(false);
        ui->comboBoxServiceReqQci5->setEnabled(false);
        ui->comboBoxServiceReqQci6->setEnabled(false);
        ui->comboBoxServiceReqQci7->setEnabled(false);
        ui->comboBoxServiceReqQci8->setEnabled(false);
        ui->comboBoxServiceReqQci9->setEnabled(false);
        ui->lineEditServiceReqIntervalBetweenUIData->setEnabled(false);
        ui->lineEditServiceReqTimeToWaitForAttach->setEnabled(false);
    }

    for(auto &QciUsed:qciUsed)
        QciUsed=false;

    refreshQci();
    saveCustomModel();
}
