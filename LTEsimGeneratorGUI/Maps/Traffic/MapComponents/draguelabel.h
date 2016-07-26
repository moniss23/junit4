#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>

class QDragEnterEvent;
class QDragMoveEvent;
class QFrame;
class MyObjectArea;

class DragUELabel : public QLabel
{
    friend class DragUELabel_Test;
public:
    DragUELabel(const QString &text, QWidget *parent = 0);
    QString labelText() const;

    void mouseDoubleClickEvent(QMouseEvent *event);
    void setmyArea(MyObjectArea *objectArea);
    MyObjectArea* getmyArea();

private:
    MyObjectArea *myArea;
    QString m_labelText;
};

#endif // DRAGLABEL_H
