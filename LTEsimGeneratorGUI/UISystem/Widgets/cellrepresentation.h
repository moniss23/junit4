#ifndef CELLREPRESENTATION_H
#define CELLREPRESENTATION_H
#include <QGraphicsObject>


class CellRepresentation : public QGraphicsObject
{
public:
    CellRepresentation(QGraphicsObject *parent = 0);

    int type() const { return UserType; }

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    static const int circlesize = 210;
    static const int centersize = 30;
    QString name;

};

#endif // CELLREPRESENTATION_H
