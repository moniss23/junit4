#ifndef STATISTICSBUTTON_H
#define STATISTICSBUTTON_H

#include <QtWidgets>

class StatisticsButton : public QPushButton
{
public:
    StatisticsButton(QWidget *parent = 0) : QPushButton("Statistics", parent){};
    void mousePressEvent(QMouseEvent *event);
};

#endif // STATISTICSBUTTON_H
