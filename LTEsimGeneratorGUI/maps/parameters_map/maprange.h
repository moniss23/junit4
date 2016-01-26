#ifndef MAPRANGE_H
#define MAPRANGE_H
#include <QList>
#include <QString>

class MapRange
{
public:
    MapRange();
    int getSouthBoundMap() const;
    void setSouthBoundMap(int value);

    int getNorthBoundMap() const;
    void setNorthBoundMap(int value);

    int getWestBoundMap() const;
    void setWestBoundMap(int value);

    int getEastBoundMap() const;
    void setEastBoundMap(int value);

private:
    int southBoundMap;
    int northBoundMap;
    int westBoundMap;
    int eastBoundMap;
    QList<QString> fileParameters;
    void openFile();
    QString searchParameters(QString);
    void setParams();
};

#endif // MAPRANGE_H
