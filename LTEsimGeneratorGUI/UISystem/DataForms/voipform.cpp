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

void VoipForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->qciUsed = qciUsed;
    this->clearUi();
    this->show();
}

void VoipForm::on_okButton_clicked()
{
    if(this->ui->qciComboBox->currentText() == "") return;
    this->voip.voipQci = this->ui->qciComboBox->currentText().toInt();
    this->voip.voipDuration = this->ui->duration->text().toInt();
    this->voip.voipActivityFactor = this->ui->activityFactor->text().toInt();
    this->voip.voipMaxTransferTime = this->ui->maxTransferTime->text().toInt();
    this->voip.voipMinPacketsReceivedInTime = this->ui->minPacketsReceivedInTime->text().toInt();

    emit saveVoipData(projectName, trafficName, currentCMindex, voip);
    this->close();
}

void VoipForm::on_cancelButton_clicked()
{
    this->close();
}

void VoipForm::clearUi()
{
    this->ui->qciComboBox->clear();
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
}
