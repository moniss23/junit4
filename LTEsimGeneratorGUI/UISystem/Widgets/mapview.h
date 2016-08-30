#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>

class MapView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MapView(QWidget *parent = 0);


    void resizeEvent(QResizeEvent* event);

 //   void setXYaxisPosition();
 //   void printNewMap();


signals:

public slots:

private:
    QPointF coordinateStart;
    QPointF coordinateXend;
    QPointF coordinateYend;
    QPointF start, end, start2, end2, endText;
    QLineF line;
    QLineF line2;
//    QPen solid;
//    QPen solid2;
//    QPen dot;
    const int maxX = 37000;
    const int maxY = 28000;
};





#endif // MAPVIEW_H