#ifndef MMESETTINGS_H
#define MMESETTINGS_H
#include <QString>
#include "Data/Interfaces/serializeinterface.h"

class MmeSettings : public SerializeInterface
{
public:
    MmeSettings();
    ~MmeSettings();
    bool simulatedCoreNetwork;
    QString name;
    QString tais;
    int numberOfMme;
    QString uris;
    QString pluginFilterPath;


    /****************************
    * SERIALIZATION INTERFACE  *
    ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);

};

#endif // MMESETTINGS_H
