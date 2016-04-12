#include "myscrollareawidget.h"
#include <QPainter>
#include <QtGui>
#include "addbutton.h"

double const myPositionX[2][4] = {{ 7000, 14000, 21000, 28000 }, {10500, 17500, 24500, 31500}};
double const myPositionY[6] = { 7000, 13000, 19000, 25000, 31000, 37000};
double const eastHorizon = 37000;
double const northHorizon = 43000;
double const westHorizon = 0;
double const southHorizon = 0;

//-------MyScrollAreaWidget Constructor (either large or standard size of the map)------
MyScrollAreaWidget::MyScrollAreaWidget( bool large /*= false*/ ) : QWidget()
{
    setAcceptDrops(true);

    createStandardMap();
    if(large)
        addLargePart();

    composition = new CompositionOfAreas;
    for(int i = 0; i < myCellArea.size(); i++)
        composition->addToList(myCellArea[i]);
    for(int i = 0; i < myHandoverArea.size(); i++)
        composition->addToList(myHandoverArea[i]);

    myLabel1.setParent(this);
    myLabel1.setText("Add UE Group:");
    myLabel1.setGeometry(850, 50, 110, 27);

    myLabel2.setParent(this);
    myLabel2.setText("Custom Models:");
    myLabel2.setGeometry(850, 220, 110, 30);

    addButton = new AddButton(this);
    addButton->setGeometry(QRect(960, 50, 80, 27));

    for(int i = 0; i < 10; i++){
        customModelLabels.append(new CustomModelLabel("CM" + QString::number(i+1), this));
        int xOfCM = 850 + (i % 2) * 60;
        int yOfCM = 250 + (i / 2) * 30;
        customModelLabels[i]->setGeometry(xOfCM, yOfCM);
    }

    statisticsButton = new StatisticsButton(this);
    statisticsButton->setGeometry(QRect(850, 450, 110, 50));

    tuningTrafficButton = new TuningTrafficButton(this);
    tuningTrafficButton->setGeometry(QRect(850, 500, 110, 50));

    timeButton = new TimeButton(this);
    timeButton->setGeometry(QRect(850, 550, 110, 50));

    const int eheigth = 930;
    const int ewidth =  eheigth * (eastHorizon - westHorizon) / (northHorizon - southHorizon);
    const int xe0 = 10;
    const int ye0 = 940;
    scl = new Scale<double, int>( xe0, ye0, ewidth, eheigth, westHorizon, southHorizon,
                     (eastHorizon - westHorizon), (northHorizon - southHorizon));
}

//------Allocating the handover and cell visual components------
void MyScrollAreaWidget::createStandardMap()
{
    for(int i = 0; i < 12; i++)
    {
        myCellArea.append(new CellArea(myPositionX[((i / 2) % 2 == 0) ? 0 : 1][(i % 2 == 0) ? 0 : 1],
          myPositionY[i / 2], (QString::number(i / 2 + 1) + QString::number((i % 2 == 0) ? 1 : 2))));
    }
    for(int i = 0; i < 6; i++)
        myHandoverArea.append(new HandoverArea(myCellArea[i * 2], myCellArea[i * 2 + 1]));
    for(int i = 0; i < 3; i++){
        myHandoverArea.append(new HandoverArea(myCellArea[i*4], myCellArea[i*4 + 2]));
        myHandoverArea.append(new HandoverArea(myCellArea[i*4 + 2], myCellArea[i*4 + 1]));
        myHandoverArea.append(new HandoverArea(myCellArea[i*4 + 1], myCellArea[i*4 + 3]));
    }
    const int bias = 2;
    for(int i = 0; i < 2; i++){
        myHandoverArea.append(new HandoverArea(myCellArea[i*4 + bias], myCellArea[i*4 + 2 + bias]));
        myHandoverArea.append(new HandoverArea(myCellArea[i*4 + bias], myCellArea[i*4 + 3 + bias]));
        myHandoverArea.append(new HandoverArea(myCellArea[i*4 + 1 + bias], myCellArea[i*4 + 3 + bias]));
    }
}
//------Appending yet another part of the visual components schould the large map be chossen------
void MyScrollAreaWidget::addLargePart()
{
    for(int i = 0; i < 12; i++)
    {
        myCellArea.append(new CellArea(myPositionX[(((i / 2) % 2 == 0) ? 0 : 1) ][((i % 2 == 0) ? 0 : 1) + 2],
          myPositionY[i / 2], (QString::number(i / 2 + 1) + QString::number(((i % 2 == 0) ? 1 : 2) + 2))));
    }
    //YET HANDOVERS TO BE ADD
}

//------Repainting the map------
void MyScrollAreaWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    drawFacade(&painter);
}

//------Structural Pttern used to hide the complexity of drawing process------
void MyScrollAreaWidget::drawFacade(QPainter *p)
{
    drawCoordinateSystem(p);
    drawGrid(p);
    drawText(p);
    drawCells(p);
    drawHandowers(p);
}

//------That function uses QPainter class method to draw circle------
void MyScrollAreaWidget::drawCell(QPoint center, double Dx, double Dy, QPainter *p)
{
    p->drawArc(center.x() - Dx/2, center.y() - Dy/2, Dx, Dy, 0, 16 * 360);
}

//------Function reponsible for drawing cirles------
void MyScrollAreaWidget::drawCells(QPainter *p)
{
    double Dx = 2 * scl->getDislpayLengthOX(CellArea::getR());
    double Dy = 2 * scl->getDisplayLengthOY(CellArea::getR());
    for(int i = 0; i < myCellArea.size(); i++){
        QPoint point(scl->getDisplayX(myCellArea[i]->getCenter().x()),
                     scl->getDisplayY(myCellArea[i]->getCenter().y()));
        drawCell(point, Dx, Dy, p);
    }
}

//------Schould draw rectangles based on boundary coordinates------
void MyScrollAreaWidget::drawHandowers(QPainter *p)
{
}

//------Function reponsible for legend and descriptions------
void MyScrollAreaWidget::drawText(QPainter *p)
{
    p->drawText(QPoint(scl->getDisplayX(westHorizon) + 10,
                scl->getDisplayY(northHorizon) + 20), "DistanceY [km]");
    p->drawText(QPoint(scl->getDisplayX(eastHorizon) + 10,
                       scl->getDisplayY(southHorizon) - 10), "DistanceX [km]");
    for(int i = 0; i < 8; i++)
        p->drawText(QPoint(scl->getDisplayX(myPositionX[((i / 4) >= 1) ? 0 : 1][i % 4]) - 20,
                    scl->getDisplayY(southHorizon) - 10),
                    QString::number(myPositionX[((i / 4) >= 1) ? 0 : 1][i % 4]));
    for(int i = 0; i < 6; i++)
        p->drawText(QPoint(scl->getDisplayX(westHorizon) + 10, scl->getDisplayY(myPositionY[i]) - 10),
                    QString::number(myPositionY[i]));
}

//------That function uses QPainter class method to draw the grid lines------
void MyScrollAreaWidget::drawGrid(QPainter *p)
{
    myPen.setStyle(Qt::DashDotLine);
    myPen.setColor(Qt::gray);
    p->setPen(myPen);
    for(int i = 0; i < 8; i++)
        p->drawLine(QPoint(scl->getDisplayX(myPositionX[((i / 4) >= 1) ? 0 : 1][i % 4]), scl->getDisplayY(southHorizon)),
                    QPoint(scl->getDisplayX(myPositionX[((i / 4) >= 1) ? 0 : 1][i % 4]), scl->getDisplayY(northHorizon)));
    for(int i = 0; i < 6; i++)
        p->drawLine(QPoint(scl->getDisplayX(westHorizon), scl->getDisplayY(myPositionY[i])),
                    QPoint(scl->getDisplayX(eastHorizon), scl->getDisplayY(myPositionY[i])));
    myPen.setStyle(Qt::SolidLine);
    myPen.setColor(Qt::black);
    p->setPen(myPen);
}

//------That function uses QPainter class method to draw the coordinate system------
void MyScrollAreaWidget::drawCoordinateSystem(QPainter *p)
{
    myPen.setWidth(2);
    p->setPen(myPen);
    p->drawLine(QPoint(scl->getDisplayX(westHorizon), scl->getDisplayY(southHorizon)),
                QPoint(scl->getDisplayX(eastHorizon), scl->getDisplayY(southHorizon)));
    p->drawLine(QPoint(scl->getDisplayX(westHorizon), scl->getDisplayY(southHorizon)),
                QPoint(scl->getDisplayX(westHorizon), scl->getDisplayY(northHorizon)));
    myPen.setWidth(1);
    p->setPen(myPen);
    p->drawLine(QPoint(scl->getDisplayX(eastHorizon), scl->getDisplayY(southHorizon)),
                QPoint(scl->getDisplayX(eastHorizon), scl->getDisplayY(northHorizon)));
    p->drawLine(QPoint(scl->getDisplayX(eastHorizon), scl->getDisplayY(northHorizon)),
                QPoint(scl->getDisplayX(westHorizon), scl->getDisplayY(northHorizon)));
}
