#include "draguelabel.h"

#include <QtWidgets>

DragUELabel::DragUELabel(const QString &text, QWidget *parent)
    : QLabel(text, parent)
{
    QFontMetrics metric(font());
    QSize size = metric.size(Qt::TextSingleLine, text);

    QImage image(size.width() + 12, size.height() + 12, QImage::Format_ARGB32_Premultiplied);
    image.fill(qRgba(0, 0, 0, 0));

    QFont font;
    font.setStyleStrategy(QFont::ForceOutline);

    QLinearGradient gradient(0, 0, 0, image.height()-1);
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(0.2, QColor(200, 200, 255));
    gradient.setColorAt(0.8, QColor(200, 200, 255));
    gradient.setColorAt(1.0, QColor(127, 127, 200));

    QPainter painter;
    painter.begin(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(gradient);
    painter.drawRoundedRect(QRectF(0.5, 0.5, image.width()-1, image.height()-1),
                            25, 25, Qt::RelativeSize);

    painter.setFont(font);
    painter.setBrush(Qt::black);
    painter.drawText(QRect(QPoint(6, 6), size), Qt::AlignCenter, text);
    painter.end();

    setPixmap(QPixmap::fromImage(image));
    m_labelText = text;
    myArea = NULL;
}

QString DragUELabel::labelText() const
{
    return m_labelText;
}

void DragUELabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    (void) event;
    //TO BE FINISHED
}

void DragUELabel::setmyArea(MyObjectArea *objectArea)
{
    myArea = objectArea;
}

MyObjectArea* DragUELabel::getmyArea()
{
<<<<<<< 6d7ccf832922aaf55c477e811f79daa1688057a5:LTEsimGeneratorGUI/maps/traffic_map/map_components/draguelabel.cpp
    return myArea;
=======
    try{
        if( myArea == NULL)
            throw 1;
        return myArea;
    } catch ( int ){
        qDebug() << "myHandoverArea points to NULL adress";
    }
>>>>>>> Renamed and relocated most of folders:LTEsimGeneratorGUI/Maps/Traffic/MapComponents/draguelabel.cpp
}

