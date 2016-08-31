#ifndef HANDOVER_H
#define HANDOVER_H

#include <QString>

class Handover
{
public:
    Handover();
    Handover(const QString &name);
    ~Handover();

    void resetParams();

public:
    QString area;
    int southBoundary;
    int northBoundary;
    int westBoundary;
    int eastBoundary;
};

#endif // HANDOVER_H
