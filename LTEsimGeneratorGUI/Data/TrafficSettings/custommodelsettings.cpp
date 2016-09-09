#include "custommodelsettings.h"

#include <QByteArray>
#include <QDataStream>
#include <QBuffer>

CustomModelSettings::CustomModelSettings()
{
    std::fill(qciUsed,&qciUsed[9],false);
}

QString CustomModelSettings::getElementType() const
{
    return QString("CustomModelSettings");
}

QByteArray CustomModelSettings::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);

    stream << CMPings.size();
    for(auto &&ping : CMPings) {
        stream << ping.serializeData();
    }
    stream << CMVoips.size();
    for(auto &&voip : CMVoips) {
        stream << voip.serializeData();
    }
    stream << CMFtpDls.size();
    for(auto &&ftpdl : CMFtpDls) {
        stream << ftpdl.serializeData();
    }
    stream << CMFtpUls.size();
    for(auto &&ftpul : CMFtpUls) {
        stream << ftpul.serializeData();
    }
    stream << CMStreamDls.size();
    for(auto &&streamDls : CMStreamDls) {
        stream << streamDls.serializeData();
    }
    stream << CMStreamUls.size();
    for(auto &&streamUls : CMStreamUls) {
        stream << streamUls.serializeData();
    }
    stream << CMSyncedPings.size();
    for(auto &&syncedPing : CMSyncedPings) {
        stream << syncedPing.serializeData();
    }
    stream << CMServiceReqs.size();
    for(auto &&serviceReqs : CMServiceReqs) {
        stream << serviceReqs.serializeData();
    }
    return serializedData.buffer();
}

void CustomModelSettings::deserializeData(const QByteArray &rawData)
{
    int objectsAmount;

    QDataStream stream(rawData);

    stream >> objectsAmount;
    while(objectsAmount--) {
        QByteArray rawCMPingsData;
        stream >> rawCMPingsData;

        Ping ping;
        ping.deserializeData(rawCMPingsData);
        CMPings.push_back(ping);
    }
    stream >> objectsAmount;
    while(objectsAmount--) {
        QByteArray rawCMVoipsData;
        stream >> rawCMVoipsData;

        Voip voip;
        voip.deserializeData(rawCMVoipsData);
        CMVoips.push_back(voip);
    }
    stream >> objectsAmount;
    while(objectsAmount--) {
        QByteArray rawCMFtpDlsData;
        stream >> rawCMFtpDlsData;

        FtpDl ftpdl;
        ftpdl.deserializeData(rawCMFtpDlsData);
        CMFtpDls.push_back(ftpdl);
    }
    stream >> objectsAmount;
    while(objectsAmount--) {
        QByteArray rawCMFtpUlsData;
        stream >> rawCMFtpUlsData;

        FtpUl ftpul;
        ftpul.deserializeData(rawCMFtpUlsData);
        CMFtpUls.push_back(ftpul);
    }
    stream >> objectsAmount;
    while(objectsAmount--) {
        QByteArray rawCMStreamDlsData;
        stream >> rawCMStreamDlsData;

        StreamDl streamDl;
        streamDl.deserializeData(rawCMStreamDlsData);
        CMStreamDls.push_back(streamDl);
    }
    stream >> objectsAmount;
    while(objectsAmount--) {
        QByteArray rawCMStreamUlsData;
        stream >> rawCMStreamUlsData;

        StreamUl streamUl;
        streamUl.deserializeData(rawCMStreamUlsData);
        CMStreamUls.push_back(streamUl);
    }
    stream >> objectsAmount;
    while(objectsAmount--) {
        QByteArray rawCMSyncedPingsData;
        stream >> rawCMSyncedPingsData;

        SyncedPing syncedPing;
        syncedPing.deserializeData(rawCMSyncedPingsData);
        CMSyncedPings.push_back(syncedPing);
    }
    stream >> objectsAmount;
    while(objectsAmount--) {
        QByteArray rawCMServiceReqsData;
        stream >> rawCMServiceReqsData;

        ServiceReq serviceReq;
        serviceReq.deserializeData(rawCMServiceReqsData);
        CMServiceReqs.push_back(serviceReq);
    }
}
