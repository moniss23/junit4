#ifndef pagingSETTINGS_H
#define pagingSETTINGS_H

#include <QVector>
#include <QStringList>

#include "Data/Interfaces/serializeinterface.h"
#include "Data/Interfaces/scriptable.h"

/**
 * @brief The PagingSettings class includes settings for Paging module
 */
class PagingSettings : public SerializeInterface, public Scriptable
{
public:
    PagingSettings();
    ~PagingSettings();

    int generators;                 ///< Number of generators
    QStringList names;              ///< Names of generators
    QStringList imsiRanges;         ///< IMSI ranges
    QStringList mmeCodes;           ///< MME codes
    QString uePagingIdentity;       ///< UE paging identity
    QStringList pagingSlapUris;     ///< Paging slap URIS

    bool isUsedInConfiguration;     ///< Usage in configuration setting (true/false)
    bool s1apCheckAsn1Contrains;    ///< Slap check ASN1 contrains setting (true/false)
    bool bundlePaging;              ///< Bundle paging setting (true/false)

    int rate=0;                     ///< Rate (default = 0)
    QVector<int> rates;             ///< Vector of rates

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
