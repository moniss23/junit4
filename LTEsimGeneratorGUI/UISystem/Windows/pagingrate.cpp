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

void PagingRate::on_AcceptButton_clicked()
{
    if (this->ui->listWidget->currentRow()>-1 && rates.size()>0) {
        this->rates[this->ui->listWidget->currentRow()] = this->ui->spinBox->value();
    }
}
void PagingRate::on_CancelButton_clicked()
{
    this->close();
}

void PagingRate::restoreDefaults(QStringList names, QVector<int> rates)
{
    this->generators = names;
    this->rates=rates;
    this->ui->listWidget->clear();
    for(QString generator:generators) {
        this->ui->listWidget->addItem(generator);
    }
}

void PagingRate::on_RestoreButton_clicked()
{
    emit restoreDefaults(projectName);
    if (this->ui->listWidget->count()) {
        this->ui->listWidget->setCurrentRow(0);
    }
}

