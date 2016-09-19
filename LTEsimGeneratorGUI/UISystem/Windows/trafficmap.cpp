#include "trafficmap.h"
#include "ui_trafficmap.h"

#include "UISystem/Widgets/mapview.h"
#include "UISystem/Widgets/uerepresentation.h"

TrafficMap::TrafficMap(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrafficMap)
{
    ui->setupUi(this);

    hBoxLayout1     = nullptr;
    hBoxLayout2     = nullptr;
    vBoxLayout      = nullptr;
    mapView         = nullptr;
    clickedUe       = nullptr;
}

TrafficMap::~TrafficMap()
{
    delete ui;
}

void TrafficMap::loadAndOpen(const Project &project, TrafficFileData *trafficFileData) {
    this->refreshWindow(project, trafficFileData);
    this->setWindowTitle(trafficFileData->filename+" - "+project.name+" - LTEsimGenerator");
    this->show();
}

void TrafficMap::refreshWindow(const Project &project, TrafficFileData *trafficFileData) {
    delete vBoxLayout;
    delete hBoxLayout1;
    delete mapView;

    this->project = project;
    this->trafficFileData = trafficFileData;

    mapView     = new MapView(project, this, this->trafficFileData->filename);
    ui->numberOfUeLabel->setText(QString::number(this->trafficFileData->userEquipments.size()));
    hBoxLayout1 = new QHBoxLayout(this);
    hBoxLayout2 = new QHBoxLayout(this);
    vBoxLayout  = new QVBoxLayout(this);

    QObject::connect(mapView, SIGNAL(updateUe_MapView(UeRepresentation*,QString,QString,UEData)),
                     this, SLOT(updateUe_MapView(UeRepresentation*,QString,QString,UEData)));
    QObject::connect(mapView, SIGNAL(spawnWindow_ueParams(UeRepresentation*,QString)),
                     this, SLOT(spawnWindow_UeParams(UeRepresentation*,QString)));

    hBoxLayout1->addWidget(mapView);
    hBoxLayout1->addLayout(vBoxLayout);
    vBoxLayout->addWidget(this->ui->ueGroupWidget, 200, Qt::AlignTop);
    vBoxLayout->addSpacing(this->height() / 10);
    vBoxLayout->addWidget(this->ui->trafficParamsWidget, 400);
    vBoxLayout->addWidget(this->ui->line, 400, Qt::AlignBottom);
    vBoxLayout->addWidget(this->ui->rbsWidget, 400, Qt::AlignBottom);
    this->ui->centralwidget->setLayout(hBoxLayout1);

    ui->removeUeButton->setVisible(false);
}

void TrafficMap::updateUe_MapView(UeRepresentation* ueRep, const QString &projectName, const QString &trafficName, const UEData &ueData) {
    this->clickedUe = ueRep;
    ui->removeUeButton->setVisible(true);
    emit updateUe(projectName, trafficName, ueData);
}

void TrafficMap::spawnWindow_UeParams(UeRepresentation *ueRepresentation, const QString &ueDataName)
{
    this->ueRepresentation = ueRepresentation;
    emit spawnWindow_ueParams(ueDataName, project.name, trafficFileData->filename);
}

void TrafficMap::updateUeDataInUeRepresentation(const UEData &ueData, int x, int y )
{
    this->ueRepresentation->ueObject = ueData;
    this->ueRepresentation->setPos(x, y);
}

void TrafficMap::on_statisticsButton_clicked() {
    spawnWindow_Statistics(project.name, trafficFileData->filename);
}

void TrafficMap::on_pushButton_pressed() {
    emit spawnWindow_CustomModels(project.name, trafficFileData->filename);
}

void TrafficMap::on_tunningTrafficButton_clicked() {
    emit spawnWindow_TuningTraffic(project.name, trafficFileData->filename);
}

void TrafficMap::on_addUeButton_clicked() {
    emit addUe(project.name, trafficFileData->filename);
}

void TrafficMap::on_removeUeButton_clicked() {
    if(ui->removeUeButton->isEnabled() && this->clickedUe != nullptr) {
        this->mapView->scene->removeItem(clickedUe);
        emit removeUe(project.name, trafficFileData->filename, clickedUe->ueObject);

        clickedUe = nullptr;
        ui->removeUeButton->setVisible(false);
    }
}

void TrafficMap::on_ucToolButton_clicked() { emit spawnWindow_UCTool(project.name,true); }
void TrafficMap::on_channelModelsButton_clicked() { emit spawnWindow_ChannelModels(project.name,true); }
void TrafficMap::on_ubSimButton_clicked() { emit spawnWindow_UBsim(project.name,true); }
void TrafficMap::on_ueButton_clicked() { emit spawnWindow_Ue(project.name,true); }
void TrafficMap::on_ipexButton_clicked() { emit spawnWindow_Ipex(project.name,true); }
void TrafficMap::on_sgwButton_clicked() { emit spawnWindow_Sgw(project.name,true); }
void TrafficMap::on_pagingButton_clicked() { emit spawnWindow_Paging(project.name,true); }
void TrafficMap::on_mmeButton_clicked() { emit spawnWindow_Mme(project.name,true); }
void TrafficMap::on_generalSettingsButton_clicked() { emit spawnWindow_GeneralSettings(project.name,true); }

void TrafficMap::on_PagingRateButton_clicked()
{
    emit spawnWindow_PagingRate(project.name);
}

void TrafficMap::on_timeButton_clicked(){ emit spawnWindow_Time(project.name, trafficFileData->filename); }

