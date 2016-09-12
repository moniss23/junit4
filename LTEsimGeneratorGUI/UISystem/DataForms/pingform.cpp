#include "pingform.h"
#include "ui_pingform.h"

PingForm::PingForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PingForm)
{
    ui->setupUi(this);
}

PingForm::~PingForm()
{
    delete ui;
}

void PingForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->qciUsed = qciUsed;
    this->ui->comboBox->clear();
    this->ui->comboBox->addItem("");
    for(unsigned i = 0; i < 9; i++) {
        if(!qciUsed[i]) {
            this->ui->comboBox->addItem(QString::number(i+1));
        }
    }
    this->show();
}

void PingForm::on_okButton_clicked()
{
    this->ping.pingQci = this->ui->comboBox->currentText().toInt();
    this->ping.pingInterval = this->ui->interval->text().toInt();
    this->ping.pingMinRecievedPings = this->ui->minRecPings->text().toInt();
    this->ping.pingNumberOfPings = this->ui->numberOfPings->text().toInt();

    emit savePingData(projectName, trafficName, currentCMindex, ping);
}

void PingForm::on_cancelButton_clicked()
{
    this->close();
}

void PingForm::on_restoreButton_clicked()
{

}
