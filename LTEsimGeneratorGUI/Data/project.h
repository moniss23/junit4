#ifndef PROJECT_H
#define PROJECT_H

#include <QDataStream>
#include <QListWidgetItem>
#include <Data/cell.h>
#include <Data/handover.h>
#include <Data/center.h>

#include <Data/serializeinterface.h>

class Project : public SerializeInterface
{
public:
    QString name;
    QString fullpath;
    QString rbOutputDir;
    QString chosenMapType;

    /****************************
     * SERIALIZATION INTERFACE  *
     ****************************/
public:
    virtual QString getElementType() const;
    virtual QByteArray serializeData();
    virtual void deserializeData(const QByteArray &rawData);
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
