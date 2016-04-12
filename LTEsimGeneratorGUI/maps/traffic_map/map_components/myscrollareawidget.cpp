#include "myscrollareawidget.h"
#include <QPainter>
#include <QtGui>
#include "addbutton.h"

//-------MyScrollAreaWidget Constructor (either large or standard size of the map)------
MyScrollAreaWidget::MyScrollAreaWidget( bool large /*= false*/ ) : QWidget()
{
    setAcceptDrops(true);

    createStandardMap();
    if(large)
        addLargePart();

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
}

//------Allocating the handover and cell visual components------
void MyScrollAreaWidget::createStandardMap()
{
}
//------Appending yet another part of the visual components schould the large map be chossen------
void MyScrollAreaWidget::addLargePart()
{
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

//------Function reponsible for drawing cirles------
void MyScrollAreaWidget::drawCells(QPainter *p)
{
}

//------Schould draw rectangles based on boundary coordinates------
void MyScrollAreaWidget::drawHandowers(QPainter *p)
{
}

//------Function reponsible for legend and descriptions------
void MyScrollAreaWidget::drawText(QPainter *p)
{
}

//------That function uses QPainter class method to draw the grid lines------
void MyScrollAreaWidget::drawGrid(QPainter *p)
{
}

//------That function uses QPainter class method to draw the coordinate system------
void MyScrollAreaWidget::drawCoordinateSystem(QPainter *p)
{
}
