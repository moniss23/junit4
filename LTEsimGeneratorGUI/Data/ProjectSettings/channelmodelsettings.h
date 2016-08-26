#ifndef CHANNELMODELSETTINGS_H
#define CHANNELMODELSETTINGS_H

#include <QList>
#include <QString>
#include <QByteArray>

#include "Data/Interfaces/serializeinterface.h"

class ChannelModelSettings : public SerializeInterface
{
public:
    ChannelModelSettings();
    ~ChannelModelSettings() {}

    QString getModel_set_name();
    QString getPdcch_drop_dl_assignment_rate() const;
    QString getPdcch_drop_grant_rate() const;
    QString getPdsch_transport_block_decoded_error_rate() const;
    QString getPhich_nack_to_ack_error_rate() const;
    QString getPhich_drop_harq_feedback_rate() const;
    QString getPusch_transport_block_decoded_error_rate() const;
    QString getPusch_drop_transport_block_rate() const;
    QString getPuxch_nack_to_ack_error_rate() const;
    QString getPuxch_dtx_to_ack_error_rate() const;
    QString getPuxch_ack_to_nack_error_rate() const;
    QString getPuxch_drop_scheduling_request_rate() const;
    QString getDlni_noise() const;
    QString getDlni_interference() const;
    QString getDl_pathloss_min_pathloss() const;
    QString getDl_pathloss_max_pathloss() const;
    QString getDl_pathloss_time_min_to_max() const;
    bool getDl_pathloss_distribute_ues() const;
    QString getPathloss_based_feedback_sinr_threshold() const;

    void setModel_set_name(const QString &value);
    void setPdcch_drop_dl_assignment_rate(const QString &value);
    void setPdcch_drop_grant_rate(const QString &value);
    void setPdsch_transport_block_decoded_error_rate(const QString &value);
    void setPhich_nack_to_ack_error_rate(const QString &value);
    void setPhich_drop_harq_feedback_rate(const QString &value);
    void setPusch_transport_block_decoded_error_rate(const QString &value);
    void setPusch_drop_transport_block_rate(const QString &value);
    void setPuxch_nack_to_ack_error_rate(const QString &value);
    void setPuxch_dtx_to_ack_error_rate(const QString &value);
    void setPuxch_ack_to_nack_error_rate(const QString &value);
    void setPuxch_drop_scheduling_request_rate(const QString &value);
    void setDlni_noise(const QString &value);
    void setDlni_interference(const QString &value);
    void setDl_pathloss_min_pathloss(const QString &value);
    void setDl_pathloss_max_pathloss(const QString &value);
    void setDl_pathloss_time_min_to_max(const QString &value);
    void setDl_pathloss_distribute_ues(const bool &value);
    void setPathloss_based_feedback_sinr_threshold(const QString &value);

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
    double pathloss_based_feedback_sinr_threshold;
    bool   dl_pathloss_distribute_ues;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // CHANNELMODELSETTINGS_H
