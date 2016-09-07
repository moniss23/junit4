#include "newmapwindow.h"
#include "ui_newmapwindow.h"

#include <QHBoxLayout>

#include "UISystem/Widgets/mapview.h"


NewMapWindow::NewMapWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewMapWindow)
{
    ui->setupUi(this);

    hBoxLayout      = nullptr;
    vBoxLayout      = nullptr;
    mapView         = nullptr;
    clickedCell     = nullptr;
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

    mapView    = new MapView(project, this);
    hBoxLayout = new QHBoxLayout(this);
    vBoxLayout = new QVBoxLayout(this);

    hBoxLayout->addWidget(mapView);
    hBoxLayout->addLayout(vBoxLayout);
    vBoxLayout->addWidget(this->ui->mapObjectsWidget, 400, Qt::AlignHCenter);
    vBoxLayout->addWidget(this->ui->rbsWidget, 400, Qt::AlignBottom);
    this->ui->centralwidget->setLayout(hBoxLayout);

    this->ui->coreNetworkCheckbox->setChecked(project.mmeSettings.simulatedCoreNetwork);
    ui->mmeButton->setEnabled(project.mmeSettings.simulatedCoreNetwork);
    ui->sgwButton->setEnabled(project.mmeSettings.simulatedCoreNetwork);
    this->ui->ueCheckbox->setChecked(project.ueParameters.startUeComponent);
    ui->ubSimButton->setEnabled(project.ueParameters.startUeComponent);
    ui->ipexButton->setEnabled(project.ueParameters.startUeComponent);

    QObject::connect(mapView, SIGNAL(spawnWindow_MapView_HandoverParams(HandoverRepresentation*, Handover)),
                     this, SLOT(spawnWindow_MapView_handoverParams(HandoverRepresentation*, Handover)));

    QObject::connect(mapView, SIGNAL(spawnWindow_MapView_CellParams(CellRepresentation*,QPair<Cell,Center>)),
                     this, SLOT(spawnWindow_MapView_cellParams(CellRepresentation*,QPair<Cell,Center>)));
    QObject::connect(mapView, SIGNAL(spawnWindow_mapRange()), this, SLOT(spawnWindow_MapRange()));

    for(int i=this->ui->mapObjectsWidget->count()-1; i>=0; --i) {
        this->ui->mapObjectsWidget->removeTab(i);
    }

    this->ui->mapObjectsWidget->setVisible(false);
    this->show();
}

void NewMapWindow::spawnWindow_MapView_handoverParams(HandoverRepresentation* clickedHo, const Handover &hoObj) {
    this->ui->eastHandoverBoundary->setText(QString::number(hoObj.eastBoundary));
    this->ui->westHandoverBoundary->setText(QString::number(hoObj.westBoundary));
    this->ui->northHandoverBoundary->setText(QString::number(hoObj.northBoundary));
    this->ui->southHandoverBoundary->setText(QString::number(hoObj.southBoundary));

    this->clickedHandover = clickedHo;
    emit updateHandover(this->clickedHandover->handoverObject, project.name);

    for(int i=this->ui->mapObjectsWidget->count()-1; i>=0; --i) {
        this->ui->mapObjectsWidget->removeTab(i);
    }
    this->ui->mapObjectsWidget->addTab(this->ui->handoverTab, "Handover");
    this->ui->mapObjectsWidget->setVisible(true);
}

void NewMapWindow::spawnWindow_MapView_cellParams(CellRepresentation *clickedCell, const QPair<Cell,Center> &cellObj) {

    this->clickedCell = clickedCell;
    this->clickedCell->updatePositions();

    this->ui->cell->setText(cellObj.first.name);
    this->ui->site->setText(cellObj.first.site);
    this->ui->pci->setText(QString::number(cellObj.first.pci));
    this->ui->position_X->setText(QString::number(cellObj.first.position_X));
    this->ui->position_Y->setText(QString::number(cellObj.first.position_Y));
    this->ui->earfcnDl->setText(QString::number(cellObj.first.earfcnDl));
    this->ui->transmitPower->setText(QString::number(cellObj.first.transmitPower));
    this->ui->ulNoiseAndInterference->setText(QString::number(cellObj.first.ulNoiseAndInterference));

    this->ui->westCenterBoundary->setText(QString::number(cellObj.second.westBoundary));
    this->ui->eastCenterBoundary->setText(QString::number(cellObj.second.eastBoundary));
    this->ui->southCenterBoundary->setText(QString::number(cellObj.second.southBoundary));
    this->ui->northCenterBoundary->setText(QString::number(cellObj.second.northBoundary));

    emit updateCell(this->clickedCell->cellInfo, project.name);

    for(int i=this->ui->mapObjectsWidget->count()-1; i>=0; --i) {
        this->ui->mapObjectsWidget->removeTab(i);
    }
    this->ui->mapObjectsWidget->addTab(this->ui->cellTab, "Cell");
    this->ui->mapObjectsWidget->addTab(this->ui->centerTab, "Center");
    this->ui->mapObjectsWidget->setVisible(true);
}

void NewMapWindow::on_setHandoverParamsBtn_clicked()
{
    if(this->clickedHandover != nullptr) {
        this->clickedHandover->handoverObject.eastBoundary = ui->eastHandoverBoundary->text().toInt();
        this->clickedHandover->handoverObject.westBoundary = ui->westHandoverBoundary->text().toInt();
        this->clickedHandover->handoverObject.northBoundary = ui->northHandoverBoundary->text().toInt();
        this->clickedHandover->handoverObject.southBoundary = ui->southHandoverBoundary->text().toInt();

        this->clickedHandover->updatePositions();
        emit updateHandover(this->clickedHandover->handoverObject, project.name);
    }

    this->ui->handoverTab->close();
    this->ui->mapObjectsWidget->setVisible(false);
}

void NewMapWindow::on_setCellParamsBtn_clicked()
{
    if(this->clickedCell != nullptr) {
        this->clickedCell->cellInfo.first.name = ui->cell->text();
        this->clickedCell->cellInfo.first.site = ui->site->text();
        this->clickedCell->cellInfo.first.pci = ui->pci->text().toInt();
        this->clickedCell->cellInfo.first.position_X = ui->position_X->text().toInt();
        this->clickedCell->cellInfo.first.position_Y = ui->position_Y->text().toInt();
        this->clickedCell->cellInfo.first.transmitPower = ui->transmitPower->text().toFloat();
        this->clickedCell->cellInfo.first.earfcnDl = ui->earfcnDl->text().toInt();
        this->clickedCell->cellInfo.first.ulNoiseAndInterference = ui->ulNoiseAndInterference->text().toFloat();

        this->clickedCell->updatePositions();
        emit updateCell(this->clickedCell->cellInfo, project.name);
    }

    this->ui->cellTab->close();
    this->ui->centerTab->close();
    this->ui->mapObjectsWidget->setVisible(false);
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

void NewMapWindow::on_mmeButton_pressed() {emit spawnWindow_Mme(project.name);}
void NewMapWindow::on_sgwButton_pressed() {emit spawnWindow_Sgw(project.name);}
void NewMapWindow::on_ipexButton_pressed() {emit spawnWindow_Ipex(project.name);}
void NewMapWindow::on_ubSimButton_pressed() {emit spawnWindow_UBSim(project.name);}
void NewMapWindow::on_ucToolButton_pressed() {emit spawnWindow_ucTool(project.name);}
void NewMapWindow::on_channelModelsButton_pressed() {emit spawnWindow_ChannelModel(project.name);}

void NewMapWindow::spawnWindow_MapRange() {
    emit spawnWindow_mapRange(project.name);
}
