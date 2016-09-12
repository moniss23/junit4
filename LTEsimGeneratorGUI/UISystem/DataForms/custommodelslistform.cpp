#include "custommodelslistform.h"
#include "ui_custommodelslistform.h"

CustomModelsListForm::CustomModelsListForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CustomModelsListForm)
{
    ui->setupUi(this);
    this->usedQci.setColor(QPalette::WindowText, Qt::green);
    this->unusedQci.setColor(QPalette::WindowText, Qt::red);
    this->currentCM.setColor(QPalette::Window, QColor(0,255,255,150));
    this->usedCM.setColor(QPalette::Window, QColor(Qt::red));
    this->unusedCM.setColor(QPalette::Window, QColor(Qt::green));
    this->currentCustomModelIndex = 0;
    setButtonsPointers();
    setAutoFillButtonsBG();
}

CustomModelsListForm::~CustomModelsListForm()
{
    delete ui;
}

void CustomModelsListForm::open(const QString &projectName, const QString &trafficName, bool *cmUsed) {
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->cmUsed = cmUsed;
    for(unsigned i = 0; i < 10; i++) {
        if(cmUsed[i])
            this->cmButtonsPtr[i]->setStyleSheet("background-color: rgb(0, 255, 0); color: rgb(0, 0, 0)");
        else
            this->cmButtonsPtr[i]->setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(0, 0, 0)");
    }
    this->show();
}

void CustomModelsListForm::on_CM1Button_clicked()
{
    emit loadData(projectName, trafficName, 0);
    this->currentCustomModelIndex = 0;
    this->refreshCmButtonsColors(0);
}

void CustomModelsListForm::on_CM2Button_clicked()
{
    emit loadData(projectName, trafficName, 1);
    this->currentCustomModelIndex = 1;
    this->refreshCmButtonsColors(1);
}

void CustomModelsListForm::on_CM3Button_clicked()
{
    emit loadData(projectName, trafficName, 2);
    this->currentCustomModelIndex = 2;
    this->refreshCmButtonsColors(2);
}

void CustomModelsListForm::on_CM4Button_clicked()
{
    emit loadData(projectName, trafficName, 3);
    this->currentCustomModelIndex = 3;
    this->refreshCmButtonsColors(3);
}

void CustomModelsListForm::on_CM5Button_clicked()
{
    emit loadData(projectName, trafficName, 4);
    this->currentCustomModelIndex = 4;
    this->refreshCmButtonsColors(4);
}

void CustomModelsListForm::on_CM6Button_clicked()
{
    emit loadData(projectName, trafficName, 5);
    this->currentCustomModelIndex = 5;
    this->refreshCmButtonsColors(5);
}

void CustomModelsListForm::on_CM7Button_clicked()
{
    emit loadData(projectName, trafficName, 6);
    this->currentCustomModelIndex = 6;
    this->refreshCmButtonsColors(6);
}

void CustomModelsListForm::on_CM8Button_clicked()
{
    emit loadData(projectName, trafficName, 7);
    this->currentCustomModelIndex = 7;
    this->refreshCmButtonsColors(7);
}

void CustomModelsListForm::on_CM9Button_clicked()
{
    emit loadData(projectName, trafficName, 8);
    this->currentCustomModelIndex = 8;
    this->refreshCmButtonsColors(8);
}

void CustomModelsListForm::on_CM10Button_clicked()
{
    emit loadData(projectName, trafficName, 9);
    this->currentCustomModelIndex = 9;
    this->refreshCmButtonsColors(9);
}

void CustomModelsListForm::on_AddPingButton_clicked()
{
    emit spawnWindow_Ping(projectName, trafficName, currentCustomModelIndex);
}

void CustomModelsListForm::on_AddVoipButton_clicked()
{
    emit spawnWindow_Voip(projectName, trafficName, currentCustomModelIndex);
}

void CustomModelsListForm::on_AddFtpDlButton_clicked()
{
    emit spawnWindow_FtpDl(projectName, trafficName, currentCustomModelIndex);
}

void CustomModelsListForm::on_AddFtpUlButton_clicked()
{
    emit spawnWindow_FtpUl(projectName, trafficName, currentCustomModelIndex);
}

void CustomModelsListForm::currentCustomModelChanged(const CustomModelSettings &customModelSettings, bool *cmUsed) {
    this->customModelSettings = customModelSettings;
    this->cmUsed = cmUsed;
    this->refreshListView();
    this->refreshQci();
}

void CustomModelsListForm::refreshListView()
{
    ui->listWidget->clear();
    for(int i=0;i<customModelSettings.CMPings.size();i++)
        ui->listWidget->addItem("Ping "+QString::number(i+1) + " (" + QString::number(customModelSettings.CMPings[i].pingQci) + ", " + QString::number(customModelSettings.CMPings[i].pingNumberOfPings) + ", " +QString::number(customModelSettings.CMPings[i].pingInterval) + ", " +QString::number(customModelSettings.CMPings[i].pingMinRecievedPings) + ")");
    for(int i=0;i<customModelSettings.CMVoips.size();i++)
        ui->listWidget->addItem("Voip "+QString::number(i+1) + " (" + QString::number(customModelSettings.CMVoips[i].voipQci) +", "+ QString::number(customModelSettings.CMVoips[i].voipDuration) + ", "+ QString::number(customModelSettings.CMVoips[i].voipActivityFactor) + ", "+ QString::number(customModelSettings.CMVoips[i].voipMaxTransferTime) + ", "+ QString::number(customModelSettings.CMVoips[i].voipMinPacketsReceivedInTime) + ")");
    for(int i=0;i<customModelSettings.CMFtpDls.size();i++)
        ui->listWidget->addItem("FTP Dl "+QString::number(i+1) + " (" + QString::number(customModelSettings.CMFtpDls[i].ftpDlQci) + ", " + QString::number(customModelSettings.CMFtpDls[i].ftpDlFilesize) + ", " + QString::number(customModelSettings.CMFtpDls[i].ftpDlMinThroughput) + ")");
    for(int i=0;i<customModelSettings.CMFtpUls.size();i++)
        ui->listWidget->addItem("FTP Ul "+QString::number(i+1) + " (" + QString::number(customModelSettings.CMFtpUls[i].ftpUlQci) + ", " + QString::number(customModelSettings.CMFtpUls[i].ftpUlFilesize) + ", " + QString::number(customModelSettings.CMFtpUls[i].ftpUlMinThroughput) + ")");
    for(int i=0;i<customModelSettings.CMStreamDls.size();i++)
        ui->listWidget->addItem("Stream Dl "+QString::number(i+1) + " (" + QString::number(customModelSettings.CMStreamDls[i].streamDlQci) + ", " + QString::number(customModelSettings.CMStreamDls[i].streamDlSpeed) + ", "+ QString::number(customModelSettings.CMStreamDls[i].streamDlDuration) + ", "+ QString::number(customModelSettings.CMStreamDls[i].streamDlMinThroughput) + ")");
    for(int i=0;i<customModelSettings.CMStreamUls.size();i++)
        ui->listWidget->addItem("Stream Ul "+QString::number(i+1) + " (" + QString::number(customModelSettings.CMStreamUls[i].streamUlQci) + ", " + QString::number(customModelSettings.CMStreamUls[i].streamUlSpeed) + ", "+ QString::number(customModelSettings.CMStreamUls[i].streamUlDuration) + ", "+ QString::number(customModelSettings.CMStreamUls[i].streamUlMinThroughput) + ")");
    for(int i=0;i<customModelSettings.CMSyncedPings.size() ;i++)
    {
        QString temp="["+QString::number(customModelSettings.CMSyncedPings[i].SyncedPingQciArray[0]);
        for(int j=1;j<AmountOfQci;j++)
        {
            if(customModelSettings.CMSyncedPings[i].SyncedPingQciArray[j]!=0)
                temp+=", " + QString::number(customModelSettings.CMSyncedPings[i].SyncedPingQciArray[j]);
        }
        temp+="]";
        ui->listWidget->addItem("Synced Ping "+QString::number(i+1) + " (" + temp + ", " + QString::number(customModelSettings.CMSyncedPings[i].SyncedPingTimeBetweenTasks) + ", "+ QString::number(customModelSettings.CMSyncedPings[i].SyncedPingNumberOfPings) + ", "+ QString::number(customModelSettings.CMSyncedPings[i].SyncedPingInterval)+ ", "+ QString::number(customModelSettings.CMSyncedPings[i].SyncedPingMinReceivedPings) + ")");
    }

    for(int i=0;i<customModelSettings.CMServiceReqs.size() ;i++)
    {
        QString temp="[" + QString::number(customModelSettings.CMServiceReqs[i].ServiceReqQciArray[0]);
        for(int j=1;j<AmountOfQci;j++)
        {
            if(customModelSettings.CMServiceReqs[i].ServiceReqQciArray[j]!=0)
                temp+=", " + QString::number(customModelSettings.CMServiceReqs[i].ServiceReqQciArray[j]);
        }
        temp+="]";
        ui->listWidget->addItem("Service Req "+QString::number(i+1) + " (" + temp + ", " + QString::number(customModelSettings.CMServiceReqs[i].ServiceReqTimeToWaitForAttach) + ", "+ QString::number(customModelSettings.CMServiceReqs[i].ServiceReqIntervalBetweenUlData) + ")");
    }
}

void CustomModelsListForm::refreshQci()
{
    this->ui->Label1->setPalette(customModelSettings.qciUsed[0] ? usedQci : unusedQci);
    this->ui->Label2->setPalette(customModelSettings.qciUsed[1] ? usedQci : unusedQci);
    this->ui->Label3->setPalette(customModelSettings.qciUsed[2] ? usedQci : unusedQci);
    this->ui->Label4->setPalette(customModelSettings.qciUsed[3] ? usedQci : unusedQci);
    this->ui->Label5->setPalette(customModelSettings.qciUsed[4] ? usedQci : unusedQci);
    this->ui->Label6->setPalette(customModelSettings.qciUsed[5] ? usedQci : unusedQci);
    this->ui->Label7->setPalette(customModelSettings.qciUsed[6] ? usedQci : unusedQci);
    this->ui->Label8->setPalette(customModelSettings.qciUsed[7] ? usedQci : unusedQci);
    this->ui->Label9->setPalette(customModelSettings.qciUsed[8] ? usedQci : unusedQci);
}
void CustomModelsListForm::setAutoFillButtonsBG() {
    for(unsigned i = 0; i < 10; i++) {
        cmButtonsPtr[i]->setAutoFillBackground(true);
    }
}

void CustomModelsListForm::setButtonsPointers()
{
    cmButtonsPtr[0] = this->ui->CM1Button;
    cmButtonsPtr[1] = this->ui->CM2Button;
    cmButtonsPtr[2] = this->ui->CM3Button;
    cmButtonsPtr[3] = this->ui->CM4Button;
    cmButtonsPtr[4] = this->ui->CM5Button;
    cmButtonsPtr[5] = this->ui->CM6Button;
    cmButtonsPtr[6] = this->ui->CM7Button;
    cmButtonsPtr[7] = this->ui->CM8Button;
    cmButtonsPtr[8] = this->ui->CM9Button;
    cmButtonsPtr[9] = this->ui->CM10Button;
}

void CustomModelsListForm::refreshCmButtonsColors(const int &index) {
    for(unsigned i = 0; i < 10; i++) {
        if(cmUsed[i])
            this->cmButtonsPtr[i]->setStyleSheet("background-color: rgb(0, 255, 0); color: rgb(0, 0, 0)");
        else
            this->cmButtonsPtr[i]->setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(0, 0, 0)");
    }
    this->cmButtonsPtr[index]->setStyleSheet("background-color: rgb(0, 255, 255); color: rgb(0, 0, 0)");
}

