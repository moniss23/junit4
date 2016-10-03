#ifndef CHANNELMODELSETTINGS_H
#define CHANNELMODELSETTINGS_H

#include "Data/Interfaces/serializeinterface.h"
#include "Data/Interfaces/scriptable.h"

/**
 * @brief The ChannelModelSettings class contains properties of Channel Model
 */
class ChannelModelSettings : public SerializeInterface, public Scriptable
{
public:
    ChannelModelSettings();
    ~ChannelModelSettings() {}

    // TODO: void setDefaultValues();

    QString model_set_name;                             ///< Channel Model name
    double pdcch_drop_grant_rate;                       ///< PDCCH drop grant rate
    double pdcch_drop_dl_assignment_rate;               ///< PDCCH drop downlink assign. rate
    double pdsch_transport_block_decoded_error_rate;    ///< PDSCH transport block dec. error rate
    double phich_nack_to_ack_error_rate;                ///< PHICH nack-ack error rate
    double phich_drop_harq_feedback_rate;               ///< PHICH drop harq. feedback rate
    double pusch_drop_transport_block_rate;             ///< PUSCH drop transport block rate
    double pusch_transport_block_decoded_error_rate;    ///< PUSCH transport block dec. error rate
    double puxch_nack_to_ack_error_rate;                ///< PUXCH nack-ack error rate
    double puxch_dtx_to_ack_error_rate;                 ///< PUXCH dtx-ack error rate
    double puxch_ack_to_nack_error_rate;                ///< PUXCH ack-nack error rate
    double puxch_drop_scheduling_request_rate;          ///< PUXCH drop scheduling request rate
    double dlni_noise;                                  ///< DLNI noise
    double dlni_interference;                           ///< DLNI interference
    double dl_pathloss_min_pathloss;                    ///< DL pathloss min. pathloss
    double dl_pathloss_max_pathloss;                    ///< DL pathloss max. pathloss
    double dl_pathloss_time_min_to_max;                 ///< DL pathloss time min-max
    double pathloss_based_feedback_sinr_threshold;      ///< Pathloss based feedback sinr threshold
    bool   dl_pathloss_distribute_ues;                  ///< DL pathloss distribute ues
    bool   enableChannelModels = false;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);

    /****************************
    *   PARSING INTERFACE       *
    ****************************/
    virtual QString ParseToScript();
};

#endif // CHANNELMODELSETTINGS_H
