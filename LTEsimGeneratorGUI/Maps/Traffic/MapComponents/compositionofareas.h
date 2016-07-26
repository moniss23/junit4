#ifndef COMPOSITIONOFAREAS_H
#define COMPOSITIONOFAREAS_H

#include "myobjectarea.h"

//------SubClass of MyObjectArea that enable to append containers and
//------single objects to the areaList object
class CompositionOfAreas : public MyObjectArea
{
public:
    bool contain(int xPos, int yPos, MyObjectArea **objPtr1)
    {
        (void) xPos;
        (void) yPos;
        (void) objPtr1;

        return 1;
    }
    QString getID()
    {
        return "composition";
    }
    void addToList(MyObjectArea *object)
    {
        areaList.append(object);
    }
    int size()
    {
        return areaList.size();
    }

    QVector<MyObjectArea*> areaList;
};

#endif // COMPOSITIONOFAREAS_H
