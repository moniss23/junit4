#include "cellarea.h"

const int CellArea::R = 5000;

bool CellArea::contain(int xPos, int yPos, MyObjectArea **objPtr1)
{
    if ((xPos-center.x())*(xPos-center.x())+(yPos-center.y())*(yPos-center.y())<=R*R){
        *objPtr1 = this;
        return true;
    }
    else
        return false;
}
