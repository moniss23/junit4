#ifndef ADDFTPDL_H
#define ADDFTPDL_H

#include <QString>

class Addftpdl
{
public:
    Addftpdl();
    ~Addftpdl();

    void setQci(QString value);
    QString getQci();

    void setFilesize(QString value);
    QString getFilesize();

    void setMinthroughput(QString value);
    QString getMinthroughput();

private:
    int qci;
    int filesize;
    int minthroughput;
};

#endif // ADDFTPDL_H
