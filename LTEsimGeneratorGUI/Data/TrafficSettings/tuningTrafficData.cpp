#include "tuningTrafficData.h"

TuningTrafficData::TuningTrafficData()
{
    for(auto name : CSSTRINGLIST) {
        CSParameters cs(name);
        csParamGroup.push_back(cs);
    }

    for(auto name : PSSTRINGLIST) {
        PSParameters ps(name);
        psParamGroup.push_back(ps);
    }

    for(auto name : MOBILITYSTRINGLIST) {
        Mobility mobility(name);
        mobilityGroup.push_back(mobility);
    };
}

TuningTrafficData::~TuningTrafficData()
{

}

QString TuningTrafficData::getElementType() const
{
    return QString("TuningTrafficData");
}

QByteArray TuningTrafficData::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);

    for(auto elem : csParamGroup) {
        stream << elem.csName << elem.callIntensity << elem.callDuration << elem.recoveryStartInterval;
    }

    for(auto elem : psParamGroup) {
        stream << elem.psName << elem.psIntensity << elem.psDuration;
    }

    for(auto elem : mobilityGroup) {
        stream << elem.mobilityName << elem.speed << elem.granularity;
    }

    return serializedData.buffer();
}

void TuningTrafficData::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);

    for(auto elem : csParamGroup) {
        stream >> elem.csName >> elem.callIntensity >> elem.callDuration >> elem.recoveryStartInterval;
    }

    for(auto elem : psParamGroup) {
        stream >> elem.psName >> elem.psIntensity >> elem.psDuration;
    }

    for(auto elem : mobilityGroup) {
        stream >> elem.mobilityName >> elem.speed >> elem.granularity;
    }
}

const QStringList TuningTrafficData::CSSTRINGLIST = {
    "PowerOnPowerOff",
    "poweron",
    "PowerOnOffPsCnt",
    "PowerOnOffPsCntRecover",
    "PowerOnForcePowerOff",
    "PowerOnPowerOffEmergency",
    "PowerOnEmergency",
    "PowerOnOffPsCntEmergency",
    "PowerOnOffPsCntRecoverEmergency",
    "PowerOnForcePowerOffEmergency"
};

const QStringList TuningTrafficData::PSSTRINGLIST = {
    "general_10s_50Mbps",
    "general_infinite_200Mbps",
    "LteFtpEightBearers",
    "LteBatStaticPing",
    "LtePing",
    "LtePingFtpOnDefault",
    "LtePingFtpDlOnDefault",
    "LtePingFtpUlOnDefault",
    "LteFtpGet",
    "LteFtpPut",
    "LteInstantMsgOrig",
    "LteInstantMsgOrig2Pdn",
    "LteInstantMsgTerm",
    "LteInstantMsgTerm2Pdn",
    "LteMobileTv",
    "LteP2P",
    "LteP2P2Pdn",
    "LtePDStreaming",
    "LtePDStreaming2Pdn",
    "LteRealTimeStreaming",
    "LteRealTimeStreaming2Pdn",
    "LteRealTimeStreamingDynSpeed",
    "LteServiceReq",
    "LteWww",
    "LteWww2Pdn",
    "LteBatRealTimeStreaming",
    "LteBatRealTimeStreamingDLUL",
    "LteBatPDStreaming",
    "LteBatWww",
    "LteBatInstantMessaging",
    "LteBatP2P",
    "LteBatPing",
    "LteBatMobileTv",
    "LteMMTelAudioVisualOrig2Pdn",
    "LteMMTelStaticBearerPingOnDefault",
    "LteMMTelStaticBearerFtpDlOnDefault",
    "LteMMTelDynamicBearerPingOnDefault",
    "LteMMTelVoip",
    "LteMMTelVoip50",
    "LteMMTelVoip2Pdn50",
    "LteMMTelVoipTerm",
    "LteMMTelVoipTerm50",
    "LteMMTelVoipTerm2Pdn50"
};

const QStringList TuningTrafficData::MOBILITYSTRINGLIST = {
    "RandomWalker",
    "standstill",
    "HorizontalWalker",
    "VerticalWalker",
    "WalkerStartAtEast",
    "WalkerStartAtNorth",
    "WalkerStartAtSouth",
    "WalkerStartAtWest"
};
