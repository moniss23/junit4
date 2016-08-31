#include <QPainter>
#include "handoverrepresentation.h"

HandoverRepresentation::HandoverRepresentation(QGraphicsObject *parent)
    : QGraphicsObject(parent)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(1);

    icon.load(":/Images/handover.png");
}

QRectF HandoverRepresentation::boundingRect() const {
    return QRectF(-width/2, -height/2, width, height);
}

QPainterPath HandoverRepresentation::shape() const {
    QPainterPath path;
    QRectF rect(-width/2, -height/2, width, height);

    path.addRect(rect);
    return path;
}

void HandoverRepresentation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    (void) option;
    (void) widget;

    QRectF rect(-width/2, -height/2, width, height);

    painter->setPen(QPen(Qt::gray, 0));
    painter->drawRoundedRect(rect, 3, 3);

    painter->fillRect(rect, QBrush(QColor(51, 153, 204, 255)));
    painter->drawImage(rect, this->icon);
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
