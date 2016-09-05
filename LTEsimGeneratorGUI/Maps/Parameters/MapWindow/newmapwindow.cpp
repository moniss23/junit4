#include "newmapwindow.h"
#include "ui_newmapwindow.h"

#include "UISystem/Widgets/mapview.h"

NewMapWindow::NewMapWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewMapWindow)
{
    ui->setupUi(this);

    hBoxLayout = nullptr;
    vBoxLayout  = nullptr;
    mapView = nullptr;
    clickedHandover = nullptr;
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

    this->ui->coreNetworkCheckbox->setChecked(project.mmeSettings.simulatedCoreNetwork);
    ui->mmeButton->setEnabled(project.mmeSettings.simulatedCoreNetwork);
    ui->sgwButton->setEnabled(project.mmeSettings.simulatedCoreNetwork);
    this->ui->ueCheckbox->setChecked(project.ueParameters.startUeComponent);
    ui->ubSimButton->setEnabled(project.ueParameters.startUeComponent);
    ui->ipexButton->setEnabled(project.ueParameters.startUeComponent);

    QObject::connect(mapView, SIGNAL(spawnWindow_MapView_HandoverParams(HandoverRepresentation*, Handover)),
                     this, SLOT(spawnWindow_MapView_handoverParams(HandoverRepresentation*, Handover)));

    this->show();
}

void NewMapWindow::spawnWindow_MapView_handoverParams(HandoverRepresentation* clickedHo, const Handover &hoObj) {
    this->ui->eastHandoverBoundary->setText(QString::number(hoObj.eastBoundary));
    this->ui->westHandoverBoundary->setText(QString::number(hoObj.westBoundary));
    this->ui->northHandoverBoundary->setText(QString::number(hoObj.northBoundary));
    this->ui->soutHandoverBoundary->setText(QString::number(hoObj.southBoundary));

    this->clickedHandover = clickedHo;
    emit updateHandover(this->clickedHandover->handoverObject, project.name);
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
    emit updateCoreNetwork(project.name, checked);
}

void NewMapWindow::on_ueCheckbox_toggled(bool checked)
{
    ui->ubSimButton->setEnabled(checked);
    ui->ipexButton->setEnabled(checked);
    emit updateUEsimulated(project.name, checked);
}

void NewMapWindow::on_setHandoverParamsBtn_clicked()
{
    if(this->clickedHandover != nullptr) {
        this->clickedHandover->handoverObject.eastBoundary = ui->eastHandoverBoundary->text().toInt();
        this->clickedHandover->handoverObject.westBoundary = ui->westHandoverBoundary->text().toInt();
        this->clickedHandover->handoverObject.northBoundary = ui->northHandoverBoundary->text().toInt();
        this->clickedHandover->handoverObject.southBoundary = ui->soutHandoverBoundary->text().toInt();

        this->clickedHandover->updatePositions();
        emit updateHandover(this->clickedHandover->handoverObject, project.name);
    }
}
