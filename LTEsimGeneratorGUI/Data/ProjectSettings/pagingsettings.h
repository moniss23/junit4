#ifndef PAGINGSETTINGS_H
#define PAGINGSETTINGS_H
#include <QString>
#include <QStringList>
#include <QVector>
#include "Data/Interfaces/serializeinterface.h"

class PagingSettings : public SerializeInterface
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
    bool bundlePaging;

    /****************************
    * SERIALIZATION INTERFACE  *
    ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);

};

#endif // PAGINGSETTINGS_H
