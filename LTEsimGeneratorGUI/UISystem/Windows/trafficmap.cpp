#include "trafficmap.h"
#include "ui_trafficmap.h"

#include "UISystem/Widgets/mapview.h"

TrafficMap::TrafficMap(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrafficMap)
{
    ui->setupUi(this);

    hBoxLayout1     = nullptr;
    hBoxLayout2     = nullptr;
    vBoxLayout      = nullptr;
    mapView         = nullptr;
}

TrafficMap::~TrafficMap()
{
    delete ui;
}

void TrafficMap::loadAndOpen(const Project &project, const TrafficFileData &trafficFileData) {
    delete vBoxLayout;
    delete hBoxLayout1;
    delete mapView;

    this->project = project;
    this->trafficFileData = trafficFileData;

    mapView     = new MapView(project, this);
    hBoxLayout1 = new QHBoxLayout(this);
    hBoxLayout2 = new QHBoxLayout(this);
    vBoxLayout  = new QVBoxLayout(this);

    hBoxLayout1->addWidget(mapView);
    hBoxLayout1->addLayout(vBoxLayout);
    vBoxLayout->addWidget(this->ui->ueGroupWidget, 200, Qt::AlignTop);
    vBoxLayout->addSpacing(this->height() / 10);
    vBoxLayout->addWidget(this->ui->trafficParamsWidget, 400);
    vBoxLayout->addWidget(this->ui->line, 400, Qt::AlignBottom);
    vBoxLayout->addWidget(this->ui->rbsWidget, 400, Qt::AlignBottom);
    this->ui->centralwidget->setLayout(hBoxLayout1);

    this->ui->coreNetworkCheckbox->setChecked(project.mmeSettings.simulatedCoreNetwork);
    ui->mmeButton->setEnabled(project.mmeSettings.simulatedCoreNetwork);
    ui->sgwButton->setEnabled(project.mmeSettings.simulatedCoreNetwork);
    this->ui->ueCheckbox->setChecked(project.ueParameters.startUeComponent);
    ui->ubSimButton->setEnabled(project.ueParameters.startUeComponent);
    ui->ipexButton->setEnabled(project.ueParameters.startUeComponent);

    this->show();
}


void TrafficMap::on_statisticsButton_clicked()
{
    spawnWindow_Statistics(project.name, trafficFileData.filename);
}

void TrafficMap::on_pushButton_pressed()
{
    emit spawnWindow_CustomModels(project.name, trafficFileData.filename);
}

void TrafficMap::on_tunningTrafficButton_clicked()
{
    emit spawnWindow_TuningTraffic(project.name, trafficFileData.filename);
}
