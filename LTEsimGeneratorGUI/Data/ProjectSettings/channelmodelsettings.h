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

    // TODO: void setDefaultValues();

    QString model_set_name;
    double pdcch_drop_grant_rate;
    double pdcch_drop_dl_assignment_rate;
    double pdsch_transport_block_decoded_error_rate;
    double phich_nack_to_ack_error_rate;
    double phich_drop_harq_feedback_rate;
    double pusch_drop_transport_block_rate;
    double pusch_transport_block_decoded_error_rate;
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
