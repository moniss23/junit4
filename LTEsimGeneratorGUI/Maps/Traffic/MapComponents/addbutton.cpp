#include "addbutton.h"

bool AddButton::created = false;

//------Adds DragUELabels to MyScrollAreaWidget------
void AddButton::mousePressEvent(QMouseEvent *event)
{
    (void) event;

    try{
        if(created)
            throw 1;
        int counter = pointer->ueGroupLabel.size();
        pointer->ueGroupLabel.append(new DragUELabel("ue" + QString::number(counter + 1), pointer));
        pointer->ueGroupLabel[counter]->show();
        pointer->ueGroupLabel[counter]->setGeometry(850, 100, 40, 30);
        created = true;
    } catch( int ) {
        // TODO:
        // zamienic ten try-catch na kiju na cos co dziala lepiej, ale to temat na osobny commit
    }
}
