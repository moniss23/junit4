#include "ueParametersForm.h"
#include "ui_ueParametersForm.h"

UeParametersForm::UeParametersForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UeParametersForm)
{
    ui->setupUi(this);
    this->ui->frstMobilityModelComboBox->addItems(UeParametersForm::MOBILITYSTRINGLIST);
    this->ui->scndMobilityModelComboBox->addItems(UeParametersForm::MOBILITYSTRINGLIST);
    this->ui->frstCsModelComboBox->addItems(UeParametersForm::CSSTRINGLIST);
    this->ui->scndCsModelComboBox->addItems(UeParametersForm::CSSTRINGLIST);
    this->ui->frstUeTypeComboBox->addItems(UeParametersForm::UESTRINGLIST);
    this->ui->scndUeTypeComboBox->addItems(UeParametersForm::UESTRINGLIST);
}

UeParametersForm::~UeParametersForm()
{
    delete ui;
}

void UeParametersForm::loadAndOpen(const QString &projectName, const QString &trafficName, const UEData &ueData, const QStringList &customModelsList, const QStringList &cellsAndHo)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->ueData = ueData;
    this->customModelsList = customModelsList;
    this->cellsAndHandovers = cellsAndHo;
    this->refreshUi();
        this->setWindowFlags( Qt::Dialog | Qt::WindowStaysOnTopHint);
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
    this->ui->frstPsModelComboBox->clear();
    this->ui->scndPsModelComboBox->clear();
    this->ui->frstArea->clear();
    this->ui->scndArea->clear();
    this->ui->frstPsModelComboBox->addItem("NoPs");
    this->ui->frstPsModelComboBox->addItems(customModelsList);
    this->ui->frstPsModelComboBox->addItems(UeParametersForm::PSSTRINGLIST);
    this->ui->scndPsModelComboBox->addItem("NoPs");
    this->ui->scndPsModelComboBox->addItems(customModelsList);
    this->ui->scndPsModelComboBox->addItems(UeParametersForm::PSSTRINGLIST);
    this->ui->frstArea->addItem(QString());
    this->ui->scndArea->addItem(QString());
    this->ui->frstArea->addItems(cellsAndHandovers);
    this->ui->scndArea->addItems(cellsAndHandovers);
    this->ui->frstPsModelComboBox->setCurrentText(this->ueData.psModelsPair.first);
    this->ui->scndPsModelComboBox->setCurrentText(this->ueData.psModelsPair.second);
    this->ui->frstCsModelComboBox->setCurrentText(this->ueData.csModelsPair.first);
    this->ui->scndCsModelComboBox->setCurrentText(this->ueData.csModelsPair.second);
    this->ui->frstMobilityModelComboBox->setCurrentText(this->ueData.mobilityModelsPair.first);
    this->ui->scndMobilityModelComboBox->setCurrentText(this->ueData.mobilityModelsPair.second);
    this->ui->frstUeTypeComboBox->setCurrentText(this->ueData.ueTypesPair.first);
    this->ui->scndUeTypeComboBox->setCurrentText(this->ueData.ueTypesPair.second);
    this->ui->pairNameLineEdit->setText(ueData.pairName);
    this->ui->amountOfPairsSpinBox->setValue(ueData.amountOfPairs);
    this->ui->frstArea->setCurrentText(this->ueData.ueArea.first);
    this->ui->scndArea->setCurrentText(this->ueData.ueArea.second);
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
    "LteWww2Pdn",
    "LteBatRealTimeStreaming",
    "LteBatRealTimeStreamingDLUL",
    "LteBatPDStreaming",
    "LteBatWww",
    "LteBatInstantMessaging",
    "LteBatP2P",
    "LteBatPing",
    "LteBatMobileTv",
    "LteMMTelAudioVisualOrig2Pdn",
    "LteMMTelStaticBearerPingOnDefault",
    "LteMMTelStaticBearerFtpDlOnDefault",
    "LteMMTelDynamicBearerPingOnDefault",
    "LteMMTelVoip",
    "LteMMTelVoip50",
    "LteMMTelVoip2Pdn50",
    "LteMMTelVoipTerm",
    "LteMMTelVoipTerm50",
    "LteMMTelVoipTerm2Pdn50"
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

const QStringList UeParametersForm::UESTRINGLIST = {
    "iratHO",
    "lteUe3CCa",
    "lteUeApn",
    "lteUeCa",
    "lteUeEmergency",
    "lteUePlmn",
    "lteUeRohc"
};

void UeParametersForm::on_restoreChangesButton_clicked()
{
    this->refreshUi();
}

void UeParametersForm::on_okButton_clicked()
{
    QString oldName = this->ueData.pairName;
    this->ueData.pairName = this->ui->pairNameLineEdit->text();
    this->ueData.amountOfPairs = this->ui->amountOfPairsSpinBox->value();
    this->ueData.mobilityModelsPair.first = this->ui->frstMobilityModelComboBox->currentText();
    this->ueData.mobilityModelsPair.second = this->ui->scndMobilityModelComboBox->currentText();
    this->ueData.csModelsPair.first = this->ui->frstCsModelComboBox->currentText();
    this->ueData.csModelsPair.second = this->ui->scndCsModelComboBox->currentText();
    this->ueData.psModelsPair.first = this->ui->frstPsModelComboBox->currentText();
    this->ueData.psModelsPair.second = this->ui->scndPsModelComboBox->currentText();
    this->ueData.ueTypesPair.first = this->ui->frstUeTypeComboBox->currentText();
    this->ueData.ueTypesPair.second = this->ui->scndUeTypeComboBox->currentText();
    this->ueData.ueArea.first = this->ui->frstArea->currentText();
    this->ueData.ueArea.second = this->ui->scndArea->currentText();

    emit saveUEData(projectName, trafficName, oldName, this->ueData);
    this->close();
}

void UeParametersForm::on_cancelButton_clicked()
{
    this->close();
}
