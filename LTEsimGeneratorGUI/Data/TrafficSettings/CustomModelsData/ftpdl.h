#ifndef FTPDL_H
#define FTPDL_H

#include "Data/Interfaces/serializeinterface.h"

/**
 * @brief The FtpDl class contains settings for FTP downlink
 */
class FtpDl : public SerializeInterface
{
public:
    FtpDl();
    ~FtpDl() {}

    int ftpDlQci = 0;               ///< FTP downlink QCI
    int ftpDlFilesize;              ///< FTP downlink filesize
    int ftpDlMinThroughput;         ///< FTP downlink min. troughput

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // FTPDL_H
