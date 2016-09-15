#include "channelmodelform.h"
#include "ui_channelmodelform.h"

ChannelModelForm::ChannelModelForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelModelForm)
{
    ui->setupUi(this);
    this->setWindowTitle("Channel Models settings");
}

ChannelModelForm::~ChannelModelForm()
{
    delete ui;
}

void ChannelModelForm::loadAndOpen(const ChannelModelSettings &channelModelSettings, const QString &projectName,bool enable) {
    this->channelModelSettings = channelModelSettings;
    this->projectName = projectName;
    this->updateUi();
    this->setReadOnly(enable);
    this->show();
}

void ChannelModelForm::on_buttonBox_accepted()
{
    this->getParameters();
    emit updateChannelModelSettings(channelModelSettings, projectName);
    this->close();

}

void ChannelModelForm::on_buttonBox_rejected()
{
    this->close();
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
}
void ChannelModelForm::setReadOnly(bool value)
{
    ui->tet_model_set_name->setReadOnly(value);
    ui->tet_pdcch_drop_dl_assignment_rate->setReadOnly(value);
    ui->tet_pdcch_drop_grant_rate->setReadOnly(value);
    ui->tet_pdsch_transport_block_decoded_error_rate->setReadOnly(value);
    ui->tet_phich_nack_to_ack_error_rate->setReadOnly(value);
    ui->tet_phich_drop_harq_feedback_rate->setReadOnly(value);
    ui->tet_pusch_transport_block_decoded_error_rate->setReadOnly(value);

    ui->tet_pusch_drop_transport_block_rate->setReadOnly(value);
    ui->tet_puxch_nack_to_ack_error_rate->setReadOnly(value);
    ui->tet_puxch_dtx_to_ack_error_rate->setReadOnly(value);
    ui->tet_puxch_ack_to_nack_error_rate->setReadOnly(value);
    ui->tet_puxch_drop_scheduling_request_rate->setReadOnly(value);
    ui->tet_dlni_noise->setReadOnly(value);

    ui->tet_dlni_interference->setReadOnly(value);
    ui->tet_dl_pathloss_min_pathloss->setReadOnly(value);
    ui->tet_dl_pathloss_max_pathloss->setReadOnly(value);
    ui->tet_dl_pathloss_time_min_to_max->setReadOnly(value);
    ui->tet_pathloss_based_feedback_sinr_threshold->setReadOnly(value);

    ui->checkBox_dl_pathloss_distribute_ues->setEnabled(!value);
}
