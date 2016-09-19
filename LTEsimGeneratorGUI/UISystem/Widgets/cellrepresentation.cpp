#include "cellrepresentation.h"

#include <QPainter>
#include <QPushButton>
#include <QStyleOption>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>

CellRepresentation::CellRepresentation(QPair<Cell,Center> &cellInfo, bool movable, QGraphicsObject *parent)
    : QGraphicsObject(parent),
      cellInfo(cellInfo),
      movable(movable)
{
    if(movable) {
      setFlag(ItemIsMovable);
      setAcceptHoverEvents(true);
    }

    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

    color = QColor(Qt::darkYellow);
}

void CellRepresentation::updatePositions() {
    setPos(cellInfo.first.position_X, -cellInfo.first.position_Y);
    update(boundingRect());
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
    (void) option;


    QColor yellow   = QColor(255,215,0, 125);
    QColor warmGrey1 = QColor(255,255,255);
    QColor warmGrey = QColor(168,168,105);

    QRadialGradient gradient(0, 0, circlesize);
    if(movable){
        gradient.setColorAt(0, yellow);
        gradient.setColorAt(1, color);
    } else {
        gradient.setColorAt(0, warmGrey1);

        gradient.setColorAt(1, warmGrey);
    }

    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::white, 0));
    painter->drawEllipse( -circlesize/2 , -circlesize/2 , circlesize, circlesize);

    QColor center(245,175,85);
    painter->setBrush(QBrush(center));
    QRectF rectangle(-centersize/2 , -centersize/2 , centersize, centersize);
    painter->drawRoundedRect(rectangle,3,3);

    painter->setPen(QPen(Qt::black, 1));
    auto font = painter->font();
    font.setPointSize(circlesize / 15);
    painter->setFont(font);
    painter->drawText(-centersize,-centersize, this->cellInfo.first.name);
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

    cellInfo.first.position_X = pos().x();
    cellInfo.first.position_Y = -pos().y();

    cellInfo.second.westBoundary = cellInfo.first.position_X-100;
    cellInfo.second.eastBoundary = cellInfo.first.position_X+100;
    cellInfo.second.southBoundary = cellInfo.first.position_Y-100;
    cellInfo.second.northBoundary = cellInfo.first.position_Y+100;

    emit spawnWindow_CellParams(this, this->cellInfo);
}

void CellRepresentation::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  color = QColor(Qt::red);
  QGraphicsItem::hoverEnterEvent(event);
}

void CellRepresentation::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
   color = QColor(Qt::darkYellow);
   QGraphicsItem::hoverLeaveEvent(event);
}
