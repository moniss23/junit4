#include "addftpdl.h"

Addftpdl::Addftpdl() : qci(0), filesize(0), minthroughput(0) {}

Addftpdl::~Addftpdl(){}

QString Addftpdl::getQci(){return QString::number(qci);}
void Addftpdl::setQci(QString value){this->qci = value.toInt();}

QString Addftpdl::getFilesize(){return QString::number(filesize);}
void Addftpdl::setFilesize(QString value){this->filesize = value.toInt();}

QString Addftpdl::getMinthroughput(){return QString::number(minthroughput);}
void Addftpdl::setMinthroughput(QString value){this->minthroughput = value.toInt();}
