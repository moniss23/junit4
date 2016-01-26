#ifndef HANDOVER_H
#define HANDOVER_H
#include <QString>
class Handover
{
public:
    Handover();
    Handover(QString name);
    ~Handover();
    QString getArea();
    QString getSouthBoundary();
    QString getNorthBoundary();
    QString getWestBoundary();
    QString getEastBoundary();

    void setSouthBoundary(QString s);
    void setNorthBoundary(QString n);
    void setWestBoundary(QString w);
    void setEastBoundary(QString e);

    void resetParams();

private:
    QString area;
    int southBoundary;
    int northBoundary;
    int westBoundary;
    int eastBoundary;

    QString *tabParams;
    void setParams();
};

#endif // HANDOVER_H
