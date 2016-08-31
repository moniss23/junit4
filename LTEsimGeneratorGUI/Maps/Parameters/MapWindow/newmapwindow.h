#ifndef NEWMAPWINDOW_H
#define NEWMAPWINDOW_H

#include <QMainWindow>
#include "UISystem/Widgets/mapview.h"

namespace Ui {
class NewMapWindow;
}

class NewMapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewMapWindow(QWidget *parent = 0);
    ~NewMapWindow();

public slots:
    void loadAndOpen(const Project &project);

private:
    Ui::NewMapWindow *ui;
    MapView *mapView;
    Project project;
};

#endif // NEWMAPWINDOW_H
