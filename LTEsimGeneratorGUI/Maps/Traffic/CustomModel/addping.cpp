#include "addping.h"

Addping::Addping() : qci(0),numberofpings(0), interval(0), minrecievedpings(0) {}

Addping::~Addping(){}

QString Addping::getQci(){return QString::number(qci);}
void Addping::setQci(QString value){this->qci = value.toInt();}

QString Addping::getNumberOfPings(){return QString::number(numberofpings);}
void Addping::setNumberOfPings(QString value){this->numberofpings = value.toInt();}

QString Addping::getInterval(){return QString::number(interval);}
void Addping::setInterval(QString value){this->interval = value.toInt();}

QString Addping::getMinRecievedPings(){return QString::number(minrecievedpings);}
void Addping::setMinRecievedPings(QString value){this->minrecievedpings = value.toInt();}
