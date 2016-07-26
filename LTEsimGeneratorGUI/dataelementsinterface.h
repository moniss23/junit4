#ifndef DATAELEMENTSINTERFACE_H
#define DATAELEMENTSINTERFACE_H
#include <QByteArray>
#include <QString>
#include <QDomDocument>
#include <CommonConstans/common_constans.h>

class DataElementsInterface
{
public:
    DataElementsInterface(){}
    virtual ~DataElementsInterface(){}

public:
    virtual QString getElementType() const = 0;
    virtual void serializeToProjectFile() = 0;
    virtual void serializeFromProjectFileOld(QByteArray rawData) = 0;
    virtual void serializeFromProjectFileNew(QDomDocument xmlDocument) = 0;
    virtual void serializeToScriptCommands() = 0;
};

#endif // DATAELEMENTSINTERFACE_H
