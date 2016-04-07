#ifndef MYSCROLLAREAWIDGET_H
#define MYSCROLLAREAWIDGET_H

#include <QtWidgets>
#include <QLabel>

class MyScrollAreaWidget : public QWidget
{
    Q_OBJECT
    friend class MyScrollAreaWidget_Test;
public:
    MyScrollAreaWidget( bool large = 0 );

private:
    void createStandardMap();
    void addLargePart();

    void drawFacade(QPainter *p);
    void drawCells(QPainter *p);
    void drawHandowers(QPainter *p);
    void drawCoordinateSystem(QPainter *p);
    void drawGrid(QPainter *p);
    void drawText(QPainter *p);

    void paintEvent(QPaintEvent *event);

    QLabel myLabel1, myLabel2;
};

#endif // MYSCROLLAREAWIDGET_H
