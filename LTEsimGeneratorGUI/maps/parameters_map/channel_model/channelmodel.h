#ifndef CHANNELMODEL_H
#define CHANNELMODEL_H

#include <QString>
#include <QList>

class ChannelModel
{
public:
    ChannelModel();
    QString getModel_set_name();
    void setModel_set_name( QString value);

    QString getPdcch_drop_dl_assignment_rate() const;
    void setPdcch_drop_dl_assignment_rate(QString value);

    QString getPdcch_drop_grant_rate() const;
    void setPdcch_drop_grant_rate(QString value);

    QString getPdsch_transport_block_decoded_error_rate() const;
    void setPdsch_transport_block_decoded_error_rate(QString value);

    QString getPhich_nack_to_ack_error_rate() const;
    void setPhich_nack_to_ack_error_rate(QString value);

    QString getPhich_drop_harq_feedback_rate() const;
    void setPhich_drop_harq_feedback_rate(QString value);

    QString getPusch_transport_block_decoded_error_rate() const;
    void setPusch_transport_block_decoded_error_rate(QString value);

    QString getPusch_drop_transport_block_rate() const;
    void setPusch_drop_transport_block_rate(QString value);

    QString getPuxch_nack_to_ack_error_rate() const;
    void setPuxch_nack_to_ack_error_rate(QString value);

    QString getPuxch_dtx_to_ack_error_rate() const;
    void setPuxch_dtx_to_ack_error_rate(QString value);

    QString getPuxch_ack_to_nack_error_rate() const;
    void setPuxch_ack_to_nack_error_rate(QString value);

    QString getPuxch_drop_scheduling_request_rate() const;
    void setPuxch_drop_scheduling_request_rate(QString value);

    QString getDlni_noise() const;
    void setDlni_noise(QString value);

    QString getDlni_interference() const;
    void setDlni_interference(QString value);

    QString getDl_pathloss_min_pathloss() const;
    void setDl_pathloss_min_pathloss(QString value);

    QString getDl_pathloss_max_pathloss() const;
    void setDl_pathloss_max_pathloss(QString value);

    QString getDl_pathloss_time_min_to_max() const;
    void setDl_pathloss_time_min_to_max(QString value);

    bool getDl_pathloss_distribute_ues() const;
    void setDl_pathloss_distribute_ues(bool value);

    QString getPathloss_based_feedback_sinr_threshold() const;
    void setPathloss_based_feedback_sinr_threshold(QString value);

    void resetParams();
private:
    QString model_set_name;
    double pdcch_drop_dl_assignment_rate;
    double pdcch_drop_grant_rate;
    double pdsch_transport_block_decoded_error_rate;
    double phich_nack_to_ack_error_rate;
    double phich_drop_harq_feedback_rate;
    double pusch_transport_block_decoded_error_rate;
    double pusch_drop_transport_block_rate;
    double puxch_nack_to_ack_error_rate;
    double puxch_dtx_to_ack_error_rate;
    double puxch_ack_to_nack_error_rate;
    double puxch_drop_scheduling_request_rate;
    double dlni_noise;
    double dlni_interference;
    double dl_pathloss_min_pathloss;
    double dl_pathloss_max_pathloss;
    double dl_pathloss_time_min_to_max;
    bool dl_pathloss_distribute_ues;
    double pathloss_based_feedback_sinr_threshold;

    QList <QString> fileParameters;
    QString searchParameter(QString name);
    QString searchDefaultParameter(QString name);
    void openFile();
    void setParameters();
    bool toBool(QString t);
};

#endif // CHANNELMODEL_H
