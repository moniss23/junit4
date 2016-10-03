#ifndef STREAMDL_H
#define STREAMDL_H

#include "Data/Interfaces/serializeinterface.h"

/**
 * @brief The StreamDl class contains settings for StreamDL component
 */
class StreamDl : public SerializeInterface
{
public:
    StreamDl();
    ~StreamDl() {}

    int streamDlQci = 0;            ///< QCI
    int streamDlSpeed;              ///< Speed
    int streamDlDuration;           ///< Duration
    int streamDlMinThroughput;      ///< Minimal throughput

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // STREAMDL_H
