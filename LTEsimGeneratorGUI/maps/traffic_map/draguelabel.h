#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>

class QDragEnterEvent;
class QDragMoveEvent;
class QFrame;

class DragUELabel : public QLabel
{
public:
    DragUELabel(const QString &text, QWidget *parent);
    QString labelText() const;

private:
    QString m_labelText;

};

#endif // DRAGLABEL_H
