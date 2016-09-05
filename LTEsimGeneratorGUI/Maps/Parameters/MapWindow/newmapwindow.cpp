#include "newmapwindow.h"
#include "ui_newmapwindow.h"

#include "UISystem/Widgets/mapview.h"

NewMapWindow::NewMapWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewMapWindow)
{
    ui->setupUi(this);


    hBoxLayout = NULL;
    vBoxLayout  = NULL;
    mapView = NULL;
}

NewMapWindow::~NewMapWindow()
{
    delete ui;
}

void NewMapWindow::loadAndOpen(const Project &project)
{
   delete vBoxLayout;
   delete hBoxLayout;
   delete mapView;


    this->project = project;
    mapView = new MapView(project, this);
    hBoxLayout = new QHBoxLayout(this);
    this->ui->centralwidget->setLayout(hBoxLayout);
    hBoxLayout->addWidget(mapView);
    vBoxLayout = new QVBoxLayout(this);
    hBoxLayout->addLayout(vBoxLayout);
    vBoxLayout->addWidget(this->ui->mapObjectsWidget, 400);
    vBoxLayout->addWidget(this->ui->rbsWidget, 400);

    this->ui->ueCheckbox->setChecked(~project.SimulatedUe);
    this->ui->ueCheckbox->setChecked(project.SimulatedUe);
    this->ui->coreNetworkCheckbox->setChecked(~project.SimulatedCoreNetwork);
    this->ui->coreNetworkCheckbox->setChecked(project.SimulatedCoreNetwork);

    QObject::connect(mapView, SIGNAL(spawnWindow_MapView_HandoverParams(Handover)),
                     this, SLOT(spawnWindow_MapView_handoverParams(Handover)));

    this->show();
}

void NewMapWindow::spawnWindow_MapView_handoverParams(const Handover &handoverObj) {
    this->ui->eastHandoverBoundary->setText(QString::number(handoverObj.eastBoundary));
    this->ui->westHandoverBoundary->setText(QString::number(handoverObj.westBoundary));
    this->ui->northHandoverBoundary->setText(QString::number(handoverObj.northBoundary));
    this->ui->soutHandoverBoundary->setText(QString::number(handoverObj.southBoundary));
}

void NewMapWindow::on_channelModelsButton_pressed()
{
    emit spawnWindow_ChannelModel(project.name);
}

void NewMapWindow::on_ucToolButton_pressed()
{
    emit spawnWindow_ucTool(project.name);
}

void NewMapWindow::on_ipexButton_pressed()
{
    emit spawnWindow_Ipex(project.name);
}

void NewMapWindow::on_ubSimButton_pressed()
{
    emit spawnWindow_UBSim(project.name);
}

void NewMapWindow::on_sgwButton_pressed()
{
    emit spawnWindow_Sgw(project.name);
}

void NewMapWindow::on_mmeButton_pressed()
{
    emit spawnWindow_Mme(project.name);
}

void NewMapWindow::on_coreNetworkCheckbox_toggled(bool checked)
{
    ui->mmeButton->setEnabled(checked);
    ui->sgwButton->setEnabled(checked);
}

void NewMapWindow::on_ueCheckbox_toggled(bool checked)
{
    ui->ubSimButton->setEnabled(checked);
    ui->ipexButton->setEnabled(checked);
}
