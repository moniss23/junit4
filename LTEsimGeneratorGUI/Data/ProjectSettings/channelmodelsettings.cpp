#include <QBuffer>
#include <QDataStream>

#include "channelmodelsettings.h"

ChannelModelSettings::ChannelModelSettings() {}

QString ChannelModelSettings::getElementType() const {
    return "ChannelModelSettings";
}

QByteArray ChannelModelSettings::serializeData() {
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << model_set_name << pdcch_drop_grant_rate << pdcch_drop_dl_assignment_rate
           << pdsch_transport_block_decoded_error_rate  << phich_nack_to_ack_error_rate
           << phich_drop_harq_feedback_rate << pusch_drop_transport_block_rate
           << pusch_transport_block_decoded_error_rate << puxch_nack_to_ack_error_rate
           << puxch_dtx_to_ack_error_rate << puxch_ack_to_nack_error_rate
           << puxch_drop_scheduling_request_rate << dlni_noise << dlni_interference
           << dl_pathloss_distribute_ues << dl_pathloss_min_pathloss << dl_pathloss_max_pathloss
           << dl_pathloss_time_min_to_max << pathloss_based_feedback_sinr_threshold;

    return serializedData.buffer();
}

void ChannelModelSettings::deserializeData(const QByteArray &rawData) {
    QDataStream stream(rawData);
    stream >> model_set_name >> pdcch_drop_grant_rate >> pdcch_drop_dl_assignment_rate
           >> pdsch_transport_block_decoded_error_rate  >> phich_nack_to_ack_error_rate
           >> phich_drop_harq_feedback_rate >> pusch_drop_transport_block_rate
           >> pusch_transport_block_decoded_error_rate >> puxch_nack_to_ack_error_rate
           >> puxch_dtx_to_ack_error_rate >> puxch_ack_to_nack_error_rate
           >> puxch_drop_scheduling_request_rate >> dlni_noise >> dlni_interference
           >> dl_pathloss_distribute_ues >> dl_pathloss_min_pathloss >> dl_pathloss_max_pathloss
           >> dl_pathloss_time_min_to_max >> pathloss_based_feedback_sinr_threshold;
}
