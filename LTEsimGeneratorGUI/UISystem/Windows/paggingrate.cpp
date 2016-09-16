#include "paggingrate.h"
#include "ui_pagging_rate.h"

PaggingRate::PaggingRate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaggingRate)
{
    ui->setupUi(this);
}

PaggingRate::~PaggingRate()
{
    delete ui;
}

void PaggingRate::loadAndSpawn(const QString &projectName, int &rate)
{
    this->rate = rate;
    this->projectName=projectName;
    this->ui->rateSpinBox->setValue(rate);
    this->show();
}

void PaggingRate::on_OkButton_clicked()
{
    this->rate = this->ui->rateSpinBox->value();
    emit updatePaggingRate(projectName,this->rate);
    this->close();
}
