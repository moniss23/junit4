#ifndef CUSTOMMODELLABEL_H
#define CUSTOMMODELLABEL_H

#include <QLabel>

class CustomModelLabel : public QLabel
{
    friend class CustomModelLabel_Test;
public:
    CustomModelLabel(const QString &text, QWidget *parent = 0);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void setGeometry(int x, int y){QLabel::setGeometry(x, y, cmWidth, cmHeigth);};
private:
    static const int cmWidth;
    static const int cmHeigth;
};

#endif // CUSTOMMODELLABEL_H
