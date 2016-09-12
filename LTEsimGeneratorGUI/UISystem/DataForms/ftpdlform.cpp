#include "ftpdlform.h"
#include "ui_ftpdlform.h"

FtpDlForm::FtpDlForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FtpDlForm)
{
    ui->setupUi(this);
}

FtpDlForm::~FtpDlForm()
{
    delete ui;
}
