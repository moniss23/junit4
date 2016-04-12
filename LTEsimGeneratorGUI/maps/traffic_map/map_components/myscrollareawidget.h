#ifndef MYSCROLLAREAWIDGET_H
#define MYSCROLLAREAWIDGET_H

#include <QtWidgets>
#include <QLabel>
#include "draguelabel.h"
#include "custommodellabel.h"
#include "statisticsbutton.h"
#include "tuningtrafficbutton.h"
#include "timebutton.h"
#include "cellarea.h"
#include "handoverarea.h"
#include "compositionofareas.h"
#include "scale.h"

class AddButton;

class MyScrollAreaWidget : public QWidget
{
    Q_OBJECT
    friend class AddButton;
    friend class MyScrollAreaWidget_Test;
public:
    MyScrollAreaWidget( bool large = 0 );

private:
    void createStandardMap();
    void addLargePart();
    MyObjectArea* whichObjectArea(int xParam, int yParam);

    void drawFacade(QPainter *p);
    void drawCells(QPainter *p);
    void drawCell(QPoint center, double Dx, double Dy, QPainter *p);
    void drawHandowers(QPainter *p);
    void drawCoordinateSystem(QPainter *p);
    void drawGrid(QPainter *p);
    void drawText(QPainter *p);

    void paintEvent(QPaintEvent *event);

    CompositionOfAreas *composition;
    QList<MyObjectArea *> myHandoverArea;
    QList<CellArea *> myCellArea;

    Scale<double, int> *scl;
    QPen myPen;
    QPoint startPos;
    QLabel myLabel1, myLabel2;
    QList<CustomModelLabel*> customModelLabels;
    StatisticsButton *statisticsButton;
    TuningTrafficButton *tuningTrafficButton;
    TimeButton *timeButton;
    QList<DragUELabel*> ueGroupLabel;
    AddButton *addButton;
};

#endif // MYSCROLLAREAWIDGET_H
