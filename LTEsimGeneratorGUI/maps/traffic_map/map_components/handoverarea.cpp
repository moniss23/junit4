#include "handoverarea.h"

bool HandoverArea::contain(int xPos, int yPos, MyObjectArea **objPtr1)
{
    if ((xPos < (rect.x() + rect.width())) && (xPos > rect.x()) &&
    (yPos < (rect.y() + rect.height())) && (yPos > rect.y())){
        *objPtr1 = this;
        return true;
    }
    else
        return false;
}
