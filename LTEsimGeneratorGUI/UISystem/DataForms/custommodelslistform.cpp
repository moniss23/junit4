#include "custommodelslistform.h"
#include "ui_custommodelslistform.h"

CustomModelsListForm::CustomModelsListForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CustomModelsListForm)
{
    ui->setupUi(this);
    this->usedQci.setColor(QPalette::WindowText, Qt::red);
    this->unusedQci.setColor(QPalette::WindowText, Qt::green);
    this->currentCustomModelIndex = 0;
}

CustomModelsListForm::~CustomModelsListForm()
{
    delete ui;
}

void CustomModelsListForm::open(const QString &projectName, const QString &trafficName) {
    this->projectName = projectName;
    this->trafficName = trafficName;

    this->show();
}

void CustomModelsListForm::loadData() {

}

void CustomModelsListForm::on_CM1Button_clicked()
{
    emit loadData(projectName, trafficName, 0);
}

void CustomModelsListForm::on_CM2Button_clicked()
{
    emit loadData(projectName, trafficName, 1);
}

void CustomModelsListForm::on_CM3Button_clicked()
{
    emit loadData(projectName, trafficName, 2);
}

void CustomModelsListForm::on_CM4Button_clicked()
{
    emit loadData(projectName, trafficName, 3);
}

void CustomModelsListForm::on_CM5Button_clicked()
{
    emit loadData(projectName, trafficName, 4);
}

void CustomModelsListForm::on_CM6Button_clicked()
{
    emit loadData(projectName, trafficName, 5);
}

void CustomModelsListForm::on_CM7Button_clicked()
{
    emit loadData(projectName, trafficName, 6);
}

void CustomModelsListForm::on_CM8Button_clicked()
{
    emit loadData(projectName, trafficName, 7);
}

void CustomModelsListForm::on_CM9Button_clicked()
{
    emit loadData(projectName, trafficName, 8);
}

void CustomModelsListForm::on_CM10Button_clicked()
{
    emit loadData(projectName, trafficName, 9);
}

void CustomModelsListForm::on_AddPingButton_clicked()
{
    emit spawnWindow_Ping(projectName, trafficName, currentCustomModelIndex);
}

void CustomModelsListForm::currentCustomModelChanged(const CustomModelSettings &customModelSettings) {
    this->customModelSettings = customModelSettings;
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
