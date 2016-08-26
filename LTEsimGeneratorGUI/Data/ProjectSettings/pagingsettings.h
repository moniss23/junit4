#ifndef PAGINGSETTINGS_H
#define PAGINGSETTINGS_H
#include <QString>
#include <QVector>
#include "Data/Interfaces/serializeinterface.h"
class PagingSettings : public SerializeInterface
{
public:
    PagingSettings();
    ~PagingSettings();
    int generators;
    QVector<QString> names;
    QString imsiRanged;
    QVector<QString> mmeCodes;
    QString uePagingIdentity;
    QString pagingSlapUris;

    /****************************
    * SERIALIZATION INTERFACE  *
    ****************************/

    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);



};

#endif // PAGINGSETTINGS_H
