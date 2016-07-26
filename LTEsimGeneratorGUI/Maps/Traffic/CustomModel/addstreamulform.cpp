#include "addstreamulform.h"
#include "ui_addstreamulform.h"

    QList<QString> StreamUlList;

AddStreamUlForm::AddStreamUlForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddStreamUlForm)
{
    ui->setupUi(this);
    this->setWindowTitle("addStreamUl");
    qciAddStreamUlPointer = ui->qciComboStreamUl;

    QRegExp rx("[0-9]{0,20}");

    ui->tet_duration->setValidator(new QRegExpValidator(rx, this));
    ui->tet_minThroughput->setValidator(new QRegExpValidator(rx, this));
    ui->tet_speed->setValidator(new QRegExpValidator(rx, this));

            ui->qciComboStreamUl->addItem("");

    for(int i=1; i<10; i++){

        QString index = QString::number(i);
        ui->qciComboStreamUl->addItem(index);

    }

}

AddStreamUlForm::~AddStreamUlForm()
{
    delete ui;
}

void AddStreamUlForm::on_tet_speed_returnPressed()
{
    addstreamul->setSpeed(ui->tet_speed->text());
}

void AddStreamUlForm::on_tet_duration_returnPressed()
{
    addstreamul->setDuration(ui->tet_duration->text());
}

void AddStreamUlForm::on_tet_minThroughput_returnPressed()
{
    addstreamul->setMinThroughput(ui->tet_minThroughput->text());
}

void AddStreamUlForm::SaveAll()
{
    addstreamul->setQci(ui->qciComboStreamUl->currentText());
    addstreamul->setSpeed(ui->tet_speed->text());
    addstreamul->setDuration(ui->tet_duration->text());
    addstreamul->setMinThroughput(ui->tet_minThroughput->text());
}

void AddStreamUlForm::setParameters(Addstreamul *addstreamul)
{
    this->addstreamul = addstreamul;

    ui->qciComboStreamUl->setCurrentText(addstreamul->getQci());
    ui->tet_speed->setText(addstreamul->getSpeed());
    ui->tet_duration->setText(addstreamul->getDuration());
    ui->tet_minThroughput->setText(addstreamul->getMinThroughput());

}

void AddStreamUlForm::on_bt_save_clicked()
{
    addToList();
    SaveAll();
    this->close();
}

void AddStreamUlForm::on_bt_cancel_clicked()
{
    this->close();
}

void AddStreamUlForm::addToList(){

    StreamUlList.clear();
    StreamUlList.append("AddStreamUl\nQCI:");
    StreamUlList.append(ui->qciComboStreamUl->currentText());
    StreamUlList.append("Speed:");
    StreamUlList.append(ui->tet_speed->text());
    StreamUlList.append("Duration:");
    StreamUlList.append(ui->tet_duration->text());
    StreamUlList.append("MinThroughtput:");
    StreamUlList.append(ui->tet_minThroughput->text());

}
