#include "ftpulform.h"
#include "ui_ftpulform.h"

FtpUlForm::FtpUlForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FtpUlForm), qciUsed(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Ftp Ul");
}

FtpUlForm::~FtpUlForm()
{
    delete ui;
}

void FtpUlForm::loadAndOpen(const QString &projectName, const QString &trafficName, const int &CMindex, bool *qciUsed, const int &ftpUlIndex, const FtpUl &ftpUl)
{
    this->projectName = projectName;
    this->trafficName = trafficName;
    this->currentCMindex = CMindex;
    this->currentFtpUlIndex = ftpUlIndex;
    this->ftpUl = ftpUl;
    this->qciUsed = qciUsed;
    this->refreshUi();
    this->show();
}

void FtpUlForm::on_okButton_clicked()
{
    if(this->ui->qciComboBox->currentText() == "") return;
    ftpUl.ftpUlQci = this->ui->qciComboBox->currentText().toInt();
    ftpUl.ftpUlFilesize = this->ui->fileSize->text().toInt();
    ftpUl.ftpUlMinThroughput = this->ui->minThroughPut->text().toInt();

    emit saveFtpUlData(projectName, trafficName, currentCMindex, ftpUl, currentFtpUlIndex, modification);
    this->close();
}

void FtpUlForm::on_cancelButton_clicked()
{
    this->close();
}

void FtpUlForm::refreshUi()
{
    this->ui->qciComboBox->clear();
    if(ftpUl.ftpUlQci == 0) {
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
            else if(i == ftpUl.ftpUlQci) {
                index = this->ui->qciComboBox->count();
                this->ui->qciComboBox->addItem(QString::number(i));
            }
        }
        this->ui->qciComboBox->setCurrentIndex(index);
        this->ui->minThroughPut->setText(QString::number(ftpUl.ftpUlMinThroughput));
        this->ui->fileSize->setText(QString::number(ftpUl.ftpUlFilesize));
        this->modification = true;
    }
}

void FtpUlForm::on_restoreButton_clicked()
{
    this->refreshUi();
}
