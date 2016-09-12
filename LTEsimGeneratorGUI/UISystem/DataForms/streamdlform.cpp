#include "streamdlform.h"
#include "ui_streamdlform.h"

StreamDlForm::StreamDlForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StreamDlForm)
{
    ui->setupUi(this);
}

StreamDlForm::~StreamDlForm()
{
    delete ui;
}
