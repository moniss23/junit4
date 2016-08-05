#include "customModel.h"
#include "ui_customModel.h"
#include <QSortFilterProxyModel>

customModel::customModel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::customModel)
{
    ui->setupUi(this);
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
