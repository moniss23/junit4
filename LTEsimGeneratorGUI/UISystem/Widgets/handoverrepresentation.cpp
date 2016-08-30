#include <QPainter>
#include "handoverrepresentation.h"

HandoverRepresentation::HandoverRepresentation(QGraphicsObject *parent)
    : QGraphicsObject(parent)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(1);
}

void HandoverRepresentation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    (void) option;
    (void) widget;

    QRectF rect(-width/2, -height/2, width, height);

    painter->drawRoundedRect(rect, 5, 5);
    painter->fillRect(rect, QBrush(Qt::blue));
}

void HandoverRepresentation::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mousePressEvent(event);
}

void HandoverRepresentation::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant HandoverRepresentation::itemChange(GraphicsItemChange change, const QVariant &value) {
    return QGraphicsItem::itemChange(change, value);
}
