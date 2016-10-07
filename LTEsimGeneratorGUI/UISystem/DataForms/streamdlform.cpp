#include "streamdlform.h"
#include "ui_streamdlform.h"

StreamDlForm::StreamDlForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StreamDlForm), qciUsed(nullptr)
{
    ui->setupUi(this);
}

StreamDlForm::~StreamDlForm()
{
    delete ui;
}

void StreamDlForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed, const int &streamDlIndex, const StreamDl &streamDl)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->currentStreamDlIndex = streamDlIndex;
    this->streamDl = streamDl;
    this->qciUsed = qciUsed;
    this->refreshUi();
        this->setWindowFlags( Qt::Dialog | Qt::WindowStaysOnTopHint);
    this->show();
}

void StreamDlForm::refreshUi()
{
    this->ui->qciComboBox->clear();
    if(streamDl.streamDlQci == 0) {
        this->ui->qciComboBox->addItem("");
        for(unsigned i = 0; i < 9; i++) {
            if(!qciUsed[i]) {
                this->ui->qciComboBox->addItem(QString::number(i+1));
            }
        }
        this->ui->speed->clear();
        this->ui->duration->clear();
        this->ui->minThroughtPut->clear();
        this->modification = false;
    } else {
        auto index = 0;
        for(auto i = 1; i < 10; i++) {
            if(!qciUsed[i-1]) {
                this->ui->qciComboBox->addItem(QString::number(i));
            }
            else if(i == streamDl.streamDlQci) {
                index = this->ui->qciComboBox->count();
                this->ui->qciComboBox->addItem(QString::number(i));
            }
        }
        this->ui->qciComboBox->setCurrentIndex(index);
        this->ui->minThroughtPut->setText(QString::number(streamDl.streamDlMinThroughput));
        this->ui->speed->setText(QString::number(streamDl.streamDlSpeed));
        this->ui->duration->setText(QString::number(streamDl.streamDlDuration));
        this->modification = true;
    }
}

void StreamDlForm::on_okButton_clicked()
{
    StreamDl streamDl;
    if(this->ui->qciComboBox->currentText() == "") return;
    streamDl.streamDlQci = this->ui->qciComboBox->currentText().toInt();
    streamDl.streamDlSpeed = this->ui->speed->text().toInt();
    streamDl.streamDlDuration = this->ui->duration->text().toInt();
    streamDl.streamDlMinThroughput = this->ui->minThroughtPut->text().toInt();

    emit saveStreamDlData(projectName, trafficName, currentCMindex, streamDl, currentStreamDlIndex, modification);
    this->close();
}

void StreamDlForm::on_cancelButton_clicked()
{
    this->close();
}

void StreamDlForm::on_restoreButton_clicked()
{
    this->refreshUi();
}
