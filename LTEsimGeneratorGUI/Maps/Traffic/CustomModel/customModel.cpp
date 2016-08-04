#include "customModel.h"
#include "ui_customModel.h"

customModel::customModel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::newCustomModel)
{
    ui->setupUi(this);
}

customModel::~customModel()
{
    delete ui;
}

void customModel::set_custom_name(QString name)
{
    this->name = name;
}
