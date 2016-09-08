#ifndef STREAMDL_H
#define STREAMDL_H

#include "Data/Interfaces/serializeinterface.h"

class StreamDl : public SerializeInterface
{
public:
    StreamDl();
    ~StreamDl() {}

    QString currentQciTextStreamDl;
    int streamDlQci;
    int streamDlSpeed;
    int streamDlDuration;
    int streamDlMinThroughput;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // STREAMDL_H
