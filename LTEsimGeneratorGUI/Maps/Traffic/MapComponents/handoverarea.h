#ifndef HANDOVERAREA_H
#define HANDOVERAREA_H

#include <QRect>
#include <Maps/Traffic/MapComponents/myobjectarea.h>
#include <Maps/Traffic/MapComponents/cellarea.h>

class HandoverArea : public MyObjectArea
{
public:
    HandoverArea(CellArea *cell1, CellArea *cell2/*, QRect rectArg*/)
        : cell1(cell1), cell2(cell2) { /*rect = rectArg;*/}
    bool contain(int xPos, int yPos, MyObjectArea **objPtr1);
    QString getID() {
        return cell1->getID() + cell2->getID();
    }

private:
    QRect rect;
    CellArea *cell1, *cell2;
};

#endif // HANDOVERAREA_H
