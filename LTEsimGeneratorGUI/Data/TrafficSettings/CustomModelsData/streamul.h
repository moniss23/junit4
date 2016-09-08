#ifndef STREAMUL_H
#define STREAMUL_H

#include "Data/Interfaces/serializeinterface.h"

class StreamUl : public SerializeInterface
{
public:
    StreamUl();
    ~StreamUl() {}

    QString currentQciTextStreamUl;
    int streamUlQci;
    int streamUlSpeed;
    int streamUlDuration;
    int streamUlMinThroughput;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // STREAMUL_H
