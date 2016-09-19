#ifndef pagingSETTINGS_H
#define pagingSETTINGS_H

#include <QStringList>
#include "Data/Interfaces/serializeinterface.h"
#include "Data/Interfaces/scriptable.h"

class PagingSettings : public SerializeInterface, public Scriptable
{
public:
    PagingSettings();
    ~PagingSettings();
    bool isUsedInConfiguration;
    int generators;
    QStringList names;
    QStringList imsiRanges;
    QStringList mmeCodes;
    QString uePagingIdentity;
    QStringList pagingSlapUris;
    bool s1apCheckAsn1Contrains;
    bool bundlePaging;
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

#endif // pagingSETTINGS_H
