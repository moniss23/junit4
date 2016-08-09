#include "customModel.h"
#include "ui_customModel.h"

customModel::customModel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::customModel)
{
    ui->setupUi(this);

    for(unsigned int i=0;i<9;i++)
        qciUsed[i]=false;
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
    ui->comboBoxPingQci->setEnabled(isPingActive);
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

void customModel::refreshPingQci()
{
    if(ui->comboBoxPingQci->currentText()!="")
    {
        qciUsed[QciCurrentText[0].toInt()-1]=false;
        QString temp=(ui->comboBoxPingQci->currentText());

        ui->comboBoxPingQci->clear();
        ui->comboBoxPingQci->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
            {
                ui->comboBoxPingQci->addItem(QString::number(i+1));
            }
        }
        qciUsed[QciCurrentText[0].toInt()-1]=true;
        ui->comboBoxPingQci->setCurrentText(temp);
    }else{
        ui->comboBoxPingQci->clear();
        ui->comboBoxPingQci->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxPingQci->addItem(QString::number(i+1));
        }
    }
}

void customModel::refreshVoipQci()
{
    if(ui->comboBoxVoipQci->currentText()!="")
    {
        qciUsed[QciCurrentText[1].toInt()-1]=false;
        QString temp=ui->comboBoxVoipQci->currentText();
        ui->comboBoxVoipQci->clear();
        ui->comboBoxVoipQci->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxVoipQci->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[1].toInt()-1]=true;
        ui->comboBoxVoipQci->setCurrentText(temp);
    }else{
        ui->comboBoxVoipQci->clear();
        ui->comboBoxVoipQci->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxVoipQci->addItem(QString::number(i+1));
        }
    }
}

void customModel::refreshFTPDlQci()
{
    if(ui->comboBoxFTPDlQci->currentText()!="")
    {
        qciUsed[QciCurrentText[2].toInt()-1]=false;
        QString temp=ui->comboBoxFTPDlQci->currentText();
        ui->comboBoxFTPDlQci->clear();
        ui->comboBoxFTPDlQci->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxFTPDlQci->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[2].toInt()-1]=true;
        ui->comboBoxFTPDlQci->setCurrentText(temp);
    }else{
        ui->comboBoxFTPDlQci->clear();
        ui->comboBoxFTPDlQci->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxFTPDlQci->addItem(QString::number(i+1));
        }
    }
}

void customModel::refreshFTPUlQci()
{
    if(ui->comboBoxFTPUlQci->currentText()!="")
    {
        qciUsed[QciCurrentText[3].toInt()-1]=false;
        QString temp=ui->comboBoxFTPUlQci->currentText();
        ui->comboBoxFTPUlQci->clear();
        ui->comboBoxFTPUlQci->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxFTPUlQci->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[3].toInt()-1]=true;
        ui->comboBoxFTPUlQci->setCurrentText(temp);
    }else{
        ui->comboBoxFTPUlQci->clear();
        ui->comboBoxFTPUlQci->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxFTPUlQci->addItem(QString::number(i+1));
        }
    }
}

void customModel::refreshStreamDlQci()
{
    if(ui->comboBoxStreamDlQci->currentText()!="")
    {
        qciUsed[QciCurrentText[4].toInt()-1]=false;
        QString temp=ui->comboBoxStreamDlQci->currentText();
        ui->comboBoxStreamDlQci->clear();
        ui->comboBoxStreamDlQci->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxStreamDlQci->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[4].toInt()-1]=true;
        ui->comboBoxStreamDlQci->setCurrentText(temp);
    }else{
        ui->comboBoxStreamDlQci->clear();
        ui->comboBoxStreamDlQci->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxStreamDlQci->addItem(QString::number(i+1));
        }
    }
}

void customModel::refreshStreamUlQci()
{
    if(ui->comboBoxStreamUlQci->currentText()!="")
    {
        qciUsed[QciCurrentText[5].toInt()-1]=false;
        QString temp=ui->comboBoxStreamUlQci->currentText();
        ui->comboBoxStreamUlQci->clear();
        ui->comboBoxStreamUlQci->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxStreamUlQci->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[5].toInt()-1]=true;
        ui->comboBoxStreamUlQci->setCurrentText(temp);
    }else{
        ui->comboBoxStreamUlQci->clear();
        ui->comboBoxStreamUlQci->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxStreamUlQci->addItem(QString::number(i+1));
        }
    }
}

void customModel::refreshSyncedPingQci()
{
    if(ui->comboBoxSyncedPingQci1->currentText()!="")
    {
        qciUsed[QciCurrentText[6].toInt()-1]=false;
        QString temp=ui->comboBoxSyncedPingQci1->currentText();
        ui->comboBoxSyncedPingQci1->clear();
        ui->comboBoxSyncedPingQci1->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci1->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[6].toInt()-1]=true;
        ui->comboBoxSyncedPingQci1->setCurrentText(temp);
    }else{
        ui->comboBoxSyncedPingQci1->clear();
        ui->comboBoxSyncedPingQci1->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci1->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxSyncedPingQci2->currentText()!="")
    {
        qciUsed[QciCurrentText[7].toInt()-1]=false;
        QString temp=ui->comboBoxSyncedPingQci2->currentText();
        ui->comboBoxSyncedPingQci2->clear();
        ui->comboBoxSyncedPingQci2->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci2->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[7].toInt()-1]=true;
        ui->comboBoxSyncedPingQci2->setCurrentText(temp);
    }else{
        ui->comboBoxSyncedPingQci2->clear();
        ui->comboBoxSyncedPingQci2->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci2->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxSyncedPingQci3->currentText()!="")
    {
        qciUsed[QciCurrentText[8].toInt()-1]=false;
        QString temp=ui->comboBoxSyncedPingQci3->currentText();
        ui->comboBoxSyncedPingQci3->clear();
        ui->comboBoxSyncedPingQci3->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci3->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[8].toInt()-1]=true;
        ui->comboBoxSyncedPingQci3->setCurrentText(temp);
    }else{
        ui->comboBoxSyncedPingQci3->clear();
        ui->comboBoxSyncedPingQci3->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci3->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxSyncedPingQci4->currentText()!="")
    {
        qciUsed[QciCurrentText[9].toInt()-1]=false;
        QString temp=ui->comboBoxSyncedPingQci4->currentText();
        ui->comboBoxSyncedPingQci4->clear();
        ui->comboBoxSyncedPingQci4->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci4->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[9].toInt()-1]=true;
        ui->comboBoxSyncedPingQci4->setCurrentText(temp);
    }else{
        ui->comboBoxSyncedPingQci4->clear();
        ui->comboBoxSyncedPingQci4->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci4->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxSyncedPingQci5->currentText()!="")
    {
        qciUsed[QciCurrentText[10].toInt()-1]=false;
        QString temp=ui->comboBoxSyncedPingQci5->currentText();
        ui->comboBoxSyncedPingQci5->clear();
        ui->comboBoxSyncedPingQci5->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci5->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[10].toInt()-1]=true;
        ui->comboBoxSyncedPingQci5->setCurrentText(temp);
    }else{
        ui->comboBoxSyncedPingQci5->clear();
        ui->comboBoxSyncedPingQci5->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci5->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxSyncedPingQci6->currentText()!="")
    {
        qciUsed[QciCurrentText[11].toInt()-1]=false;
        QString temp=ui->comboBoxSyncedPingQci6->currentText();
        ui->comboBoxSyncedPingQci6->clear();
        ui->comboBoxSyncedPingQci6->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci6->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[11].toInt()-1]=true;
        ui->comboBoxSyncedPingQci6->setCurrentText(temp);
    }else{
        ui->comboBoxSyncedPingQci6->clear();
        ui->comboBoxSyncedPingQci6->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci6->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxSyncedPingQci7->currentText()!="")
    {
        qciUsed[QciCurrentText[12].toInt()-1]=false;
        QString temp=ui->comboBoxSyncedPingQci7->currentText();
        ui->comboBoxSyncedPingQci7->clear();
        ui->comboBoxSyncedPingQci7->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci7->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[12].toInt()-1]=true;
        ui->comboBoxSyncedPingQci7->setCurrentText(temp);
    }else{
        ui->comboBoxSyncedPingQci7->clear();
        ui->comboBoxSyncedPingQci7->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci7->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxSyncedPingQci8->currentText()!="")
    {
        qciUsed[QciCurrentText[13].toInt()-1]=false;
        QString temp=ui->comboBoxSyncedPingQci8->currentText();
        ui->comboBoxSyncedPingQci8->clear();
        ui->comboBoxSyncedPingQci8->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci8->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[13].toInt()-1]=true;
        ui->comboBoxSyncedPingQci8->setCurrentText(temp);
    }else{
        ui->comboBoxSyncedPingQci8->clear();
        ui->comboBoxSyncedPingQci8->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci8->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxSyncedPingQci9->currentText()!="")
    {
        qciUsed[QciCurrentText[14].toInt()-1]=false;
        QString temp=ui->comboBoxSyncedPingQci9->currentText();
        ui->comboBoxSyncedPingQci9->clear();
        ui->comboBoxSyncedPingQci9->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci9->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[14].toInt()-1]=true;
        ui->comboBoxSyncedPingQci9->setCurrentText(temp);
    }else{
        ui->comboBoxSyncedPingQci9->clear();
        ui->comboBoxSyncedPingQci9->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxSyncedPingQci9->addItem(QString::number(i+1));
        }
    }
}

void customModel::refreshServiceReqQci()
{
    if(ui->comboBoxServiceReqQci1->currentText()!="")
    {
        qciUsed[QciCurrentText[15].toInt()-1]=false;
        QString temp=ui->comboBoxServiceReqQci1->currentText();
        ui->comboBoxServiceReqQci1->clear();
        ui->comboBoxServiceReqQci1->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci1->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[15].toInt()-1]=true;
        ui->comboBoxServiceReqQci1->setCurrentText(temp);
    }else{
        ui->comboBoxServiceReqQci1->clear();
        ui->comboBoxServiceReqQci1->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci1->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxServiceReqQci2->currentText()!="")
    {
        qciUsed[QciCurrentText[16].toInt()-1]=false;
        QString temp=ui->comboBoxServiceReqQci2->currentText();
        ui->comboBoxServiceReqQci2->clear();
        ui->comboBoxServiceReqQci2->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci2->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[16].toInt()-1]=true;
        ui->comboBoxServiceReqQci2->setCurrentText(temp);
    }else{
        ui->comboBoxServiceReqQci2->clear();
        ui->comboBoxServiceReqQci2->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci2->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxServiceReqQci3->currentText()!="")
    {
        qciUsed[QciCurrentText[17].toInt()-1]=false;
        QString temp=ui->comboBoxServiceReqQci3->currentText();
        ui->comboBoxServiceReqQci3->clear();
        ui->comboBoxServiceReqQci3->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci3->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[17].toInt()-1]=true;
        ui->comboBoxServiceReqQci3->setCurrentText(temp);
    }else{
        ui->comboBoxServiceReqQci3->clear();
        ui->comboBoxServiceReqQci3->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci3->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxServiceReqQci4->currentText()!="")
    {
        qciUsed[QciCurrentText[18].toInt()-1]=false;
        QString temp=ui->comboBoxServiceReqQci4->currentText();
        ui->comboBoxServiceReqQci4->clear();
        ui->comboBoxServiceReqQci4->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci4->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[18].toInt()-1]=true;
        ui->comboBoxServiceReqQci4->setCurrentText(temp);
    }else{
        ui->comboBoxServiceReqQci4->clear();
        ui->comboBoxServiceReqQci4->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci4->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxServiceReqQci5->currentText()!="")
    {
        qciUsed[QciCurrentText[19].toInt()-1]=false;
        QString temp=ui->comboBoxServiceReqQci5->currentText();
        ui->comboBoxServiceReqQci5->clear();
        ui->comboBoxServiceReqQci5->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci5->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[19].toInt()-1]=true;
        ui->comboBoxServiceReqQci5->setCurrentText(temp);
    }else{
        ui->comboBoxServiceReqQci5->clear();
        ui->comboBoxServiceReqQci5->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci5->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxServiceReqQci6->currentText()!="")
    {
        qciUsed[QciCurrentText[20].toInt()-1]=false;
        QString temp=ui->comboBoxServiceReqQci6->currentText();
        ui->comboBoxServiceReqQci6->clear();
        ui->comboBoxServiceReqQci6->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci6->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[20].toInt()-1]=true;
        ui->comboBoxServiceReqQci6->setCurrentText(temp);
    }else{
        ui->comboBoxServiceReqQci6->clear();
        ui->comboBoxServiceReqQci6->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci6->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxServiceReqQci7->currentText()!="")
    {
        qciUsed[QciCurrentText[21].toInt()-1]=false;
        QString temp=ui->comboBoxServiceReqQci7->currentText();
        ui->comboBoxServiceReqQci7->clear();
        ui->comboBoxServiceReqQci7->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci7->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[21].toInt()-1]=true;
        ui->comboBoxServiceReqQci7->setCurrentText(temp);
    }else{
        ui->comboBoxServiceReqQci7->clear();
        ui->comboBoxServiceReqQci7->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci7->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxServiceReqQci8->currentText()!="")
    {
        qciUsed[QciCurrentText[22].toInt()-1]=false;
        QString temp=ui->comboBoxServiceReqQci8->currentText();
        ui->comboBoxServiceReqQci8->clear();
        ui->comboBoxServiceReqQci8->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci8->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[22].toInt()-1]=true;
        ui->comboBoxServiceReqQci8->setCurrentText(temp);
    }else{
        ui->comboBoxServiceReqQci8->clear();
        ui->comboBoxServiceReqQci8->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci8->addItem(QString::number(i+1));
        }
    }

    if(ui->comboBoxServiceReqQci9->currentText()!="")
    {
        qciUsed[QciCurrentText[23].toInt()-1]=false;
        QString temp=ui->comboBoxServiceReqQci9->currentText();
        ui->comboBoxServiceReqQci9->clear();
        ui->comboBoxServiceReqQci9->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci9->addItem(QString::number(i+1));
        }
        qciUsed[QciCurrentText[23].toInt()-1]=true;
        ui->comboBoxServiceReqQci9->setCurrentText(temp);
    }else{
        ui->comboBoxServiceReqQci9->clear();
        ui->comboBoxServiceReqQci9->addItem("");
        for(unsigned i=0;i<9;i++)
        {
            if(!qciUsed[i])
                ui->comboBoxServiceReqQci9->addItem(QString::number(i+1));
        }
    }
}

void customModel::refreshQci()
{
    refreshPingQci();
    refreshVoipQci();
    refreshFTPDlQci();
    refreshFTPUlQci();
    refreshStreamDlQci();
    refreshStreamUlQci();
    refreshSyncedPingQci();
    refreshServiceReqQci();
}

void customModel::on_comboBoxPingQci_activated(const QString &arg1)
{
    if(QciCurrentText[0]!="")
    {
        qciUsed[QciCurrentText[0].toInt()-1]=false;
    }
    QciCurrentText[0]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxVoipQci_activated(const QString &arg1)
{
    if(QciCurrentText[1]!="")
    {
        qciUsed[QciCurrentText[1].toInt()-1]=false;
    }
    QciCurrentText[1]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxFTPDlQci_activated(const QString &arg1)
{
    if(QciCurrentText[2]!="")
    {
        qciUsed[QciCurrentText[2].toInt()-1]=false;
    }
    QciCurrentText[2]=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxFTPUlQci_activated(const QString &arg1)
{
    if(QciCurrentText[3]!="")
    {
        qciUsed[QciCurrentText[3].toInt()-1]=false;
    }
    QciCurrentText[3]=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxStreamDlQci_activated(const QString &arg1)
{
    if(QciCurrentText[4]!="")
    {
        qciUsed[QciCurrentText[4].toInt()-1]=false;
    }
    QciCurrentText[4]=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxStreamUlQci_activated(const QString &arg1)
{
    if(QciCurrentText[5]!="")
    {
        qciUsed[QciCurrentText[5].toInt()-1]=false;
    }
    QciCurrentText[5]=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci1_activated(const QString &arg1)
{
    if(QciCurrentText[6]!="")
    {
        qciUsed[QciCurrentText[6].toInt()-1]=false;
    }
    QciCurrentText[6]=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci2_activated(const QString &arg1)
{
    if(QciCurrentText[7]!="")
    {
        qciUsed[QciCurrentText[7].toInt()-1]=false;
    }
    if(arg1!="")
        QciCurrentText[7]=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci3_activated(const QString &arg1)
{
    if(QciCurrentText[8]!="")
    {
        qciUsed[QciCurrentText[8].toInt()-1]=false;
    }
    QciCurrentText[8]=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci4_activated(const QString &arg1)
{
    if(QciCurrentText[9]!="")
    {
        qciUsed[QciCurrentText[9].toInt()-1]=false;
    }
    QciCurrentText[9]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci5_activated(const QString &arg1)
{
    if(QciCurrentText[10]!="")
    {
        qciUsed[QciCurrentText[10].toInt()-1]=false;
    }
    QciCurrentText[10]=arg1;
    qciUsed[arg1.toInt()-1]=true;

    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci6_activated(const QString &arg1)
{
    if(QciCurrentText[11]!="")
    {
        qciUsed[QciCurrentText[11].toInt()-1]=false;
    }
    QciCurrentText[11]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci7_activated(const QString &arg1)
{
    if(QciCurrentText[12]!="")
    {
        qciUsed[QciCurrentText[12].toInt()-1]=false;
    }
    QciCurrentText[12]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci8_activated(const QString &arg1)
{
    if(QciCurrentText[13]!="")
    {
        qciUsed[QciCurrentText[13].toInt()-1]=false;
    }
    QciCurrentText[13]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxSyncedPingQci9_activated(const QString &arg1)
{
    if(QciCurrentText[14]!="")
    {
        qciUsed[QciCurrentText[14].toInt()-1]=false;
    }
    QciCurrentText[14]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci1_activated(const QString &arg1)
{
    if(QciCurrentText[15]!="")
    {
        qciUsed[QciCurrentText[15].toInt()-1]=false;
    }
    QciCurrentText[15]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci2_activated(const QString &arg1)
{
    if(QciCurrentText[16]!="")
    {
        qciUsed[QciCurrentText[16].toInt()-1]=false;
    }
    QciCurrentText[16]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci3_activated(const QString &arg1)
{
    if(QciCurrentText[17]!="")
    {
        qciUsed[QciCurrentText[17].toInt()-1]=false;
    }
    QciCurrentText[17]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci4_activated(const QString &arg1)
{
    if(QciCurrentText[18]!="")
    {
        qciUsed[QciCurrentText[18].toInt()-1]=false;
    }
    QciCurrentText[18]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci5_activated(const QString &arg1)
{
    if(QciCurrentText[19]!="")
    {
        qciUsed[QciCurrentText[19].toInt()-1]=false;
    }
    QciCurrentText[19]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci6_activated(const QString &arg1)
{
    if(QciCurrentText[20]!="")
    {
        qciUsed[QciCurrentText[20].toInt()-1]=false;
    }
    QciCurrentText[20]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci7_activated(const QString &arg1)
{
    if(QciCurrentText[12]!="")
    {
        qciUsed[QciCurrentText[21].toInt()-1]=false;
    }
    QciCurrentText[21]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci8_activated(const QString &arg1)
{
    if(QciCurrentText[22]!="")
    {
        qciUsed[QciCurrentText[22].toInt()-1]=false;
    }
    QciCurrentText[22]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}

void customModel::on_comboBoxServiceReqQci9_activated(const QString &arg1)
{
    if(QciCurrentText[23]!="")
    {
        qciUsed[QciCurrentText[23].toInt()-1]=false;
    }
    QciCurrentText[23]=arg1;
    qciUsed[arg1.toInt()-1]=true;
    refreshQci();
}
