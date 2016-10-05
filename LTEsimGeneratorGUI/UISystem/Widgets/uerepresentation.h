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

signals:
    /**
     * @brief updateUe is a signal sent to update a UE on the view
     * @param ueData is the data of current UE pair
     */
    void updateUe(UeRepresentation*, const UEData &ueData);
    /**
     * @brief spawnWindow_UeParams is a signal sent to show current UE's parameters
     * @param ueRepresentation is current UE
     * @param ueDataName is a name of a single UE from a pair
     */
    void spawnWindow_UeParams(UeRepresentation* ueRepresentation, const QString &ueDataName);

public:
    QColor color;                                //<<< Color for graphical representation
    QImage icon;                                 //<<< Graphical representation of a single UE
    UEData ueObject;                             //<<< Data of UE pair

    int index;                                   //<<< Numerical identifier of a UE
    UeRepresentation* relatedUe;                 //<<< Pointer to second UE from the pair

    const int width = 1200, height = 2400;       //<<< Size of a UE
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
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
};

#endif // UEREPRESENTATION_H
