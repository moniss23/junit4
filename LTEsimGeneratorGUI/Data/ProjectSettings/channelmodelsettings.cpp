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
           << dl_pathloss_time_min_to_max << pathloss_based_feedback_sinr_threshold
           << enableChannelModels;

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
           >> dl_pathloss_time_min_to_max >> pathloss_based_feedback_sinr_threshold
           >> enableChannelModels;
}
QString ChannelModelSettings::ParseToScript(){
    QString outputString;
    QString header = " #\n\
 # Configure channel models\n\
 #\n\
 def Parameters.getChannelModelConfigParameters()\n\
  # Define and return default values\n\
  default = {}\n";
    outputString.append(header);
    int precision = 1;


    // MODEL SET NAME
    outputString.append("  default[:model_set_name] = \"");
    outputString.append(model_set_name);
    outputString.append("\"\n");
    // PDCCH DROP DL ASSIGNMENT RATE
    outputString.append("  default[:pdcch_drop_dl_assignment_rate] = ");
    outputString.append(QString::number(pdcch_drop_dl_assignment_rate,'f',precision));
    outputString.append("\n");
    // PDCCH DROP DL GRANT RATE
    outputString.append("  default[:pdcch_drop_grant_rate] = ");
    outputString.append(QString::number(pdcch_drop_grant_rate,'f',precision));
    outputString.append("\n");
    // PDCCH TRANSPORT BLOCK DECODED ERROR RATE
    outputString.append("  default[:pdsch_transport_block_decoded_error_rate] = ");
    outputString.append(QString::number(pdsch_transport_block_decoded_error_rate,'f',precision));
    outputString.append("\n");
    // PHICH NACK TO ACK ERROR RATE
    outputString.append("  default[:phich_nack_to_ack_error_rate] = ");
    outputString.append(QString::number(phich_nack_to_ack_error_rate,'f',precision));
    outputString.append("\n");
    // PHICH DROP HARQ FEEDBACK RATE
    outputString.append("  default[:phich_drop_harq_feedback_rate] = ");
    outputString.append(QString::number(phich_drop_harq_feedback_rate,'f',precision));
    outputString.append("\n");
    // PUSCH TRANSPORT BLOCK DECODED ERROR RATE
    outputString.append("  default[:pusch_transport_block_decoded_error_rate] = ");
    outputString.append(QString::number(pusch_transport_block_decoded_error_rate,'f',precision));
    outputString.append("\n");
    // PUSCH DROP TRANSPORT BLOCK RATE
    outputString.append("  default[:pusch_drop_transport_block_rate] = ");
    outputString.append(QString::number(pusch_drop_transport_block_rate,'f',precision));
    outputString.append("\n");
    // PUXCH NACK TO ACK ERROR RATE
    outputString.append("  default[:puxch_nack_to_ack_error_rate] = ");
    outputString.append(QString::number(puxch_nack_to_ack_error_rate,'f',precision));
    outputString.append("\n");
    // PUXCH DTX TO ACK ERROR RATE
    outputString.append("  default[:puxch_dtx_to_ack_error_rate] = ");
    outputString.append(QString::number(puxch_dtx_to_ack_error_rate,'f',precision));
    outputString.append("\n");
    // PUXCH ACK TO NACK ERROR RATE
    outputString.append("  default[:puxch_ack_to_nack_error_rate] = ");
    outputString.append(QString::number(puxch_ack_to_nack_error_rate,'f',precision));
    outputString.append("\n");
    // PUXCH DROP SCHEDULING REQUEST RATE
    outputString.append("  default[:puxch_drop_scheduling_request_rate] = ");
    outputString.append(QString::number(puxch_drop_scheduling_request_rate,'f',precision));
    outputString.append("\n");
    // DLNI NOISE
    outputString.append("  default[:dlni_noise] = ");
    outputString.append(QString::number(dlni_noise,'f',precision));
    outputString.append("\n");
    // DLNI INTERFERENCE
    outputString.append("  default[:dlni_interference] = ");
    outputString.append(QString::number(dlni_interference,'f',precision));
    outputString.append("\n");
    // DL PATHLOSS MIN PATHLOSS
    outputString.append("  default[:dl_pathloss_min_pathloss] = ");
    outputString.append(QString::number(dl_pathloss_min_pathloss,'f',precision));
    outputString.append("\n");
    // DL PATHLOSS MAX PATHLOSS
    outputString.append("  default[:dl_pathloss_max_pathloss] = ");
    outputString.append(QString::number(dl_pathloss_max_pathloss,'f',precision));
    outputString.append("\n");
    // DL PATHLOSS TIME MIN TO MAX
    outputString.append("  default[:dl_pathloss_time_min_to_max] = ");
    outputString.append(QString::number(dl_pathloss_time_min_to_max,'f',precision));
    outputString.append("\n");
    // DL PATHLOSS DISTRIBUTE UES
    outputString.append("  default[:dl_pathloss_distribute_ues] = ");
    if (dl_pathloss_distribute_ues) {
        outputString.append("true");
    }
    else {
        outputString.append("false");
    }
    outputString.append("\n");
    //
    // PATHLOSS BASED FEEDBACK SINR THRESHOLD
    outputString.append("  default[:pathloss_based_feedback_sinr_threshold] = ");
    outputString.append(QString::number(pathloss_based_feedback_sinr_threshold,'f',precision));
    outputString.append("\n");

    outputString.append("  return default\n");
    outputString.append(" end\n");
    return outputString;
}
