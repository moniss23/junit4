#ifndef MYOBJECTAREA_H
#define MYOBJECTAREA_H

#include <QString>

//------Interface of area objects------
class MyObjectArea
{
public:
    virtual bool contain(int xPos, int yPos, MyObjectArea **objPtr1) = 0;
    virtual QString getID() = 0;
    virtual ~MyObjectArea(){}
};

#endif // MYOBJECTAREA_H
