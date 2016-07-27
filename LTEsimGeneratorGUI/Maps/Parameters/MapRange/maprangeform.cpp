#include "maprangeform.h"
#include "ui_maprangeform.h"
#include <Maps/Parameters/MapWindow/mapwindow.h>
extern MapWindow *map_w;
MapRangeForm::MapRangeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapRangeForm)
{
    ui->setupUi(this);
    flagConfirmNewValue = true;
}

MapRangeForm::~MapRangeForm()
{
    delete ui;
}

void MapRangeForm::setParameters(MapRange *mapRange, bool destination)
{
    ui->lbl_east->setHidden(destination);
    ui->lbl_west->setHidden(destination);
    ui->tet_eastBoundMap->setHidden(destination);
    ui->tet_westBoundMap->setHidden(destination);
    ui->lbl_north->setHidden(!destination);
    ui->lbl_south->setHidden(!destination);
    ui->tet_southBoundMap->setHidden(!destination);
    ui->tet_northBoundMap->setHidden(!destination);

    this->mapRange=mapRange;
    ui->tet_eastBoundMap->setValue(mapRange->getEastBoundMap());
    ui->tet_northBoundMap->setValue(mapRange->getNorthBoundMap());
    ui->tet_southBoundMap->setValue(mapRange->getSouthBoundMap());
    ui->tet_westBoundMap->setValue(mapRange->getWestBoundMap());
}

void MapRangeForm::on_buttonBox_accepted()
{
    mapRange->setEastBoundMap(ui->tet_eastBoundMap->value());
    mapRange->setNorthBoundMap(ui->tet_northBoundMap->value());
    mapRange->setSouthBoundMap(ui->tet_southBoundMap->value());
    mapRange->setWestBoundMap(ui->tet_westBoundMap->value());
    map_w->changeMapRange_x_northBoundMap();
    map_w->changeMapRange_y_northBoundMap();
    this->close();
}

void MapRangeForm::on_buttonBox_rejected()
{
    this->close();
}

void MapRangeForm::on_tet_northBoundMap_valueChanged(double arg1)
{
    mapRange->setNorthBoundMap(arg1);
    map_w->changeMapRange_x_northBoundMap();
}

void MapRangeForm::on_tet_eastBoundMap_valueChanged(double arg1)
{
    mapRange->setEastBoundMap(arg1);
    map_w->changeMapRange_y_northBoundMap();
}


void MapRangeForm::on_tet_southBoundMap_valueChanged(double arg1)
{
    mapRange->setSouthBoundMap(arg1);
}

void MapRangeForm::on_tet_westBoundMap_valueChanged(double arg1)
{
   mapRange->setWestBoundMap(arg1);
}