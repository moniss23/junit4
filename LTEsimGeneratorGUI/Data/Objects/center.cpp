#include <QFile>
#include <QTextStream>

#include "Data/Objects/center.h"
#include "Maps/Parameters/MapWindow/mapwindow.h"

Center::Center() {}
Center::Center(const QString &name) {area = name;}

void Center::resetParams() {}
