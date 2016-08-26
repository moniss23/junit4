#include "channelmodelsettings.h"

ChannelModelSettings::ChannelModelSettings() {}

QString ChannelModelSettings::getElementType() const {
    return "ChannelModelSettings";
}

QByteArray ChannelModelSettings::serializeData() {
    return QByteArray();
}

void ChannelModelSettings::deserializeData(const QByteArray &rawData) {
    (void) rawData;
}

/***********
 * GETTERS *
 ***********/

QString ChannelModelSettings::getModel_set_name() {
    return model_set_name.remove(QChar('"'));
}
QString ChannelModelSettings::getPdcch_drop_dl_assignment_rate() const {
    return QString::number(pdcch_drop_dl_assignment_rate);
}
QString ChannelModelSettings::getPdcch_drop_grant_rate() const {
    return QString::number(pdcch_drop_grant_rate);
}
QString ChannelModelSettings::getPdsch_transport_block_decoded_error_rate() const {
    return QString::number(pdsch_transport_block_decoded_error_rate);
}
QString ChannelModelSettings::getPhich_nack_to_ack_error_rate() const {
    return QString::number(phich_nack_to_ack_error_rate);
}
QString ChannelModelSettings::getPhich_drop_harq_feedback_rate() const {
    return QString::number(phich_drop_harq_feedback_rate);
}
QString ChannelModelSettings::getPusch_transport_block_decoded_error_rate() const {
    return QString::number(pusch_transport_block_decoded_error_rate);
}
QString ChannelModelSettings::getPusch_drop_transport_block_rate() const {
    return QString::number(pusch_drop_transport_block_rate);
}
QString ChannelModelSettings::getPuxch_nack_to_ack_error_rate() const {
    return QString::number(puxch_nack_to_ack_error_rate);
}
QString ChannelModelSettings::getPuxch_dtx_to_ack_error_rate() const {
    return QString::number(puxch_dtx_to_ack_error_rate);
}
QString ChannelModelSettings::getPuxch_ack_to_nack_error_rate() const {
    return QString::number(puxch_ack_to_nack_error_rate);
}
QString ChannelModelSettings::getPuxch_drop_scheduling_request_rate() const {
    return QString::number(puxch_drop_scheduling_request_rate);
}
QString ChannelModelSettings::getDlni_noise() const {
    return QString::number(dlni_noise);
}
QString ChannelModelSettings::getDlni_interference() const {
    return QString::number(dlni_interference);
}
QString ChannelModelSettings::getDl_pathloss_min_pathloss() const {
    return QString::number(dl_pathloss_min_pathloss);
}
QString ChannelModelSettings::getDl_pathloss_max_pathloss() const {
    return QString::number(dl_pathloss_max_pathloss);
}
QString ChannelModelSettings::getDl_pathloss_time_min_to_max() const {
    return QString::number(dl_pathloss_time_min_to_max);
}
bool ChannelModelSettings::getDl_pathloss_distribute_ues() const {
    return dl_pathloss_distribute_ues;
}
QString ChannelModelSettings::getPathloss_based_feedback_sinr_threshold() const {
    return QString::number(pathloss_based_feedback_sinr_threshold);
}

/***********
 * SETTERS *
 ***********/

void ChannelModelSettings::setModel_set_name(const QString &value) {
    model_set_name = "\"" + value + "\"";
}
void ChannelModelSettings::setPdcch_drop_dl_assignment_rate(const QString &value) {
    pdcch_drop_dl_assignment_rate = value.toDouble();
}
void ChannelModelSettings::setPdcch_drop_grant_rate(const QString &value) {
    pdcch_drop_grant_rate = value.toDouble();
}
void ChannelModelSettings::setPdsch_transport_block_decoded_error_rate(const QString &value) {
    pdsch_transport_block_decoded_error_rate = value.toDouble();
}
void ChannelModelSettings::setPhich_nack_to_ack_error_rate(const QString &value) {
    phich_nack_to_ack_error_rate = value.toDouble();
}
void ChannelModelSettings::setPhich_drop_harq_feedback_rate(const QString &value) {
    phich_drop_harq_feedback_rate = value.toDouble();
}
void ChannelModelSettings::setPusch_transport_block_decoded_error_rate(const QString &value) {
    pusch_transport_block_decoded_error_rate = value.toDouble();
}
void ChannelModelSettings::setPusch_drop_transport_block_rate(const QString &value) {
    pusch_drop_transport_block_rate = value.toDouble();
}
void ChannelModelSettings::setPuxch_nack_to_ack_error_rate(const QString &value) {
    puxch_nack_to_ack_error_rate = value.toDouble();
}
void ChannelModelSettings::setPuxch_dtx_to_ack_error_rate(const QString &value) {
    puxch_dtx_to_ack_error_rate = value.toDouble();
}
void ChannelModelSettings::setPuxch_ack_to_nack_error_rate(const QString &value) {
    puxch_ack_to_nack_error_rate = value.toDouble();
}
void ChannelModelSettings::setPuxch_drop_scheduling_request_rate(const QString &value) {
    puxch_drop_scheduling_request_rate = value.toDouble();
}
void ChannelModelSettings::setDlni_noise(const QString &value) {
    dlni_noise = value.toDouble();
}
void ChannelModelSettings::setDlni_interference(const QString &value) {
    dlni_interference = value.toDouble();
}
void ChannelModelSettings::setDl_pathloss_min_pathloss(const QString &value) {
    dl_pathloss_min_pathloss = value.toDouble();
}
void ChannelModelSettings::setDl_pathloss_max_pathloss(const QString &value) {
    dl_pathloss_max_pathloss = value.toDouble();
}
void ChannelModelSettings::setDl_pathloss_time_min_to_max(const QString &value) {
    dl_pathloss_time_min_to_max = value.toDouble();
}
void ChannelModelSettings::setDl_pathloss_distribute_ues(const bool &value) {
    dl_pathloss_distribute_ues = value;
}
void ChannelModelSettings::setPathloss_based_feedback_sinr_threshold(const QString &value) {
    pathloss_based_feedback_sinr_threshold = value.toDouble();
}
