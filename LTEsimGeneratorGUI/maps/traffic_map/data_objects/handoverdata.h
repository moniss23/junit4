#ifndef HANDOVERDATA_H
#define HANDOVERDATA_H
#include <QString>

class HandoverData
{
public:

    HandoverData(QString name);

    //----------------------------Getters------------------------------------------------

    QString getHandoverName();
    QString getSouthBoundary();
    QString getNorthBoundary();
    QString getWestBoundary();
    QString getEastBoundary();

    //----------------------------Setters------------------------------------------------

    void setHandoverName(QString name);
    void setSouthBoundary(QString south);
    void setNorthBoundary(QString north);
    void setWestBoundary(QString west);
    void setEastBoundary(QString east);

    void readParamsFromScript();

private:

    QString handoverName;
    int southBoundary;
    int northBoundary;
    int westBoundary;
    int eastBoundary;
};

#endif // HANDOVERDATA_H
