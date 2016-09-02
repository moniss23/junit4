#include "maprange.h"

#include <QBuffer>
#include <QDataStream>

MapRange::MapRange()
{

}
QString MapRange::getElementType() const {
    return QString("MapRange");
}

QByteArray MapRange::serializeData() {
    QBuffer serializedData;
    serializedData.open(QBuffer::WriteOnly);

    QDataStream stream(&serializedData);
    stream << northBoundMap << southBoundMap << eastBoundMap << westBoundMap ;

    return serializedData.buffer();
}

void MapRange::deserializeData(const QByteArray &rawData) {
    QDataStream stream(rawData);
    stream >> northBoundMap >> southBoundMap >> eastBoundMap >> westBoundMap ;
}
