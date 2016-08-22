#ifndef CENTER_H
#define CENTER_H
#include <QString>
class Center
{
public:
    Center();
    Center(QString name);

    QString getArea();
    QString getSouthBoundary();
    QString getNorthBoundary();
    QString getWestBoundary();
    QString getEastBoundary();

    void setArea(QString value);
    void setSouthBoundary(QString s);
    void setNorthBoundary(QString n);
    void setWestBoundary(QString w);
    void setEastBoundary(QString e);

    bool wasThereParametersChange();

    void resetParams();

    QString getNew_name_area() const;
    void setNew_name_area(const QString &value);

private:
    QString new_name_area;
    QString area;
    int southBoundary;
    int northBoundary;
    int westBoundary;
    int eastBoundary;

    void setParams();
    QString *tabParams;
};

#endif // CENTER_H
