#include "UISystem/DataForms/maprangeform.h"
#include "Maps/Parameters/MapWindow/mapwindow.h"

MapRangeForm::MapRangeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapRangeForm)
{
    ui->setupUi(this);
    this->setWindowTitle("MapRange settings");
    this->ui->lbl_north->setToolTip("Max vertical map range");
    this->ui->lbl_south->setToolTip("Min vertical map range");
    this->ui->lbl_east->setToolTip("Max horizontal map range");
    this->ui->lbl_west->setToolTip("Min horizontal map range");
}

MapRangeForm::~MapRangeForm()
{
    delete ui;
}

void MapRangeForm::setDefaultParameters()
{
    this->ui->tet_northBoundMap->setValue(mapRange.northBoundMap);
    this->ui->tet_southBoundMap->setValue(mapRange.southBoundMap);
    this->ui->tet_eastBoundMap->setValue(mapRange.eastBoundMap);
    this->ui->tet_westBoundMap->setValue(mapRange.westBoundMap);
}
void MapRangeForm::setMapRangeChanges()
{
    this->mapRange.northBoundMap = this->ui->tet_northBoundMap->value();
    this->mapRange.southBoundMap = this->ui->tet_southBoundMap->value();
    this->mapRange.westBoundMap = this->ui->tet_westBoundMap->value();
    this->mapRange.eastBoundMap = this->ui->tet_eastBoundMap->value();
}

void MapRangeForm::on_buttonBox_accepted()
{
    setMapRangeChanges();
    emit updateMapRange(mapRange,projectName);
    this->close();
}
void MapRangeForm::on_buttonBox_rejected()
{
    this->close();
}

void MapRangeForm::loadAndSpawn(const MapRange &mapRange, const QString &projectName)
{
    this->mapRange = mapRange;
    this->projectName = projectName;
    this->setDefaultParameters();
    this->show();

}
