#ifndef CELLAREA_H
#define CELLAREA_H

#include <QPoint>
#include "myobjectarea.h"

class CellArea : public MyObjectArea
{
    friend class CellArea_Test;
public:
    CellArea(int positionX, int positionY, QString ID) {
        center.setX(positionX);
        center.setY(positionY);
        pci = ID;
    }

    bool contain(int xPos, int yPos, MyObjectArea **objPtr1);
    QPoint getCenter() { return center; }
    QString getID() {
        return pci;
    }
    static int getR(){ return R; }
private:
    QPoint center;
    static const int R;
    QString pci;
};
#endif // CELLAREA_H
