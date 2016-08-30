#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include <Data/project.h>

class MapView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MapView(QWidget *parent = 0);

    void resizeEvent(QResizeEvent* event);

    void printNewMap();

public slots:

    void loadAndOpen(const Project &project);

private:
    void DrawCellRepresentations();
    void DrawMapLines();
    void DrawAxis();

private:
    QGraphicsScene *scene;
    QLineF x_AxisLine;
    QLineF y_AxisLine;
    QPointF gridLineStart, gridLineEnd, tickMarkStart, tickMarkEnd, textPoint;
    QPen solidPen;
    QPen solid2;
    QPen dotPen;
    int maxX = 26000;
    int maxY = 37000;

    Project project;
};

#endif // MAPVIEW_H
