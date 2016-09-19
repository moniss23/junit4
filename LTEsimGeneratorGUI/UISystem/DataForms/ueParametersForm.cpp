#include "ueParametersForm.h"
#include "ui_ueParametersForm.h"

UeParametersForm::UeParametersForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UeParametersForm)
{
    ui->setupUi(this);
    this->setWindowTitle("UeData");
    this->ui->frstMobilityModelComboBox->addItems(UeParametersForm::MOBILITYSTRINGLIST);
    this->ui->scndMobilityModelComboBox->addItems(UeParametersForm::MOBILITYSTRINGLIST);
    this->ui->frstCsModelComboBox->addItems(UeParametersForm::CSSTRINGLIST);
    this->ui->scndCsModelComboBox->addItems(UeParametersForm::CSSTRINGLIST);
    this->ui->frstPsModelComboBox->addItems(UeParametersForm::PSSTRINGLIST);
    this->ui->scndPsModelComboBox->addItems(UeParametersForm::PSSTRINGLIST);
    this->ui->frstUeTypeComboBox->addItem("iratHO");
    this->ui->scndUeTypeComboBox->addItem("iratHO");
}

UeParametersForm::~UeParametersForm()
{
    delete ui;
}

void UeParametersForm::loadAndOpen(const QString &projectName, const QString &trafficName, const UEData &ueData)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->ueData = ueData;
    this->refreshUi();
    this->show();
}

void UeParametersForm::on_pairNameLineEdit_editingFinished()
{

}

void UeParametersForm::on_amountOfPairsSpinBox_editingFinished()
{

}

void UeParametersForm::on_frstMobilityModelComboBox_currentIndexChanged(int index) {
    (void) index;
}

void UeParametersForm::on_scndMobilityModelComboBox_currentIndexChanged(int index) {
    (void) index;
}

void UeParametersForm::on_frstCsModelComboBox_currentIndexChanged(int index) {
    (void) index;
}

void UeParametersForm::on_scndCsModelComboBox_currentIndexChanged(int index) {
    (void) index;
}

void UeParametersForm::on_frstPsModelComboBox_currentIndexChanged(int index) {
    (void) index;
}

void UeParametersForm::on_scndPsModelComboBox_currentIndexChanged(int index) {
    (void) index;
}

void UeParametersForm::on_frstUeTypeComboBox_currentIndexChanged(int index) {
    (void) index;
}

void UeParametersForm::on_scndUeTypeComboBox_currentIndexChanged(int index) {
    (void) index;
}

void UeParametersForm::refreshUi()
{
    this->ui->pairNameLineEdit->setText(ueData.pairName);
    this->ui->amountOfPairsSpinBox->setValue(ueData.amountOfPairs);
    this->ui->frstAreaLineEdit->setText(ueData.ueArea.first);
    this->ui->scndAreaLineEdit->setText(ueData.ueArea.second);
}

const QStringList UeParametersForm::CSSTRINGLIST = {
    "PowerOnPowerOff",
    "poweron",
    "PowerOnOffPsCnt",
    "PowerOnOffPsCntRecover",
    "PowerOnForcePowerOff",
    "PowerOnPowerOffEmergency",
    "PowerOnEmergency",
    "PowerOnOffPsCntEmergency",
    "PowerOnOffPsCntRecoverEmergency",
    "PowerOnForcePowerOffEmergency"
};

const QStringList UeParametersForm::PSSTRINGLIST = {
    "NoPs",
    "general_10s_50Mbps",
    "general_infinite_200Mbps",
    "LteFtpEightBearers",
    "LteBatStaticPing",
    "LtePing",
    "LtePingFtpOnDefault",
    "LtePingFtpDlOnDefault",
    "LtePingFtpUlOnDefault",
    "LteFtpGet",
    "LteFtpPut",
    "LteInstantMsgOrig",
    "LteInstantMsgOrig2Pdn",
    "LteInstantMsgTerm",
    "LteInstantMsgTerm2Pdn",
    "LteMobileTv",
    "LteP2P",
    "LteP2P2Pdn",
    "LtePDStreaming",
    "LtePDStreaming2Pdn",
    "LteRealTimeStreaming",
    "LteRealTimeStreaming2Pdn",
    "LteRealTimeStreamingDynSpeed",
    "LteServiceReq",
    "LteWww",
    "LteWww2Pdn"
};

const QStringList UeParametersForm::MOBILITYSTRINGLIST = {
    "RandomWalker",
    "standstill",
    "HorizontalWalker",
    "VerticalWalker",
    "WalkerStartAtEast",
    "WalkerStartAtNorth",
    "WalkerStartAtSouth",
    "WalkerStartAtWest"
};
