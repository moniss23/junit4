#ifndef ADDBUTTON_H
#define ADDBUTTON_H

#include <QtWidgets>
#include "myscrollareawidget.h"

class AddButton : public QPushButton
{
    friend class MyScrollAreaWidget;
    friend class AddButton_Test;
public:
    AddButton(QWidget *parent = 0) : QPushButton("+", parent),
        pointer(dynamic_cast<MyScrollAreaWidget *>(parent)){};
    void mousePressEvent(QMouseEvent *event);
private:
    MyScrollAreaWidget *pointer;
    static bool created;
};

#endif // ADDBUTTON_H
