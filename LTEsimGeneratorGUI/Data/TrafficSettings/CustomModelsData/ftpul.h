#ifndef FTPUL_H
#define FTPUL_H

#include "Data/Interfaces/serializeinterface.h"

class FtpUl : public SerializeInterface
{
public:
    FtpUl();
    ~FtpUl() {}

    int ftpUlQci = 0;
    int ftpUlFilesize;
    int ftpUlMinThroughput;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // FTPUL_H
