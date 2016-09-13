#include "servicereqform.h"
#include "ui_servicereqform.h"

ServiceReqForm::ServiceReqForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServiceReqForm), qciUsed(nullptr)
{
    ui->setupUi(this);
    this->setPtrToCheckbox();
}

ServiceReqForm::~ServiceReqForm()
{
    delete ui;
}


void ServiceReqForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->qciUsed = qciUsed;
    this->clearUi();
    this->show();
}

void ServiceReqForm::on_okButton_clicked()
{
    ServiceReq serviceReq;
    bool qciChecked = false;
    for(unsigned i = 0; i < 9; i++) {
        if(checkBoxPtr[i]->isChecked()) {
            qciChecked = true;
            serviceReq.ServiceReqQciArray.push_back(i+1);
        }
    }
    if(!qciChecked) return;
    serviceReq.ServiceReqIntervalBetweenUlData = this->ui->IntervalBetweenUlData->text().toInt();
    serviceReq.ServiceReqTimeToWaitForAttach = this->ui->timeToWaitForAttach->text().toInt();

    emit saveServiceReqData(projectName, trafficName, currentCMindex, serviceReq);
    this->close();
}

void ServiceReqForm::on_cancelButton_clicked()
{
    this->close();
}

void ServiceReqForm::clearUi()
{
    for(unsigned i = 0; i < 9; i++) {
        this->checkBoxPtr[i]->setChecked(false);
        this->checkBoxPtr[i]->setEnabled(!qciUsed[i]);
    }
    this->ui->IntervalBetweenUlData->clear();
    this->ui->timeToWaitForAttach->clear();
}

void ServiceReqForm::setPtrToCheckbox()
{
    this->checkBoxPtr[0] = this->ui->qci1;
    this->checkBoxPtr[1] = this->ui->qci2;
    this->checkBoxPtr[2] = this->ui->qci3;
    this->checkBoxPtr[3] = this->ui->qci4;
    this->checkBoxPtr[4] = this->ui->qci5;
    this->checkBoxPtr[5] = this->ui->qci6;
    this->checkBoxPtr[6] = this->ui->qci7;
    this->checkBoxPtr[7] = this->ui->qci8;
    this->checkBoxPtr[8] = this->ui->qci9;
}
