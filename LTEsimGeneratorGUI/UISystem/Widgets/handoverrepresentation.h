#ifndef HANDOVERREPRESENTATION_H
#define HANDOVERREPRESENTATION_H

#include <QGraphicsScene>
#include <QGraphicsObject>

#include "Data/Objects/handover.h"

class HandoverRepresentation : public QGraphicsObject
{
    Q_OBJECT

public:
    HandoverRepresentation(Handover &handover, QGraphicsObject *parent = 0);
    ~HandoverRepresentation() {}

    void updatePositions();
    int type() const { return UserType; }
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

signals:
    void spawnWindow_HandoverParams(HandoverRepresentation*, const Handover &handoverObj);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

public:
    QImage icon;
    QString name;
    Handover handoverObject;

    int width, height;
    int position_X, position_Y;
};

#endif // HANDOVERREPRESENTATION_H
