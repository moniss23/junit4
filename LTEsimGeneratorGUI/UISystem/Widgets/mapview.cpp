#include "mapview.h"

#include <QPushButton>

MapView::MapView(const Project& project, QWidget *parent, QString trafficName)
    : QGraphicsView(parent), project(project), trafficName(trafficName),
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
    this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}

void MapView::printNewMap()
{
    this->drawCellRepresentations();
    this->drawHandoverRepresentations();
    if(not trafficName.isEmpty()) this->drawUeRepresentations();

    this->drawAxisAndButtons();
    this->drawMapLines();

    this->setScene(scene);
}

void MapView::drawAxisAndButtons()
{
    double mapWidth = scene->sceneRect().width() - CellRepresentation::circlesize;
    double mapHeight = scene->sceneRect().height() - CellRepresentation::circlesize;

    mapWidth = std::max(mapWidth, (double)CellRepresentation::circlesize);
    mapHeight = std::max(mapHeight, (double)CellRepresentation::circlesize);

    double widthScale = (project.mapRange.eastBoundMap - (project.mapRange.eastBoundMap%project.mapRange.mapScale)) / mapWidth;
    double heightScale = (project.mapRange.northBoundMap - (project.mapRange.northBoundMap%project.mapRange.mapScale)) / mapHeight;

    QPointF Xend(mapWidth * widthScale, 0.0);
    QPointF Yend(0.0, -mapHeight * heightScale);

    x_AxisLine.setPoints(QPointF(0.0, 0.0), Xend);
    y_AxisLine.setPoints(QPointF(0.0, 0.0), Yend);
    scene->addLine(x_AxisLine, solidPen);
    scene->addLine(y_AxisLine, solidPen);

    if(trafficName.isEmpty()) {
        QPushButton *xButton = new QPushButton();
        QPushButton *yButton = new QPushButton();
        xButton->setGeometry(QRect(0, -200, Xend.x(), scene->sceneRect().height() / 100));
        yButton->setGeometry(QRect(-200, Yend.y(), scene->sceneRect().width() / 100, -Yend.y()));
        QBrush tb(Qt::transparent);
        xButton->setPalette(QPalette(tb,tb,tb,tb,tb,tb,tb,tb,tb));
        yButton->setPalette(QPalette(tb,tb,tb,tb,tb,tb,tb,tb,tb));
        xButton->setFlat(true);
        yButton->setFlat(true);
        scene->addWidget(xButton);
        scene->addWidget(yButton);

        QObject::connect(xButton, SIGNAL(pressed()), this, SLOT(spawnWindow_MapRange()));
        QObject::connect(yButton, SIGNAL(pressed()), this, SLOT(spawnWindow_MapRange()));
    }

    static const double Pi = 3.14159265358979323846264338327950288419717;
    qreal arrowSize = 500;

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
    for(int i = 1; i < (project.mapRange.northBoundMap / project.mapRange.mapScale) + 1; i++) {

        QLineF gridLine;
        distanceBetweenGridLines = y_AxisLine.length() / (project.mapRange.northBoundMap / project.mapRange.mapScale);

        //Grid line start, end points
        gridLineStart.setX(x_AxisLine.x1());
        gridLineStart.setY(x_AxisLine.y1() - (distanceBetweenGridLines * i));
        gridLineEnd.setX(x_AxisLine.x2());
        gridLineEnd.setY(x_AxisLine.y2() - (distanceBetweenGridLines * i));

        //coordinate system scale point
        textPoint.setX(x_AxisLine.x1() - scene->sceneRect().height() / 15);
        textPoint.setY(x_AxisLine.y2() - (distanceBetweenGridLines * i) - scene->sceneRect().height() / 100);

        QGraphicsTextItem *textItem = scene->addText(QString::number(project.mapRange.mapScale * (i)));
        auto textFont = textItem->font();
        textFont.setPointSize(500);
        textItem->setFont(textFont);

        //Setting start, end points
        gridLine.setPoints(gridLineStart, gridLineEnd);
        textItem->setPos(textPoint);

        //Adding lines to scene
        scene->addLine(gridLine, dotPen);
    }

    //Drawing vertical lines
    for(int i = 1; i < (project.mapRange.eastBoundMap / project.mapRange.mapScale) + 1; i++) {

        QLineF gridLine;
        distanceBetweenGridLines = x_AxisLine.length() / (project.mapRange.eastBoundMap / project.mapRange.mapScale);

        //Grid line start, end points
        gridLineStart.setX(y_AxisLine.x1() + (distanceBetweenGridLines * i));
        gridLineStart.setY(y_AxisLine.y1());
        gridLineEnd.setX(y_AxisLine.x2() + (distanceBetweenGridLines * i));
        gridLineEnd.setY(y_AxisLine.y2());

        //Coordinate system scale point
        textPoint.setX(y_AxisLine.x2() + (distanceBetweenGridLines * i) - scene->sceneRect().width() / 35);
        textPoint.setY(y_AxisLine.y1());

        QGraphicsTextItem *textItem = scene->addText(QString::number(project.mapRange.mapScale * i));
        auto textFont = textItem->font();
        textFont.setPointSize(500);
        textItem->setFont(textFont);

        //Settings start, end points
        textItem->setPos(textPoint);
        gridLine.setPoints(gridLineStart, gridLineEnd);

        //Adding lines to scene
        scene->addLine(gridLine, dotPen);
    }
}

QColor MapView::generateColorForUe(int ueDataIndex) {
    QColor ueColor;
    int colorHue(0), colorSat(100), colorStep(32);
    colorHue = (colorHue+ueDataIndex*colorStep) % 255;
    colorSat = (colorSat + (ueDataIndex / 255/colorStep)*2*colorStep) % 255;

    ueColor.setHsv(colorHue, colorSat, 240);
    return ueColor;
}

void MapView::drawUeRepresentations() {
    if(not trafficName.isEmpty()) {
        TrafficFileData *currentTraffic = project.findTrafficFileByName(trafficName);

        for(int i=0; i<currentTraffic->userEquipments.size(); ++i) {
//            emit addUeToScene(currentTraffic->userEquipments[i], i); <-- nie dociera do TrafficMap

            UEData ueData = currentTraffic->userEquipments[i];

            QColor ueColor = generateColorForUe(i);
            UeRepresentation *ueRep = new UeRepresentation(ueData, 0, ueColor);
            UeRepresentation *ueRep2 = new UeRepresentation(ueData, 1, ueColor);

            ueRep->relatedUe = ueRep2;
            ueRep2->relatedUe = ueRep;

            scene->addItem(ueRep);
            scene->addItem(ueRep2);

            ueRep->setPos(ueRep->ueObject.position[0].first, -ueRep->ueObject.position[0].second);
            ueRep2->setPos(ueRep2->ueObject.position[1].first, -ueRep2->ueObject.position[1].second);

            QObject::connect(ueRep, SIGNAL(updateUe(UeRepresentation*,UEData)),
                             this, SLOT(updateUe(UeRepresentation*,UEData)));
            QObject::connect(ueRep, SIGNAL(spawnWindow_UeParams(UeRepresentation*,QString)),
                             this, SLOT(spawnWindow_UeParams(UeRepresentation*,QString)));
            QObject::connect(ueRep2, SIGNAL(updateUe(UeRepresentation*,UEData)),
                             this, SLOT(updateUe(UeRepresentation*,UEData)));
            QObject::connect(ueRep2, SIGNAL(spawnWindow_UeParams(UeRepresentation*,QString)),
                             this, SLOT(spawnWindow_UeParams(UeRepresentation*,QString)));
        }
    }
}

void MapView::drawCellRepresentations()
{
    for(auto &cellCenter : project.cellsInfo) {
        CellRepresentation *cellRep;
        if(!trafficName.isEmpty()){
            cellRep = new CellRepresentation(cellCenter, false);
        }else {
            cellRep = new CellRepresentation(cellCenter);
        }

        scene->addItem(cellRep);
        cellRep->updatePositions();
        QObject::connect(cellRep, SIGNAL(spawnWindow_CellParams(CellRepresentation*,QPair<Cell,Center>)),
                         this, SLOT(spawnWindow_CellParams(CellRepresentation*,QPair<Cell,Center>)));
    }
}

void MapView::drawHandoverRepresentations()
{
    for(auto &handover : project.handovers) {
        HandoverRepresentation *hoRep = new HandoverRepresentation(handover);
        scene->addItem(hoRep);
        hoRep->updatePositions();
        if(!trafficName.isEmpty()) hoRep->setFlag(QGraphicsItem::ItemIsMovable, false);
        QObject::connect(hoRep, SIGNAL(spawnWindow_HandoverParams(HandoverRepresentation*,Handover)),
                         this, SLOT(spawnWindow_HandoverParams(HandoverRepresentation*,Handover)));
    }
}

void MapView::spawnWindow_HandoverParams(HandoverRepresentation *hoRep, const Handover &hoObj) {
    emit spawnWindow_MapView_HandoverParams(hoRep, hoObj);
}

void MapView::spawnWindow_CellParams(CellRepresentation *cellRep, const QPair<Cell,Center> &cellObj) {
    emit spawnWindow_MapView_CellParams(cellRep, cellObj);
}

void MapView::spawnWindow_MapRange() {
    emit spawnWindow_mapRange();
}

void MapView::updateUe(UeRepresentation* ueRep, const UEData &ueData) {
    emit updateUe_MapView(ueRep, project.name, trafficName, ueData);
}

void MapView::spawnWindow_UeParams(UeRepresentation *ueRepresentation, const QString &ueDataName)
{
    emit spawnWindow_ueParams(ueRepresentation, ueDataName);
}
