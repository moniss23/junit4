#include "statisticsForm.h"
#include "ui_statisticsform.h"

StatisticsForm::StatisticsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsForm)
{
    ui->setupUi(this);
    this->setFixedSize(413, 523);
}

StatisticsForm::~StatisticsForm() {
    delete ui;
}

void StatisticsForm::loadAndSpawn(const QString &projectName, const QString &trafficFileName, const StatisticsData& statisticsData)
{
    this->projectName = projectName;
    this->trafficFileName = trafficFileName;
    this->statisticsData = statisticsData;
    refreshUi();
    this->setWindowFlags( Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
    this->show();
}


void StatisticsForm::on_pushButton_clicked()
{
    this->close();
}
void StatisticsForm::on_saveButton_clicked()
{
    saveStatisticsData();
    emit updateStatisticsData(projectName, trafficFileName, statisticsData);
    this->close();
}

void StatisticsForm::on_restoreButton_clicked()
{
    refreshUi();
}

void StatisticsForm::refreshUi()
{
    //General tab
    this->ui->ueStatisticsCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->ueStatisticsCheckBox->text()));
    this->ui->modelExpNasCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->modelExpNasCheckBox->text()));
    this->ui->modelExpRrcCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->modelExpRrcCheckBox->text()));
    this->ui->modelExpMobilityCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->modelExpMobilityCheckBox->text()));
    this->ui->modelExpThroughputCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->modelExpThroughputCheckBox->text()));
    this->ui->perUeThroughputCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->perUeThroughputCheckBox->text()));
    this->ui->ueExpMobilityCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->ueExpMobilityCheckBox->text()));
    this->ui->modelExpPsCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->modelExpPsCheckBox->text()));
    this->ui->ueExpPsCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->ueExpPsCheckBox->text()));
    this->ui->modelExpCsCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->modelExpCsCheckBox->text()));
    this->ui->ueExpCsCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->ueExpCsCheckBox->text()));
    this->ui->writeGeneralStatisticsToFileCheckBox->setChecked(!statisticsData.getStatMapFor(this->ui->writeGeneralStatisticsToFileCheckBox->text()));
    this->ui->writeGeneralStatisticsToFileCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->writeGeneralStatisticsToFileCheckBox->text()));
    this->ui->ueLineEdit->setText(statisticsData.generalUe);
    this->ui->delayBetweenPacketsLineEdit->setText(statisticsData.generalDelayBetweenPackets);
    this->ui->generalNumberOfSecondsLineEdit->setText(statisticsData.generalTotalNumberOfSeconds);
    this->ui->mtuSizeLineEdit->setText(statisticsData.generalMtuSize);
    this->ui->generalMeasurementLineEdit->setText(statisticsData.generalMeasurementDelta);
    //IPEX tab
    this->ui->ipexProtocolStatsCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->ipexProtocolStatsCheckBox->text()));
    this->ui->tguStatsCheckBox->setChecked(!statisticsData.getStatMapFor(this->ui->tguStatsCheckBox->text()));
    this->ui->tguStatsCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->tguStatsCheckBox->text()));
    this->ui->ipexTguImsiLineEdit->setText(statisticsData.ipexTguImsi);
    this->ui->writeIpexToFileCheckBox->setChecked(!statisticsData.getStatMapFor(this->ui->writeIpexToFileCheckBox->text()));
    this->ui->writeIpexToFileCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->writeIpexToFileCheckBox->text()));
    this->ui->ipexFilenameLineEdit->setText(statisticsData.ipexFileName);
    this->ui->ipexNumberOfSecondsLineEdit->setText(statisticsData.ipexFileName);
    this->ui->ipexMeasurementLineEdit->setText(statisticsData.ipexFileName);
    //PDCP-U tab
    this->ui->pdcpuProtocolStatsCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->pdcpuProtocolStatsCheckBox->text()));
    this->ui->rohcStatsCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->rohcStatsCheckBox->text()));
    this->ui->bearerStatusWordsCheckBox->setChecked(!statisticsData.getStatMapFor(this->ui->bearerStatusWordsCheckBox->text()));
    this->ui->bearerStatusWordsCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->bearerStatusWordsCheckBox->text()));
    this->ui->bearerStatusImsiLineEdit->setText(statisticsData.pdcpuBearerStatusImsi);
    this->ui->bearerStatusEpsBearerIdLineEdit->setText(statisticsData.pdcpuBearerStatusEpsBearerId);
    this->ui->bearerStatusImsiLineEdit->setText(statisticsData.pdcpuBearerRohcImsi);
    this->ui->bearerStatusEpsBearerIdLineEdit->setText(statisticsData.pdcpuBearerRohcEpsBearerId);
    this->ui->bearerRohcCheckBox->setChecked(!statisticsData.getStatMapFor(this->ui->bearerRohcCheckBox->text()));
    this->ui->bearerRohcCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->bearerRohcCheckBox->text()));
    this->ui->bearerRohcImsiLineEdit->setText(statisticsData.pdcpuBearerErrorImsi);
    this->ui->bearerRohcEpsBearerIdLineEdit->setText(statisticsData.pdcpuBearerErrorEpsBearerId);
    this->ui->writePdcpuToFileCheckBox->setChecked(!statisticsData.getStatMapFor(this->ui->writePdcpuToFileCheckBox->text()));
    this->ui->writePdcpuToFileCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->writePdcpuToFileCheckBox->text()));
    this->ui->pdcpuFilenameLineEdit->setText(statisticsData.pdcpuFileName);
    this->ui->pdcpuNumberOfSecondsLineEdit->setText(statisticsData.pdcpuSeconds);
    this->ui->pdcpuMeasurementLineEdit->setText(statisticsData.pdcpuMeasurement);
    this->ui->bearerErrorCheckBox->setChecked(!statisticsData.getStatMapFor(this->ui->bearerErrorCheckBox->text()));
    this->ui->bearerErrorCheckBox->setChecked(statisticsData.getStatMapFor(this->ui->bearerErrorCheckBox->text()));
    this->ui->bearerErrorImsiLineEdit->setText(statisticsData.pdcpuBearerErrorImsi);
    this->ui->bearerErrorEpsBearerIdLineEdit->setText(statisticsData.pdcpuBearerErrorEpsBearerId);
}

void StatisticsForm::saveStatisticsData()
{
    //General tab
    statisticsData.setStatMapFor(this->ui->ueStatisticsCheckBox->text(), this->ui->ueStatisticsCheckBox->isChecked());
    statisticsData.setStatMapFor(this->ui->modelExpNasCheckBox->text(), this->ui->modelExpNasCheckBox->isChecked());
    statisticsData.setStatMapFor(this->ui->modelExpRrcCheckBox->text(), this->ui->modelExpRrcCheckBox->isChecked());
    statisticsData.setStatMapFor(this->ui->modelExpMobilityCheckBox->text(), this->ui->modelExpMobilityCheckBox->isChecked());
    statisticsData.setStatMapFor(this->ui->modelExpThroughputCheckBox->text(), this->ui->modelExpThroughputCheckBox->isChecked());
    statisticsData.setStatMapFor(this->ui->perUeThroughputCheckBox->text(), this->ui->perUeThroughputCheckBox->isChecked());
    statisticsData.setStatMapFor(this->ui->ueExpMobilityCheckBox->text(), this->ui->ueExpMobilityCheckBox->isChecked());
    statisticsData.setStatMapFor(this->ui->modelExpPsCheckBox->text(), this->ui->modelExpPsCheckBox->isChecked());
    statisticsData.setStatMapFor(this->ui->ueExpPsCheckBox->text(), this->ui->ueExpPsCheckBox->isChecked());
    statisticsData.setStatMapFor(this->ui->modelExpCsCheckBox->text(), this->ui->modelExpCsCheckBox->isChecked());
    statisticsData.setStatMapFor(this->ui->ueExpCsCheckBox->text(), this->ui->ueExpCsCheckBox->isChecked());
    statisticsData.setStatMapFor(this->ui->writeGeneralStatisticsToFileCheckBox->text(), this->ui->writeGeneralStatisticsToFileCheckBox->isChecked());
    statisticsData.generalUe = this->ui->ueLineEdit->text();
    statisticsData.generalDelayBetweenPackets = this->ui->delayBetweenPacketsLineEdit->text();
    statisticsData.generalTotalNumberOfSeconds = this->ui->generalNumberOfSecondsLineEdit->text();
    statisticsData.generalMtuSize = this->ui->mtuSizeLineEdit->text();
    statisticsData.generalMeasurementDelta = this->ui->generalMeasurementLineEdit->text();
    //IPEX tab
    statisticsData.setStatMapFor(this->ui->ipexProtocolStatsCheckBox->text(), this->ui->ipexProtocolStatsCheckBox->isChecked());
    statisticsData.setStatMapFor(this->ui->tguStatsCheckBox->text(), this->ui->tguStatsCheckBox->isChecked());
    statisticsData.ipexTguImsi = this->ui->ipexTguImsiLineEdit->text();
    statisticsData.setStatMapFor(this->ui->writeIpexToFileCheckBox->text(), this->ui->writeIpexToFileCheckBox->isChecked());
    statisticsData.ipexFileName = this->ui->ipexFilenameLineEdit->text();
    statisticsData.ipexSeconds = this->ui->ipexNumberOfSecondsLineEdit->text();
    statisticsData.ipexMeasurement = this->ui->ipexMeasurementLineEdit->text();
    //PDCP-U tab
    statisticsData.setStatMapFor(this->ui->pdcpuProtocolStatsCheckBox->text(), this->ui->pdcpuProtocolStatsCheckBox->isChecked());
    statisticsData.setStatMapFor(this->ui->rohcStatsCheckBox->text(), this->ui->rohcStatsCheckBox->isChecked());
    statisticsData.setStatMapFor(this->ui->bearerStatusWordsCheckBox->text(), this->ui->bearerStatusWordsCheckBox->isChecked());
    statisticsData.pdcpuBearerStatusImsi = this->ui->bearerStatusImsiLineEdit->text();
    statisticsData.pdcpuBearerStatusEpsBearerId = this->ui->bearerStatusEpsBearerIdLineEdit->text();
    statisticsData.setStatMapFor(this->ui->bearerRohcCheckBox->text(), this->ui->bearerRohcCheckBox->isChecked());
    statisticsData.pdcpuBearerRohcImsi = this->ui->bearerRohcImsiLineEdit->text();
    statisticsData.pdcpuBearerRohcEpsBearerId = this->ui->bearerRohcEpsBearerIdLineEdit->text();
    statisticsData.setStatMapFor(this->ui->bearerErrorCheckBox->text(), this->ui->bearerErrorCheckBox->isChecked());
    statisticsData.pdcpuBearerErrorImsi = this->ui->bearerErrorImsiLineEdit->text();
    statisticsData.pdcpuBearerErrorEpsBearerId = this->ui->bearerErrorEpsBearerIdLineEdit->text();
    statisticsData.setStatMapFor(this->ui->writePdcpuToFileCheckBox->text(), this->ui->writePdcpuToFileCheckBox->isChecked());
    statisticsData.pdcpuFileName = this->ui->pdcpuFilenameLineEdit->text();
    statisticsData.pdcpuSeconds = this->ui->pdcpuNumberOfSecondsLineEdit->text();
    statisticsData.pdcpuMeasurement = this->ui->pdcpuMeasurementLineEdit->text();
}

void StatisticsForm::on_bearerStatusWordsCheckBox_toggled(bool checked)
{
    this->ui->bearerStatusImsiLabel->setEnabled(checked);
    this->ui->bearerStatusImsiLineEdit->setEnabled(checked);
    this->ui->bearerStatusEpsBearerIdLabel->setEnabled(checked);
    this->ui->bearerStatusEpsBearerIdLineEdit->setEnabled(checked);
}

void StatisticsForm::on_bearerRohcCheckBox_toggled(bool checked)
{
    this->ui->bearerRohcImsiLabel->setEnabled(checked);
    this->ui->bearerRohcImsiLineEdit->setEnabled(checked);
    this->ui->bearerRohcEpsBearerIdLabel->setEnabled(checked);
    this->ui->bearerRohcEpsBearerIdLineEdit->setEnabled(checked);
}

void StatisticsForm::on_bearerErrorCheckBox_toggled(bool checked)
{
    this->ui->bearerErrorImsiLabel->setEnabled(checked);
    this->ui->bearerErrorImsiLineEdit->setEnabled(checked);
    this->ui->bearerErrorEpsBearerIdLabel->setEnabled(checked);
    this->ui->bearerErrorEpsBearerIdLineEdit->setEnabled(checked);
}

void StatisticsForm::on_writePdcpuToFileCheckBox_toggled(bool checked)
{
    this->ui->pdcpuFilenameLabel->setEnabled(checked);
    this->ui->pdcpuFilenameLineEdit->setEnabled(checked);
    this->ui->pdcpuNumberOfSecondsLabel->setEnabled(checked);
    this->ui->pdcpuNumberOfSecondsLineEdit->setEnabled(checked);
    this->ui->pdcpuMeasurementLabel->setEnabled(checked);
    this->ui->pdcpuMeasurementLineEdit->setEnabled(checked);
}

void StatisticsForm::on_tguStatsCheckBox_toggled(bool checked)
{
    this->ui->ipexTguImsiLabel->setEnabled(checked);
    this->ui->ipexTguImsiLineEdit->setEnabled(checked);
}

void StatisticsForm::on_writeIpexToFileCheckBox_toggled(bool checked)
{
    this->ui->ipexFilenameLabel->setEnabled(checked);
    this->ui->ipexFilenameLineEdit->setEnabled(checked);
    this->ui->ipexNumberOfSecondsLabel->setEnabled(checked);
    this->ui->ipexNumberOfSecondsLineEdit->setEnabled(checked);
    this->ui->ipexMeasurementLabel->setEnabled(checked);
    this->ui->ipexMeasurementLineEdit->setEnabled(checked);
}

void StatisticsForm::on_writeGeneralStatisticsToFileCheckBox_toggled(bool checked)
{
    this->ui->writeGeneralStatisticsToFileCheckBox->setChecked(checked);

    this->ui->ueLabel->setEnabled(checked);
    this->ui->ueLineEdit->setEnabled(checked);
    this->ui->delayBetweenPacketsLabel->setEnabled(checked);
    this->ui->delayBetweenPacketsLineEdit->setEnabled(checked);
    this->ui->mtuSizeLabel->setEnabled(checked);
    this->ui->mtuSizeLineEdit->setEnabled(checked);
    this->ui->generalNumberOfSecondsLabel->setEnabled(checked);
    this->ui->generalNumberOfSecondsLineEdit->setEnabled(checked);
    this->ui->generalMeasurementLabel->setEnabled(checked);
    this->ui->generalMeasurementLineEdit->setEnabled(checked);
}
