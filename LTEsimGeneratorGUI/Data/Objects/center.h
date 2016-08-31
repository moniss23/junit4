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
    QString new_name_area;

    int southBoundary;
    int northBoundary;
    int westBoundary;
    int eastBoundary;
};

#endif // CENTER_H
