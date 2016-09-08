#ifndef SERVICEREQ_H
#define SERVICEREQ_H

#include <QVector>

#include "Data/Interfaces/serializeinterface.h"

class ServiceReq : public SerializeInterface
{
public:
    ServiceReq();
    ~ServiceReq() {}

    QVector<QString> currentQciTextServiceReq;
    QVector<int> ServiceReqQciArray;
    int ServiceReqTimeToWaitForAttach;
    int ServiceReqIntervalBetweenUlData;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // SERVICEREQ_H
