#ifndef TIMEBUTTON_H
#define TIMEBUTTON_H

#include <QtWidgets>

class TimeButton : public QPushButton
{
public:
    TimeButton(QWidget *parent = 0) : QPushButton("Time", parent){};
    void mousePressEvent(QMouseEvent *event);
};

#endif // TIMEBUTTON_H
