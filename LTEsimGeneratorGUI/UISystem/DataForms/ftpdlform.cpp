#include "ftpdlform.h"
#include "ui_ftpdlform.h"

FtpDlForm::FtpDlForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FtpDlForm), qciUsed(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Ftp Dl");
}

FtpDlForm::~FtpDlForm()
{
    delete ui;
}



void FtpDlForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed, const int &ftpDlIndex, const FtpDl &ftpDl)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->currentFtpDlIndex = ftpDlIndex;
    this->ftpDl = ftpDl;
    this->qciUsed = qciUsed;
    this->refreshUi();
    this->show();
}

void FtpDlForm::on_okButton_clicked()
{
    if(this->ui->qciComboBox->currentText() == "") return;
    ftpDl.ftpDlQci = this->ui->qciComboBox->currentText().toInt();
    ftpDl.ftpDlFilesize = this->ui->fileSize->text().toInt();
    ftpDl.ftpDlMinThroughput = this->ui->minThroughPut->text().toInt();

    emit saveFtpDlData(projectName, trafficName, currentCMindex, ftpDl, currentFtpDlIndex, modification);
    this->close();
}

void FtpDlForm::on_cancelButton_clicked()
{
    this->close();
}

void FtpDlForm::refreshUi()
{
    this->ui->qciComboBox->clear();
    if(ftpDl.ftpDlQci == 0) {
        this->ui->qciComboBox->addItem("");
        for(unsigned i = 0; i < 9; i++) {
            if(!qciUsed[i]) {
                this->ui->qciComboBox->addItem(QString::number(i+1));
            }
        }
        this->ui->fileSize->clear();
        this->ui->minThroughPut->clear();
        this->modification = false;
    } else {
        auto index = 0;
        for(auto i = 1; i < 10; i++) {
            if(!qciUsed[i-1]) {
                this->ui->qciComboBox->addItem(QString::number(i));
            }
            else if(i == ftpDl.ftpDlQci) {
                index = this->ui->qciComboBox->count();
                this->ui->qciComboBox->addItem(QString::number(i));
            }
        }
        this->ui->qciComboBox->setCurrentIndex(index);
        this->ui->minThroughPut->setText(QString::number(ftpDl.ftpDlMinThroughput));
        this->ui->fileSize->setText(QString::number(ftpDl.ftpDlFilesize));
        this->modification = true;
    }
}

void FtpDlForm::on_restoreButton_clicked()
{
    this->refreshUi();
}
