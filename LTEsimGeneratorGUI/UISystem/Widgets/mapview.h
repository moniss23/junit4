#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "Data/project.h"
#include "UISystem/Widgets/uerepresentation.h"
#include "UISystem/Widgets/cellrepresentation.h"
#include "UISystem/Widgets/handoverrepresentation.h"

class MapView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MapView(const Project& project, QWidget *parent = 0, QString trafficName = "");

    void printNewMap();
    void resizeEvent(QResizeEvent* event);

public slots:
    void spawnWindow_MapRange();
    void spawnWindow_HandoverParams(HandoverRepresentation*, const Handover&);
    void spawnWindow_CellParams(CellRepresentation*, const QPair<Cell,Center>&);
    void updateUe(const UEData &ueData);

signals:
    void spawnWindow_mapRange();
    void spawnWindow_MapView_HandoverParams(HandoverRepresentation*, const Handover&);
    void spawnWindow_MapView_CellParams(CellRepresentation*, const QPair<Cell,Center>&);
    void updateUe_MapView(const QString &projectName, const QString &trafficName, const UEData &ueData);

private:
    void drawMapLines();
    void drawAxisAndButtons();
    void drawUeRepresentations();
    void drawCellRepresentations();
    void drawHandoverRepresentations();

public:
    QGraphicsScene *scene;

private:
    Project project;
    QString trafficName;

    QLineF x_AxisLine, y_AxisLine;
    QPen solidPen, solid2, dotPen;
    QPointF gridLineStart, gridLineEnd, textPoint;
};

#endif // MAPVIEW_H
