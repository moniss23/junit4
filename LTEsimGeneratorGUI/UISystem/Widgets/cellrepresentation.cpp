#include "cellrepresentation.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsProxyWidget>

#include <QDebug>
#include <QPushButton>

CellRepresentation::CellRepresentation(QGraphicsObject *parent)
    :QGraphicsObject(parent)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

    QPushButton *button = new QPushButton("OK");
    QGraphicsProxyWidget *widget =new QGraphicsProxyWidget(this);
    widget->setWidget(button);
    widget->setPos(30,30);

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

    QColor co2l =  QColor(Qt::red).lighter(90);
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



    painter->setPen(QPen(Qt::black, 0));
    painter->drawText(-centersize,-centersize, "cell12");
}




QVariant CellRepresentation::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        qDebug()<<"Position has changed to:"<<pos();
        break;
    default:
        break;
    };

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

