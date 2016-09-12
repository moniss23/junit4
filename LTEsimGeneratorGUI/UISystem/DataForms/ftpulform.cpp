#include "ftpulform.h"
#include "ui_ftpulform.h"

FtpUlForm::FtpUlForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FtpUlForm)
{
    ui->setupUi(this);
}

FtpUlForm::~FtpUlForm()
{
    delete ui;
}
