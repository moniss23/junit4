#include "mapview.h"

#include "UISystem/Widgets/cellrepresentation.h"
#include "UISystem/Widgets/handoverrepresentation.h"

#include <QDebug>

MapView::MapView(const Project& project, QWidget *parent) : QGraphicsView(parent), project(project),
    solidPen(Qt::black, 50, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin),
    solid2(Qt::black, 50, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin),
    dotPen(Qt::black, 25, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setMinimumSize(600,600);
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    this->printNewMap();
    this->show();
}

void MapView::resizeEvent(QResizeEvent *event)
{
    qDebug() << "w resizeEvent scene.width - " << scene->sceneRect().width();
    qDebug() << "w resizeEvent scene.height - " << scene->sceneRect().height();
    this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}

void MapView::printNewMap()
{
    this->drawCellRepresentations();
    this->drawAxis();
    this->drawMapLines();
//    this->drawHandoverRepresentations();

    this->setScene(scene);
}

void MapView::drawAxis()
{
    double mapHeight = scene->sceneRect().height();
    qDebug() << "mapHeight - " << mapHeight;
    double mapWidth = scene->sceneRect().width();
    qDebug() << "mapWidth - " << mapWidth;
    QPointF widgetOffset(30.0, -15.0);
    QPointF Xend(mapWidth, 0.0);
    QPointF Yend(0.0, -mapHeight);

    x_AxisLine.setPoints(QPointF(0.0, 0.0), Xend);
    y_AxisLine.setPoints(QPointF(0.0, 0.0), Yend);
    scene->addLine(x_AxisLine, solidPen);
    scene->addLine(y_AxisLine, solidPen);


    static const double Pi = 3.14159265358979323846264338327950288419717;
    qreal arrowSize = 10;

    // Draw the arrows
    double angle = ::acos(x_AxisLine.dx() / x_AxisLine.length());
    QPointF sourceArrowP1 = x_AxisLine.p2() + QPointF(sin(angle - Pi / 3) * arrowSize,
                                                    cos(angle - Pi / 3) * arrowSize);
    QPointF sourceArrowP2 = x_AxisLine.p2() + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                                    cos(angle - Pi + Pi / 3) * arrowSize);

    angle = ::acos(y_AxisLine.dx() / y_AxisLine.length());
    QPointF destArrowP1 = y_AxisLine.p2() + QPointF(sin(angle - Pi / 3) * arrowSize,
                                                  cos(angle - Pi / 3) * arrowSize);
    QPointF destArrowP2 = y_AxisLine.p2() + QPointF(sin(angle - Pi + Pi / 3) * arrowSize,
                                                  cos(angle - Pi + Pi / 3) * arrowSize);
    scene->addPolygon(QPolygonF() << x_AxisLine.p2() << sourceArrowP1 << sourceArrowP2, solid2, QBrush(Qt::SolidPattern));
    scene->addPolygon(QPolygonF() << y_AxisLine.p2() << destArrowP1 << destArrowP2, solid2, QBrush(Qt::SolidPattern));
}

void MapView::drawMapLines()
{
    int distanceBetweenGridLines;

    //Drawing horizontal lines
    for(int i = 1; i < (maxY / 7000) + 1; i++) {

        QLineF tickMarkLine;
        QLineF gridLine;

        distanceBetweenGridLines = y_AxisLine.length() / (maxY / 7000);

        //Grid line start, end points
        gridLineStart.setX(x_AxisLine.x1());
        gridLineStart.setY(x_AxisLine.y1() - (distanceBetweenGridLines * i));
        gridLineEnd.setX(x_AxisLine.x2());
        gridLineEnd.setY(x_AxisLine.y2() - (distanceBetweenGridLines * i));

        //Tick mark start,end points
        tickMarkStart.setX(x_AxisLine.x1() + 5);
        tickMarkStart.setY(x_AxisLine.y1() - (distanceBetweenGridLines * i));
        tickMarkEnd.setX(x_AxisLine.x1() - 5);
        tickMarkEnd.setY(x_AxisLine.y2() - (distanceBetweenGridLines * i));

        //coordinate system scale point
        textPoint.setX(x_AxisLine.x1() - 60);
        textPoint.setY(x_AxisLine.y2() - (distanceBetweenGridLines * i) - 10);

        QGraphicsTextItem *textItem = scene->addText(QString::number(7000 * (i)));

        //Setting start, end points
        gridLine.setPoints(gridLineStart, gridLineEnd);
        tickMarkLine.setPoints(tickMarkStart, tickMarkEnd);
        textItem->setPos(textPoint);

        //Adding lines to scene
        scene->addLine(gridLine, dotPen);
        scene->addLine(tickMarkLine, solidPen);
    }

    //Drawing vertical lines
    for(int i = 1; i < (maxX / 7000) + 1; i++) {

        QLineF gridLine;
        QLineF tickMarkLine;

        distanceBetweenGridLines = x_AxisLine.length() / (maxX / 7000);

        //Grid line start, end points
        gridLineStart.setX(y_AxisLine.x1() + (distanceBetweenGridLines * i));
        gridLineStart.setY(y_AxisLine.y1());
        gridLineEnd.setX(y_AxisLine.x2() + (distanceBetweenGridLines * i));
        gridLineEnd.setY(y_AxisLine.y2());

        //Tick mark start,end points
        tickMarkStart.setX(y_AxisLine.x1() + (distanceBetweenGridLines * i));
        tickMarkStart.setY(y_AxisLine.y1() + 5);
        tickMarkEnd.setX(y_AxisLine.x2() + (distanceBetweenGridLines * i));
        tickMarkEnd.setY(y_AxisLine.y1() - 5);

        //Coordinate system scale point
        textPoint.setX(y_AxisLine.x2() + (distanceBetweenGridLines * i) - 20);
        textPoint.setY(y_AxisLine.y1() + 15);

        QGraphicsTextItem *textItem = scene->addText(QString::number(7000 * i));

        //Settings start, end points
        textItem->setPos(textPoint);
        gridLine.setPoints(gridLineStart, gridLineEnd);
        tickMarkLine.setPoints(tickMarkStart, tickMarkEnd);

        //Adding lines to scene
        scene->addLine(gridLine, dotPen);
        scene->addLine(tickMarkLine, solidPen);
    }
}

void MapView::drawCellRepresentations()
{
    for(int i = 0; i<project.cellsInfo.size(); i++) {
        CellRepresentation *node1 = new CellRepresentation(project.cellsInfo[i].first);
        scene->addItem(node1);
        node1->setPos(project.cellsInfo[i].first.position_X, - project.cellsInfo[i].first.position_Y);
    }
}

void MapView::drawHandoverRepresentations() {
//    for(int i=0; i<project.handovers.size(); ++i) {
    HandoverRepresentation *ho = new HandoverRepresentation(project.handovers[0]);
    scene->addItem(ho);
    ho->setPos(200, -200);
//    }
}
