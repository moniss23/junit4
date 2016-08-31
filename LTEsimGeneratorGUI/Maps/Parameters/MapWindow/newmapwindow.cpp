#include "newmapwindow.h"
#include "ui_newmapwindow.h"
#include <QDebug>

#include "UISystem/Widgets/mapview.h"

NewMapWindow::NewMapWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewMapWindow)
{
    ui->setupUi(this);
}

NewMapWindow::~NewMapWindow()
{
    delete ui;
}

void NewMapWindow::loadAndOpen(const Project &project)
{
    this->project = project;
    mapView = new MapView(project, this);
    QGridLayout* layout = this->findChild<QGridLayout*>("mainGridLayout");
    layout->addWidget(mapView,0,0);
    QTabWidget* tabWidget = this->findChild<QTabWidget*>("mapObjectsWidget");
    layout->addWidget(tabWidget,0,1);
    this->show();
}
