#ifndef CENTER_H
#define CENTER_H

#include <QString>

class Center
{
public:
    Center();
    Center(const QString &name);

    void resetParams();

public:
    QString area;
    int southBoundary;
    int northBoundary;
    int westBoundary;
    int eastBoundary;
};

QDataStream &operator>>(QDataStream &in, Center &center);
QDataStream &operator<<(QDataStream &out, const Center &center);

#endif // CENTER_H
