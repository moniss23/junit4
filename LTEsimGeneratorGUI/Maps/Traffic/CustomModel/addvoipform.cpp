#include "addvoipform.h"
#include "ui_addvoipform.h"

QList<QString> VoipList;

AddVoipForm::AddVoipForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddVoipForm)
{
    ui->setupUi(this);
    this->setWindowTitle("addVoip");

    qciAddVoipPointer = ui->qciComboVoip;

    ui->tet_duration->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->tet_maxTransferTime->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->tet_activityFactor->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->tet_minPacketsReceivedInTime->setValidator(new QIntValidator(0, INT_MAX, this));

    ui->qciComboVoip->addItem("");
    for(int i=1; i<10; i++){
        QString index = QString::number(i);
        ui->qciComboVoip->addItem(index);
    }
}

AddVoipForm::~AddVoipForm()
{
    delete ui;
}

void AddVoipForm::on_bt_save_clicked()
{
    addToList();
    SaveAll();
    this->close();
}

void AddVoipForm::on_bt_cancel_clicked()
{
    this->close();
}

void AddVoipForm::on_tet_duration_returnPressed()
{
    addvoip->setDuration(ui->tet_duration->text());
}

void AddVoipForm::on_tet_activityFactor_returnPressed()
{
    addvoip->setActivityFactor(ui->tet_activityFactor->text());
}

void AddVoipForm::on_tet_maxTransferTime_returnPressed()
{
    addvoip->setMaxTransferTime(ui->tet_maxTransferTime->text());
}

void AddVoipForm::on_tet_minPacketsReceivedInTime_returnPressed()
{
    addvoip->setMinPacketsReceivedInTime(ui->tet_minPacketsReceivedInTime->text());
}

void AddVoipForm::SaveAll()
{
    addvoip->setQci(ui->qciComboVoip->currentText());
    addvoip->setDuration(ui->tet_duration->text());
    addvoip->setActivityFactor(ui->tet_activityFactor->text());
    addvoip->setMaxTransferTime(ui->tet_maxTransferTime->text());
    addvoip->setMinPacketsReceivedInTime(ui->tet_minPacketsReceivedInTime->text());
}

void AddVoipForm::setParameters(Addvoip *addvoip)
{
    this->addvoip = addvoip;

    ui->qciComboVoip->setCurrentText(addvoip->getQci());
    ui->tet_duration->setText(addvoip->getduration());
    ui->tet_activityFactor->setText(addvoip->getActivityFactor());
    ui->tet_maxTransferTime->setText(addvoip->getMaxTransferTime());
    ui->tet_minPacketsReceivedInTime->setText(addvoip->getMinPacketsReceivedInTime());
}


void AddVoipForm::addToList(){
    VoipList.clear();
    VoipList.append("AddVoip\nQCI:");
    VoipList.append(ui->qciComboVoip->currentText());
    VoipList.append("Duration:");
    VoipList.append(ui->tet_duration->text());
    VoipList.append("ActivityFactor:");
    VoipList.append(ui->tet_activityFactor->text());
    VoipList.append("MaxTransferTime:");
    VoipList.append(ui->tet_maxTransferTime->text());
    VoipList.append("MinPacketReceivedInTime:");
    VoipList.append(ui->tet_minPacketsReceivedInTime->text());
}
