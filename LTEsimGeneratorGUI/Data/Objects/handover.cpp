#include "Data/Objects/handover.h"

#include <QDataStream>

Handover::Handover() {}
Handover::Handover(const QString &name) {area = name;}

Handover::~Handover() {}

void Handover::resetParams() {}

QDataStream &operator>>(QDataStream &in, Handover &handover)
{
    in >> handover.area;
    in >> handover.southBoundary >> handover.northBoundary;
    in >> handover.westBoundary >> handover.eastBoundary;

    return in;
}

QDataStream &operator<<(QDataStream &out, const Handover &handover)
{
    out << handover.area;
    out << handover.southBoundary << handover.northBoundary;
    out << handover.westBoundary << handover.eastBoundary;

    return out;
}
