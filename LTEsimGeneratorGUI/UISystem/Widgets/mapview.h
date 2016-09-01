#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "Data/project.h"

class MapView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MapView(const Project& project, QWidget *parent = 0);

    void printNewMap();
    void resizeEvent(QResizeEvent* event);

private:
    void drawAxis();
    void drawMapLines();
    void drawCellRepresentations();
    void drawHandoverRepresentations();

private:
    QGraphicsScene *scene;
    QLineF x_AxisLine;
    QLineF y_AxisLine;
    QPointF gridLineStart, gridLineEnd, tickMarkStart, tickMarkEnd, textPoint;
    QPen solidPen;
    QPen solid2;
    QPen dotPen;
    int maxX = 28000;
    int maxY = 35000;

    Project project;
};

#endif // MAPVIEW_H
