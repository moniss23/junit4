#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "Data/project.h"
#include "UISystem/Widgets/cellrepresentation.h"
#include "UISystem/Widgets/handoverrepresentation.h"

class MapView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MapView(const Project& project, QWidget *parent = 0);

    void printNewMap();
    void resizeEvent(QResizeEvent* event);

public slots:
    void spawnWindow_HandoverParams(HandoverRepresentation*, const Handover&);
    void spawnWindow_CellParams(CellRepresentation*, const QPair<Cell,Center>&);

signals:
    void spawnWindow_MapView_HandoverParams(HandoverRepresentation*, const Handover&);
    void spawnWindow_MapView_CellParams(CellRepresentation*, const QPair<Cell,Center>&);

private:
    void drawAxis();
    void drawMapLines();
    void drawCellRepresentations();
    void drawHandoverRepresentations();

private:
    Project project;

    QGraphicsScene *scene;
    QLineF x_AxisLine, y_AxisLine;
    QPen solidPen, solid2, dotPen;
    QPointF gridLineStart, gridLineEnd, textPoint;

    const int scale = 7000;
};

#endif // MAPVIEW_H
