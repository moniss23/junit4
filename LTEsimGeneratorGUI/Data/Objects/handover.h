#ifndef HANDOVER_H
#define HANDOVER_H
#include <QString>

class Handover {
public:
    Handover();
    Handover(const QString &name);
    ~Handover();

    QString getArea() const;
    QString getSouthBoundary() const;
    QString getNorthBoundary() const;
    QString getWestBoundary() const;
    QString getEastBoundary() const;

    void setArea(const QString &name);
    void setWestBoundary(const QString &west);
    void setEastBoundary(const QString &east);
    void setSouthBoundary(const QString &south);
    void setNorthBoundary(const QString &north);

    void resetParams();

private:
    QString area;
    int southBoundary;
    int northBoundary;
    int westBoundary;
    int eastBoundary;

    void setParams();
};

#endif // HANDOVER_H
