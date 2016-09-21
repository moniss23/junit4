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

void PagingRate::loadAndSpawn(const QString &projectName, QStringList generators, QVector<int> rates)
{
    this->ui->listWidget->clear();
    this->rates = rates;
    this->generators=generators;
    this->projectName=projectName;
    for(QString generator:generators) {
        this->ui->listWidget->addItem(generator);
    }
    this->show();
}

void PagingRate::on_OkButton_clicked()
{
    emit updatePagingRate(projectName,this->generators,this->rates);
    this->close();
}
void PagingRate::enablePagingRate(bool value)
{
    this->setEnabled(value);
}

void PagingRate::on_listWidget_currentItemChanged(QListWidgetItem *current)
{
    if (current!=NULL && this->ui->listWidget->currentRow()>-1 && this->ui->listWidget->currentRow()<this->rates.size()) {
        this->ui->spinBox->setValue(rates[this->ui->listWidget->currentRow()]);
    }
}

void PagingRate::on_pushButton_clicked()
{
    if (this->ui->listWidget->currentRow()>-1 && rates.size()>0) {
        this->rates[this->ui->listWidget->currentRow()] = this->ui->spinBox->value();
    }
}
