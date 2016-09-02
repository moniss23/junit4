#include "cellrepresentation.h"

#include <QPainter>
#include <QPushButton>
#include <QStyleOption>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>

CellRepresentation::CellRepresentation(Cell &cell, QGraphicsObject *parent)
    : QGraphicsObject(parent),
      cellObject(cell)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

    QPushButton *button = new QPushButton("OK");
    auto font = button->font();
    font.setPointSize(circlesize / 20);
    button->setFont(font);
    button->setFixedSize(circlesize / 2.5,circlesize / 8);
    QGraphicsProxyWidget *widget =new QGraphicsProxyWidget(this);
    widget->setWidget(button);
    widget->setPos(centersize / 10, centersize);

}

QRectF CellRepresentation::boundingRect() const
{
    return QRectF( -circlesize/2 , -circlesize/2 , circlesize , circlesize );
}

QPainterPath CellRepresentation::shape() const
{
    QRectF rectangle(-centersize/2 , -centersize/2 , centersize, centersize);

    QPainterPath path;
    //path.addEllipse(boundingRect());
    path.addRect(rectangle);
    return path;
}

void CellRepresentation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void) widget;

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QColor col =  QColor(Qt::yellow).lighter(120);
    col.setAlpha(125);

    //QColor co2l =  QColor(Qt::red).lighter(90);
    QColor center(245,175,85);

    QRadialGradient gradient(-10, -10, circlesize);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, Qt::darkYellow);
        gradient.setColorAt(0, Qt::darkYellow);
    } else {
        gradient.setColorAt(0, col);
        gradient.setColorAt(1, Qt::darkYellow);
    }

    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::white, 0));
    painter->drawEllipse( -circlesize/2 , -circlesize/2 , circlesize, circlesize);

    painter->setBrush(QBrush(center));
    QRectF rectangle(-centersize/2 , -centersize/2 , centersize, centersize);
    painter->drawRoundedRect(rectangle,3,3);

    painter->setPen(QPen(Qt::black, 1));
    auto font = painter->font();
    font.setPointSize(circlesize / 15);
    painter->setFont(font);
    painter->drawText(-centersize,-centersize, this->cellObject.name);
}

QVariant CellRepresentation::itemChange(GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsItem::itemChange(change, value);
}

void CellRepresentation::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void CellRepresentation::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}
