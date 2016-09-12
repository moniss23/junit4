#include "streamulform.h"
#include "ui_streamulform.h"

StreamUlForm::StreamUlForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StreamUlForm)
{
    ui->setupUi(this);
}

StreamUlForm::~StreamUlForm()
{
    delete ui;
}
