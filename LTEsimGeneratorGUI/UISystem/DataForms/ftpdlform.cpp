#include "ftpdlform.h"
#include "ui_ftpdlform.h"

FtpDlForm::FtpDlForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FtpDlForm), qciUsed(nullptr)
{
    ui->setupUi(this);
}

FtpDlForm::~FtpDlForm()
{
    delete ui;
}



void FtpDlForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->qciUsed = qciUsed;
    this->clearUi();
    this->show();
}

void FtpDlForm::on_okButton_clicked()
{
    if(this->ui->qciComboBox->currentText() == "") return;
    this->ftpDl.ftpDlQci = this->ui->qciComboBox->currentText().toInt();
    this->ftpDl.ftpDlFilesize = this->ui->fileSize->text().toInt();
    this->ftpDl.ftpDlMinThroughput = this->ui->minThroughPut->text().toInt();

    emit saveFtpDlData(projectName, trafficName, currentCMindex, ftpDl);
    this->close();
}

void FtpDlForm::on_cancelButton_clicked()
{
    this->close();
}

void FtpDlForm::clearUi()
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
