#include "newmapwindow.h"
#include "ui_newmapwindow.h"

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
    hBoxLayout = new QHBoxLayout(this);
    this->ui->centralwidget->setLayout(hBoxLayout);
    hBoxLayout->addWidget(mapView);
    vBoxLayout = new QVBoxLayout(this);
    hBoxLayout->addLayout(vBoxLayout);
    vBoxLayout->addWidget(this->ui->mapObjectsWidget, 400);
    vBoxLayout->addWidget(this->ui->rbsWidget, 400);
    this->show();
}
