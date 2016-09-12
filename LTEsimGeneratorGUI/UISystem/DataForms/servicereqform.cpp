#include "servicereqform.h"
#include "ui_servicereqform.h"

ServiceReqForm::ServiceReqForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServiceReqForm)
{
    ui->setupUi(this);
}

ServiceReqForm::~ServiceReqForm()
{
    delete ui;
}
