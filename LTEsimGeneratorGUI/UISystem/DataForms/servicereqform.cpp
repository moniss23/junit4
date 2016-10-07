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


void ServiceReqForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed, const int &serviceReqIndex, const ServiceReq &serviceReq)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->currentServiceReqIndex = serviceReqIndex;
    this->serviceReq = serviceReq;
    this->qciUsed = qciUsed;
    this->refreshUi();
        this->setWindowFlags( Qt::Dialog | Qt::WindowStaysOnTopHint);
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

    emit saveServiceReqData(projectName, trafficName, currentCMindex, serviceReq, currentServiceReqIndex, modification);
    this->close();
}

void ServiceReqForm::on_cancelButton_clicked()
{
    this->close();
}

void ServiceReqForm::refreshUi()
{
    for(unsigned i = 0; i < 9; i++) {
        this->checkBoxPtr[i]->setChecked(false);
        this->checkBoxPtr[i]->setEnabled(!qciUsed[i]);
    }
    if(serviceReq.ServiceReqQciArray.size() == 0) {
        this->ui->IntervalBetweenUlData->clear();
        this->ui->timeToWaitForAttach->clear();
        this->modification = false;
    } else {
        for(auto &qci : serviceReq.ServiceReqQciArray) {
            this->checkBoxPtr[qci-1]->setChecked(true);
            this->checkBoxPtr[qci-1]->setEnabled(true);
        }
        this->ui->IntervalBetweenUlData->setText(QString::number(serviceReq.ServiceReqIntervalBetweenUlData));
        this->ui->timeToWaitForAttach->setText(QString::number(serviceReq.ServiceReqTimeToWaitForAttach));
        this->modification = true;
    }
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

void ServiceReqForm::on_restoreButton_clicked()
{
    this->refreshUi();
}
