#ifndef UeParameters_H
#define UeParameters_H

#include <QString>
#include <QPair>
#include <QVector>

#include "Data/Interfaces/scriptable.h"
#include "Data/Interfaces/serializeinterface.h"

class UeParameters: public SerializeInterface
{
public:
    UeParameters();
    ~UeParameters();
    bool startUeComponent;// = false;//TODO: get rid of that default value after implementing parsing method
    QString name;
    QString managers;
    QString pluginFilterPath;
    QString ucToolIp;
    QString ucToolcIds;
    QString ucToolServiceIp;
    QString ueNetworkCapability;
    QString ueKeyDerivationAlgorithm;
    QString ueKey;
    QString ueOp;

    /****************************
    * SERIALIZATION INTERFACE  *
    ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);

};

#endif // UeParameters_H
