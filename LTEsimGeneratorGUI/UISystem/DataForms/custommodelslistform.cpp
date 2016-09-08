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

void CustomModelsListForm::on_CM1Button_clicked()
{
    emit loadData(projectName, trafficName, 0);
}

void CustomModelsListForm::on_CM2Button_clicked()
{
    emit loadData(projectName, trafficName, 1);
}

void CustomModelsListForm::on_CM3Button_clicked()
{
    emit loadData(projectName, trafficName, 2);
}

void CustomModelsListForm::on_CM4Button_clicked()
{
    emit loadData(projectName, trafficName, 3);
}

void CustomModelsListForm::on_CM5Button_clicked()
{
    emit loadData(projectName, trafficName, 4);
}

void CustomModelsListForm::on_CM6Button_clicked()
{
    emit loadData(projectName, trafficName, 5);
}

void CustomModelsListForm::on_CM7Button_clicked()
{
    emit loadData(projectName, trafficName, 6);
}

void CustomModelsListForm::on_CM8Button_clicked()
{
    emit loadData(projectName, trafficName, 7);
}

void CustomModelsListForm::on_CM9Button_clicked()
{
    emit loadData(projectName, trafficName, 8);
}

void CustomModelsListForm::on_CM10Button_clicked()
{
    emit loadData(projectName, trafficName, 9);
}
