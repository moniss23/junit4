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
        qDebug() << "There is the other UE Group. Please use it before creating the new one.";
    }
}
