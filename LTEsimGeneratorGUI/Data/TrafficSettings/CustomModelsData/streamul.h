#ifndef STREAMUL_H
#define STREAMUL_H

#include "Data/Interfaces/serializeinterface.h"

/**
 * @brief The StreamUl class contains settings for StreamUL component
 */
class StreamUl : public SerializeInterface
{
public:
    StreamUl();
    ~StreamUl() {}

    int streamUlQci = 0;            ///< QCI
    int streamUlSpeed;              ///< Speed
    int streamUlDuration;           ///< Duration
    int streamUlMinThroughput;      ///< Minimal throughput

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // STREAMUL_H
