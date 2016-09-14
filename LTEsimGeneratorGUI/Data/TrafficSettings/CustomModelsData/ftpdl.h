#ifndef FTPDL_H
#define FTPDL_H

#include "Data/Interfaces/serializeinterface.h"

class FtpDl : public SerializeInterface
{
public:
    FtpDl();
    ~FtpDl() {}

    int ftpDlQci = 0;
    int ftpDlFilesize;
    int ftpDlMinThroughput;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // FTPDL_H
