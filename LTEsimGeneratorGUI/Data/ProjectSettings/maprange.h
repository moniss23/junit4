#ifndef MAPRANGE_H
#define MAPRANGE_H

#include "Data/Interfaces/serializeinterface.h"

/**
 * @brief The MapRange class contains boundaries for map
 */
class MapRange : public SerializeInterface
{
public:
    MapRange();
    ~MapRange() {}

    int northBoundMap;      ///< Northern boundary
    int southBoundMap;      ///< Southern boundary
    int eastBoundMap;       ///< Eastern boundary
    int westBoundMap;       ///< Western boundary
    int mapScale = 7000;    ///< Map scale

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
};

#endif // MAPRANGE_H
