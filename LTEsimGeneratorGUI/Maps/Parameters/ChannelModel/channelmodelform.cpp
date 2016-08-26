#include "channelmodelform.h"
#include "ui_channelmodelform.h"

ChannelModelForm::ChannelModelForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelModelForm)
{
    ui->setupUi(this);
    this->setWindowTitle("Channel Models settings");

    flagConfirmNewValue = true;
    wasThereChanges=false;
}

ChannelModelForm::~ChannelModelForm()
{
    delete ui;
}

void ChannelModelForm::setParameters(ChannelModelSettings *chmod)
{
    this->chmod = chmod;

    ui->tet_model_set_name->setText(chmod->getModel_set_name());
    ui->tet_pdcch_drop_dl_assignment_rate->setText(chmod->getPdcch_drop_dl_assignment_rate());
    ui->tet_pdcch_drop_grant_rate->setText(chmod->getPdcch_drop_grant_rate());
    ui->tet_pdsch_transport_block_decoded_error_rate->setText(chmod->getPdsch_transport_block_decoded_error_rate());
    ui->tet_phich_nack_to_ack_error_rate->setText(chmod->getPhich_nack_to_ack_error_rate());
    ui->tet_phich_drop_harq_feedback_rate->setText(chmod->getPhich_drop_harq_feedback_rate());
    ui->tet_pusch_transport_block_decoded_error_rate->setText(chmod->getPusch_transport_block_decoded_error_rate());

    ui->tet_pusch_drop_transport_block_rate->setText(chmod->getPusch_drop_transport_block_rate());
    ui->tet_puxch_nack_to_ack_error_rate->setText(chmod->getPuxch_nack_to_ack_error_rate());
    ui->tet_puxch_dtx_to_ack_error_rate->setText(chmod->getPuxch_dtx_to_ack_error_rate());
    ui->tet_puxch_ack_to_nack_error_rate->setText(chmod->getPuxch_ack_to_nack_error_rate());
    ui->tet_puxch_drop_scheduling_request_rate->setText(chmod->getPuxch_drop_scheduling_request_rate());
    ui->tet_dlni_noise->setText(chmod->getDlni_noise());

    ui->tet_dlni_interference->setText(chmod->getDlni_interference());
    ui->tet_dl_pathloss_min_pathloss->setText(chmod->getDl_pathloss_min_pathloss());
    ui->tet_dl_pathloss_max_pathloss->setText(chmod->getDl_pathloss_max_pathloss());
    ui->tet_dl_pathloss_time_min_to_max->setText(chmod->getDl_pathloss_time_min_to_max());
    ui->tet_pathloss_based_feedback_sinr_threshold->setText(chmod->getPathloss_based_feedback_sinr_threshold());

    ui->checkBox_dl_pathloss_distribute_ues->setChecked(chmod->getDl_pathloss_distribute_ues());
}

void ChannelModelForm::on_buttonBox_accepted()
{
    this->close();
    if(wasChangesBeforeAccept())
        setChanges();
    msg.setText(" Changes has been succesfully approved ");
    if(wasThereChanges && flagConfirmNewValue)
        msg.exec();
    chmod->setDl_pathloss_distribute_ues(ui->checkBox_dl_pathloss_distribute_ues->isChecked());
    wasThereChanges=false;
}

void ChannelModelForm::on_buttonBox_clicked(QAbstractButton * button)
{
    if((QPushButton *)button== ui->buttonBox->button(QDialogButtonBox::RestoreDefaults) ){
      //chmod->resetParams();
      //setParameters(chmod);
    }
}


void ChannelModelForm::on_buttonBox_rejected()
{
    if(wasChangesBeforeAccept())
    {
        msgBox.setWindowTitle("Warning");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText(trUtf8(("File was changed")));
        msgBox.setInformativeText(trUtf8("Do you want to save changes?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);

        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Save:
            setChanges();
            this->close();
            break;
        case QMessageBox::Discard:
            this->close();
            break;
        case QMessageBox::Cancel:
            msgBox.close();
            break;
        default:

            break;
        }
    }else
    {
        this->close();
    }
    wasThereChanges=false;
}



void ChannelModelForm::on_tet_model_set_name_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_model_set_name->text() != chmod->getModel_set_name())){
        chmod->setModel_set_name(ui->tet_model_set_name->text());
        wasThereChanges=true;
        msg.setText("model_set_name: "+ chmod->getModel_set_name() );
        msg.exec();
    }else
        chmod->setModel_set_name(ui->tet_model_set_name->text());
}

void ChannelModelForm::on_tet_pdcch_drop_dl_assignment_rate_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_pdcch_drop_dl_assignment_rate->text() != chmod->getPdcch_drop_dl_assignment_rate())){
        chmod->setPdcch_drop_dl_assignment_rate(ui->tet_pdcch_drop_dl_assignment_rate->text());
        wasThereChanges=true;
        msg.setText("pdcch_drop_dl_assignment_rate: "+ chmod->getPdcch_drop_dl_assignment_rate() );
        msg.exec();
    }else
        chmod->setPdcch_drop_dl_assignment_rate(ui->tet_pdcch_drop_dl_assignment_rate->text());
}

void ChannelModelForm::on_tet_pdcch_drop_grant_rate_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_pdcch_drop_grant_rate->text() != chmod->getPdcch_drop_grant_rate())){
        chmod->setPdcch_drop_grant_rate(ui->tet_pdcch_drop_grant_rate->text());
        wasThereChanges=true;
        msg.setText("pdcch_drop_grant_rate: "+ chmod->getPdcch_drop_grant_rate() );
        msg.exec();
    }
    chmod->setPdcch_drop_grant_rate(ui->tet_pdcch_drop_grant_rate->text());
}

void ChannelModelForm::on_tet_pdsch_transport_block_decoded_error_rate_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_pdsch_transport_block_decoded_error_rate->text() != chmod->getPdsch_transport_block_decoded_error_rate())){
        chmod->setPdsch_transport_block_decoded_error_rate(ui->tet_pdsch_transport_block_decoded_error_rate->text());
        wasThereChanges=true;
        msg.setText("pdsch_transport_block_decoded_error_rate: "+ chmod->getPdsch_transport_block_decoded_error_rate() );
        msg.exec();
    }
    chmod->setPdsch_transport_block_decoded_error_rate(ui->tet_pdsch_transport_block_decoded_error_rate->text());
}

void ChannelModelForm::on_tet_phich_nack_to_ack_error_rate_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_phich_nack_to_ack_error_rate->text() != chmod->getPhich_nack_to_ack_error_rate())){
        chmod->setPhich_nack_to_ack_error_rate(ui->tet_phich_nack_to_ack_error_rate->text());
        wasThereChanges=true;
        msg.setText("phich_nack_to_ack_error_rate: "+ chmod->getPhich_nack_to_ack_error_rate());
        msg.exec();
    }
    chmod->setPhich_nack_to_ack_error_rate(ui->tet_phich_nack_to_ack_error_rate->text());
}

void ChannelModelForm::on_tet_phich_drop_harq_feedback_rate_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_phich_drop_harq_feedback_rate->text() != chmod->getPhich_drop_harq_feedback_rate())){
        chmod->setPhich_drop_harq_feedback_rate(ui->tet_phich_drop_harq_feedback_rate->text());
        wasThereChanges=true;
        msg.setText("phich_drop_harq_feedback_rate: "+ chmod->getPhich_drop_harq_feedback_rate());
        msg.exec();
    }
    chmod->setPhich_drop_harq_feedback_rate(ui->tet_phich_drop_harq_feedback_rate->text());
}

void ChannelModelForm::on_tet_pusch_transport_block_decoded_error_rate_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_pusch_transport_block_decoded_error_rate->text() != chmod->getPusch_transport_block_decoded_error_rate())){
        chmod->setPusch_transport_block_decoded_error_rate(ui->tet_pusch_transport_block_decoded_error_rate->text());
        wasThereChanges=true;
        msg.setText("pusch_transport_block_decoded_error_rate: "+ chmod->getPusch_transport_block_decoded_error_rate());
        msg.exec();
    }
    chmod->setPusch_transport_block_decoded_error_rate(ui->tet_pusch_transport_block_decoded_error_rate->text());
}

void ChannelModelForm::on_tet_pusch_drop_transport_block_rate_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_pusch_drop_transport_block_rate->text() != chmod->getPusch_drop_transport_block_rate())){
        chmod->setPusch_drop_transport_block_rate(ui->tet_pusch_drop_transport_block_rate->text());
        wasThereChanges=true;
        msg.setText("pusch_drop_transport_block_rate: "+ chmod->getPusch_drop_transport_block_rate());
        msg.exec();
    }
    chmod->setPusch_drop_transport_block_rate(ui->tet_pusch_drop_transport_block_rate->text());
}

void ChannelModelForm::on_tet_puxch_nack_to_ack_error_rate_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_puxch_nack_to_ack_error_rate->text() != chmod->getPuxch_nack_to_ack_error_rate())){
        chmod->setPuxch_nack_to_ack_error_rate(ui->tet_puxch_nack_to_ack_error_rate->text());
        wasThereChanges=true;
        msg.setText("puxch_nack_to_ack_error_rate: "+ chmod->getPuxch_nack_to_ack_error_rate());
        msg.exec();
    }
    chmod->setPuxch_nack_to_ack_error_rate(ui->tet_puxch_nack_to_ack_error_rate->text());
}

void ChannelModelForm::on_tet_puxch_dtx_to_ack_error_rate_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_puxch_dtx_to_ack_error_rate->text() != chmod->getPuxch_dtx_to_ack_error_rate())){
        chmod->setPuxch_dtx_to_ack_error_rate(ui->tet_puxch_dtx_to_ack_error_rate->text());
        wasThereChanges=true;
        msg.setText("puxch_dtx_to_ack_error_rate: "+ chmod->getPuxch_dtx_to_ack_error_rate());
        msg.exec();
    }
    chmod->setPuxch_dtx_to_ack_error_rate(ui->tet_puxch_dtx_to_ack_error_rate->text());
}

void ChannelModelForm::on_tet_puxch_ack_to_nack_error_rate_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_puxch_ack_to_nack_error_rate->text() != chmod->getPuxch_ack_to_nack_error_rate())){
        chmod->setPuxch_ack_to_nack_error_rate(ui->tet_puxch_ack_to_nack_error_rate->text());
        wasThereChanges=true;
        msg.setText("puxch_ack_to_nack_error_rate: "+ chmod->getPuxch_ack_to_nack_error_rate());
        msg.exec();
    }
    chmod->setPuxch_ack_to_nack_error_rate(ui->tet_puxch_ack_to_nack_error_rate->text());
}

void ChannelModelForm::on_tet_puxch_drop_scheduling_request_rate_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_puxch_drop_scheduling_request_rate->text() != chmod->getPuxch_drop_scheduling_request_rate())){
        chmod->setPuxch_drop_scheduling_request_rate(ui->tet_puxch_drop_scheduling_request_rate->text());
        wasThereChanges=true;
        msg.setText("puxch_drop_scheduling_request_rate: "+ chmod->getPuxch_drop_scheduling_request_rate());
        msg.exec();
    }
    chmod->setPuxch_drop_scheduling_request_rate(ui->tet_puxch_drop_scheduling_request_rate->text());
}

void ChannelModelForm::on_tet_dlni_noise_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_dlni_noise->text() != chmod->getDlni_noise())){
        chmod->setDlni_noise(ui->tet_dlni_noise->text());
        wasThereChanges=true;
        msg.setText("dlni_noise: "+ chmod->getDlni_noise());
        msg.exec();
    }
    chmod->setDlni_noise(ui->tet_dlni_noise->text());
}

void ChannelModelForm::on_tet_dlni_interference_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_dlni_interference->text() != chmod->getDlni_interference())){
        chmod->setDlni_interference(ui->tet_dlni_interference->text());
        wasThereChanges=true;
        msg.setText("dlni_interference: "+ chmod->getDlni_interference());
        msg.exec();
    }
    chmod->setDlni_interference(ui->tet_dlni_interference->text());
}

void ChannelModelForm::on_tet_dl_pathloss_min_pathloss_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_dl_pathloss_min_pathloss->text() != chmod->getDl_pathloss_min_pathloss())){
        chmod->setDl_pathloss_min_pathloss(ui->tet_dl_pathloss_min_pathloss->text());
        wasThereChanges=true;
        msg.setText("dl_pathloss_min_pathloss: "+ chmod->getDl_pathloss_min_pathloss());
        msg.exec();
    }
    chmod->setDl_pathloss_min_pathloss(ui->tet_dl_pathloss_min_pathloss->text());
}

void ChannelModelForm::on_tet_dl_pathloss_max_pathloss_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_dl_pathloss_max_pathloss->text() != chmod->getDl_pathloss_max_pathloss())){
        chmod->setDl_pathloss_max_pathloss(ui->tet_dl_pathloss_max_pathloss->text());
        wasThereChanges=true;
        msg.setText("pathloss_max_pathloss: "+ chmod->getDl_pathloss_max_pathloss());
        msg.exec();
    }
    chmod->setDl_pathloss_max_pathloss(ui->tet_dl_pathloss_max_pathloss->text());
}

void ChannelModelForm::on_tet_dl_pathloss_time_min_to_max_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_dl_pathloss_time_min_to_max->text() != chmod->getDl_pathloss_time_min_to_max())){
        chmod->setDl_pathloss_time_min_to_max(ui->tet_dl_pathloss_time_min_to_max->text());
        wasThereChanges=true;
        msg.setText("dl_pathloss_time_min_to_max: "+ chmod->getDl_pathloss_time_min_to_max());
        msg.exec();
    }
    chmod->setDl_pathloss_time_min_to_max(ui->tet_dl_pathloss_time_min_to_max->text());
}

void ChannelModelForm::on_tet_pathloss_based_feedback_sinr_threshold_returnPressed()
{
    if(flagConfirmNewValue && (ui->tet_pathloss_based_feedback_sinr_threshold->text() != chmod->getPathloss_based_feedback_sinr_threshold())){
        chmod->setPathloss_based_feedback_sinr_threshold(ui->tet_pathloss_based_feedback_sinr_threshold->text());
        wasThereChanges=true;
        msg.setText("pathloss_based_feedback_sinr_threshold: "+ chmod->getPathloss_based_feedback_sinr_threshold());
        msg.exec();
    }
    chmod->setPathloss_based_feedback_sinr_threshold(ui->tet_pathloss_based_feedback_sinr_threshold->text());
}

void ChannelModelForm::on_checkBox_dl_pathloss_distribute_ues_clicked()
{
    chmod->setDl_pathloss_distribute_ues(ui->checkBox_dl_pathloss_distribute_ues->isChecked());
}

bool ChannelModelForm::wasChangesBeforeAccept()
{
    if(ui->tet_model_set_name->text() != chmod->getModel_set_name())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_pdcch_drop_dl_assignment_rate->text() != chmod->getPdcch_drop_dl_assignment_rate())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_pdcch_drop_grant_rate->text() != chmod->getPdcch_drop_grant_rate())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_pdsch_transport_block_decoded_error_rate->text() != chmod->getPdsch_transport_block_decoded_error_rate())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_phich_nack_to_ack_error_rate->text() != chmod->getPhich_nack_to_ack_error_rate())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_phich_drop_harq_feedback_rate->text() != chmod->getPhich_drop_harq_feedback_rate())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_pusch_transport_block_decoded_error_rate->text() != chmod->getPusch_transport_block_decoded_error_rate())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_pusch_drop_transport_block_rate->text() != chmod->getPusch_drop_transport_block_rate())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_puxch_nack_to_ack_error_rate->text() != chmod->getPuxch_nack_to_ack_error_rate())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_puxch_dtx_to_ack_error_rate->text() != chmod->getPuxch_dtx_to_ack_error_rate())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_puxch_ack_to_nack_error_rate->text() != chmod->getPuxch_ack_to_nack_error_rate())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_puxch_drop_scheduling_request_rate->text() != chmod->getPuxch_drop_scheduling_request_rate())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_dlni_noise->text() != chmod->getDlni_noise())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_dlni_interference->text() != chmod->getDlni_interference())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_dl_pathloss_min_pathloss->text() != chmod->getDl_pathloss_min_pathloss())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_dl_pathloss_max_pathloss->text() != chmod->getDl_pathloss_max_pathloss())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_dl_pathloss_time_min_to_max->text() != chmod->getDl_pathloss_time_min_to_max())
    {
        wasThereChanges=true;
        return true;
    }else if(ui->tet_pathloss_based_feedback_sinr_threshold->text() != chmod->getPathloss_based_feedback_sinr_threshold())
    {
        wasThereChanges=true;
        return true;
    }else
    {
        return false;
    }
}

void ChannelModelForm::setChanges()
{
    chmod->setModel_set_name(ui->tet_model_set_name->text());
    chmod->setPdcch_drop_dl_assignment_rate(ui->tet_pdcch_drop_dl_assignment_rate->text());
    chmod->setPdcch_drop_grant_rate(ui->tet_pdcch_drop_grant_rate->text());
    chmod->setPdsch_transport_block_decoded_error_rate(ui->tet_pdsch_transport_block_decoded_error_rate->text());
    chmod->setPhich_nack_to_ack_error_rate(ui->tet_phich_nack_to_ack_error_rate->text());
    chmod->setPhich_drop_harq_feedback_rate(ui->tet_phich_drop_harq_feedback_rate->text());
    chmod->setPusch_transport_block_decoded_error_rate(ui->tet_pusch_transport_block_decoded_error_rate->text());

    chmod->setPusch_drop_transport_block_rate(ui->tet_pusch_drop_transport_block_rate->text());
    chmod->setPuxch_nack_to_ack_error_rate(ui->tet_puxch_nack_to_ack_error_rate->text());
    chmod->setPuxch_dtx_to_ack_error_rate(ui->tet_puxch_dtx_to_ack_error_rate->text());
    chmod->setPuxch_ack_to_nack_error_rate(ui->tet_puxch_ack_to_nack_error_rate->text());
    chmod->setPuxch_drop_scheduling_request_rate(ui->tet_puxch_drop_scheduling_request_rate->text());
    chmod->setDlni_noise(ui->tet_dlni_noise->text());

    chmod->setDlni_interference(ui->tet_dlni_interference->text());
    chmod->setDl_pathloss_min_pathloss(ui->tet_dl_pathloss_min_pathloss->text());
    chmod->setDl_pathloss_max_pathloss(ui->tet_dl_pathloss_max_pathloss->text());
    chmod->setDl_pathloss_time_min_to_max(ui->tet_dl_pathloss_time_min_to_max->text());
    chmod->setPathloss_based_feedback_sinr_threshold(ui->tet_pathloss_based_feedback_sinr_threshold->text());
}
