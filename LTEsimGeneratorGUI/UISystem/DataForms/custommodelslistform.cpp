#include "custommodelslistform.h"
#include "ui_custommodelslistform.h"

CustomModelsListForm::CustomModelsListForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CustomModelsListForm)
{
    ui->setupUi(this);
}

CustomModelsListForm::~CustomModelsListForm()
{
    delete ui;
}

void CustomModelsListForm::open(const QString &projectName, const QString &trafficName) {
    this->projectName = projectName;
    this->trafficName = trafficName;

    this->show();
}

void CustomModelsListForm::loadData() {

}

void CustomModelsListForm::on_pushButton_clicked()
{

}

void CustomModelsListForm::on_pushButton_2_clicked()
{

}

void CustomModelsListForm::on_pushButton_3_clicked()
{

}

void CustomModelsListForm::on_pushButton_4_clicked()
{

}

void CustomModelsListForm::on_pushButton_5_clicked()
{

}

void CustomModelsListForm::on_pushButton_6_clicked()
{

}

void CustomModelsListForm::on_pushButton_7_clicked()
{

}

void CustomModelsListForm::on_pushButton_8_clicked()
{

}

void CustomModelsListForm::on_pushButton_9_clicked()
{

}

void CustomModelsListForm::on_pushButton_10_clicked()
{

}
