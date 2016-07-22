#include "custommodellabel.h"

const int CustomModelLabel::cmWidth = 50;
const int CustomModelLabel::cmHeigth = 27;

CustomModelLabel::CustomModelLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent)
{
    setFrameShape(QFrame::Box);
    setStyleSheet("QLabel { background-color : rgb(193, 193, 193)}");
}

void CustomModelLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    (void) event;
}
