#ifndef CELLREPRESENTATION_H
#define CELLREPRESENTATION_H

#include <QGraphicsObject>

#include "Data/Objects/cell.h"

class CellRepresentation : public QGraphicsObject
{
public:
    CellRepresentation(Cell &cell, QGraphicsObject *parent = 0);

    int type() const { return UserType; }

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    Cell cellObject;
    static const int circlesize = 8500;
    static const int centersize = 1500;

};

#endif // CELLREPRESENTATION_H
