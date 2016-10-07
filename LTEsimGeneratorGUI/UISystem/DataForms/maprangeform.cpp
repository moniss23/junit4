#include "UISystem/DataForms/maprangeform.h"

MapRangeForm::MapRangeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapRangeForm)
{
    ui->setupUi(this);
    this->ui->lbl_north->setToolTip("Max vertical map range");
    this->ui->lbl_south->setToolTip("Min vertical map range");
    this->ui->lbl_east->setToolTip("Max horizontal map range");
    this->ui->lbl_west->setToolTip("Min horizontal map range");
    this->ui->mapScaleLabel->setToolTip("Map scale");
}

MapRangeForm::~MapRangeForm()
{
    delete ui;
}

void MapRangeForm::updateUi()
{
    this->ui->tet_northBoundMap->setValue(mapRange.northBoundMap);
    this->ui->tet_southBoundMap->setValue(mapRange.southBoundMap);
    this->ui->tet_eastBoundMap->setValue(mapRange.eastBoundMap);
    this->ui->tet_westBoundMap->setValue(mapRange.westBoundMap);
    this->ui->scaleSpinBox->setValue(mapRange.mapScale);
}
void MapRangeForm::setMapRangeChanges()
{
    this->mapRange.northBoundMap = this->ui->tet_northBoundMap->value();
    this->mapRange.southBoundMap = this->ui->tet_southBoundMap->value();
    this->mapRange.westBoundMap = this->ui->tet_westBoundMap->value();
    this->mapRange.eastBoundMap = this->ui->tet_eastBoundMap->value();
    this->mapRange.mapScale = this->ui->scaleSpinBox->value();
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
    this->updateUi();
    this->setWindowFlags( Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
    this->show();
}

void MapRangeForm::on_RestoreDefaultsButton_clicked()
{
    this->updateUi();
}
