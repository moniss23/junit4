#ifndef HANDOVERREPRESENTATION_H
#define HANDOVERREPRESENTATION_H

#include <QGraphicsScene>
#include <QGraphicsObject>

#include "Data/Objects/handover.h"

class HandoverRepresentation : public QGraphicsObject
{
public:
    HandoverRepresentation(Handover &handover, QGraphicsObject *parent = 0);

    int type() const { return UserType; }
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

private:
    QImage icon;
    QString name;
    Handover handoverObject;

    static const int width = 60;
    static const int height = 110;
};

#endif // HANDOVERREPRESENTATION_H
