#include "voipform.h"
#include "ui_voipform.h"

VoipForm::VoipForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoipForm), qciUsed(nullptr)
{
    ui->setupUi(this);
}

VoipForm::~VoipForm()
{
    delete ui;
}

void VoipForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed, const int &voipIndex, const Voip &voip)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->currentVoipIndex = voipIndex;
    this->voip = voip;
    this->qciUsed = qciUsed;
    this->refreshUi();
    this->setWindowFlags( Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
    this->show();
}

void VoipForm::on_okButton_clicked()
{
    Voip voip;
    if(this->ui->qciComboBox->currentText() == "") return;
    voip.voipQci = this->ui->qciComboBox->currentText().toInt();
    voip.voipDuration = this->ui->duration->text().toInt();
    voip.voipActivityFactor = this->ui->activityFactor->text().toInt();
    voip.voipMaxTransferTime = this->ui->maxTransferTime->text().toInt();
    voip.voipMinPacketsReceivedInTime = this->ui->minPacketsReceivedInTime->text().toInt();

    emit saveVoipData(projectName, trafficName, currentCMindex, voip, currentVoipIndex, modification);
    this->close();
}

void VoipForm::on_cancelButton_clicked()
{
    this->close();
}

void VoipForm::on_restoreButton_clicked()
{
    this->refreshUi();
}

void VoipForm::refreshUi()
{
    this->ui->qciComboBox->clear();
    if(voip.voipQci == 0) {
        this->ui->qciComboBox->addItem("");
        for(unsigned i = 0; i < 9; i++) {
            if(!qciUsed[i]) {
                this->ui->qciComboBox->addItem(QString::number(i+1));
            }
        }
        this->ui->duration->clear();
        this->ui->activityFactor->clear();
        this->ui->maxTransferTime->clear();
        this->ui->minPacketsReceivedInTime->clear();
        this->modification = false;
    } else {
        auto index = 0;
        for(auto i = 1; i < 10; i++) {
            if(!qciUsed[i-1]) {
                this->ui->qciComboBox->addItem(QString::number(i));
            }
            else if(i == voip.voipQci) {
                index = this->ui->qciComboBox->count();
                this->ui->qciComboBox->addItem(QString::number(i));
            }
        }
        this->ui->qciComboBox->setCurrentIndex(index);
        this->ui->duration->setText(QString::number(voip.voipDuration));
        this->ui->activityFactor->setText(QString::number(voip.voipActivityFactor));
        this->ui->maxTransferTime->setText(QString::number(voip.voipMaxTransferTime));
        this->ui->minPacketsReceivedInTime->setText(QString::number(voip.voipMinPacketsReceivedInTime));
        this->modification = true;
    }
}
