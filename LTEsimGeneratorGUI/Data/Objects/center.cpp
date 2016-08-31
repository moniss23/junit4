#include <QFile>
#include <QTextStream>

#include "Data/Objects/center.h"
#include "Maps/Parameters/MapWindow/mapwindow.h"

Center::Center() {}
Center::Center(const QString &name) {area = name;}

void Center::resetParams() {}

QDataStream &operator>>(QDataStream &in, Center &center)
{
    in >> center.area;
    in >> center.southBoundary >> center.northBoundary;
    in >> center.westBoundary >> center.eastBoundary;

    return in;
}

QDataStream &operator<<(QDataStream &out, const Center &center)
{
    out << center.area;
    out << center.southBoundary << center.northBoundary;
    out << center.westBoundary << center.eastBoundary;

    return out;
}
