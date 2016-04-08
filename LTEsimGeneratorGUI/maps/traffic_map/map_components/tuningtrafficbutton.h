#ifndef TUNINGTRAFFICBUTTON_H
#define TUNINGTRAFFICBUTTON_H

#include <QtWidgets>

class TuningTrafficButton : public QPushButton
{
public:
    TuningTrafficButton(QWidget *parent = 0) : QPushButton("Tuning traffic", parent){};
    void mousePressEvent(QMouseEvent *event);
};

#endif // TUNINGTRAFFICBUTTON_H
