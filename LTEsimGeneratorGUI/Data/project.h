#ifndef PROJECT_H
#define PROJECT_H

#include <QListWidgetItem>
#include <Maps/MapObjects/cell.h>
#include <Maps/MapObjects/handover.h>
#include <Maps/MapObjects/center.h>

struct Project{

    QString name;
    QString fullpath;
    QListWidgetItem* widget;
    QString rbOutputDir;
    QString chosenMapType;
};

struct cellName{
    Cell* obj;
    QString name;
};

struct centerName{
    Center* obj;
    QString name;
};

struct handoverName{
    Handover* obj;
    QString name;
};

#endif // PROJECT_H
