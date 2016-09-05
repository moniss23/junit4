#ifndef SCRIPTABLE_H
#define SCRIPTABLE_H

#include <QString>

class Scriptable
{
public:
    Scriptable(){}
    virtual ~Scriptable(){}
public:
    virtual QString ParseToScript()=0;
};

#endif // SCRIPTABLE_H
