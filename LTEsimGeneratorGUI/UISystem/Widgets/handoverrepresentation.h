#ifndef HANDOVERREPRESENTATION_H
#define HANDOVERREPRESENTATION_H

#include <QGraphicsObject>

#include "Data/Objects/handover.h"

class HandoverRepresentation : public QGraphicsObject
{
    Q_OBJECT

public:
    HandoverRepresentation(Handover &handover, QGraphicsObject *parent = 0);
    ~HandoverRepresentation() {}

    enum { Type = UserType + 3 };
    /**
     * @brief updatePositions is used to update Handover positions on the view
     */
    void updatePositions();

signals:
    /**
     * @brief spawnWindow_HandoverParams ia a signal sent to show Handover parameters
     * @param handoverObj is object with data to be shown and changed
     */
    void spawnWindow_HandoverParams(HandoverRepresentation*, const Handover &handoverObj);

public:
    QString name;                                //<<< Name of Handover to be identified by
    QImage icon;                                 //<<< Graphical representation of Handover on the view
    Handover handoverObject;                     //<<< Information about current Handover object

    int width, height;                           //<<< Size of the Handover
    int position_X, position_Y;                  //<<< Position of the Handover

/*****************************************
 * INHERITED METHODS AND EVENTS OVERRIDES
 *****************************************/
public:
    int type() const { return Type; }
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
};

#endif // HANDOVERREPRESENTATION_H
