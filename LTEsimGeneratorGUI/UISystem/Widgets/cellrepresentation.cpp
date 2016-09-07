#include "cellrepresentation.h"

#include <QPainter>
#include <QPushButton>
#include <QStyleOption>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>

CellRepresentation::CellRepresentation(QPair<Cell,Center> &cellInfo, QGraphicsObject *parent)
    : QGraphicsObject(parent),
      cellInfo(cellInfo)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void CellRepresentation::updatePositions() {
    int X = cellInfo.first.position_X;
    int Y = cellInfo.first.position_Y;

    this->setPos(X, -Y);
    cellInfo.second.westBoundary = X-100;
    cellInfo.second.eastBoundary = X+100;
    cellInfo.second.southBoundary = Y-100;
    cellInfo.second.northBoundary = Y+100;
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

    emit spawnWindow_CellParams(this, this->cellInfo);
}
