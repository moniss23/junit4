#ifndef CENTER_H
#define CENTER_H
#include <QString>
class Center
{
public:
    Center();
    Center(const QString &name);

    QString getArea() const;
    QString getSouthBoundary() const;
    QString getNorthBoundary() const;
    QString getWestBoundary() const;
    QString getEastBoundary() const;
    QString getNew_name_area() const;

    void setArea(const QString &value);
    void setEastBoundary(const QString &east);
    void setWestBoundary(const QString &west);
    void setNorthBoundary(const QString &north);
    void setSouthBoundary(const QString &south);
    void setNew_name_area(const QString &value);

    void resetParams();

private:
    QString area;
    QString new_name_area;

    int southBoundary;
    int northBoundary;
    int westBoundary;
    int eastBoundary;

    void setParams();
};

#endif // CENTER_H
