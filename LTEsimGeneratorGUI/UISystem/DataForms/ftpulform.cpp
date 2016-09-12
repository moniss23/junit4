#include "ftpulform.h"
#include "ui_ftpulform.h"

FtpUlForm::FtpUlForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FtpUlForm), qciUsed(nullptr)
{
    ui->setupUi(this);
}

FtpUlForm::~FtpUlForm()
{
    delete ui;
}

void FtpUlForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->qciUsed = qciUsed;
    this->clearUi();
    this->show();
}

void FtpUlForm::on_okButton_clicked()
{
    if(this->ui->qciComboBox->currentText() == "") return;
    this->ftpUl.ftpUlQci = this->ui->qciComboBox->currentText().toInt();
    this->ftpUl.ftpUlFilesize = this->ui->fileSize->text().toInt();
    this->ftpUl.ftpUlMinThroughput = this->ui->minThroughPut->text().toInt();

    emit saveFtpUlData(projectName, trafficName, currentCMindex, ftpUl);
    this->close();
}

void FtpUlForm::on_cancelButton_clicked()
{
    this->close();
}

void FtpUlForm::clearUi()
{
    this->ui->qciComboBox->clear();
    this->ui->qciComboBox->addItem("");
    for(unsigned i = 0; i < 9; i++) {
        if(!qciUsed[i]) {
            this->ui->qciComboBox->addItem(QString::number(i+1));
        }
    }
    this->ui->fileSize->clear();
    this->ui->minThroughPut->clear();
}
