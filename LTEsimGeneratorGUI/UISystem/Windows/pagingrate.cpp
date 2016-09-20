#include "pagingrate.h"
#include "ui_paging_rate.h"

PagingRate::PagingRate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PagingRate)
{
    ui->setupUi(this);
}

PagingRate::~PagingRate()
{
    delete ui;
}

void PagingRate::loadAndSpawn(const QString &projectName, int &rate)
{
    this->rate = rate;
    this->projectName=projectName;
    this->ui->rateSpinBox->setValue(rate);
    this->show();
}

void PagingRate::on_OkButton_clicked()
{
    this->rate = this->ui->rateSpinBox->value();
    emit updatePagingRate(projectName,this->rate);
    this->close();
}
void PagingRate::enablePagingRate(bool value)
{
    this->setEnabled(value);
}
