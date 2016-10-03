#ifndef FTPUL_H
#define FTPUL_H

#include "Data/Interfaces/serializeinterface.h"

/**
 * @brief The FtpUl class contains settings for FTP uplink
 */
class FtpUl : public SerializeInterface
{
public:
    FtpUl();
    ~FtpUl() {}

    int ftpUlQci = 0;                   ///< FTP uplink QCI
    int ftpUlFilesize;                  ///< FTP uplink filesize
    int ftpUlMinThroughput;             ///< FTP uplink min. throughput

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // FTPUL_H
