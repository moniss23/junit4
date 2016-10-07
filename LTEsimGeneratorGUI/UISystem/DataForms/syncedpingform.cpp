#include "syncedpingform.h"
#include "ui_syncedpingform.h"

SyncedPingForm::SyncedPingForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SyncedPingForm), qciUsed(nullptr)
{
    ui->setupUi(this);
    setPtrToCheckbox();
}

SyncedPingForm::~SyncedPingForm()
{
    delete ui;
}

void SyncedPingForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed, const int &syncedPingIndex, const SyncedPing &syncedPing)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->currentSyncedPingIndex = syncedPingIndex;
    this->syncedPing = syncedPing;
    this->qciUsed = qciUsed;
    this->refreshUi();
    this->setWindowFlags( Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
    this->show();
}

void SyncedPingForm::on_okButton_clicked()
{
    SyncedPing syncedPing;
    bool qciChecked = false;
    for(unsigned i = 0; i < 9; i++) {
        if(checkBoxPtr[i]->isChecked()) {
            qciChecked = true;
            syncedPing.SyncedPingQciArray.push_back(i+1);
        }
    }
    if(!qciChecked) return;
    syncedPing.SyncedPingTimeBetweenTasks = this->ui->timeBetweenTasks->text().toInt();
    syncedPing.SyncedPingNumberOfPings = this->ui->numberOfPings->text().toInt();
    syncedPing.SyncedPingInterval = this->ui->interval->text().toInt();
    syncedPing.SyncedPingMinReceivedPings = this->ui->minReceivedPings->text().toInt();

    emit saveSyncedPingData(projectName, trafficName, currentCMindex, syncedPing, currentSyncedPingIndex, modification);
    this->close();
}

void SyncedPingForm::on_cancelButton_clicked()
{
    this->close();
}

void SyncedPingForm::refreshUi()
{
    for(unsigned i = 0; i < 9; i++) {
        this->checkBoxPtr[i]->setChecked(false);
        this->checkBoxPtr[i]->setEnabled(!qciUsed[i]);
    }
    if(syncedPing.SyncedPingQciArray.size() == 0) {
        this->ui->timeBetweenTasks->clear();
        this->ui->numberOfPings->clear();
        this->ui->interval->clear();
        this->ui->minReceivedPings->clear();
        this->modification = false;
    } else {
        for(auto &qci : syncedPing.SyncedPingQciArray) {
            this->checkBoxPtr[qci-1]->setChecked(true);
            this->checkBoxPtr[qci-1]->setEnabled(true);
        }
        this->ui->timeBetweenTasks->setText(QString::number(syncedPing.SyncedPingTimeBetweenTasks));
        this->ui->numberOfPings->setText(QString::number(syncedPing.SyncedPingNumberOfPings));
        this->ui->interval->setText(QString::number(syncedPing.SyncedPingInterval));
        this->ui->minReceivedPings->setText(QString::number(syncedPing.SyncedPingMinReceivedPings));
        this->modification = true;
    }
}

void SyncedPingForm::setPtrToCheckbox()
{
    this->checkBoxPtr[0] = this->ui->qci1;
    this->checkBoxPtr[1] = this->ui->qci2;
    this->checkBoxPtr[2] = this->ui->qci3;
    this->checkBoxPtr[3] = this->ui->qci4;
    this->checkBoxPtr[4] = this->ui->qci5;
    this->checkBoxPtr[5] = this->ui->qci6;
    this->checkBoxPtr[6] = this->ui->qci7;
    this->checkBoxPtr[7] = this->ui->qci8;
    this->checkBoxPtr[8] = this->ui->qci9;
}

void SyncedPingForm::on_restoreButton_clicked()
{
    this->refreshUi();
}
