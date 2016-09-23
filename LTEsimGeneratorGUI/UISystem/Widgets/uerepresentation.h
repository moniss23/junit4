#ifndef UEREPRESENTATION_H
#define UEREPRESENTATION_H

#include <QGraphicsObject>
#include "Data/TrafficSettings/uedata.h"
#include "UISystem/Widgets/cellrepresentation.h"
#include "UISystem/Widgets/handoverrepresentation.h"

class UeRepresentation : public QGraphicsObject
{
    Q_OBJECT

public:
    UeRepresentation(UEData &ueObject, int index, QColor color);
    ~UeRepresentation() {}

    enum { Type = UserType + 1 };

    int type() const { return Type; }
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

signals:
    void updateUe(UeRepresentation*, const UEData &ueData);
    void spawnWindow_UeParams(UeRepresentation* ueRepresentation, const QString &ueDataName);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

public:
    QImage icon;
    QColor color;
    UEData ueObject;

    int index;
    UeRepresentation* relatedUe;

    const int width = 1600, height = 1600;
};

#endif // UEREPRESENTATION_H
