#include "statisticsform.h"
#include "ui_statisticsform.h"

StatisticsForm::StatisticsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsForm)
{
    ui->setupUi(this);
    setFixedSize(sizeHint());

}

StatisticsForm::~StatisticsForm()
{
    delete ui;
}

void StatisticsForm::setParameters(Statistics *statistics)
{
    this->statistics = statistics;

    ui->checkBox->setChecked(statistics->getListingStaticInformationforEachUE());
    ui->checkBox_2->setChecked(statistics->getResettingAllStatisticsCounters());
    ui->checkBox_3->setChecked(statistics->getListingStatisticsonNAS());
    ui->checkBox_4->setChecked(statistics->getListingStatisticsonRRC());
    ui->checkBox_5->setChecked(statistics->getListingMobilityStatisticsperModelandArea());
    ui->checkBox_6->setChecked(statistics->getListingThroughputStatisticsperAreaandModel());
    ui->checkBox_7->setChecked(statistics->getListingThroughputStatisticsperUEandModel());
    ui->checkBox_8->setChecked(statistics->getListingMobilityStatisticsperUE());
    ui->checkBox_9->setChecked(statistics->getListingPSStatisticsperModel());
    ui->checkBox_10->setChecked(statistics->getListingPSStatisticsperUE());
    ui->checkBox_11->setChecked(statistics->getListingCSStatisticsperModel());
    ui->checkBox_12->setChecked(statistics->getListingCSStatisticsperUE());
    ui->checkBox_13->setChecked(statistics->getIPGWTG_ProtocolStatistics());
    ui->checkBox_14->setChecked(statistics->getIPGWTG_TGUStatistics());
    ui->checkBox_15->setChecked(statistics->getIPGWTG_ContinuousStatistics());
    ui->checkBox_16->setChecked(statistics->getPDCP_U_ProtocolStatistics());
    ui->checkBox_17->setChecked(statistics->getPDCP_U_ROHCProtocolStatistics());
    ui->checkBox_18->setChecked(statistics->getPDCP_U_GeneralBearerInformation());
    ui->checkBox_19->setChecked(statistics->getPDCP_U_BearerROHCinformation());
    ui->checkBox_20->setChecked(statistics->getPDCP_U_BearerErrorStatistics());
    ui->checkBox_21->setChecked(statistics->getPDCP_U_ContinuousStatistics());

}

void StatisticsForm::on_checkBox_clicked()
{
    statistics->setListingStaticInformationforEachUE(ui->checkBox->isChecked());
}

void StatisticsForm::on_checkBox_2_clicked()
{
    statistics->setResettingAllStatisticsCounters(ui->checkBox_2->isChecked());
}

void StatisticsForm::on_checkBox_3_clicked()
{
    statistics->setListingStatisticsonNAS(ui->checkBox_3->isChecked());
}

void StatisticsForm::on_checkBox_4_clicked()
{
    statistics->setListingStatisticsonRRC(ui->checkBox_4->isChecked());
}

void StatisticsForm::on_checkBox_5_clicked()
{
    statistics->setListingMobilityStatisticsperModelandArea(ui->checkBox_5->isChecked());
}

void StatisticsForm::on_checkBox_6_clicked()
{
    statistics->setListingThroughputStatisticsperAreaandModel(ui->checkBox_6->isChecked());
}

void StatisticsForm::on_checkBox_7_clicked()
{
    statistics->setListingThroughputStatisticsperUEandModel(ui->checkBox_7->isChecked());
}

void StatisticsForm::on_checkBox_8_clicked()
{
    statistics->setListingMobilityStatisticsperUE(ui->checkBox_8->isChecked());
}

void StatisticsForm::on_checkBox_9_clicked()
{
    statistics->setListingPSStatisticsperModel(ui->checkBox_9->isChecked());
}

void StatisticsForm::on_checkBox_10_clicked()
{
    statistics->setListingPSStatisticsperUE(ui->checkBox_10->isChecked());
}

void StatisticsForm::on_checkBox_11_clicked()
{
    statistics->setListingCSStatisticsperModel(ui->checkBox_11->isChecked());
}

void StatisticsForm::on_checkBox_12_clicked()
{
    statistics->setListingCSStatisticsperUE(ui->checkBox_12->isChecked());
}

void StatisticsForm::on_checkBox_13_clicked()
{
    statistics->setIPGWTG_ProtocolStatistics(ui->checkBox_13->isChecked());
}

void StatisticsForm::on_checkBox_14_clicked()
{
    statistics->setIPGWTG_TGUStatistics(ui->checkBox_14->isChecked());
}

void StatisticsForm::on_checkBox_15_clicked()
{
    statistics->setIPGWTG_ContinuousStatistics(ui->checkBox_15->isChecked());
}

void StatisticsForm::on_checkBox_16_clicked()
{
    statistics->setPDCP_U_ProtocolStatistics(ui->checkBox_16->isChecked());
}

void StatisticsForm::on_checkBox_17_clicked()
{
    statistics->setPDCP_U_ROHCProtocolStatistics(ui->checkBox_17->isChecked());
}

void StatisticsForm::on_checkBox_18_clicked()
{
    statistics->setPDCP_U_GeneralBearerInformation(ui->checkBox_18->isChecked());
}

void StatisticsForm::on_checkBox_19_clicked()
{
    statistics->setPDCP_U_BearerROHCinformation(ui->checkBox_19->isChecked());
}

void StatisticsForm::on_checkBox_20_clicked()
{
    statistics->setPDCP_U_BearerErrorStatistics(ui->checkBox_20->isChecked());
}

void StatisticsForm::on_checkBox_21_clicked()
{
    statistics->setPDCP_U_ContinuousStatistics(ui->checkBox_21->isChecked());
}

