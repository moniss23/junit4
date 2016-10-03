#ifndef SERVICEREQ_H
#define SERVICEREQ_H

#include <QVector>

#include "Data/Interfaces/serializeinterface.h"

/**
 * @brief The ServiceReq class contains settings for ServiceReq component
 */
class ServiceReq : public SerializeInterface
{
public:
    ServiceReq();
    ~ServiceReq() {}

    QVector<int> ServiceReqQciArray;        ///< Container for serviceReq QCIs
    int ServiceReqTimeToWaitForAttach;      ///< Time to wait for attachment (in miliseconds)
    int ServiceReqIntervalBetweenUlData;    ///< Interval between UL data (in miliseconds)

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // SERVICEREQ_H
