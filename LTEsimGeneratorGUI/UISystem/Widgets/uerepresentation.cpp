#include <QPainter>

#include "uerepresentation.h"

UeRepresentation::UeRepresentation(UEData &ueObject, int index, QColor color) :
    ueObject(ueObject), color(color), index(index)
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

    if(this->ueObject.position[index].first != pos().x() || this->ueObject.position[index].second != -pos().y()) {

        this->ueObject.position[index].first = pos().x();
        this->ueObject.position[index].second = -pos().y();

        bool anyCollision = false;
        for(auto collision : this->collidingItems()) {
            if(collision->type() == UserType+3) {
                if(HandoverRepresentation* hoRepresentation = dynamic_cast<HandoverRepresentation*>(collision)) {
                    anyCollision = true;
                    if(index == 0) {this->ueObject.ueArea.first = hoRepresentation->handoverObject.area;}
                    else {this->ueObject.ueArea.second = hoRepresentation->handoverObject.area;}
                    break;
                }
            }
            else if(collision->type() == UserType+2) {
                if(CellRepresentation* cellRepresentation = dynamic_cast<CellRepresentation*>(collision)) {
                    anyCollision = true;
                    if(index == 0) {this->ueObject.ueArea.first = cellRepresentation->cellInfo.second.area;}
                    else {this->ueObject.ueArea.second = cellRepresentation->cellInfo.second.area;}
                }
            }
        }

        if(!anyCollision) {
            if(index==0) { this->ueObject.ueArea.first = QString(); }
            else { this->ueObject.ueArea.second = QString(); }
        }
    }

    this->relatedUe->ueObject = this->ueObject;
    emit updateUe(this, ueObject);
}

QVariant UeRepresentation::itemChange(GraphicsItemChange change, const QVariant &value) {
    return QGraphicsItem::itemChange(change, value);
}

void UeRepresentation::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    color.setHsv(color.hue(), color.saturation(), color.value()+15);
    QGraphicsItem::hoverEnterEvent(event);
}

void UeRepresentation::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit spawnWindow_UeParams(this, ueObject.pairName);
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void UeRepresentation::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    color.setHsv(color.hue(), color.saturation(), color.value()-15);
    QGraphicsItem::hoverLeaveEvent(event);
}


