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

void StreamUlForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed, const int &streamUlIndex, const StreamUl &streamUl)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->currentStreamUlIndex = streamUlIndex;
    this->streamUl = streamUl;
    this->qciUsed = qciUsed;
    this->refreshUi();
    this->show();
}

void StreamUlForm::refreshUi()
{
    this->ui->qciComboBox->clear();
    if(streamUl.streamUlQci == 0) {
        this->ui->qciComboBox->addItem("");
        for(unsigned i = 0; i < 9; i++) {
            if(!qciUsed[i]) {
                this->ui->qciComboBox->addItem(QString::number(i+1));
            }
        }
        this->ui->speed->clear();
        this->ui->duration->clear();
        this->ui->minThroughPut->clear();
        this->modification = false;
    } else {
        auto index = 0;
        for(auto i = 1; i < 10; i++) {
            if(!qciUsed[i-1]) {
                this->ui->qciComboBox->addItem(QString::number(i));
            }
            else if(i == streamUl.streamUlQci) {
                index = this->ui->qciComboBox->count();
                this->ui->qciComboBox->addItem(QString::number(i));
            }
        }
        this->ui->qciComboBox->setCurrentIndex(index);
        this->ui->minThroughPut->setText(QString::number(streamUl.streamUlMinThroughput));
        this->ui->speed->setText(QString::number(streamUl.streamUlSpeed));
        this->ui->duration->setText(QString::number(streamUl.streamUlDuration));
        this->modification = true;
    }
}

void StreamUlForm::on_okButton_clicked()
{
    StreamUl streamUl;
    if(this->ui->qciComboBox->currentText() == "") return;
    streamUl.streamUlQci = this->ui->qciComboBox->currentText().toInt();
    streamUl.streamUlSpeed = this->ui->speed->text().toInt();
    streamUl.streamUlDuration = this->ui->duration->text().toInt();
    streamUl.streamUlMinThroughput = this->ui->minThroughPut->text().toInt();

    emit saveStreamUlData(projectName, trafficName, currentCMindex, streamUl, currentStreamUlIndex, modification);
    this->close();
}

void StreamUlForm::on_cancelButton_clicked()
{
    this->close();
}

void StreamUlForm::on_restoreButton_clicked()
{
    this->refreshUi();
}
