#include <QPainter>

#include "uerepresentation.h"

UeRepresentation::UeRepresentation(UEData &ueObject, int index) : color(255,120,170,255), ueObject(ueObject), index(index)
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

    auto font = painter->font();
    font.setPointSize(8500/15);
    painter->setFont(font);
    painter->drawText(0,500,QString::number(this->index));
}

void UeRepresentation::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mousePressEvent(event);
}

void UeRepresentation::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);

    this->ueObject.position[index].first = pos().x();
    this->ueObject.position[index].second = -pos().y();

    emit updateUe(this, ueObject);
}

QVariant UeRepresentation::itemChange(GraphicsItemChange change, const QVariant &value) {
    return QGraphicsItem::itemChange(change, value);
}

void UeRepresentation::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  color = QColor(0, 255, 255, 205);
  QGraphicsItem::hoverEnterEvent(event);
}

void UeRepresentation::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit spawnWindow_UeParams(this, ueObject.pairName);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void UeRepresentation::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
   color = QColor(255, 120, 170, 255);
   QGraphicsItem::hoverLeaveEvent(event);
}


