#ifndef UEREPRESENTATION_H
#define UEREPRESENTATION_H

#include <QGraphicsObject>


class UeRepresentation : public QGraphicsObject
{
    Q_OBJECT

public:
    UeRepresentation();
    ~UeRepresentation() {}

    int type() const { return UserType; }
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

    QColor color;

public:
    QImage icon;

    const int width = 1250, height = 1250;
    int position_X, position_Y;
};

#endif // UEREPRESENTATION_H
