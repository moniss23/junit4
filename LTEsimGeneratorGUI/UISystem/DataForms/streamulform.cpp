#include "streamulform.h"
#include "ui_streamulform.h"

StreamUlForm::StreamUlForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StreamUlForm), qciUsed(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Stream Ul");
}

StreamUlForm::~StreamUlForm()
{
    delete ui;
}

void StreamUlForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->qciUsed = qciUsed;
    this->clearUi();
    this->show();
}

void StreamUlForm::clearUi() {
    this->ui->qciComboBox->clear();
    this->ui->qciComboBox->addItem("");
    for(unsigned i = 0; i < 9; i++) {
        if(!qciUsed[i]) {
            this->ui->qciComboBox->addItem(QString::number(i+1));
        }
    }
    this->ui->speed->clear();
    this->ui->duration->clear();
    this->ui->minThroughPut->clear();
}

void StreamUlForm::on_okButton_clicked()
{
    if(this->ui->qciComboBox->currentText() == "") return;
    this->streamUl.streamUlQci = this->ui->qciComboBox->currentText().toInt();
    this->streamUl.streamUlSpeed = this->ui->speed->text().toInt();
    this->streamUl.streamUlDuration = this->ui->duration->text().toInt();
    this->streamUl.streamUlMinThroughput = this->ui->minThroughPut->text().toInt();

    emit saveStreamUlData(projectName, trafficName, currentCMindex, streamUl);
    this->close();
}

void StreamUlForm::on_cancelButton_clicked()
{
    this->close();
}
