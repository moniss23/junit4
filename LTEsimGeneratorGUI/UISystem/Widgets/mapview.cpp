#include "mapview.h"

MapView::MapView(QWidget *parent) : QGraphicsView(parent)
{

}

void MapView::resizeEvent(QResizeEvent *event)
{


    QGraphicsView::resizeEvent(event);
}

