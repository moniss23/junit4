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

    QObject::connect(mapView, SIGNAL(spawnWindow_MapView_CellParams(CellRepresentation*,Cell)),
                     this, SLOT(spawnWindow_MapView_cellParams(CellRepresentation*,Cell)));

    this->ui->mapObjectsWidget->removeTab(0);
    this->ui->mapObjectsWidget->removeTab(1);
    this->ui->mapObjectsWidget->setVisible(false);
    this->show();
}

void NewMapWindow::spawnWindow_MapView_handoverParams(HandoverRepresentation* clickedHo, const Handover &hoObj) {
    this->ui->eastHandoverBoundary->setText(QString::number(hoObj.eastBoundary));
    this->ui->westHandoverBoundary->setText(QString::number(hoObj.westBoundary));
    this->ui->northHandoverBoundary->setText(QString::number(hoObj.northBoundary));
    this->ui->soutHandoverBoundary->setText(QString::number(hoObj.southBoundary));

    this->clickedHandover = clickedHo;
    emit updateHandover(this->clickedHandover->handoverObject, project.name);

    this->ui->mapObjectsWidget->removeTab(0);
    this->ui->mapObjectsWidget->addTab(this->ui->handoverTab, "Handovers");
    this->ui->mapObjectsWidget->setVisible(true);
}

void NewMapWindow::spawnWindow_MapView_cellParams(CellRepresentation *clickedCell, const Cell &cellObj) {
    this->ui->cell->setText(cellObj.name);
    this->ui->site->setText(cellObj.site);
    this->ui->pci->setText(QString::number(cellObj.pci));
    this->ui->position_X->setText(QString::number(cellObj.position_X));
    this->ui->position_Y->setText(QString::number(cellObj.position_Y));
    this->ui->earfcnDl->setText(QString::number(cellObj.earfcnDl));
    this->ui->transmitPower->setText(QString::number(cellObj.transmitPower));
    this->ui->ulNoiseAndInterference->setText(QString::number(cellObj.ulNoiseAndInterference));

    this->clickedCell = clickedCell;
    emit updateCell(this->clickedCell->cellObject, project.name);

    this->ui->mapObjectsWidget->removeTab(0);
    this->ui->mapObjectsWidget->addTab(this->ui->cellTab, "Cells");
    this->ui->mapObjectsWidget->setVisible(true);
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

    this->ui->handoverTab->close();
    this->ui->mapObjectsWidget->setVisible(false);
}

void NewMapWindow::on_setCellParamsBtn_clicked()
{
    if(this->clickedCell != nullptr) {
        this->clickedCell->cellObject.name = ui->cell->text();
        this->clickedCell->cellObject.site = ui->site->text();
        this->clickedCell->cellObject.pci = ui->pci->text().toInt();
        this->clickedCell->cellObject.position_X = ui->position_X->text().toInt();
        this->clickedCell->cellObject.position_Y = ui->position_Y->text().toInt();
        this->clickedCell->cellObject.transmitPower = ui->transmitPower->text().toFloat();
        this->clickedCell->cellObject.earfcnDl = ui->earfcnDl->text().toInt();
        this->clickedCell->cellObject.ulNoiseAndInterference = ui->ulNoiseAndInterference->text().toFloat();

        this->clickedCell->updatePositions();
        emit updateCell(this->clickedCell->cellObject, project.name);
    }

    this->ui->cellTab->close();
    this->ui->mapObjectsWidget->setVisible(false);
}
