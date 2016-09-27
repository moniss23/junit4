#include "channelmodelform.h"
#include "ui_channelmodelform.h"

ChannelModelForm::ChannelModelForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelModelForm)
{
    ui->setupUi(this);
}

ChannelModelForm::~ChannelModelForm()
{
    delete ui;
}

void ChannelModelForm::loadAndOpen(const ChannelModelSettings &channelModelSettings, const QString &projectName,bool enable) {
    this->channelModelSettings = channelModelSettings;
    this->projectName = projectName;
    this->updateUi();

    this->enableWindow(channelModelSettings.enableChannelModels);
    this->setReadOnly(!enable);

    this->show();
}

void ChannelModelForm::on_restoreDefaults_clicked()
{
    this->updateUi();
}

void ChannelModelForm::updateUi()
{
    ui->tet_model_set_name->setText(channelModelSettings.model_set_name);
    ui->tet_pdcch_drop_dl_assignment_rate->setText(QString::number(channelModelSettings.pdcch_drop_dl_assignment_rate));
    ui->tet_pdcch_drop_grant_rate->setText(QString::number(channelModelSettings.pdcch_drop_grant_rate));
    ui->tet_pdsch_transport_block_decoded_error_rate->setText(QString::number(channelModelSettings.pdsch_transport_block_decoded_error_rate));
    ui->tet_phich_nack_to_ack_error_rate->setText(QString::number(channelModelSettings.phich_nack_to_ack_error_rate));
    ui->tet_phich_drop_harq_feedback_rate->setText(QString::number(channelModelSettings.phich_drop_harq_feedback_rate));
    ui->tet_pusch_transport_block_decoded_error_rate->setText(QString::number(channelModelSettings.pusch_transport_block_decoded_error_rate));

    ui->tet_pusch_drop_transport_block_rate->setText(QString::number(channelModelSettings.pusch_drop_transport_block_rate));
    ui->tet_puxch_nack_to_ack_error_rate->setText(QString::number(channelModelSettings.puxch_nack_to_ack_error_rate));
    ui->tet_puxch_dtx_to_ack_error_rate->setText(QString::number(channelModelSettings.puxch_dtx_to_ack_error_rate));
    ui->tet_puxch_ack_to_nack_error_rate->setText(QString::number(channelModelSettings.puxch_ack_to_nack_error_rate));
    ui->tet_puxch_drop_scheduling_request_rate->setText(QString::number(channelModelSettings.puxch_drop_scheduling_request_rate));
    ui->tet_dlni_noise->setText(QString::number(channelModelSettings.dlni_noise));

    ui->tet_dlni_interference->setText(QString::number(channelModelSettings.dlni_interference));
    ui->tet_dl_pathloss_min_pathloss->setText(QString::number(channelModelSettings.dl_pathloss_min_pathloss));
    ui->tet_dl_pathloss_max_pathloss->setText(QString::number(channelModelSettings.dl_pathloss_max_pathloss));
    ui->tet_dl_pathloss_time_min_to_max->setText(QString::number(channelModelSettings.dl_pathloss_time_min_to_max));
    ui->tet_pathloss_based_feedback_sinr_threshold->setText(QString::number(channelModelSettings.pathloss_based_feedback_sinr_threshold));

    ui->checkBox_dl_pathloss_distribute_ues->setChecked(channelModelSettings.dl_pathloss_distribute_ues);
    ui->checkBox->setChecked(channelModelSettings.enableChannelModels);
}

void ChannelModelForm::getParameters()
{
    channelModelSettings.model_set_name = ui->tet_model_set_name->text();
    channelModelSettings.pdcch_drop_dl_assignment_rate = ui->tet_pdcch_drop_dl_assignment_rate->text().toDouble();
    channelModelSettings.pdcch_drop_grant_rate = ui->tet_pdcch_drop_grant_rate->text().toDouble();
    channelModelSettings.pdsch_transport_block_decoded_error_rate = ui->tet_pdsch_transport_block_decoded_error_rate->text().toDouble();
    channelModelSettings.phich_nack_to_ack_error_rate = ui->tet_phich_nack_to_ack_error_rate->text().toDouble();
    channelModelSettings.phich_drop_harq_feedback_rate = ui->tet_phich_drop_harq_feedback_rate->text().toDouble();
    channelModelSettings.pusch_transport_block_decoded_error_rate = ui->tet_pusch_transport_block_decoded_error_rate->text().toDouble();

    channelModelSettings.pusch_drop_transport_block_rate = ui->tet_pusch_drop_transport_block_rate->text().toDouble();
    channelModelSettings.puxch_nack_to_ack_error_rate = ui->tet_puxch_nack_to_ack_error_rate->text().toDouble();
    channelModelSettings.puxch_dtx_to_ack_error_rate = ui->tet_puxch_dtx_to_ack_error_rate->text().toDouble();
    channelModelSettings.puxch_ack_to_nack_error_rate = ui->tet_puxch_ack_to_nack_error_rate->text().toDouble();
    channelModelSettings.puxch_drop_scheduling_request_rate = ui->tet_puxch_drop_scheduling_request_rate->text().toDouble();
    channelModelSettings.dlni_noise = ui->tet_dlni_noise->text().toDouble();

    channelModelSettings.dlni_interference = ui->tet_dlni_interference->text().toDouble();
    channelModelSettings.dl_pathloss_min_pathloss = ui->tet_dl_pathloss_min_pathloss->text().toDouble();
    channelModelSettings.dl_pathloss_max_pathloss = ui->tet_dl_pathloss_max_pathloss->text().toDouble();
    channelModelSettings.dl_pathloss_time_min_to_max = ui->tet_dl_pathloss_time_min_to_max->text().toDouble();
    channelModelSettings.pathloss_based_feedback_sinr_threshold = ui->tet_pathloss_based_feedback_sinr_threshold->text().toDouble();

    channelModelSettings.dl_pathloss_distribute_ues = ui->checkBox_dl_pathloss_distribute_ues->isChecked();
    channelModelSettings.enableChannelModels = ui->checkBox->isChecked();
}
void ChannelModelForm::setReadOnly(bool value)
{
    ui->checkBox->setEnabled(value);
    ui->tet_model_set_name->setEnabled(value);
    ui->tet_pdcch_drop_dl_assignment_rate->setEnabled(value);
    ui->tet_pdcch_drop_grant_rate->setEnabled(value);
    ui->tet_pdsch_transport_block_decoded_error_rate->setEnabled(value);
    ui->tet_phich_nack_to_ack_error_rate->setEnabled(value);
    ui->tet_phich_drop_harq_feedback_rate->setEnabled(value);
    ui->tet_pusch_transport_block_decoded_error_rate->setEnabled(value);

    ui->tet_pusch_drop_transport_block_rate->setEnabled(value);
    ui->tet_puxch_nack_to_ack_error_rate->setEnabled(value);
    ui->tet_puxch_dtx_to_ack_error_rate->setEnabled(value);
    ui->tet_puxch_ack_to_nack_error_rate->setEnabled(value);
    ui->tet_puxch_drop_scheduling_request_rate->setEnabled(value);
    ui->tet_dlni_noise->setEnabled(value);

    ui->tet_dlni_interference->setEnabled(value);
    ui->tet_dl_pathloss_min_pathloss->setEnabled(value);
    ui->tet_dl_pathloss_max_pathloss->setEnabled(value);
    ui->tet_dl_pathloss_time_min_to_max->setEnabled(value);
    ui->tet_pathloss_based_feedback_sinr_threshold->setEnabled(value);

    ui->checkBox_dl_pathloss_distribute_ues->setEnabled(value);
    ui->restoreDefaults->setEnabled(value);
    ui->okButton->setEnabled(value);
}

void ChannelModelForm::enableWindow(bool value)
{
    ui->tet_model_set_name->setEnabled(value);
    ui->tet_pdcch_drop_dl_assignment_rate->setEnabled(value);
    ui->tet_pdcch_drop_grant_rate->setEnabled(value);
    ui->tet_pdsch_transport_block_decoded_error_rate->setEnabled(value);
    ui->tet_phich_nack_to_ack_error_rate->setEnabled(value);
    ui->tet_phich_drop_harq_feedback_rate->setEnabled(value);
    ui->tet_pusch_transport_block_decoded_error_rate->setEnabled(value);

    ui->tet_pusch_drop_transport_block_rate->setEnabled(value);
    ui->tet_puxch_nack_to_ack_error_rate->setEnabled(value);
    ui->tet_puxch_dtx_to_ack_error_rate->setEnabled(value);
    ui->tet_puxch_ack_to_nack_error_rate->setEnabled(value);
    ui->tet_puxch_drop_scheduling_request_rate->setEnabled(value);
    ui->tet_dlni_noise->setEnabled(value);

    ui->tet_dlni_interference->setEnabled(value);
    ui->tet_dl_pathloss_min_pathloss->setEnabled(value);
    ui->tet_dl_pathloss_max_pathloss->setEnabled(value);
    ui->tet_dl_pathloss_time_min_to_max->setEnabled(value);
    ui->tet_pathloss_based_feedback_sinr_threshold->setEnabled(value);

    ui->checkBox_dl_pathloss_distribute_ues->setEnabled(value);
}

void ChannelModelForm::on_okButton_clicked()
{
    this->getParameters();
    emit updateChannelModelSettings(channelModelSettings, projectName);
    this->close();
}

void ChannelModelForm::on_cancelButton_clicked()
{
    this->close();
}

void ChannelModelForm::on_checkBox_toggled(bool checked)
{
    this->enableWindow(checked);
    this->channelModelSettings.enableChannelModels = checked;
}
