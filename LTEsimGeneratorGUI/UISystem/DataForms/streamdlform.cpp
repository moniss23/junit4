#include "streamdlform.h"
#include "ui_streamdlform.h"

StreamDlForm::StreamDlForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StreamDlForm), qciUsed(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Stream Dl");
}

StreamDlForm::~StreamDlForm()
{
    delete ui;
}

void StreamDlForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->qciUsed = qciUsed;
    this->clearUi();
    this->show();
}

void StreamDlForm::clearUi() {
    this->ui->qciComboBox->clear();
    this->ui->qciComboBox->addItem("");
    for(unsigned i = 0; i < 9; i++) {
        if(!qciUsed[i]) {
            this->ui->qciComboBox->addItem(QString::number(i+1));
        }
    }
    this->ui->speed->clear();
    this->ui->duration->clear();
    this->ui->minThroughtPut->clear();
}

void StreamDlForm::on_okButton_clicked()
{
    if(this->ui->qciComboBox->currentText() == "") return;
    this->streamDl.streamDlQci = this->ui->qciComboBox->currentText().toInt();
    this->streamDl.streamDlSpeed = this->ui->speed->text().toInt();
    this->streamDl.streamDlDuration = this->ui->duration->text().toInt();
    this->streamDl.streamDlMinThroughput = this->ui->minThroughtPut->text().toInt();

    emit saveStreamDlData(projectName, trafficName, currentCMindex, streamDl);
    this->close();
}

void StreamDlForm::on_cancelButton_clicked()
{
    this->close();
}
