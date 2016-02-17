#ifndef DATAELEMENTSINTERFACE_H
#define DATAELEMENTSINTERFACE_H
#include <QByteArray>
#include <QString>



class DataElementsInterface
{
public:
    DataElementsInterface(){}
    virtual ~DataElementsInterface(){}

public:
    virtual QString getElementType()=0;
    virtual QByteArray serializeToProjectFile()const  = 0;
    virtual void serializeFromProjectFile(QByteArray rawData) = 0;
    virtual void serializeToScriptCommands() = 0;

};

#endif // DATAELEMENTSINTERFACE_H
