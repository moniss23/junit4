#include "addftpul.h"

Addftpul::Addftpul()
{
    qci=0;
    filesize=0;
    minthroughput=0;
}

Addftpul::~Addftpul()
{
}

void Addftpul::setQci(QString value)
{
    this->qci = value.toInt();
}
QString Addftpul::getQci()
{
    return QString::number(qci);
}

void Addftpul::setFilesize(QString value)
{
    this->filesize = value.toInt();
}

QString Addftpul::getFilesize()
{
    return QString::number(filesize);
}

void Addftpul::setMinthroughput(QString value)
{
    this->minthroughput = value.toInt();
}

QString Addftpul::getMinthroughput()
{
    return QString::number(minthroughput);
}
