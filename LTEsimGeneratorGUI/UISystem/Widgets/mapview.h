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
    Project project;

    QGraphicsScene *scene;
    QLineF x_AxisLine, y_AxisLine;
    QPen solidPen, solid2, dotPen;
    QPointF gridLineStart, gridLineEnd, textPoint;

    const int scale = 7000;
    int circleSize;

    int maxX = 50000;
    int maxY = 70000;
};

#endif // MAPVIEW_H
