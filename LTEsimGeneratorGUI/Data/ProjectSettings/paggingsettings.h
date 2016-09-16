#ifndef paggingSETTINGS_H
#define paggingSETTINGS_H

#include <QStringList>
#include "Data/Interfaces/serializeinterface.h"
#include "Data/Interfaces/scriptable.h"

class PaggingSettings : public SerializeInterface, public Scriptable
{
public:
    PaggingSettings();
    ~PaggingSettings();
    bool isUsedInConfiguration;
    int generators;
    QStringList names;
    QStringList imsiRanges;
    QStringList mmeCodes;
    QString uePaggingIdentity;
    QStringList paggingSlapUris;
    bool s1apCheckAsn1Contrains;
    bool bundlePagging;
    int rate=0;

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

#endif // paggingSETTINGS_H
