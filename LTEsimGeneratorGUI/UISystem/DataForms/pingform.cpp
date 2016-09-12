#include "pingform.h"
#include "ui_pingform.h"

PingForm::PingForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PingForm), qciUsed(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Ping");
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
    this->clearUi();
    this->show();
}

void PingForm::on_okButton_clicked()
{
    Ping ping;
    if(this->ui->comboBox->currentText() == "") return;
    ping.pingQci = this->ui->comboBox->currentText().toInt();
    ping.pingInterval = this->ui->interval->text().toInt();
    ping.pingMinRecievedPings = this->ui->minRecPings->text().toInt();
    ping.pingNumberOfPings = this->ui->numberOfPings->text().toInt();

    emit savePingData(projectName, trafficName, currentCMindex, ping);
    this->close();
}

void PingForm::on_cancelButton_clicked()
{
    this->close();
}

void PingForm::on_restoreButton_clicked() {
}

void PingForm::clearUi()
{
    this->ui->comboBox->clear();
    this->ui->comboBox->addItem("");
    for(unsigned i = 0; i < 9; i++) {
        if(!qciUsed[i]) {
            this->ui->comboBox->addItem(QString::number(i+1));
        }
    }
    this->ui->interval->clear();
    this->ui->minRecPings->clear();
    this->ui->numberOfPings->clear();
}
