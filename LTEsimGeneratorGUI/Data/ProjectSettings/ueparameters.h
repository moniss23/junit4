#ifndef UeParameters_H
#define UeParameters_H

#include <QString>
#include <QPair>
#include <QVector>

class UeParameters
{
public:
    UeParameters();
    ~UeParameters();
    bool startUeComponent;
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
