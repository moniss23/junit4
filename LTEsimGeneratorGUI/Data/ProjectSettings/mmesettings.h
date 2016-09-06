#ifndef MMESETTINGS_H
#define MMESETTINGS_H

#include "Data/Interfaces/serializeinterface.h"
#include "Data/Interfaces/scriptable.h"

class MmeSettings : public SerializeInterface, public Scriptable
{
public:
    MmeSettings();
    ~MmeSettings();
    bool simulatedCoreNetwork;
    QStringList names;
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


    /****************************
    *   PARSING INTERFACE       *
    ****************************/

    virtual QString ParseToScript();
};

#endif // MMESETTINGS_H
