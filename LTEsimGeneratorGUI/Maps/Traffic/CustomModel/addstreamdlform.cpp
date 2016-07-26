#include "addstreamdlform.h"
#include "ui_addstreamdlform.h"

    QList<QString> StreamDlList;

AddStreamDlForm::AddStreamDlForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddStreamDlForm)
{
    ui->setupUi(this);
    this->setWindowTitle("addStreamDl");
    qciAddStreamDlPointer = ui->qciComboStreamDl;

    QRegExp rx("[0-9]{0,20}");

    ui->tet_duration->setValidator(new QRegExpValidator(rx, this));
    ui->tet_minThroughput->setValidator(new QRegExpValidator(rx, this));
    ui->tet_speed->setValidator(new QRegExpValidator(rx, this));

    ui->qciComboStreamDl->addItem("");
for(int i=1; i<10; i++){

QString index = QString::number(i);
ui->qciComboStreamDl->addItem(index);

}

}

AddStreamDlForm::~AddStreamDlForm()
{
    delete ui;
}


void AddStreamDlForm::on_tet_speed_returnPressed()
{
    addstreamdl->setSpeed(ui->tet_speed->text());
}

void AddStreamDlForm::on_tet_duration_returnPressed()
{
    addstreamdl->setDuration(ui->tet_duration->text());
}

void AddStreamDlForm::on_tet_minThroughput_returnPressed()
{
    addstreamdl->setMinThroughput(ui->tet_minThroughput->text());
}

void AddStreamDlForm::SaveAll()
{
    addstreamdl->setQci(ui->qciComboStreamDl->currentText());
    addstreamdl->setSpeed(ui->tet_speed->text());
    addstreamdl->setDuration(ui->tet_duration->text());
    addstreamdl->setMinThroughput(ui->tet_minThroughput->text());

}

void AddStreamDlForm::on_bt_save_clicked()
{
    addToList();
    SaveAll();
    this->close();
}

void AddStreamDlForm::on_bt_cancel_clicked()
{
    this->close();
}

void AddStreamDlForm::setParameters(Addstreamdl *addstreamdl)
{
    this->addstreamdl = addstreamdl;

    ui->qciComboStreamDl->setCurrentText(addstreamdl->getQci());
    ui->tet_speed->setText(addstreamdl->getSpeed());
    ui->tet_duration->setText(addstreamdl->getDuration());
    ui->tet_minThroughput->setText(addstreamdl->getMinThroughput());
}

void AddStreamDlForm::addToList(){

    StreamDlList.clear();
    StreamDlList.append("AddStreamDl\nQCI:");
    StreamDlList.append(ui->qciComboStreamDl->currentText());
    StreamDlList.append("Speed:");
    StreamDlList.append(ui->tet_speed->text());
    StreamDlList.append("Duration:");
    StreamDlList.append(ui->tet_duration->text());
    StreamDlList.append("MinThroughput:");
    StreamDlList.append(ui->tet_minThroughput->text());

}
