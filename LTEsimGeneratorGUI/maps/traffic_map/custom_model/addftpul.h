#ifndef ADDFTPUL_H
#define ADDFTPUL_H

#include <QString>
class Addftpul
{
public:
    Addftpul();
    ~Addftpul();

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

#endif // ADDFTPUL_H
