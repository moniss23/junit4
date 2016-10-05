#ifndef CELLREPRESENTATION_H
#define CELLREPRESENTATION_H

#include <QGraphicsObject>

#include "Data/Objects/cell.h"
#include "Data/Objects/center.h"
/**
 * @brief The CellRepresentation class is grapical representation of Cell and Center objects
 */
class CellRepresentation : public QGraphicsObject
{
    Q_OBJECT

public:
    CellRepresentation(QPair<Cell,Center> &cellInfo, bool movable = true, QGraphicsObject *parent = 0);

    enum { Type = UserType + 2 };
    int type() const { return Type; }
    /**
     * @brief updatePositions update position of Cells on the map
     */
    void updatePositions();

signals:
    /**
     * @brief spawnWindow_CellParams signal is sent to show Cell Parameters
     * @param cellObj object with information about certain Cell
     */
    void spawnWindow_CellParams(CellRepresentation*, const QPair<Cell,Center> &cellObj);

public:
    QPair<Cell,Center> cellInfo;                    //<<< Container for Cell information
    static const int circlesize = 8500;             //<<< Default Cell size
    static const int centersize = 1500;             //<<< Default Center size

protected:
    QColor color;                                   //<<< Color of the Cell
    bool movable;                                   //<<< Is the Cell movable

/******************************
* INHERITED EVENTS AND METHODS
*******************************/
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
};

#endif // CELLREPRESENTATION_H
