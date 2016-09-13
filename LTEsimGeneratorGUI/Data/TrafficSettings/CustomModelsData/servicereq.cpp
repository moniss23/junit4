#include "servicereq.h"

ServiceReq::ServiceReq()
{
}

QString ServiceReq::getElementType() const
{
    return QString("ServiceReq");
}

QByteArray ServiceReq::serializeData()
{
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << ServiceReqQciArray << ServiceReqTimeToWaitForAttach
           << ServiceReqIntervalBetweenUlData;

    return serializedData.buffer();
}

void ServiceReq::deserializeData(const QByteArray &rawData)
{
    QDataStream stream(rawData);
    stream >> ServiceReqQciArray >> ServiceReqTimeToWaitForAttach
           >> ServiceReqIntervalBetweenUlData;
}
