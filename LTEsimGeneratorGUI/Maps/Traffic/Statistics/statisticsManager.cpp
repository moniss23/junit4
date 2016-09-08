#include "statisticsManager.h"
#include "ui_statistics.h"
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>

StatisticsManager::StatisticsManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistics)
{
    ui->setupUi(this);
    this->setFixedSize(413, 523);
    this->setWindowTitle("Statistics");
    updateView();
}

StatisticsManager::~StatisticsManager() {
    delete ui;
}

void StatisticsManager::loadAndSpawn(const QString &projectName, const QString &trafficFileName, const StatisticsData& statisticsData)
{
    this->projectName = projectName;
    this->trafficFileName = trafficFileName;
    this->statisticsData = statisticsData;
    updateView();
    this->show();
}

void StatisticsManager::on_saveButton_clicked()
{
    saveStatisticsData();
    emit updateStatisticsData(statisticsData); // TODO when trafficWindowManager is created: {TrafficWindow.TrafficFile.StatisticsData = localStats;}
}

void StatisticsManager::on_restoreButton_clicked()
{
    emit restoreDefaultValues(); //TODO when trafficWindowManager is created: {localStats = TraficWindow.TrafficFileData.StatisticsData;}
    updateView();
}

void StatisticsManager::on_writePdcpuToFileCheckBox_clicked(bool checked)
{
    ui->pdcpuFilenameLabel->setEnabled(checked);
    ui->pdcpuFilenameLineEdit->setEnabled(checked);
    ui->pdcpuNumberOfSecondsLabel->setEnabled(checked);
    ui->pdcpuNumberOfSecondsLineEdit->setEnabled(checked);
    ui->pdcpuMeasurementLabel->setEnabled(checked);
    ui->pdcpuMeasurementLineEdit->setEnabled(checked);
}

void StatisticsManager::on_bearerErrorCheckBox_clicked(bool checked)
{
    ui->bearerErrorImsiLabel->setEnabled(checked);
    ui->bearerErrorImsiLineEdit->setEnabled(checked);
    ui->bearerErrorEpsBearerIdLabel->setEnabled(checked);
    ui->bearerErrorEpsBearerIdLineEdit->setEnabled(checked);
}

void StatisticsManager::on_bearerRohcCheckBox_clicked(bool checked)
{
    ui->bearerRohcImsiLabel->setEnabled(checked);
    ui->bearerRohcImsiLineEdit->setEnabled(checked);
    ui->bearerRohcEpsBearerIdLabel->setEnabled(checked);
    ui->bearerRohcEpsBearerIdLineEdit->setEnabled(checked);
}

void StatisticsManager::on_bearerStatusWordsCheckBox_clicked(bool checked)
{
    ui->bearerStatusImsiLabel->setEnabled(checked);
    ui->bearerStatusImsiLineEdit->setEnabled(checked);
    ui->bearerStatusEpsBearerIdLabel->setEnabled(checked);
    ui->bearerStatusEpsBearerIdLineEdit->setEnabled(checked);
}

void StatisticsManager::on_tguStatsCheckBox_clicked(bool checked)
{
    ui->ipexTguImsiLabel->setEnabled(checked);
    ui->ipexTguImsiLineEdit->setEnabled(checked);
}

void StatisticsManager::on_writeIpexToFileCheckBox_clicked(bool checked)
{
    ui->ipexFilenameLabel->setEnabled(checked);
    ui->ipexFilenameLineEdit->setEnabled(checked);
    ui->ipexNumberOfSecondsLabel->setEnabled(checked);
    ui->ipexNumberOfSecondsLineEdit->setEnabled(checked);
    ui->ipexMeasurementLabel->setEnabled(checked);
    ui->ipexMeasurementLineEdit->setEnabled(checked);
}

void StatisticsManager::on_writeGeneralStatisticsToFileCheckBox_clicked(bool checked)
{
    ui->ueLabel->setEnabled(checked);
    ui->ueLineEdit->setEnabled(checked);
    ui->delayBetweenPacketsLabel->setEnabled(checked);
    ui->delayBetweenPacketsLineEdit->setEnabled(checked);
    ui->mtuSizeLabel->setEnabled(checked);
    ui->mtuSizeLineEdit->setEnabled(checked);
    ui->generalNumberOfSecondsLabel->setEnabled(checked);
    ui->generalNumberOfSecondsLineEdit->setEnabled(checked);
    ui->generalMeasurementLabel->setEnabled(checked);
    ui->generalMeasurementLineEdit->setEnabled(checked);
}

void StatisticsManager::updateView()
{
    //General tab
    ui->ueStatisticsCheckBox->setChecked(statisticsData.getStatMapFor(ui->ueStatisticsCheckBox->text()));
    ui->modelExpNasCheckBox->setChecked(statisticsData.getStatMapFor(ui->modelExpNasCheckBox->text()));
    ui->modelExpRrcCheckBox->setChecked(statisticsData.getStatMapFor(ui->modelExpRrcCheckBox->text()));
    ui->modelExpMobilityCheckBox->setChecked(statisticsData.getStatMapFor(ui->modelExpMobilityCheckBox->text()));
    ui->modelExpThroughputCheckBox->setChecked(statisticsData.getStatMapFor(ui->modelExpThroughputCheckBox->text()));
    ui->perUeThroughputCheckBox->setChecked(statisticsData.getStatMapFor(ui->perUeThroughputCheckBox->text()));
    ui->ueExpMobilityCheckBox->setChecked(statisticsData.getStatMapFor(ui->ueExpMobilityCheckBox->text()));
    ui->modelExpPsCheckBox->setChecked(statisticsData.getStatMapFor(ui->modelExpPsCheckBox->text()));
    ui->ueExpPsCheckBox->setChecked(statisticsData.getStatMapFor(ui->ueExpPsCheckBox->text()));
    ui->modelExpCsCheckBox->setChecked(statisticsData.getStatMapFor(ui->modelExpCsCheckBox->text()));
    ui->ueExpCsCheckBox->setChecked(statisticsData.getStatMapFor(ui->ueExpCsCheckBox->text()));
    ui->writeGeneralStatisticsToFileCheckBox->clicked(statisticsData.getStatMapFor(ui->writeGeneralStatisticsToFileCheckBox->text()));
    ui->ueLineEdit->setText(statisticsData.generalUe);
    ui->delayBetweenPacketsLineEdit->setText(statisticsData.generalDelayBetweenPackets);
    ui->generalNumberOfSecondsLineEdit->setText(statisticsData.generalTotalNumberOfSeconds);
    ui->mtuSizeLineEdit->setText(statisticsData.generalMtuSize);
    ui->generalMeasurementLineEdit->setText(statisticsData.generalMeasurementDelta);
    //IPEX tab
    ui->ipexProtocolStatsCheckBox->setChecked(statisticsData.getStatMapFor(ui->ipexProtocolStatsCheckBox->text()));
    ui->tguStatsCheckBox->clicked(statisticsData.getStatMapFor(ui->tguStatsCheckBox->text()));
    ui->ipexTguImsiLineEdit->setText(statisticsData.ipexTguImsi);
    ui->writeIpexToFileCheckBox->clicked(statisticsData.getStatMapFor(ui->writeIpexToFileCheckBox->text()));
    ui->ipexFilenameLineEdit->setText(statisticsData.ipexFileName);
    ui->ipexNumberOfSecondsLineEdit->setText(statisticsData.ipexFileName);
    ui->ipexMeasurementLineEdit->setText(statisticsData.ipexFileName);
    //PDCP-U tab
    ui->pdcpuProtocolStatsCheckBox->setChecked(statisticsData.getStatMapFor(ui->pdcpuProtocolStatsCheckBox->text()));
    ui->rohcStatsCheckBox->setChecked(statisticsData.getStatMapFor(ui->rohcStatsCheckBox->text()));
    ui->bearerStatusWordsCheckBox->clicked(statisticsData.getStatMapFor(ui->bearerStatusWordsCheckBox->text()));
    ui->bearerStatusImsiLineEdit->setText(statisticsData.pdcpuBearerStatusImsi);
    ui->bearerStatusEpsBearerIdLineEdit->setText(statisticsData.pdcpuBearerStatusEpsBearerId);
    ui->bearerRohcCheckBox->clicked(statisticsData.getStatMapFor(ui->bearerRohcCheckBox->text()));
    ui->bearerStatusImsiLineEdit->setText(statisticsData.pdcpuBearerRohcImsi);
    ui->bearerStatusEpsBearerIdLineEdit->setText(statisticsData.pdcpuBearerRohcEpsBearerId);
    ui->bearerRohcCheckBox->clicked(statisticsData.getStatMapFor(ui->bearerRohcCheckBox->text()));
    ui->bearerRohcImsiLineEdit->setText(statisticsData.pdcpuBearerErrorImsi);
    ui->bearerRohcEpsBearerIdLineEdit->setText(statisticsData.pdcpuBearerErrorEpsBearerId);
    ui->writePdcpuToFileCheckBox->clicked(statisticsData.getStatMapFor(ui->writePdcpuToFileCheckBox->text()));
    ui->pdcpuFilenameLineEdit->setText(statisticsData.pdcpuFileName);
    ui->pdcpuNumberOfSecondsLineEdit->setText(statisticsData.pdcpuSeconds);
    ui->pdcpuMeasurementLineEdit->setText(statisticsData.pdcpuMeasurement);
}

void StatisticsManager::saveStatisticsData()
{
    //General tab
    statisticsData.setStatMapFor(ui->ueStatisticsCheckBox->text(), ui->ueStatisticsCheckBox->isChecked());
    statisticsData.setStatMapFor(ui->modelExpNasCheckBox->text(), ui->modelExpNasCheckBox->isChecked());
    statisticsData.setStatMapFor(ui->modelExpRrcCheckBox->text(), ui->modelExpRrcCheckBox->isChecked());
    statisticsData.setStatMapFor(ui->modelExpMobilityCheckBox->text(), ui->modelExpMobilityCheckBox->isChecked());
    statisticsData.setStatMapFor(ui->modelExpThroughputCheckBox->text(), ui->modelExpThroughputCheckBox->isChecked());
    statisticsData.setStatMapFor(ui->perUeThroughputCheckBox->text(), ui->perUeThroughputCheckBox->isChecked());
    statisticsData.setStatMapFor(ui->ueExpMobilityCheckBox->text(), ui->ueExpMobilityCheckBox->isChecked());
    statisticsData.setStatMapFor(ui->modelExpPsCheckBox->text(), ui->modelExpPsCheckBox->isChecked());
    statisticsData.setStatMapFor(ui->ueExpPsCheckBox->text(), ui->ueExpPsCheckBox->isChecked());
    statisticsData.setStatMapFor(ui->modelExpCsCheckBox->text(), ui->modelExpCsCheckBox->isChecked());
    statisticsData.setStatMapFor(ui->ueExpCsCheckBox->text(), ui->ueExpCsCheckBox->isChecked());
    statisticsData.setStatMapFor(ui->writeGeneralStatisticsToFileCheckBox->text(), ui->writeGeneralStatisticsToFileCheckBox->isChecked());
    statisticsData.generalUe = ui->ueLineEdit->text();
    statisticsData.generalDelayBetweenPackets = ui->delayBetweenPacketsLineEdit->text();
    statisticsData.generalTotalNumberOfSeconds = ui->generalNumberOfSecondsLineEdit->text();
    statisticsData.generalMtuSize = ui->mtuSizeLineEdit->text();
    statisticsData.generalMeasurementDelta = ui->generalMeasurementLineEdit->text();
    //IPEX tab
    statisticsData.setStatMapFor(ui->ipexProtocolStatsCheckBox->text(), ui->ipexProtocolStatsCheckBox->isChecked());
    statisticsData.setStatMapFor(ui->tguStatsCheckBox->text(), ui->tguStatsCheckBox->isChecked());
    statisticsData.ipexTguImsi = ui->ipexTguImsiLineEdit->text();
    statisticsData.setStatMapFor(ui->writeIpexToFileCheckBox->text(), ui->writeIpexToFileCheckBox->isChecked());
    statisticsData.ipexFileName = ui->ipexFilenameLineEdit->text();
    statisticsData.ipexSeconds = ui->ipexNumberOfSecondsLineEdit->text();
    statisticsData.ipexMeasurement = ui->ipexMeasurementLineEdit->text();
    //PDCP-U tab
    statisticsData.setStatMapFor(ui->pdcpuProtocolStatsCheckBox->text(), ui->pdcpuProtocolStatsCheckBox->isChecked());
    statisticsData.setStatMapFor(ui->rohcStatsCheckBox->text(), ui->rohcStatsCheckBox->isChecked());
    statisticsData.setStatMapFor(ui->bearerStatusWordsCheckBox->text(), ui->bearerStatusWordsCheckBox->isChecked());
    statisticsData.pdcpuBearerStatusImsi = ui->bearerStatusImsiLineEdit->text();
    statisticsData.pdcpuBearerStatusEpsBearerId = ui->bearerStatusEpsBearerIdLineEdit->text();
    statisticsData.setStatMapFor(ui->bearerRohcCheckBox->text(), ui->bearerRohcCheckBox->isChecked());
    statisticsData.pdcpuBearerRohcImsi = ui->bearerRohcImsiLineEdit->text();
    statisticsData.pdcpuBearerRohcEpsBearerId = ui->bearerRohcEpsBearerIdLineEdit->text();
    statisticsData.setStatMapFor(ui->bearerErrorCheckBox->text(), ui->bearerErrorCheckBox->isChecked());
    statisticsData.pdcpuBearerErrorImsi = ui->bearerErrorImsiLineEdit->text();
    statisticsData.pdcpuBearerErrorEpsBearerId = ui->bearerErrorEpsBearerIdLineEdit->text();
    statisticsData.setStatMapFor(ui->writePdcpuToFileCheckBox->text(), ui->writePdcpuToFileCheckBox->isChecked());
    statisticsData.pdcpuFileName = ui->pdcpuFilenameLineEdit->text();
    statisticsData.pdcpuSeconds = ui->pdcpuNumberOfSecondsLineEdit->text();
    statisticsData.pdcpuMeasurement = ui->pdcpuMeasurementLineEdit->text();
}
