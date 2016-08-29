#include "handoverrepresentation.h"

HandoverRepresentation::HandoverRepresentation(QGraphicsObject *parent)
    : QGraphicsObject(parent)
{

}

void HandoverRepresentation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    (void) painter;
    (void) option;
    (void) widget;
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
