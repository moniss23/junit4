#include "channelmodel.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

extern QString parametersFileContent;
extern QStringList parametersFileContentList;
extern QString savedParametersFileContent;
extern std::vector<QString> trafficFilesContent;

ChannelModel::ChannelModel()
{
    setParameters();
}
QString ChannelModel::getModel_set_name()
{
    return model_set_name.remove(QChar('"'));
}

void ChannelModel::setModel_set_name(QString value)
{
    model_set_name = "\"" + value + "\"";
}
QString ChannelModel::getPdcch_drop_dl_assignment_rate() const
{
    return QString::number(pdcch_drop_dl_assignment_rate);
}

void ChannelModel::setPdcch_drop_dl_assignment_rate(QString value)
{
    pdcch_drop_dl_assignment_rate = value.toDouble();
}
QString ChannelModel::getPdcch_drop_grant_rate() const
{
    return QString::number(pdcch_drop_grant_rate);
}

void ChannelModel::setPdcch_drop_grant_rate(QString value)
{
    pdcch_drop_grant_rate = value.toDouble();
}
QString ChannelModel::getPdsch_transport_block_decoded_error_rate() const
{
    return QString::number(pdsch_transport_block_decoded_error_rate);
}

void ChannelModel::setPdsch_transport_block_decoded_error_rate(QString value)
{
    pdsch_transport_block_decoded_error_rate = value.toDouble();
}
QString ChannelModel::getPhich_nack_to_ack_error_rate() const
{
    return QString::number(phich_nack_to_ack_error_rate);
}

void ChannelModel::setPhich_nack_to_ack_error_rate(QString value)
{
    phich_nack_to_ack_error_rate = value.toDouble();
}
QString ChannelModel::getPhich_drop_harq_feedback_rate() const
{
    return QString::number(phich_drop_harq_feedback_rate);
}

void ChannelModel::setPhich_drop_harq_feedback_rate(QString value)
{
    phich_drop_harq_feedback_rate = value.toDouble();
}
QString ChannelModel::getPusch_transport_block_decoded_error_rate() const
{
    return QString::number(pusch_transport_block_decoded_error_rate);
}

void ChannelModel::setPusch_transport_block_decoded_error_rate(QString value)
{
    pusch_transport_block_decoded_error_rate = value.toDouble();
}
QString ChannelModel::getPusch_drop_transport_block_rate() const
{
    return QString::number(pusch_drop_transport_block_rate);
}

void ChannelModel::setPusch_drop_transport_block_rate(QString value)
{
    pusch_drop_transport_block_rate = value.toDouble();
}
QString ChannelModel::getPuxch_nack_to_ack_error_rate() const
{
    return QString::number(puxch_nack_to_ack_error_rate);
}

void ChannelModel::setPuxch_nack_to_ack_error_rate(QString value)
{
    puxch_nack_to_ack_error_rate = value.toDouble();
}
QString ChannelModel::getPuxch_dtx_to_ack_error_rate() const
{
    return QString::number(puxch_dtx_to_ack_error_rate);
}

void ChannelModel::setPuxch_dtx_to_ack_error_rate(QString value)
{
    puxch_dtx_to_ack_error_rate = value.toDouble();
}
QString ChannelModel::getPuxch_ack_to_nack_error_rate() const
{
    return QString::number(puxch_ack_to_nack_error_rate);
}

void ChannelModel::setPuxch_ack_to_nack_error_rate(QString value)
{
    puxch_ack_to_nack_error_rate = value.toDouble();
}
QString ChannelModel::getPuxch_drop_scheduling_request_rate() const
{
    return QString::number(puxch_drop_scheduling_request_rate);
}

void ChannelModel::setPuxch_drop_scheduling_request_rate(QString value)
{
    puxch_drop_scheduling_request_rate = value.toDouble();
}
QString ChannelModel::getDlni_noise() const
{
    return QString::number(dlni_noise);
}

void ChannelModel::setDlni_noise(QString value)
{
    dlni_noise = value.toDouble();
}
QString ChannelModel::getDlni_interference() const
{
    return QString::number(dlni_interference);
}

void ChannelModel::setDlni_interference(QString value)
{
    dlni_interference = value.toDouble();
}
QString ChannelModel::getDl_pathloss_min_pathloss() const
{
    return QString::number(dl_pathloss_min_pathloss);
}

void ChannelModel::setDl_pathloss_min_pathloss(QString value)
{
    dl_pathloss_min_pathloss = value.toDouble();
}
QString ChannelModel::getDl_pathloss_max_pathloss() const
{
    return QString::number(dl_pathloss_max_pathloss);
}

void ChannelModel::setDl_pathloss_max_pathloss(QString value)
{
    dl_pathloss_max_pathloss = value.toDouble();
}
QString ChannelModel::getDl_pathloss_time_min_to_max() const
{
    return QString::number(dl_pathloss_time_min_to_max);
}

void ChannelModel::setDl_pathloss_time_min_to_max(QString value)
{
    dl_pathloss_time_min_to_max = value.toDouble();
}
bool ChannelModel::getDl_pathloss_distribute_ues() const
{
    return dl_pathloss_distribute_ues;
}

void ChannelModel::setDl_pathloss_distribute_ues(bool value)
{
    dl_pathloss_distribute_ues = value;
}
QString ChannelModel::getPathloss_based_feedback_sinr_threshold() const
{
    return QString::number(pathloss_based_feedback_sinr_threshold);
}

void ChannelModel::setPathloss_based_feedback_sinr_threshold(QString value)
{
    pathloss_based_feedback_sinr_threshold = value.toDouble();
}

void ChannelModel::resetParams()
{
    openFile();
    model_set_name = searchDefaultParameter(":model_set_name").trimmed();
    pdcch_drop_dl_assignment_rate= searchDefaultParameter(":pdcch_drop_dl_assignment_rate").toDouble();
    pdcch_drop_grant_rate= searchDefaultParameter(":pdcch_drop_grant_rate").toDouble();
    pdsch_transport_block_decoded_error_rate= searchDefaultParameter(":pdsch_transport_block_decoded_error_rate").toDouble();
    phich_nack_to_ack_error_rate= searchDefaultParameter(":phich_nack_to_ack_error_rate").toDouble();
    phich_drop_harq_feedback_rate= searchDefaultParameter(":phich_drop_harq_feedback_rate").toDouble();
    pusch_transport_block_decoded_error_rate= searchDefaultParameter(":pusch_transport_block_decoded_error_rate").toDouble();
    pusch_drop_transport_block_rate= searchDefaultParameter(":pusch_drop_transport_block_rate").toDouble();
    puxch_nack_to_ack_error_rate= searchDefaultParameter(":puxch_nack_to_ack_error_rate").toDouble();
    puxch_dtx_to_ack_error_rate= searchDefaultParameter(":puxch_dtx_to_ack_error_rate").toDouble();
    puxch_ack_to_nack_error_rate= searchDefaultParameter(":puxch_ack_to_nack_error_rate").toDouble();
    puxch_drop_scheduling_request_rate= searchDefaultParameter(":puxch_drop_scheduling_request_rate").toDouble();
    dlni_noise= searchDefaultParameter(":dlni_noise").toDouble();
    dlni_interference= searchDefaultParameter(":dlni_interference").toDouble();
    dl_pathloss_min_pathloss= searchDefaultParameter(":dl_pathloss_min_pathloss").toDouble();
    dl_pathloss_max_pathloss= searchDefaultParameter(":dl_pathloss_max_pathloss").toDouble();
    dl_pathloss_time_min_to_max= searchDefaultParameter(":dl_pathloss_time_min_to_max").toDouble();
    dl_pathloss_distribute_ues= toBool(searchDefaultParameter(":dl_pathloss_distribute_ues"));
    pathloss_based_feedback_sinr_threshold= searchDefaultParameter(":pathloss_based_feedback_sinr_threshold").toDouble();
}
bool ChannelModel::toBool(QString t){
    if (t.trimmed() == "true" || t.trimmed() == "True" || t.trimmed()=="TRUE" || t.trimmed()=="1")
        return true;
    if (t.trimmed() == "false" || t.trimmed() == "False" || t.trimmed()=="FALSE" || t.trimmed()=="0")
        return false;
    return NULL;
}

void ChannelModel::openFile()
{
    QString fileName = ":/RbFiles/parameters.rb";
    QFile file1(fileName);

    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
        return;              // if coudn't open file: stop loading file

    QString text1="";
    QTextStream stream(&file1);

    while(!stream.atEnd()){
        text1 = stream.readLine();
        fileParameters << text1.trimmed();
   }
}

QString ChannelModel::searchParameter(QString name)
{
    QStringList list;
    QString text1= "";
    for (int i=0; i<parametersFileContentList.size();i++)
    {
        if (parametersFileContentList[i].contains(name)){
            text1 = parametersFileContentList[i];
            if(text1.left(1)!="#"){
                list = text1.split("#");
                text1 = list[0];
                list = text1.split("=");
                return list[1];
            }
        }
    }
    return NULL;
}

QString ChannelModel::searchDefaultParameter(QString name)
{
    QStringList list;
    QString text1= "";
    for (int i=0; i<fileParameters.size();i++)
    {
        if (fileParameters[i].contains(name)){
            text1 = fileParameters[i];
            if(text1.left(1)!="#"){
                list = text1.split("#");
                text1 = list[0];
                list = text1.split("=");
                return list[1];
            }
        }
    }
    return NULL;
}

void ChannelModel::setParameters()
{
     model_set_name = searchParameter(":model_set_name").trimmed();
     pdcch_drop_dl_assignment_rate= searchParameter(":pdcch_drop_dl_assignment_rate").toDouble();
     pdcch_drop_grant_rate= searchParameter(":pdcch_drop_grant_rate").toDouble();
     pdsch_transport_block_decoded_error_rate= searchParameter(":pdsch_transport_block_decoded_error_rate").toDouble();
     phich_nack_to_ack_error_rate= searchParameter(":phich_nack_to_ack_error_rate").toDouble();
     phich_drop_harq_feedback_rate= searchParameter(":phich_drop_harq_feedback_rate").toDouble();
     pusch_transport_block_decoded_error_rate= searchParameter(":pusch_transport_block_decoded_error_rate").toDouble();
     pusch_drop_transport_block_rate= searchParameter(":pusch_drop_transport_block_rate").toDouble();
     puxch_nack_to_ack_error_rate= searchParameter(":puxch_nack_to_ack_error_rate").toDouble();
     puxch_dtx_to_ack_error_rate= searchParameter(":puxch_dtx_to_ack_error_rate").toDouble();
     puxch_ack_to_nack_error_rate= searchParameter(":puxch_ack_to_nack_error_rate").toDouble();
     puxch_drop_scheduling_request_rate= searchParameter(":puxch_drop_scheduling_request_rate").toDouble();
     dlni_noise= searchParameter(":dlni_noise").toDouble();
     dlni_interference= searchParameter(":dlni_interference").toDouble();
     dl_pathloss_min_pathloss= searchParameter(":dl_pathloss_min_pathloss").toDouble();
     dl_pathloss_max_pathloss= searchParameter(":dl_pathloss_max_pathloss").toDouble();
     dl_pathloss_time_min_to_max= searchParameter(":dl_pathloss_time_min_to_max").toDouble();
     dl_pathloss_distribute_ues= toBool(searchParameter(":dl_pathloss_distribute_ues"));
     pathloss_based_feedback_sinr_threshold= searchParameter(":pathloss_based_feedback_sinr_threshold").toDouble();
}

