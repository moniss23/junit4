#ifndef CELLREPRESENTATION_H
#define CELLREPRESENTATION_H

#include <QGraphicsObject>

#include "Data/Objects/cell.h"
#include "Data/Objects/center.h"

class CellRepresentation : public QGraphicsObject
{
    Q_OBJECT

public:
    CellRepresentation(QPair<Cell,Center> &cellInfo, QGraphicsObject *parent = 0);

    void updatePositions();
    int type() const { return UserType; }
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

signals:
    void spawnWindow_CellParams(CellRepresentation*, const QPair<Cell,Center> &cellObj);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

    QColor color;


public:
    QPair<Cell,Center> cellInfo;
    static const int circlesize = 8500;
    static const int centersize = 1500;
};

#endif // CELLREPRESENTATION_H
