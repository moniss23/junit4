#include "addstreamdl.h"

Addstreamdl::Addstreamdl() : qci(0), speed(0), duration(0), minthroughput(0) {}

Addstreamdl::~Addstreamdl(){}

QString Addstreamdl::getQci(){return QString::number(qci);}
void Addstreamdl::setQci(QString value){this->qci = value.toInt();}

QString Addstreamdl::getSpeed(){return QString::number(speed);}
void Addstreamdl::setSpeed(QString value){this->speed = value.toInt();}

QString Addstreamdl::getDuration(){return QString::number(duration);}
void Addstreamdl::setDuration(QString value){this->duration = value.toInt();}

QString Addstreamdl::getMinThroughput(){return QString::number(minthroughput);}
void Addstreamdl::setMinThroughput(QString value){this->minthroughput = value.toInt();}
