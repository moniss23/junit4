#include <QPainter>

#include "handoverrepresentation.h"

HandoverRepresentation::HandoverRepresentation(Handover &handover, QGraphicsObject *parent)
    : QGraphicsObject(parent),
      handoverObject(handover)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(1);

    icon.load(":/Images/handover.png");
}

void HandoverRepresentation::updatePositions() {
    width = handoverObject.eastBoundary - handoverObject.westBoundary;
    height = handoverObject.northBoundary - handoverObject.southBoundary;

    position_X = handoverObject.westBoundary + width/2;
    position_Y = handoverObject.northBoundary - height/2;

    if(width > height) {
        icon = icon.transformed(QMatrix().rotate(90.0));
    }

    this->setPos(position_X, -position_Y);
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

    painter->fillRect(rect, QBrush(QColor(51, 153, 204, 205)));
    painter->drawImage(rect, this->icon);
}

void HandoverRepresentation::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mousePressEvent(event);
}

void HandoverRepresentation::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);

    int posX = pos().x();
    int posY = pos().y();
    handoverObject.westBoundary = posX-width/2;
    handoverObject.eastBoundary = posX+width/2;
    handoverObject.southBoundary = -posY-height/2;
    handoverObject.northBoundary = -posY+height/2;

    emit spawnWindow_HandoverParams(this, this->handoverObject);
}

QVariant HandoverRepresentation::itemChange(GraphicsItemChange change, const QVariant &value) {
    return QGraphicsItem::itemChange(change, value);
}
