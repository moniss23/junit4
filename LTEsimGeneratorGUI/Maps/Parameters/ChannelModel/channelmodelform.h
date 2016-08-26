#ifndef CHANNELMODELFORM_H
#define CHANNELMODELFORM_H

#include <QWidget>
#include <QMessageBox>

#include "Data/ProjectSettings/channelmodelsettings.h"

namespace Ui {
class ChannelModelForm;
}

class ChannelModelForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelModelForm(QWidget *parent = 0);
    ~ChannelModelForm();
    void setParameters(ChannelModelSettings *chmod);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_tet_model_set_name_returnPressed();
    void on_tet_pdcch_drop_dl_assignment_rate_returnPressed();
    void on_tet_pdcch_drop_grant_rate_returnPressed();
    void on_tet_pdsch_transport_block_decoded_error_rate_returnPressed();
    void on_tet_phich_nack_to_ack_error_rate_returnPressed();
    void on_tet_phich_drop_harq_feedback_rate_returnPressed();
    void on_tet_pusch_transport_block_decoded_error_rate_returnPressed();
    void on_tet_pusch_drop_transport_block_rate_returnPressed();
    void on_tet_puxch_nack_to_ack_error_rate_returnPressed();
    void on_tet_puxch_dtx_to_ack_error_rate_returnPressed();
    void on_tet_puxch_ack_to_nack_error_rate_returnPressed();
    void on_tet_puxch_drop_scheduling_request_rate_returnPressed();
    void on_tet_dlni_noise_returnPressed();
    void on_tet_dlni_interference_returnPressed();
    void on_tet_dl_pathloss_min_pathloss_returnPressed();
    void on_tet_dl_pathloss_max_pathloss_returnPressed();
    void on_tet_dl_pathloss_time_min_to_max_returnPressed();
    void on_tet_pathloss_based_feedback_sinr_threshold_returnPressed();

    void on_checkBox_dl_pathloss_distribute_ues_clicked();

    bool wasChangesBeforeAccept();
    void setChanges();

private:
    Ui::ChannelModelForm *ui;

    ChannelModelSettings *chmod;
    bool flagConfirmNewValue;
    QMessageBox msg,msgBox;
    bool wasThereChanges;


};

#endif // CHANNELMODELFORM_H
