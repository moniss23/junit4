#include "pingform.h"
#include "ui_pingform.h"

PingForm::PingForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PingForm), qciUsed(nullptr)
{
    ui->setupUi(this);
}

PingForm::~PingForm()
{
    delete ui;
}

void PingForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool* qciUsed,const int &pingIndex, const Ping &ping)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->currentPingIndex = pingIndex;
    this->qciUsed = qciUsed;
    this->ping = ping;
    this->refreshUi();
    this->setWindowFlags( Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
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

    emit savePingData(projectName, trafficName, currentCMindex, ping, currentPingIndex, modification);
    this->close();
}

void PingForm::on_cancelButton_clicked()
{
    this->close();
}

void PingForm::on_restoreButton_clicked() {
    this->refreshUi();
}

void PingForm::refreshUi()
{
    this->ui->comboBox->clear();
    if(ping.pingQci == 0) {
        this->ui->comboBox->addItem("");
        for(unsigned i = 0; i < 9; i++) {
            if(!qciUsed[i]) {
                this->ui->comboBox->addItem(QString::number(i+1));
            }
        }
        this->ui->interval->clear();
        this->ui->minRecPings->clear();
        this->ui->numberOfPings->clear();
        modification = false;
    } else {
        auto index = 0;
        for(auto i = 1; i < 10; i++) {
            if(!qciUsed[i-1]) {
                this->ui->comboBox->addItem(QString::number(i));
            }
            else if(i == ping.pingQci) {
                index = this->ui->comboBox->count();
                this->ui->comboBox->addItem(QString::number(i));
            }
        }
        this->ui->comboBox->setCurrentIndex(index);
        this->ui->interval->setText(QString::number(ping.pingInterval));
        this->ui->minRecPings->setText(QString::number(ping.pingMinRecievedPings));
        this->ui->numberOfPings->setText(QString::number(ping.pingNumberOfPings));
        modification = true;
    }
}
