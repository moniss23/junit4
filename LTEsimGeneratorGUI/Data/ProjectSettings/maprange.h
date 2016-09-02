#ifndef MAPRANGE_H
#define MAPRANGE_H
#include <QString>

#include "Data/Interfaces/serializeinterface.h"

class MapRange : public SerializeInterface
{
public:
    MapRange();
    ~MapRange() {}

    int northBoundMap;
    int southBoundMap;
    int eastBoundMap;
    int westBoundMap;


    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // MAPRANGE_H
