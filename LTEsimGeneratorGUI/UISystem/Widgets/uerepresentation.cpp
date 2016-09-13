#include <QPainter>

#include "uerepresentation.h"

UeRepresentation::UeRepresentation(UEData &ueObject) : color(128,128,128,255), ueObject(ueObject)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setAcceptHoverEvents(true);
    setZValue(1);
}

QRectF UeRepresentation::boundingRect() const {
    return QRectF(-width/2, -height/2, width, height);
}

QPainterPath UeRepresentation::shape() const {
    QPainterPath path;
    QRectF rect(-width/2, -height/2, width, height);

    path.addRect(rect);
    return path;
}

void UeRepresentation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    (void) widget;
    (void) option;
    QRectF rect(-width/2, -height/2, width, height);

    painter->setBrush(QBrush(color));
    painter->setPen(QPen(Qt::black, 1));
    painter->drawRoundedRect(rect, 3, 3);
}

void UeRepresentation::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mousePressEvent(event);
}

void UeRepresentation::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);

//    int posX = pos().x();
//    int posY = pos().y();
}

QVariant UeRepresentation::itemChange(GraphicsItemChange change, const QVariant &value) {
    return QGraphicsItem::itemChange(change, value);
}

void UeRepresentation::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  color = QColor(0, 255, 255, 205);
   QGraphicsItem::hoverEnterEvent(event);
}

void UeRepresentation::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
   color = QColor(128, 128, 128, 205);
   QGraphicsItem::hoverLeaveEvent(event);
}


