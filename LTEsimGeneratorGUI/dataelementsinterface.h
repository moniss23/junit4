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
    virtual QString getElementType() const = 0;
    virtual void serializeToProjectFile() const = 0;
    virtual void serializeFromProjectFileOld(QByteArray rawData) = 0;
    virtual void serializeFromProjectFileNew(QByteArray rawData) = 0;
    virtual void serializeToScriptCommands() = 0;
    virtual QByteArray readDataFromProj() = 0;
};

#endif // DATAELEMENTSINTERFACE_H
