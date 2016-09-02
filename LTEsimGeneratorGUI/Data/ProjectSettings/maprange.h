#ifndef MAPRANGE_H
#define MAPRANGE_H
#include <QString>

#include "Data/Interfaces/serializeinterface.h"

class MapRange : public SerializeInterface
{
public:
    MapRange();
    double northBoundMap;
    double southBoundMap;
    double eastBoundMap;
    double westBoundMap;


    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);



};

#endif // MAPRANGE_H
